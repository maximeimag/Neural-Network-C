#include "network_array.h"
#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

typedef struct DenseLayer DenseLayer;
struct DenseLayer
{
    int input_size;
    int output_size;
    int nb_batchs;
    int activation_name;
    int normalization_type;
    NetworkArray *weighted_sum;
    NetworkArray *activation;
    double *biais;
    double **weights;
};

// Constructors
DenseLayer *create_dense_layer(int input_size, int output_size, int nb_batchs, int activation_name, int normalization_type);

// Initialization
void init_layer_values(DenseLayer *layer);
void init_layer_output_array(DenseLayer *layer);
void init_layer_weights(DenseLayer *layer);

// Comparators
int is_compatible_layer_input(DenseLayer *layer, NetworkArray *input_array);
int is_compatible_layer_output(DenseLayer *layer, NetworkArray *output_array);

// Feed forward
int feed_forward(DenseLayer *layer, NetworkArray *input_array);

// Utils
void display_dense_layer(DenseLayer *layer);
void free_layer(DenseLayer *layer);


#endif // LAYER_H_INCLUDED
