#ifndef __SORT_HH__
#define __SORT_HH__

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <stack>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Number of elements that trigger insertion sort from quicksort by default
#define CHUNK 16

// Type large enough to contain any Leonardo number
typedef unsigned long leonardo_t;

// Struct for holding the sizes of existing heaps
typedef struct {
    // Sizes of existing heaps (right shifted so that the last bit is a 1)
    unsigned long long mask;
    // Size of the smallest heap (mask << offset == unshifted mask)
    unsigned offset;
} heapsize_t;


namespace sort {
    // Number of Leonardo numbers smaller than 2^32
    const unsigned num_leonardo = 46;

    // Precomputed array of Leonardo numbers smaller than 2^32
    const leonardo_t leonardo_numbers[num_leonardo] = {
        1UL, 1UL, 3UL, 5UL, 9UL, 15UL, 25UL, 41UL, 67UL, 109UL, 177UL, 287UL, 
        465UL, 753UL, 1219UL, 1973UL, 3193UL, 5167UL, 8361UL, 13529UL, 
        21891UL, 35421UL, 57313UL, 92735UL, 150049UL, 242785UL, 392835UL, 
        635621UL, 1028457UL, 1664079UL, 2692537UL, 4356617UL, 7049155UL, 
        11405773UL, 18454929UL, 29860703UL, 48315633UL, 78176337UL, 
        126491971UL, 204668309UL, 331160281UL, 535828591UL, 866988873UL, 
        1402817465UL, 2269806339UL, 3672623805UL
    };

    // Numeric type (with ++ and -- overloads) for keeping track of
    // Djikstra's b and c for smoothsort (produces precomputed values
    // above)
    class leonardo {
    private:
        // Current Leonardo number
        leonardo_t b;
        // Previous Leonardo number
        leonardo_t c;

    public:
        // Default constructor
        leonardo() throw() : b(1), c(1) { 
            return; 
        }
        // Copy constructor
        leonardo(const leonardo &l) throw() : b(l.b), c(l.c) { 
            return; 
        }

        // Calculate the gap between the current and previous Leonardo numbers
        unsigned gap() const throw() {
            return b - c;
        }

        // Increment to the next Leonardo number
        leonardo &operator++() throw() {
            std::swap(b, c);
            b += c + 1;
            
            return *this;
        }

        // Decrement to the previous Leonardo number
        leonardo &operator--() throw() {
            std::swap(b, c);
            c -= b + 1;

            return *this;
        }

        // Return current value
        operator leonardo_t() const throw() {
            return b;
        }

        // Return previous value
        leonardo_t operator~() const throw() {
            return c;
        }
    };


