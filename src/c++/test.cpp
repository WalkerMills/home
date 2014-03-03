#include <chrono>
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
    // std::vector<unsigned> *vectors = gen_vectors(SAMPLES, SIZE);
    unsigned **arrays = gen_arrays(SAMPLES, SIZE);

    for ( int i = 0; i < 3; ++i ) {
        std::chrono::high_resolution_clock::time_point start, end;

        switch ( i ) {
            case 0:
                std::cout << "Insertion sort:" << std::endl;
                start = std::chrono::high_resolution_clock::now();
                // sort::insertion_sort(vectors[i]);
                sort::insertion_sort(arrays[i], SIZE);
                end = std::chrono::high_resolution_clock::now();
                break;

            case 1:
                std::cout << "Quicksort:" << std::endl;
                start = std::chrono::high_resolution_clock::now();
                sort::quicksort(arrays[i], SIZE);
                end = std::chrono::high_resolution_clock::now();
                break;

            case 2:
                std::cout << "Introsort:" << std::endl;
                start = std::chrono::high_resolution_clock::now();
                sort::introsort(arrays[i], SIZE);
                end = std::chrono::high_resolution_clock::now();
                break;

            default:
                break;
        }
        std::chrono::microseconds elapsed = 
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << elapsed.count() << " ms to sort " << SIZE << " elements; "
                  << ((float) SIZE) / elapsed.count() 
                  << " elements per microsecond" << std::endl;

        sort::show(arrays[i], arrays[i] + SIZE);
   
        std::cout << std::endl;
    }

    delete [] arrays;

    return 0;
}