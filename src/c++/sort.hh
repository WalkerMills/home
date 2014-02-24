#ifndef __SORT_HH__
#define __SORT_HH__

#include <iterator>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>


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
    }

    // Decrement to the previous Leonardo number
    leonardo &operator--() throw() {
        unsigned tmp = b;
        
        b = a - b - 1;
        a = tmp;
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
    // Print an input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void print(C<T> input) {
    // template<typename T, template <typename T> class C>
    // void print(C<T> input) {
        for ( typename C<T>::const_iterator i = input.begin(); 
              i != input.end(); i++ ) {
            std::cout << *i;
        }
        std::cout << std::endl;
    }

    // Print an input array
    template<typename T>
    void print(T *input, unsigned size) {
        for ( unsigned i = 0; i < size; i++ ) {
              std::cout << input[i] << " ";
        }
        std::cout << std::endl;
    }


    // In-place insertion sort on the specified range in the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void insertion_sort(C<T> input, unsigned start, unsigned stop) {
        for ( unsigned i = start + 1; i <= stop; i++ ) {
            for ( std::reverse_iterator<typename C<T>::iterator> 
                  j = input.rend() - i; j != input.rend() - start; j++ ) {
                std::swap(*j, *(j + 1));
            }
        }
    }

    // In-place insertion sort on the specified range in the input array
    template<typename T>
    void insertion_sort(T *input, unsigned start, unsigned stop) {
        for ( unsigned i = start + 1; i <= stop; i++ ) {
            for (unsigned j = i; j > start && input[j - 1] > input[j]; j-- ) {
                std::swap(input[j], input[j - 1]);
            }
        }
    }

    // In-place insertion sort on the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void insertion_sort(C<T> input) {
        insertion_sort<C, T>(input, 0, input.size() - 1);
    }

    // In-place insertion sort on the input array
    template<typename T>
    void insertion_sort(T *input, unsigned size) {
        insertion_sort<T>(input, 0, size - 1);
    }


    // In-place smoothsort on the specified range in the input array
    template<typename T>
    void smoothsort(T *input, unsigned start, unsigned stop) {

    }

    // In-place smoothsort on the specified range in the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void smoothsort(C<T> input, unsigned start, unsigned stop) {

    }

    // In-place smoothsort on the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void smoothsort(C<T> input) {
        smoothsort<C<T>>(input, 0, input.size() - 1);
    }

    // In-place smoothsort on the input array
    template<typename T>
    void smoothsort(T *input, unsigned size) {
        smoothsort<T>(input, 0, size - 1);
    }


    // Partitioning helper function for quicksort on a container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    static unsigned partition(C<T> input, unsigned start, unsigned stop,
                              unsigned chunk) {
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

        while ( stop - start > chunk ) {
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

    // Partitioning helper function for quicksort on an array
    template<typename T>
    static unsigned partition(T *input, unsigned start, unsigned stop,
                              unsigned chunk) {
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

        while ( stop - start > chunk ) {
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


    // In-place quicksort on the specified range in the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void quicksort(C<T> input, unsigned start, unsigned stop) {
        if (start < stop) {
            unsigned pivot = partition<C, T>(input, start, stop, 0);
            quicksort<C, T>(input, start, pivot - 1);
            quicksort<C, T>(input, pivot + 1, stop);
        }
    }

    // In-place quicksort on the specified range in the input array
    template<typename T>
    void quicksort(T *input, unsigned start, unsigned stop) {
        if ( start < stop ) {
            unsigned pivot = partition<T>(input, start, stop, 0);
            quicksort<T>(input, start, pivot - 1);
            quicksort<T>(input, pivot + 1, stop);
        }
    }

    // In-place quicksort on the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void quicksort(C<T> input) {
        quicksort<C, T>(input, 0, input.size() - 1);
    }

    // In-place quicksort on the input array
    template<typename T>
    void quicksort(T *input, unsigned size) {
        quicksort<T>(input, 0, size - 1);
    }


    // In-place introsort on the specified range in the input array
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void introsort(C<T> input, unsigned start, unsigned stop, 
                   unsigned depth) {
        while ( stop - start >= 16 ) {
            if ( depth > 0 ) {
                unsigned pivot = partition<C, T>(input, start, stop, 15);
                introsort<C, T>(input, pivot + 1, stop, depth - 1);
                stop = pivot + 1;
            } else {
                smoothsort<C, T>(input, start, stop);
                return;
            }
        }
    }

    // In-place introsort on the specified range in the input array
    template<typename T>
    void introsort(T *input, unsigned start, unsigned stop, 
                   unsigned depth) {
        while ( stop - start >= 16 ) {
            if ( depth > 0 ) {
                unsigned pivot = partition<T>(input, start, stop, 15);
                introsort<T>(input, pivot + 1, stop, depth - 1);
                stop = pivot + 1;
            } else {
                smoothsort<T>(input, start, stop);
                return;
            }
        }
    }

    // In-place introsort on the input container
    template<
        template<typename TT, class A=std::allocator<TT>> class C,
        typename T>
    void introsort(C<T> input) {
        unsigned size = input.size();
        unsigned max = 2 * log2(size) + 1;

        introsort<C, T>(input, 0, size - 1, max);
        insertion_sort<C, T>(input, 0, size - 1);
    }

    // In-place introsort on the input array
    template<typename T>
    void introsort(T *input, unsigned size) {
        unsigned max = 2 * log2(size) + 1;

        introsort<T>(input, 0, size - 1, max);
        insertion_sort<T>(input, 0, size - 1);
    }

}

#endif // __SORT_HH__
