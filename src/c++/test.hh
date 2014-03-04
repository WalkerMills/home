#ifndef __TEST_HH__
#define __TEST_HH__

#include <vector>

#define SAMPLES 100000
#define SIZE 1000


std::vector<unsigned> *gen_vectors(unsigned samples, unsigned size);
unsigned **gen_arrays(unsigned samples, unsigned size);

#endif