#include "network.h"
#include "network_array.h"
#include "layer.h"
#include <stdio.h>
#include <stdlib.h>

/* Constructors */

DenseNetwork *create_network(
    int input_size,
    int output_size,
    int nb_batchs,
    int activation_name,
    int nb_layers,
    int *layer_sizes
)
{
    DenseNetwork *network = (DenseNetwork *)malloc(sizeof(DenseNetwork));
    network->input_size = input_size;
    network->output_size = output_size;
    network->nb_batchs = nb_batchs;
    network->activation_name = activation_name;
    network->nb_layers = nb_layers;
    DenseLayer *layer;
    network->layer_list = (DenseLayer **)malloc(sizeof(DenseLayer *) * nb_layers);
    for (int i = 0; i < nb_layers; i++)
    {
        layer = create_dense_layer(layer_sizes[i], layer_sizes[i + 1], nb_batchs, activation_name);
        network->layer_list[i] = layer;
        network->output = layer->output;
    }
    return network;
}


/* Comparators */

int is_compatible_input(DenseNetwork *network, NetworkArray *input_array)
{
    return is_compatible(network->layer_list[0], input_array);
}

int is_compatible_output(DenseNetwork *network, NetworkArray *truth)
{
    if (network->nb_batchs != truth->nb_batchs)
    {
        return 0;
    }
    if (network->output_size != truth->batch_size)
    {
        return 0;
    }
    return 1;
}



/* Feed Forward */

int feed_forward_network(DenseNetwork *network, NetworkArray *input_array)
{
    if (!is_compatible_input(network, input_array))
    {
        return -1;
    }
    feed_forward(network->layer_list[0], input_array);
    for (int i = 1; i < network->nb_layers; i++)
    {
        feed_forward(network->layer_list[i], network->layer_list[i - 1]->output);
    }
    return 1;
}

NetworkArray *predict(DenseNetwork *network, NetworkArray *input_array)
{
    int res = feed_forward_network(network, input_array);
    if (res == 1)
    {
        return network->output;
    }
    else
    {
        return NULL;
    }
}

/* Back-propagation */
int back_propagation(DenseNetwork *network, NetworkArray *truth)
{
    return (int)is_compatible_output(network, truth);
}

void display_network(DenseNetwork *network)
{
    printf("\nSummary : \n");
    printf("Input size : %d \n", network->input_size);
    printf("Output size : %d \n", network->output_size);
    printf("Batch size : %d \n", network->nb_batchs);
    printf("Number of layers : %d \n", network->nb_layers);
    DenseLayer *layer;
    for (int i = 0; i < network->nb_layers; i++)
    {
        layer = network->layer_list[i];
        printf("layer %d : (%d, %d) -> (%d, %d) \n", i, layer->input_size, layer->nb_batchs, layer->output_size, layer->nb_batchs);
    }
}

void free_network(DenseNetwork *network)
{
    for (int i = 0; i < network->nb_layers; i++)
    {
        free_layer(network->layer_list[i]);
    }
    free(network->layer_list);
    free(network);
}
