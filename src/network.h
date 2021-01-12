#include "layer.h"
#include "network_array.h"
#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

typedef struct DenseNetwork DenseNetwork;
struct DenseNetwork
{
    int input_size;
    int output_size;
    int nb_batchs;
    int activation_name;
    int normalization_type;
    int nb_layers;
    DenseLayer **layer_list;
    NetworkArray *final_activation;
    NetworkArray *output;
};

// Constructors
DenseNetwork *create_network(
    int input_size,
    int output_size,
    int nb_batchs,
    int activation_name,
    int normalization_type,
    int nb_layers,
    int *layer_sizes
);

// Comparators
int is_compatible_input(DenseNetwork *network, NetworkArray *input_array);
int is_compatible_output(DenseNetwork *network, NetworkArray *truth);

// Feed forward
int feed_forward_network(DenseNetwork *network, NetworkArray *input_array);
NetworkArray *predict(DenseNetwork *network, NetworkArray *input_array);

// Back-propagation
int fit(DenseNetwork *network, NetworkArray *input_array, NetworkArray *truth);
int back_propagation(DenseNetwork *network, NetworkArray *truth);

// Utils
void summary(DenseNetwork *network);
void summary_with_output(DenseNetwork *network);
void free_network(DenseNetwork *network);

#endif // NETWORK_H_INCLUDED
