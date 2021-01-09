#ifndef NORMALIZATION_H_INCLUDED
#define NORMALIZATION_H_INCLUDED

#include "network_array.h"

// Normalization types
#define NO_NORMALIZATION 0
#define STANDARDIZATION 1
#define MIN_MAX 2


// Implemntation on simple arrays

int normalize(double **array, int array_size, int normalization_type);

// Implementation on network array

int normalize_network_array(NetworkArray *network_array, int normalization_type);

#endif // NORMALIZATION_H_INCLUDED
