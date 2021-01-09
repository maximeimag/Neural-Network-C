#include <stdio.h>
#include <stdlib.h>
#include "layer.h"
#include "network.h"
#include "network_array.h"
#include "utils.h"
#include "activation.h"
#include "normalization.h"

int main()
{
    // Initialize variables to define network
    int input_size = 2, output_size = 2, nb_batchs = 5, hidden_size = 6;
    int nb_labels = output_size;
    int nb_layers = 5;
    int activation_name = ACTIVATION_ReLU;
    int normalization_type = MIN_MAX;
    int i;
    int *layer_sizes = (int *)malloc(sizeof(int) * (nb_layers + 1));
    layer_sizes[0] = input_size;
    layer_sizes[nb_layers] = output_size;
    for (i = 1; i < nb_layers; i++)
    {
        layer_sizes[i] = hidden_size;
    }

    //Initialize Input array
    NetworkArray *input_array = create_random_array(input_size, nb_batchs);
    printf("\n \n ** Input array ** \n");
    display_network_array(input_array);

    // Initialize Labels array
    int *labels = create_random_labels_array(nb_labels, nb_batchs);
    printf("\n ** Labels array ** \n");
    NetworkArray *labels_array = create_array_from_labels(nb_labels, labels, nb_batchs);
    display_network_array(labels_array);

    // Initialize a single layer
    DenseLayer *layer;
    layer = create_dense_layer(input_size, output_size, nb_batchs, activation_name, normalization_type);
    printf("\n ** Random layer ** \n");
    display_dense_layer(layer);

    // Update Output for a single layer
    feed_forward(layer, input_array);
    printf("\n ** Random layer after feed forward ** \n");
    display_dense_layer(layer);

    //Initialize a network
    DenseNetwork *network;
    network = create_network(
        input_size,
        output_size,
        nb_batchs,
        activation_name,
        nb_layers,
        layer_sizes
    );
    printf("\n ** Network Structure ** \n");
    display_network(network);
    printf("\n ** Network output before update ** \n");
    display_network_array(network->output);

    // Update and display output
    feed_forward_network(network, input_array);
    printf("\n ** Network output after update ** \n");
    display_network_array(network->output);

    // Get MSE errors
    printf("\n ** Labels array ** \n");
    display_network_array(labels_array);
    printf("\n ** MSE Array ** \n");
    double *mse_errors = NULL;
    int status = compute_MSE(network->output, labels_array, &mse_errors);
    printf(" * Output status %u \n", status);
    for (i = 0; i < nb_batchs; i++)
    {
        printf("%f ", mse_errors[i]);
    }

    // Free datas
    free_network(network);
    free_layer(layer);
    free_network_array(labels_array);
    free(labels);
    free_network_array(input_array);
    free(mse_errors);
    return 0;
}
