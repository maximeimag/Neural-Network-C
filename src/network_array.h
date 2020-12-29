#include <stdio.h>

#ifndef NETWORK_ARRAY_H_INCLUDED
#define NETWORK_ARRAY_H_INCLUDED

typedef struct NetworkArray NetworkArray;
struct NetworkArray
{
    int nb_batchs;
    int batch_size;
    double **vals;
    // vals[batch_id][val_id]
    // with batch_id in [0, nb_batchs - 1]
    // and val_id in [0, batch_size - 1]
};

// Constructors
// Fully random
NetworkArray *create_random_array(int batch_size, int nb_batchs);
// From labels in 1D array
NetworkArray *create_array_from_labels(int batch_size, int *labels, int nb_batchs);

// Initialization
void init_array_values(NetworkArray *network_array);

// Getters and Setters
int is_valid_index(NetworkArray *network_array, int batch_id, int val_id);
int set_val(NetworkArray *network_array, int batch_id, int val_id, double new_val);
double get_val(NetworkArray *network_array, int batch_id, int val_id);

// Comparators
int compare_size(NetworkArray *network_array_1, NetworkArray *network_array_2);
double *MSE(NetworkArray *prediction, NetworkArray *truth);

// Utils
void free_network_array(NetworkArray *network_array);
void display_network_array(NetworkArray *network_array);

#endif // UTILS_ARRAY_H_INCLUDED
