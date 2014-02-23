#include <iostream>

#include "sort.hh"


int main(int argc, char const *argv[]) {
    int input[10] = {1, 3, 4, 2, 5, 8, 9, 6, 0, 7};
    quicksort(input, 0, 9);

    for (int i = 0; i < 10; i++) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}