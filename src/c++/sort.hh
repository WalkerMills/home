#ifndef __SORT_HH__
#define __SORT_HH__

#include <vector>

namespace sort {
    template<typename T>
    void sort::insertion_sort(T *input, unsigned start, unsigned stop);
    template<typename T, typename C=std::vector>
    void sort::insertion_sort(C<T> input, unsigned start, unsigned stop);
    template<typename T>
    void sort::insertion_sort(T *input, unsigned size);
    template<typename T, typename C=std::vector>
    void sort::insertion_sort(C<T> input);

    template<typename T>
    void sort::smoothsort(T *input, unsigned start, unsigned stop);
    template<typename T, typename C=std::vector>
    void sort::smoothsort(C<T> input, unsigned start, unsigned stop);
    template<typename T>
    void sort::smoothsort(T *input, unsigned size);
    template<typename T, typename C=std::vector>
    void sort::smoothsort(C<T> input);

    template<typename T>
    void sort::quicksort(T *input, unsigned start, unsigned stop);
    template<typename T, typename C=std::vector>
    void sort::quicksort(C<T> input, unsigned start, unsigned stop);
    template<typename T>
    void sort::quicksort(T *input, unsigned size);
    template<typename T, typename C=std::vector>
    void sort::quicksort(C<T> input);

    template<typename T>
    void sort::introsort(T *input, unsigned start, unsigned stop, 
                         unsigned depth);
    template<typename T, typename C=std::vector>
    void sort::introsort(C<T> input, unsigned start, unsigned stop, 
                         unsigned depth);
    template<typename T>
    void sort::introsort(T *input, unsigned size);
    template<typename T, typename C=std::vector>
    void sort::introsort(C<T> input);
}

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

#endif // __SORT_HH__
