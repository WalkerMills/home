#ifndef __TEST_HH__
#define __TEST_HH__

#include <vector>

#define SAMPLES 10000
#define SIZE 1000


typedef void (*array_fp)(unsigned *input, unsigned size);
typedef void (*vector_fp)(std::vector<unsigned> &input);

unsigned **gen_arrays(unsigned samples, unsigned size);
std::vector<unsigned> *gen_vectors(unsigned samples, unsigned size);

void benchmark_array(unsigned samples, unsigned size, array_fp f);
void benchmark_vector(unsigned samples, unsigned size, vector_fp f);

#endif