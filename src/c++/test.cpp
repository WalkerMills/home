#include <chrono>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "sort.hh"
#include "test.hh"


unsigned **gen_arrays(unsigned samples, unsigned size) {
    unsigned **arrays = new unsigned*[samples];

    srand(time(NULL));
    for ( unsigned i = 0; i < samples; ++i ) {
        unsigned *arr = new unsigned[size];

        for ( unsigned j = 0; j < size; ++j ) {
            arr[j] = rand() % (size * 10);
        }

        arrays[i] = arr;
    }

    return arrays;
}

std::vector<unsigned> *gen_vectors(unsigned samples, unsigned size) {
    std::vector<unsigned> *vectors = new std::vector<unsigned>[samples];

    srand(time(NULL));
    for ( unsigned i = 0; i < samples; ++i ) {
        std::vector<unsigned> vec(size);

        for ( unsigned j = 0; j < size; ++j ) {
            vec[j] = rand() % (size * 10);
        }

        vectors[i] = vec;
    }

    return vectors;
}

int main(int argc, char **argv) {
    std::vector<array_fp> const array_sorts = {
        &std::sort<unsigned *>,
        &std::stable_sort<unsigned *>,
        // &sort::insertion_sort<unsigned *>,
        &sort::quicksort<unsigned *>,
        // &sort::smoothsort<unsigned *>,
        &sort::introsort<unsigned *>,
        &sort::parallel_introsort<unsigned *>
    };

    unsigned i = 0;

    for ( auto &fp : array_sorts ) {
        switch ( i ) {
            case 0:
                std::cout << "STL sort:" << std::endl;
                break;

            case 1:
                std::cout << "STL stable sort:" << std::endl;
                break;

            case 2:
                // std::cout << "Insertion sort:" << std::endl;
                // break;
                ++i;

            case 3:
                std::cout << "Quicksort:" << std::endl;
                break;
                // ++i;

            case 4:
                // std::cout << "Smoothsort:" << std::endl;
                // break;
                ++i;

            case 5:
                std::cout << "Introsort:" << std::endl;
                break;

            case 6:
                std::cout << "Parallelized introsort:" << std::endl;
                break;

            default:
                break;
        }
        ++i;

        std::pair<double, double> res = benchmark<unsigned>(SAMPLES, SIZE, fp);
        std::cout << res.first << " elements per microsecond, standard "
                     "deviation of " << res.second 
                  << " (" << res.second / res.first * 100 << "%) for "
                  << SAMPLES << " samples of " << SIZE << " elements"
                  << std::endl << std::endl;
    }

    std::ofstream ofs ("data.txt");
    pid_t cpid, wpid;
    int status;

    for ( unsigned i = 0; i <= SIZE; i += 10 ) {
        for ( unsigned j = 1; j <= THREADS; ++j ) {
            double *times = new double[THREADS];
            double *deviations = new double[THREADS];

            if ( (cpid = fork()) < 0 ) {
                perror("fork error");
                exit(EXIT_FAILURE);
            } else if ( cpid == 0 ) {
                std::pair<double, double> res = benchmark<unsigned>(SAMPLES, i,
                    [j] (unsigned *start, unsigned *stop) {
                        sort::parallel_introsort(start, stop, j);
                });

                times[j - 1] = res.first;
                deviations[j - 1] = res.second;

                exit(EXIT_SUCCESS);
            } else {
                if ( (wpid = wait(&status)) < 0 ) {
                    perror("wait error");
                } else {
                    if ( WIFSIGNALED(status) != 0 ) {
                        printf("Child process ended by signal %d\n",
                               WTERMSIG(status));
                    } else if ( WIFEXITED(status) != 0 && 
                                WEXITSTATUS(status) != 0 ) {
                        printf("Child process ended with status %d\n",
                               WEXITSTATUS(status));
                    } else {
                        printf("Child process did not end normally\n");
                    }
                }
            }

            double mu = mean(times, times + SAMPLES);
            double sigma = mean(deviations, deviations + SAMPLES);

            std::cout << i << " elements, " << j << " threads, "
                      << mu << " microseconds, standard deviation of "
                      << sigma << std::endl;
            ofs << i << ' ' << j << ' ' << mu << ' ' << sigma << std::endl;

            delete [] times;
            delete [] deviations;            
        }
    }

    ofs.close();

    return 0;
}