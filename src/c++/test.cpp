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

void benchmark_array(unsigned samples, unsigned size, array_fp f) {
    unsigned **arrays = gen_arrays(samples, size);
    std::chrono::microseconds elapsed = std::chrono::microseconds::zero();
    std::chrono::high_resolution_clock::time_point start, end;

    for ( unsigned i = 0; i < samples; ++i ) {
        start = std::chrono::high_resolution_clock::now();
        f(arrays[i], size);
        end = std::chrono::high_resolution_clock::now();
        elapsed += 
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    }

    std::cout << elapsed.count() << " microseconds to sort " << samples 
              << " arrays of " << size << " elements; " 
              << ((float)(samples * size)) / elapsed.count()
              << " elements per microsecond" << std::endl;

    for ( unsigned i = 0; i < samples; ++i ) {
        if ( ! sort::check(arrays[i], arrays[i] + size) ) {
            std::cerr << "Warning: sample " << i + 1 << " is not sorted"
                      << std::endl;
        }
    }

    delete [] arrays;
}

void benchmark_vector(unsigned samples, unsigned size, vector_fp f) {
    std::vector<unsigned> *vectors = gen_vectors(samples, size);
    std::chrono::microseconds elapsed = std::chrono::microseconds::zero();
    std::chrono::high_resolution_clock::time_point start, end;

    for ( unsigned i = 0; i < samples; ++i ) {
        start = std::chrono::high_resolution_clock::now();
        f(vectors[i]);
        end = std::chrono::high_resolution_clock::now();
        elapsed += 
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    }

    std::cout << elapsed.count() << " microseconds to sort " << samples 
              << " vectors of " << size << " elements; " 
              << ((float)(samples * size)) / elapsed.count()
              << " elements per microsecond" << std::endl;

    for ( unsigned i = 0; i < samples; ++i ) {
        if ( ! sort::check(vectors[i]) ) {
            std::cerr << "Warning: sample " << i + 1 << " is not sorted"
                      << std::endl;
        }
    }

    delete [] vectors;
}

int main(int argc, char **argv) {
    array_fp const array_sorts[] = {
        &sort::insertion_sort<unsigned>,
        &sort::quicksort<unsigned>,
        &sort::smoothsort<unsigned>,
        &sort::introsort<unsigned>
    };
    vector_fp const vector_sorts[] = {
        &sort::insertion_sort<std::vector<unsigned>>,
        &sort::quicksort<std::vector<unsigned>>,
        &sort::smoothsort<std::vector<unsigned>>,
        &sort::introsort<std::vector<unsigned>>
    };

    for ( unsigned i = 1; i < 4; ++i ) {
        switch ( i ) {
            case 0:
                std::cout << "Insertion sort:" << std::endl;
                break;

            case 1:
                std::cout << "Quicksort:" << std::endl;
                break;

            case 2:
                std::cout << "Smoothsort:" << std::endl;
                break;

            case 3:
                std::cout << "Introsort:" << std::endl;
                break;

            default:
                break;
        }
        std::cout << "Arrays: ";
        benchmark_array(SAMPLES, SIZE, array_sorts[i]);
        std::cout << "Vectors: ";
        benchmark_vector(SAMPLES, SIZE, vector_sorts[i]);
        std::cout << std::endl;
    }

    return 0;
}