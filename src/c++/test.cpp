#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "sort.hh"
#include "test.hh"


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

    return 0;
}