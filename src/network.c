#include "network.h"
#include "network_array.h"
#include "layer.h"
#include "constants.h"
#include "normalization.h"

#include <stdio.h>
#include <stdlib.h>

/* Constructors */

DenseNetwork *create_network(
    int input_size,
    int output_size,
    int nb_batchs,
    int activation_name,
    int normalization_type,
    int nb_layers,
    int *layer_sizes
)
{
    DenseNetwork *network = (DenseNetwork *)malloc(sizeof(DenseNetwork));
    network->input_size = input_size;
    network->output_size = output_size;
    network->nb_batchs = nb_batchs;
    network->activation_name = activation_name;
    network->normalization_type = normalization_type;
    network->nb_layers = nb_layers;
    DenseLayer *layer;
    network->layer_list = (DenseLayer **)malloc(sizeof(DenseLayer *) * nb_layers);
    for (int i = 0; i < nb_layers; i++)
    {
        layer = create_dense_layer(layer_sizes[i], layer_sizes[i + 1], nb_batchs, activation_name, NO_NORMALIZATION);
        network->layer_list[i] = layer;
        network->final_activation = layer->activation;
    }
    network->output = create_array(output_size, nb_batchs);
    return network;
}


/* Comparators */

int is_compatible_network_input(DenseNetwork *network, NetworkArray *input_array)
{
    return is_compatible_layer_input(network->layer_list[0], input_array);
}

int is_compatible_network_output(DenseNetwork *network, NetworkArray *truth)
{
    return is_compatible_layer_output(network->layer_list[network->nb_layers - 1], truth);
}



/* Feed Forward */

int feed_forward_network(DenseNetwork *network, NetworkArray *input_array)
{
    // Check sizes
    int check_size = is_compatible_network_input(network, input_array);
    if (check_size != COMPATIBLE_SIZES)
    {
        return check_size;
    }
    // Feed forward to each layer
    int end_status;
    // Input array to first layer
    end_status = feed_forward(network->layer_list[0], input_array);
    if (end_status != SUCCESS)
    {
        return end_status;
    }
    // Last layer's output to the next
    for (int i = 1; i < network->nb_layers; i++)
    {
        if (end_status != SUCCESS)
        {
            return end_status;
        }
        end_status = feed_forward(network->layer_list[i], network->layer_list[i - 1]->activation);
    }
    // last normalization
    // * Copy final acrtivation
    int copy_status = copy_network_array(network->final_activation, network->output);
    if (copy_status != SUCCESS)
    {
        return copy_status;
    }
    // Apply normalization
    if (network->normalization_type != NO_NORMALIZATION)
    {
        return normalize_network_array(network->output, network->normalization_type);
    }
    return SUCCESS;
}

NetworkArray *predict(DenseNetwork *network, NetworkArray *input_array)
{
    int end_status = feed_forward_network(network, input_array);
    if (end_status == SUCCESS)
    {
        return network->output;
    }
    else
    {
        return NULL;
    }
}

/* Back-propagation */
int fit(DenseNetwork *network, NetworkArray *input_array, NetworkArray *truth)
{
    // Check sizes
    int check_size = is_compatible_network_input(network, input_array);
    if (check_size != COMPATIBLE_SIZES)
    {
        return check_size;
    }
    // Feed forward to get output
    int feed_status = feed_forward_network(network, input_array);
    // If feed forward is a success, apply back_propagation
    if (feed_status != SUCCESS)
    {
        return back_propagation(network, truth);
    }
    else
    {
        return feed_status;
    }
}


int back_propagation(DenseNetwork *network, NetworkArray *truth)
{
    int check_size = is_compatible_network_output(network, truth);
    if (check_size != COMPATIBLE_SIZES)
    {
        return check_size;
    }
    // Get MSE errors
    double *mse_errors = NULL;
    int mse_status = compute_MSE(network->output, truth, &mse_errors);
    if (mse_status != SUCCESS)
    {
        return mse_status;
    }
    // TODO : Implement Back propagation
    // Back propagate to last layer
    return SUCCESS;
}

void summary(DenseNetwork *network)
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

void summary_with_output(DenseNetwork *network)
{
    summary(network);
    printf("Final Activation : \n");
    display_network_array(network->final_activation);
    printf("Normalized output : \n");
    display_network_array(network->output);
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
