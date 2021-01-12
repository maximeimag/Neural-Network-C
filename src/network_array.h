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
NetworkArray *create_array(int batch_size, int nb_batchs);
// With fixed value
NetworkArray *create_fixed_array(int batch_size, int nb_batchs, double init_value);
// Fully random
NetworkArray *create_random_array(int batch_size, int nb_batchs, double upper, double lower);
// From labels in 1D array
NetworkArray *create_array_from_labels(int batch_size, int *labels, int nb_batchs);

// Initialization
void set_fixed_value(NetworkArray *network_array, double fixed_value);
void set_random_values(NetworkArray *network_array, double lower, double upper);

// Getters and Setters
int is_valid_index(NetworkArray *network_array, int batch_id, int val_id);
int set_val(NetworkArray *network_array, int batch_id, int val_id, double new_val);
double get_val(NetworkArray *network_array, int batch_id, int val_id);
double *get_batch(NetworkArray *network_array, int batch_id);

// Comparators
int compare_size(NetworkArray *network_array_1, NetworkArray *network_array_2);
int compute_MSE(NetworkArray *prediction, NetworkArray *truth, double **mse_array);
/* diff <- network_array_1 - network_array_2 */
int compute_diff(NetworkArray *network_array_1, NetworkArray *network_array_2, NetworkArray *diff);

// Utils
void free_network_array(NetworkArray *network_array);
void display_network_array(NetworkArray *network_array);

#endif // UTILS_ARRAY_H_INCLUDED
