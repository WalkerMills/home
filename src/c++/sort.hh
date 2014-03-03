#ifndef __SORT_HH__
#define __SORT_HH__

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
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
        std::swap(a, b);
        a += b + 1;
        
        return *this;
    }

    // Decrement to the previous Leonardo number
    leonardo &operator--() throw() {
        std::swap(a, b);
        b -= a + 1;

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
        for ( T i = first; i < last; ++i ) {
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
    }

    // Print all the elements in a container
    template<typename T>
    void print(T input) {
        sort::print(input.begin(), input.end());
    }

    template<typename T>
    bool check(T start, T stop) {
        for ( T i = start + 1; i < stop; ++i ) {
            if ( *(i - 1) > *i ) {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool check(T input) {
        return sort::check(input.begin(), input.end());
    }

    template<typename T>
    bool show(T start, T stop) {
        bool sorted = true;
        std::stringstream ss;

        for ( T i = start; i < stop; ++i ) {
            if ( i < stop - 1 && *i > *(i + 1) ) {
                sorted = false;

                ss << "[ " << *i++ << ' ';

                for ( ; i < stop - 1 && *i > *(i + 1); ++i ) {
                    std::cerr << *i << ' ';
                }

                ss << *i << " ] ";
            } else {
                ss << *i << ' ';
            }
        }

        if ( ! sorted ) {
            std::cerr << ss.str() << std::endl;
        }
        return sorted;
    }

    template<typename T>
    void show(T input) {
        sort::show(input.begin(), input.end());
    }

    // In-place insertion sort on the elements in the range [first, last)
    template<typename T>
    void insertion_sort(T start, T stop) {
        T min = start;

        for ( T i = start + 1; i < stop; ++i ) {
            if ( *min > *i ) {
                min = i;
            }
        }

        std::iter_swap(start, min);
        for ( T i = start + 1; i < stop; ++i ) {
            for ( T j = i; j != start && *(j - 1) > *j; --j ) {
                std::iter_swap(j, j - 1);
            }
        }
    }

    // In-place insertion sort on all the elements in a container
    template<typename T>
    void insertion_sort(T &input) {
        sort::insertion_sort(input.begin(), input.end());
    }

    // In-place insertion sort on all the elements in an array
    template<typename T>
    void insertion_sort(T *input, unsigned SIZE) {
        sort::insertion_sort(input, input + SIZE);
    }


    // In-place smoothsort on the elements in the range [start, stop)
    template<typename T>
    void smoothsort(T start, T stop) {

    }

    // In-place smoothsort on all the elements in a container
    template<typename T>
    void smoothsort(T &input) {
        sort::smoothsort(input.begin(), input.end());
    }

    template<typename T>
    static T medianOf3(T a, T b, T c) {
        T maximum = std::max(std::max(a, b), c);
        T minimum = std::min(std::min(a, b), c);

        return a ^ b ^ c ^ minimum ^ maximum;
    }

    template<typename T>
    std::pair<T, T> partition(T start, T stop, unsigned chunk) {
        int n = stop - start;

        if ( n <= chunk ) {
            insertion_sort(start, stop);
            return std::make_pair(start, stop);
        } else if ( stop - start <= 40 ) {
            auto median = medianOf3(*start, *(start + n / 2), *(stop - 1));
            std::swap(*start, median);
        } else {
            int part = n / 8;
            T mid = start + n / 2;
            auto median0 = medianOf3(*start, *(start + part), 
                                     *(start + part + part));
            auto median1 = medianOf3(*(mid - part), *mid, *(mid + part));
            auto median2 = medianOf3(*(stop - 1 - part - part), 
                                     *(stop - 1 - part), *(stop - 1));
            auto ninther = medianOf3(median0, median1, median2);
            std::swap(*start, ninther);
        }

        T i = start, p = start;
        T j = stop, q = stop;
        auto pivot = *start;

        while ( true ) {
            while ( *++i < pivot ) {
                if ( i == stop - 1 ) break;
            }

            while ( pivot < *--j ) {
                if ( j == start ) break;
            }

            if ( i == j && *i == pivot ) std::iter_swap(i, ++p);
            if ( i >= j ) break;

            std::iter_swap(i, j);

            if ( *i == pivot ) std::iter_swap(i, ++p);
            if ( *j == pivot ) std::iter_swap(j, --q);
        }

        i = j + 1;
        for ( T k = start; k <= p; ++k ) std::iter_swap(k, j--);
        for ( T k = stop - 1; k >= q; --k ) std::iter_swap(k, i++);

        return std::make_pair(j + 1, i);
    }

    template<typename T>
    void quicksort(T start, T stop) {
        if (start < stop) {
            std::pair<T, T> indices = sort::partition(start, stop, CHUNK);
            sort::quicksort(start, indices.first);
            sort::quicksort(indices.second, stop);
        }
    }

    // In-place quicksort on the input container
    template<typename T>
    void quicksort(T &input) {
        sort::quicksort(input.begin(), input.end());
    }

    // In-place quicksort on the input array
    template<typename T>
    void quicksort(T *input, unsigned size) {
        sort::quicksort(input, input + size);
    }

    // In-place introsort on the elements in the range [start, stop)
    template<typename T>
    void introsort(T start, T stop, unsigned depth) {
        if ( start < stop ) {
            if ( depth > 0 ) {
                std::pair<T, T> indices = sort::partition(start, stop, CHUNK);
                sort::introsort(start, indices.first, depth - 2);
                sort::introsort(indices.second, stop, depth - 2);
            } else {
                sort::smoothsort(start, stop);
                return;
            }
        }
    }

    // In-place introsort on the input container
    template<typename T>
    void introsort(T &input) {
        unsigned max = 2 * log2(input.size()) + 1;

        sort::introsort(input.begin(), input.end(), max);
        sort::insertion_sort(input);
    }

    // In-place introsort on the input array
    template<typename T>
    void introsort(T *input, unsigned size) {
        unsigned max = 2 * log2(size) + 1;

        sort::introsort(input, input + size, max);
        sort::insertion_sort(input, input + size);
    }

}

#endif // __SORT_HH__
