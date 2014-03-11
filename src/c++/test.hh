#ifndef __TEST_HH__
#define __TEST_HH__

#include <chrono>
#include <numeric>
#include <utility>
#include <vector>
#include <cmath>

#include "sort.hh"

#define SAMPLES 10
#define SIZE 1000000


typedef void (*array_fp)(unsigned *start, unsigned *stop);
typedef void (*vector_fp)(std::vector<unsigned>::iterator start,
                          std::vector<unsigned>::iterator stop);

unsigned **gen_arrays(unsigned samples, unsigned size);
std::vector<unsigned> *gen_vectors(unsigned samples, unsigned size);

void benchmark_array(unsigned samples, unsigned size, array_fp f);
void benchmark_vector(unsigned samples, unsigned size, vector_fp f);

template<typename T>
double mean(T start, T stop) {
    double sum = 0;
    unsigned count = 0;

    while ( start < stop ) {
        sum += *start++;
        ++count;
    }

    return count ? sum / count : count;
}

template<typename T>
double stddev(T start, T stop, double mu) {
    double sum = 0;
    unsigned count = 0;

    while ( start < stop ) {
        sum += pow(*start++ - mu, 2);
        ++count;
    }

    return count ? sqrt(sum / count) : count;
}

template<typename T>
double stddev(T start, T stop) {
    double mu = mean(start, stop);

    return stddev(start, stop, mu);
}

template<typename T, typename F>
std::pair<double, double> benchmark(unsigned samples, unsigned size, F fp) {
    T **arrays = gen_arrays(samples, size);
    double *res = new double[samples];

    std::chrono::microseconds elapsed;
    std::chrono::high_resolution_clock::time_point start, end;

    for ( unsigned i = 0; i < samples; ++i ) {
        start = std::chrono::high_resolution_clock::now();
        fp(arrays[i], arrays[i] + size);
        end = std::chrono::high_resolution_clock::now();
        elapsed = 
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        res[i] = (double) SIZE / elapsed.count();
    }

    for ( unsigned i = 0; i < samples; ++i ) {
        delete [] arrays[i];
    }
    delete [] arrays;

    double mu = mean(res, res + SAMPLES);
    double sigma = stddev(res, res + SAMPLES, mu);

    delete [] res;

    return std::make_pair(mu, sigma);
}

#endif