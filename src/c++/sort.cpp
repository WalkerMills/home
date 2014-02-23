#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "sort.hh"

template<typename T>
static void print(std::vector<T> input) {
    for ( std::vector<T>::const_iterator i = input.begin();
          i != input.end(); i++ ) {
          std::cout << *i << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void sort::insertion_sort(std::vector<T> input, int start, int stop) {
    for ( int i = start + 1; i <= stop; i++ ) {
        for (int j = i; j > start && input[j - 1] > input[j]; j-- ) {
            std::swap(input[j], input[j - 1]);
        }
    }
}

template<typename T>
void sort::insertion_sort(std::vector<T> input) {
    insertion_sort(input, 0, input.size() - 1);
}

template<typename T>
void sort::heapsort(std::vector<T> input, int start, int stop) {

}

template<typename T>
void sort::heapsort(std::vector<T> input) {
    heapsort(input, 0, input.size() - 1);
}

template<typename T>
int sort::partition(std::vector<T> input, int start, int stop) {
    int r;
    T a, b, c, pivot;

    // pivot is chosen to be the median of three elements around a
    // random index inside the partition
    srand(time(NULL));
    r = (rand() % (stop - start)) / 2 + start + (stop - start) / 4;
    a = input[r - 1];
    b = input[r];
    c = input[r + 1];

    if (( b >= a && b <= c ) || 
        ( b <= a && b >= c )) {
        pivot = b;
    } else if (( a >= b && a <= c ) || 
               ( a <= b && a >= c )) {
        pivot = a;
    } else {
        pivot = c;
    }

    while ( stop - start >= 16 ) {
        while ( input[start] < pivot ) {
            start++;
        }

        while ( input[stop] > pivot ) {
            stop--;
        }

        if ( input[start] == input[stop] ) {
            start++;
        } else if ( stop > start ) {
            std::swap(input[start], input[stop]);
        }
    }

    print(input);
    return stop;
}


template<typename T>
void sort::quicksort(std::vector<T> input, int start, int stop) {
    if ( start < stop ) {
        int pivot = partition(input, start, stop);
        quicksort(input, start, pivot - 1);
        quicksort(input, pivot + 1, stop);
    }
}


template<typename T>
void sort::introsort(std::vector<T> input, int start, int stop, int depth) {
    while ( stop - start > 0 ) {
        if ( depth > 0 ) {
            int pivot = partition(input, start, stop);
            introsort(input, pivot + 1, stop, depth - 1);
            stop = pivot + 1;
        } else {
            heapsort(input, start, stop);
            return;
        }
    }
}

template<typename T>
void sort::introsort(std::vector<T> input) {
    int size = input.size();
    int max = 2 * log2(size) + 1;

    introsort(input, 0, size - 1, max);
    insertion_sort(input, 0, size - 1);
}

}
