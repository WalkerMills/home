#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

#include "sort.hh"
#include "test.hh"
#include "timsort.hpp"


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
    std::map<char *, array_fp> const sorts = {
        {"stl sort", &std::sort<unsigned *>},
        {"stl stable sort", &std::stable_sort<unsigned *>},
        // {"insertion sort", &sort::insertion_sort<unsigned *>},
        // {"shellsort", &sort::shellsort<unsigned *>},
        {"smoothsort", &sort::smoothsort<unsigned *>},
        {"quicksort", &sort::quicksort<unsigned *>},
        {"introsort", &sort::introsort<unsigned *>},
        {"parallel quicksort", &sort::parallel_quicksort<unsigned *>},
        {"parallel introsort", &sort::parallel_introsort<unsigned *>},
        // {"timsort", &gfx::timsort}
    };

    for ( std::map<char *, array_fp>::const_iterator it = sorts.begin();
          it != sorts.end(); ++it ) {
        std::cout << it->first << ':' << std::endl;
        std::pair<double, double> res = 
            benchmark<unsigned>(SAMPLES, SIZE, it->second);
        std::cout << res.first << " elements per microsecond, standard "
                     "deviation of " << res.second 
                  << " (" << 100 * res.second / res.first << "%) for "
                  << SAMPLES << " samples of " << SIZE << " elements"
                  << std::endl << std::endl;
    }

    return 0;
}