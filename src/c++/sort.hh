#ifndef __SORT_HH__
#define __SORT_HH__

#include <vector>


namespace sort {

    template<typename T>
    void insertion_sort(std::vector<T> input, int start, int stop);

    template<typename T>
    void insertion_sort(std::vector<T> input);

    template<typename T>
    void heapsort(std::vector<T> input, int start, int stop);

    template<typename T>
    void heapsort(std::vector<T> input);

    template<typename T>
    int partition(std::vector<T> input, int start, int stop);

    template<typename T>
    void quicksort(std::vector<T> input, int start, int stop);

    template<typename T>
    void introsort(std::vector<T> input, int start, int stop, int depth);

    template<typename T>
    void introsort(std::vector<T> input);

}

#endif // __SORT_HH__
