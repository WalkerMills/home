#include <iostream>
#include <new>
#include <cstdlib>
#include <ctime>

#include "sort.hh"

#define SIZE 1024


static unsigned *gen_array(unsigned size) {
    unsigned *arr = new unsigned[size];
    srand(time(NULL));

    for ( unsigned i = 0; i < size; i++ ) {
        arr[i] = rand() % (size * 10);
    }

    return arr;
}

int main(int argc, char const *argv[]) {
    unsigned *arr = gen_array(SIZE);
    std::vector<unsigned> vec(arr, arr + SIZE);

    sort::print<unsigned>(arr, SIZE);
    sort::introsort<unsigned>(arr, SIZE);
    sort::print<unsigned>(arr, SIZE);
    std::cout << std::endl;

    sort::print<std::vector, unsigned>(vec);
    sort::introsort<std::vector, unsigned>(vec);
    sort::print<std::vector, unsigned>(vec);
    std::cout << std::endl;

    return 0;
}