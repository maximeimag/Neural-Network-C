#include "layer.h"
#include "utils_func.h"
#include "network_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Constructors */

DenseLayer *create_dense_layer(int input_size, int output_size, int nb_batchs, int activation_name)
{
    DenseLayer *layer = (DenseLayer *)malloc(sizeof(DenseLayer));
    layer->input_size = input_size;
    layer->output_size = output_size;
    layer->nb_batchs = nb_batchs;
    layer->activation_name = activation_name;
    // layers->output->vals[k][i] : ith value of the kth batch in the output
    layer->output = create_random_array(output_size, nb_batchs);
    // biais[i] = biais for output neuron i
    layer->biais = (double *)malloc(sizeof(double) * output_size);
    // weights[i][j] = weight of link between output neuron i and input neuron j
    layer->weights = (double **)malloc(sizeof(double *) * output_size);
    for (int i = 0; i < output_size; i ++)
    {
        layer->weights[i] = (double *)malloc(sizeof(double) * input_size);
    }
    init_layer_values(layer);
    return layer;
}


/* Initialization */

void init_layer_biais(DenseLayer *layer)
{
    int j;
    for (j = 0; j < layer->output_size; j ++)
    {
        layer->biais[j] = 1.0f;
    }
}

void init_layer_weights(DenseLayer *layer)
{
    int i, j;
    for (i = 0; i < layer->output_size; i ++)
    {
        for (j = 0; j < layer->input_size; j ++)
        {
            layer->weights[i][j] = get_random_value();
        }
    }
}

void init_layer_values(DenseLayer *layer)
{
    init_layer_biais(layer);
    init_layer_weights(layer);
    init_array_values(layer->output);
}


/* Comparators */

int is_compatible(DenseLayer *layer, NetworkArray *input_array)
{
    if (input_array->batch_size != layer->input_size || input_array->nb_batchs > layer->nb_batchs)
    {
        return 0;
    }
    return 1;
}


/* Feed forward */

int feed_forward(DenseLayer *layer, NetworkArray *input_array)
{
    int i, k;
    if (!is_compatible(layer, input_array))
    {
        return -1;
    }
    // Compute Activation and Sigmoid for each element in output
    // The kth input in input-array of size (layer->input_size)
    for (k = 0; k < input_array->nb_batchs; k++)
    {
        // Compute The ith neuron activation value
        for (i = 0; i < input_array->batch_size; i++)
        {
            layer->output->vals[k][i] = dot_product(layer->weights[i], input_array->vals[k], layer->input_size);
            layer->output->vals[k][i] += layer->biais[i];
            layer->output->vals[k][i] = get_activation_value(get_val(layer->output, k, i), layer->activation_name, 0);
        }
    }
    return 1;
}


// Utils

void display_dense_layer(DenseLayer *layer)
{
    size_t i, j;
    printf("\n Input size : %d \n", layer->input_size);
    printf("Output size : %d \n", layer->output_size);
    printf("Output Array : \n [");
    display_network_array(layer->output);
    printf("Bias : \n [");
    for (i = 0; i < layer->output_size; i ++)
    {
        printf("%f ", layer->biais[i]);
    }
    printf("] \n");
    printf("Weights Array : \n");
    for (i = 0; i < layer->output_size; i ++)
    {
        for (j = 0; j < layer->input_size; j ++)
        {
            printf("%f ", layer->weights[i][j]);
        }
        printf("\n");

    }
}

void free_layer(DenseLayer *layer)
{
    free_network_array(layer->output);
    free(layer->biais);
    for (size_t i = 0; i < layer->input_size; i ++)
    {
        free(layer->weights[i]);
    }
    free(layer->weights);
    free(layer);
}
