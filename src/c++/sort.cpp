#include <iterator>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "sort.hh"


// Print an input array
template<typename T>
static void print(T *input, unsigned size) const {
    for ( unsigned i = 0; i < size; i++ ) {
          std::cout << input[i] << " ";
    }
    std::cout << std::endl;
}

// Print an input container
template<typename T, typename C=std::vector>
static void print(C<T> input) const {
    print<T, C>(input, input.size());
}


// In-place insertion sort on the specified range in the input array
template<typename T>
void sort::insertion_sort(T *input, unsigned start, unsigned stop) {
    for ( unsigned i = start + 1; i <= stop; i++ ) {
        for (unsigned j = i; j > start && input[j - 1] > input[j]; j-- ) {
            std::swap(input[j], input[j - 1]);
        }
    }
}

// In-place insertion sort on the specified range in the input container
template<typename T, typename C=std::vector>
void sort::insertion_sort(C<T> input, unsigned start, unsigned stop) {
    for ( unsigned i = start + 1; i <= stop; i++ ) {
        for ( std::reverse_iterator<C<T>::iterator> j = input.rbegin() + i; 
              j > input.rbegin() + start && *(j - 1) > *j; j++) {
            std::swap(*j, *(j - 1));
        }
    }
}

// In-place insertion sort on the input array
template<typename T>
void sort::insertion_sort(T *input, unsigned size) {
    sort::insertion_sort<T>(input, 0, size - 1);
}

// In-place insertion sort on the input container
template<typename T, typename C=std::vector>
void sort::insertion_sort(C<T> input) {
    sort::insertion_sort<T, C>(input, 0, input.size() - 1);
}


// In-place smoothsort on the specified range in the input array
template<typename T>
void sort::smoothsort(T *input, unsigned start, unsigned stop) {

}

// In-place smoothsort on the specified range in the input container
template<typename T, typename C=std::vector>
void sort::smoothsort(C<T> input, unsigned start, unsigned stop) {

}

// In-place smoothsort on the input array
template<typename T>
void sort::smoothsort(T *input, unsigned size) {
    sort::smoothsort<T>(input, 0, size - 1);
}

// In-place smoothsort on the input container
template<typename T, typename C=std::vector>
void sort::smoothsort(C<T> input) {
    sort::smoothsort<T, C>(input, 0, input.size() - 1);
}


// Partitioning helper function for quicksort on an array
template<typename T>
static unsigned partition(T *input, unsigned start, unsigned stop) {
    unsigned r;
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

    return stop;
}

// Partitioning helper function for quicksort on a container
template<typename T, typename C=std::vector>
static unsigned partition(C<T> input, unsigned start, unsigned stop) {
    unsigned r;
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

    return stop;
}


// In-place quicksort on the specified range in the input array
template<typename T>
void sort::quicksort(T *input, unsigned start, unsigned stop) {
    if ( start < stop ) {
        unsigned pivot = partition<T>(input, start, stop);
        sort::quicksort<T>(input, start, pivot - 1);
        sort::quicksort<T>(input, pivot + 1, stop);
    }
}

// In-place quicksort on the specified range in the input container
template<typename T, typename C=std::vector>
void sort::quicksort(C<T> input, unsigned start, unsigned stop) {
    if ( start < stop ) {
        unsigned pivot = partition<T, C>(input, start, stop);
        sort::quicksort<T, C>(input, start, pivot - 1);
        sort::quicksort<T, C>(input, pivot + 1, stop);
    }
}

// In-place quicksort on the input array
template<typename T>
void sort::quicksort(T *input, unsigned size) {
    sort::quicksort<T>(input, 0, size - 1);
}

// In-place quicksort on the input container
template<typename T, typename C=std::vector>
void sort::quicksort(C<T> input) {
    sort::quicksort<T, C>(input, 0, input.size() - 1);
}


// In-place introsort on the specified range in the input array
template<typename T>
void sort::introsort(T *input, unsigned start, unsigned stop, unsigned depth) {
    while ( stop - start >= 16 ) {
        if ( depth > 0 ) {
            unsigned pivot = partition<T>(input, start, stop);
            sort::introsort<T>(input, pivot + 1, stop, depth - 1);
            stop = pivot + 1;
        } else {
            sort::smoothsort<T>(input, start, stop);
            return;
        }
    }
}

// In-place introsort on the specified range in the input container
template<typename T, typename C=std::vector>
void sort::introsort(C<T> input, unsigned start, unsigned stop, 
                     unsigned depth) {
    while ( stop - start >= 16 ) {
        if ( depth > 0 ) {
            unsigned pivot = partition<T, C>(input, start, stop);
            sort::introsort<T, C>(input, pivot + 1, stop, depth - 1);
            stop = pivot + 1;
        } else {
            sort::smoothsort<T, C>(input, start, stop);
            return;
        }
    }
}

// In-place introsort on the input array
template<typename T>
void sort::introsort(T *input, unsigned size) {
    unsigned max = 2 * log2(size) + 1;

    sort::introsort<T>(input, 0, size - 1, max);
    sort::insertion_sort<T>(input, 0, size - 1);
}

// In-place introsort on the input container
template<typename T, typename C=std::vector>
void sort::introsort(C<T> input) {
    sort::introsort<T, C>(input, input.size() - 1);
}

}