    // Print the elements in the range [first, last) 
    template<typename T>
    void print(T first, T last) {
        for ( T i = first; i < last; ++i ) {
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
    }

    // Print all the elements in the container
    template<typename T>
    void print(T input) {
        sort::print(input.begin(), input.end());
    }


    // Return true iff the elements in the range [start, stop) are sorted
    template<typename T>
    bool check(T start, T stop) {
        for ( T i = start + 1; i < stop; ++i ) {
            if ( *(i - 1) > *i ) {
                return false;
            }
        }

        return true;
    }

    // Return true iff all the elements in the container are sorted
    template<typename T>
    bool check(T input) {
        return sort::check(input.begin(), input.end());
    }


    // If the elements in the range [start, stop) aren't sorted, then print
    // the array, with brackets around runs in reverse sorted order, and
    // return false. Otherwise, return true.
    template<typename T>
    bool show(T start, T stop) {
        bool sorted = true;
        std::stringstream ss;

        for ( T i = start; i < stop; ++i ) {
            if ( i < stop - 1 && *i > *(i + 1) ) {
                // There are unsorted elements in this range
                sorted = false;

                // Append the run of elements in reverse sorted order to the
                // stream
                ss << "[ " << *i++ << ' ';

                // Append while still reverse sorted
                for ( ; i < stop - 1 && *i > *(i + 1); ++i ) {
                    std::cerr << *i << ' ';
                }

                // Finish appending the run
                ss << *i << " ] ";
            } else {
                // Append other elements to the stream
                ss << *i << ' ';
            }
        }

        // Print the range, if it's not sorted
        if ( ! sorted ) {
            std::cerr << ss.str() << std::endl;
        }

        return sorted;
    }

    // If the elements in the container aren't sorted, then print the array,
    // with brackets around runs in reverse sorted order, and  return false.
    // Otherwise, return true.
    template<typename T>
    void show(T input) {
        sort::show(input.begin(), input.end());
    }


    // Rebalance the tree at the given root
    template<typename T>
    inline void sift(T root, unsigned size) {
        T left, right, next;
        unsigned child_size;

        // Store original value
        auto val = *root;

        // We are in a leaf of the tree, so return
        if ( size < 2 ) return;

        do {
            // Find right child
            right = root - 1;
            // Find left child
            left = right - sort::leonardo_numbers[size - 2];

            // Compare the children's roots
            if ( *left < *right ) {
                // Choose right child
                next = right;
                child_size = size - 2; 
            } else {
                // Choose left child
                next = left;
                child_size = size - 1;
            }

            // If both of the children's roots are less than the original
            // value, then root is at the correct position
            if ( *next <= val ) break;

            // Push the larger root up the tree by chain swapping
            *root = *next;

            // Move down the tree
            root = next;
            size = child_size;
        } while ( size > 1 );

        // Put the original value in the correct position
        *root = val;
    }

    // Rebalance and sort the roots of the heaps in the tree at the given root 
    template<typename T>
    inline void trinkle(T root, heapsize_t size) {
        T left, right, next;

        // Store original value
        auto val = *root;

        // Traverse the implicit list of heaps from right to left
        while ( size.mask != 1 ) {

            auto max = val;

            // If this heap contains any subheaps
            if ( size.offset > 1 ) {
                // Find right child
                right = root - 1;
                // Find left child
                left = right - sort::leonardo_numbers[size.offset - 2];

                // Use the maximum of *left, *right, and val for any
                // comparisons
                if ( max < *left ) max = *left;
                if ( max < *right ) max = *right;
            }

            // Find the next heap
            next = root - leonardo_numbers[size.offset];

            // If it's already in order, stop
            if ( *next <= max ) break;

            // Push the larger root up the tree
            *root = *next;

            // Move down the tree
            root = next;

            // Get the previous heap from the implicit list
            do {
                size.mask >>= 1;
                ++size.offset;
            } while ( ! (size.mask & 1) );
        }

        // Put the original value in the correct position by chain swapping
        *root = val;

        // Make sure that the heap we stopped at is ordered properly
        sort::sift(root, size.offset);
    }

    // Heapify the elements in the range [start, stop)
    template<typename T>
    heapsize_t heapify(T start, T stop) {
        heapsize_t size;

        // Indicates whether a heap will need to be fused later
        bool fuse;

        size.mask = 1;
        size.offset = 1;

        for ( T i = start; i < stop; ++i ) {
            // If the sizes of the last two heaps are contiguous Leonardo
            // numbers
            if ( size.mask & 2 ) {
                // Fuse the last two heaps
                size.mask = (size.mask >> 2) | 1;
                size.offset += 2;
            // If the last heap is of size leonardo_numbers[1]
            } else if ( size.offset == 1 ) {
                // Make a new heap of size leonardo_numbers[0]
                size.mask = (size.mask << 1) | 1;
                size.offset = 0;
            } else {
                // Otherwise, make a new heap of size leonardo_numbers[1]
                size.mask = (size.mask << (size.offset - 1)) | 1;
                size.offset = 1;
            }

            // If the sizes of the last two heaps are contiguous Leonardo
            // numbers and there's at least one more element in the range,
            // or the size of this heap is a Leonardo number and there are
            // at least as many elements remaining in the range as the
            // previous Leonardo number, then this heap will need to be fused
            fuse = ((size.mask & 2) && (i + 1 < stop)) || 
                   ((size.offset > 0) && 
                    (i + leonardo_numbers[size.offset - 1] + 1 < stop));

            if ( fuse ) {
                // If it needs to be fused eventually, we can just do a sift
                sift(i, size.offset);
            } else {
                // Otherwise, it is a final heap, so we need to do a trinkle
                trinkle(i, size);
            }
        }

        return size;
    }

    // Extract all elements from the (heapified) range [start, stop)
    template<typename T>
    void extract(T start, T stop, heapsize_t size) {
        // Extract all elements except for the last two
        for ( T i = stop - 1; i > start + 1; --i ) {
            // If the last heap only has one element, ignore it
            if ( size.offset < 2 ) {
                do {
                    size.mask >>= 1;
                    ++size.offset;
                } while ( ! (size.mask & 1) );
            } else {
                // Remove this heap
                size.mask &= ~1ULL;

                // Add the left child and make sure its roots are sorted
                size.mask = (size.mask << 1) | 1;
                trinkle(i - leonardo_numbers[--size.offset - 1] - 1, size);

                // Add the right child and make sure its roots are sorted
                size.mask = (size.mask << 1) | 1;
                --size.offset;
                trinkle(i - 1, size);
            }
        }
    }


    // In-place smoothsort on the elements in the range [start, stop)
    template<typename T>
    void smoothsort(T start, T stop) {
        if ( stop - start < 2 ) return;

        heapsize_t size = sort::heapify(start, stop);
        sort::extract(start, stop, size);
    }

    // In-place smoothsort on all the elements in the container
    template<typename T>
    void smoothsort(T &input) {
        if ( input.size() < 2 ) return;

        heapsize_t size = sort::heapify(input.begin(), input.end());
        sort::extract(input.begin(), input.end(), size);
    }

    // In-place smoothsort sort on all the elements in an array
    template<typename T>
    void smoothsort(T *input, unsigned n) {
        if ( n < 2 ) return;

        heapsize_t size = sort::heapify(input, input + n);
        sort::extract(input, input + n, size);
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

    // In-place insertion sort on all the elements in the container
    template<typename T>
    void insertion_sort(T &input) {
        sort::insertion_sort(input.begin(), input.end());
    }

    // In-place insertion sort on the first n elements of the input array
    template<typename T>
    void insertion_sort(T *input, unsigned size) {
        sort::insertion_sort(input, input + size);
    }


    // Calculate the median of three values
    template<typename T>
    static T medianOf3(T a, T b, T c) {
        // Find the maximum of all three elements
        T maximum = std::max(std::max(a, b), c);

        // Find the minimum of all three elements
        T minimum = std::min(std::min(a, b), c);

        // xor'ing all these values together will zero all but the median
        return a ^ b ^ c ^ minimum ^ maximum;
    }


    // Quicksort partitioning function
    template<typename T>
    std::pair<T, T> partition(T start, T stop, unsigned chunk) {
        int n = stop - start;

        if ( n <= chunk ) {
            // Perform insertion sort on any chunk smaller than the given
            // cutoff
            sort::insertion_sort(start, stop);
            return std::make_pair(start, stop);
        } else if ( stop - start <= 40 ) {
            // Find the median of the first, middle, and last elements of
            // small ranges
            auto median = sort::medianOf3(*start, *(start + n / 2), 
                                          *(stop - 1));

            // Swap it to the beginning of the range
            std::swap(*start, median);
        } else {
            // Compute Tukey's ninther
            int part = n / 8;
            T mid = start + n / 2;
            auto median0 = sort::medianOf3(*start, *(start + part), 
                                           *(start + part + part));
            auto median1 = sort::medianOf3(*(mid - part), *mid, *(mid + part));
            auto median2 = sort::medianOf3(*(stop - 1 - part - part), 
                                           *(stop - 1 - part), *(stop - 1));
            auto ninther = sort::medianOf3(median0, median1, median2);

            // Swap it to the beginning of the range
            std::swap(*start, ninther);
        }

        // Bentley-McIlroy three-way partitioning
        T i = start, p = start;
        T j = stop, q = stop;

        // Pivot is either median or Tukey's ninther
        auto pivot = *start;

        while ( true ) {
            // Increment i while its value is less than the pivot
            while ( *++i < pivot ) {
                if ( i == stop - 1 ) break;
            }

            // Decrement j while its value is greater than the pivot
            while ( pivot < *--j ) {
                if ( j == start ) break;
            }

            // i and j have crossed
            if ( i == j && *i == pivot ) std::iter_swap(i, ++p);

            // i has passed j
            if ( i >= j ) break;

            // Swap i and j
            std::iter_swap(i, j);

            // Move pivot values to the ends of the range
            if ( *i == pivot ) std::iter_swap(i, ++p);
            if ( *j == pivot ) std::iter_swap(j, --q);
        }

        // Swap pivot values into place in the array such that all preceding
        // elements are smaller, and all following elements are larger
        i = j + 1;
        for ( T k = start; k <= p; ++k ) std::iter_swap(k, j--);
        for ( T k = stop - 1; k >= q; --k ) std::iter_swap(k, i++);

        // Return the (inclusive) indices of the range that has been sorted
        return std::make_pair(j + 1, i);
    }


    // In-place quicksort on the elements in the range [start, stop), with the
    // given chunk size
    template<typename T>
    void quicksort(T start, T stop, unsigned chunk) {
        // Make a stack for holding pairs of iterators representing the
        // non-inclusive range [first, second)
        std::stack<std::pair<T, T>> *st = new std::stack<std::pair<T, T>>();

        // Push a terminal element onto the stack
        st->push(std::make_pair(start, start));

        while ( ! st->empty() ) {
            while ( start < stop ) {
                // Partition the given range using the default chunk size
                std::pair<T, T> indices = sort::partition(start, stop, chunk);

                // Push the range which includes elements larger than the
                // pivot onto the stack
                st->push(std::make_pair(indices.second, stop));

                // Set the end of the range to be the end of the range which
                // includes elements smaller than the pivot
                stop = indices.first;
            }

            // Retrieve the next range from the stack
            std::pair<T, T> indices = st->top();
            st->pop();

            // Set the next range
            start = indices.first;
            stop = indices.second;
        }

        delete st;
    }

    // In-place quicksort on the elements in the range [start, stop)
    template<typename T>
    void quicksort(T start, T stop) {
        sort::quicksort(start, stop, CHUNK);
    }

    // In-place quicksort on all the elements in the container
    template<typename T>
    void quicksort(T &input) {
        sort::quicksort(input.begin(), input.end(), CHUNK);
    }

    // In-place quicksort on the first n elements of the input array
    template<typename T>
    void quicksort(T *input, unsigned n) {
        sort::quicksort(input, input + n, CHUNK);
    }


    // In-place introsort on the elements in the range [start, stop)
    template<typename T>
    void introsort(T start, T stop, unsigned depth) {
        // Make a stack for holding pairs of iterators representing the
        // non-inclusive range [first, second)
        std::stack<std::pair<T, T>> *st = new std::stack<std::pair<T, T>>();

        // Push a terminal element onto the stack
        st->push(std::make_pair(start, start));

        while ( ! st->empty() ) {
            while ( start < stop ) {
                if ( --depth > 0 ) {
                    // Partition the given range using the default chunk size
                    std::pair<T, T> indices = 
                        sort::partition(start, stop, CHUNK);

                    // Push the range which includes elements larger than the
                    // pivot onto the stack
                    st->push(std::make_pair(indices.second, stop));

                    // Set the end of the range to be the end of the range
                    // which includes elements smaller than the pivot
                    stop = indices.first;
                } else {
                    // If we've exceeded the maximum depth, smoothsort the
                    // remaining elements
                    sort::smoothsort(start, stop);
                    break;
                }
            }

            // Retrieve the next range from the stack
            std::pair<T, T> indices = st->top();
            st->pop();

            // Set the next range
            start = indices.first;
            stop = indices.second;
        }

        delete st;
    }

    // In-place introsort on the input container
    template<typename T>
    void introsort(T &input) {
        // Set a default maximum recursion depth of 2 * log(n)
        unsigned max = 2 * log2(input.size()) + 1;

        sort::introsort(input.begin(), input.end(), max);
    }

    // In-place introsort on the first n elements of the input array
    template<typename T>
    void introsort(T *input, unsigned n) {
        // Set a default maximum recursion depth of 2 * log(n)
        unsigned max = 2 * log2(n) + 1;

        sort::introsort(input, input + n, max);
    }
}

#endif // __SORT_HH__
