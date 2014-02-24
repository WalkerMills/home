#ifndef __SORT_HH__
#define __SORT_HH__

#include <iterator>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define CHUNK 16


class leonardo {
private:
    // Current Leonardo number
    unsigned a;
    // Previous Leonardo number
    unsigned b;

public:
    // Default constructor
    leonardo() throw() : a(1), b(1) { 
        return; 
    }
    // Copy constructor
    leonardo(const leonardo &l) throw() : a(l.a), b(l.b) { 
        return; 
    }

    // Calculate the gap between the current and previous Leonardo numbers
    unsigned gap() const throw() {
        return a - b;
    }

    // Increment to the next Leonardo number
    leonardo &operator++() throw() {
        unsigned tmp = a;
        
        a = a + b + 1;
        b = tmp;

        return *this;
    }

    // Decrement to the previous Leonardo number
    leonardo &operator--() throw() {
        unsigned tmp = b;
        
        b = a - b - 1;
        a = tmp;

        return *this;
    }

    // Return current value
    operator unsigned() const throw() {
        return a;
    }

    // Return previous value
    unsigned operator~() const throw() {
        return b;
    }
};


namespace sort {
    // Print the elements in the range [first, last) 
    template<typename T>
    void print(T first, T last) {
        for ( T i = first; i != last; i++ ) {
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
    }

    // Print all the elements in a container
    template<typename T>
    void print(T input) {
        print(input.begin(), input.end());
    }


    // In-place insertion sort on the elements in the range [first, last)
    template<typename T>
    void insertion_sort(T start, T stop) {
        T min = start;

        for ( T i = start + 1; i < stop; i++ ) {
            if ( *min > *i ) {
                min = i;
            }
        }

        std::iter_swap(start, min);
        for ( T i = start + 1; i < stop; i++ ) {
            for ( T j = i; j != start && *(j - 1) > *j; j-- ) {
                std::iter_swap(j, j - 1);
            }
        }
    }

    // In-place insertion sort on all the elements in a container
    template<typename T>
    void insertion_sort(T &input) {
        insertion_sort(input.begin(), input.end());
    }


    // In-place smoothsort on the elements in the range [start, stop)
    template<typename T>
    void smoothsort(T start, T stop) {

    }

    // In-place smoothsort on all the elements in a container
    template<typename T>
    void smoothsort(T &input) {
        smoothsort(input.begin(), input.end());
    }


    // Partitioning helper function for quicksort on an array
    template<typename T>
    static T partition(T start, T stop, unsigned chunk) {
        if ( stop > start ) {
            T pivot;

            // Minimum chunk size is 1
            if ( chunk == 0 ) {
                chunk = 1;
            }


            if ( stop > start + 1 ) {
                // pivot is chosen to be the median of three elements around a
                // random index inside the partition
                srand(time(NULL));
                pivot = start + (rand() % (stop - start - 1)) + 1;
                insertion_sort(pivot - 1, pivot + 2);

                while ( stop > start + chunk ) {
                    while ( *start < *pivot ) {
                        start++;
                    }

                    while ( *stop > *pivot ) {
                        stop--;
                    }

                    if ( *start == *stop ) {
                        start++;
                    } else if ( *stop > *start ) {
                        std::iter_swap(start, stop);
                    }
                }
            } else if ( *start > *stop ) {
                std::iter_swap(start, stop);
            }
        }

        return stop;
    }


    // In-place quicksort on the elements in the range [start, stop)
    template<typename T>
    void quicksort(T start, T stop) {
        if (start < stop) {
            T pivot = partition(start, stop, 0);
            quicksort(start, pivot);
            quicksort(pivot + 1, stop);
        }
    }

    // In-place quicksort on the input container
    template<typename T>
    void quicksort(T &input) {
        quicksort(input.begin(), input.end());
    }

    // In-place introsort on the elements in the range [start, stop)
    template<typename T>
    void introsort(T start, T stop, unsigned depth) {
        while ( stop > start + CHUNK ) {
            if ( depth > 0 ) {
                T pivot = partition(start, stop, CHUNK);
                introsort(pivot + 1, stop, depth - 1);
                stop = pivot + 1;
            } else {
                smoothsort(start, stop);
                return;
            }
        }
    }

    // In-place introsort on the input container
    template<typename T>
    void introsort(T &input) {
        unsigned max = 2 * log2(input.size()) + 1;

        introsort(input.begin(), input.end(), max);
        insertion_sort(input);
    }

    // In-place introsort on the input array
    template<typename T>
    void introsort(T *input, unsigned size) {
        unsigned max = 2 * log2(size) + 1;

        introsort(input, input + size, max);
        insertion_sort(input, input + size);
    }

}

#endif // __SORT_HH__
