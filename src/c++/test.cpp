#include <iostream>
#include <cstdlib>
#include <ctime>

#include "sort.hh"

#define SIZE 100


static unsigned *gen_array(unsigned size) {
    unsigned *arr = new unsigned[size];
    srand(time(NULL));

    for ( unsigned i = 0; i < size; i++ ) {
        arr[i] = rand() % (size * 10);
    }

    return arr;
}

int main(int argc, char **argv) {
    unsigned *arr = gen_array(SIZE);
    std::vector<unsigned> vec(arr, arr + SIZE);

    sort::print(arr, arr + SIZE);
    std::cout << std::endl;

    sort::introsort(arr, SIZE);
    sort::print(arr, arr + SIZE);
    std::cout << std::endl << std::endl;

    sort::print(vec);
    std::cout << std::endl;

    sort::introsort(vec);
    sort::print(vec);
    std::cout << std::endl << std::endl;

    return 0;
}