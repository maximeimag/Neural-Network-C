#include "network_array.h"
#include "utils_func.h"
#include <stdio.h>
#include <stdlib.h>

/* Contructors */

NetworkArray *create_random_array(int batch_size, int nb_batchs)
{
    int i, j;
    NetworkArray *network_array = (NetworkArray *)malloc(sizeof(NetworkArray));
    network_array->batch_size = batch_size;
    network_array->nb_batchs = nb_batchs;
    network_array->vals = (double **)malloc(sizeof(double *) * nb_batchs);
    for (i = 0; i < nb_batchs; i++)
    {
        network_array->vals[i] = (double *)malloc(sizeof(double) * batch_size);
        for (j = 0; j < batch_size; j++)
        {
            network_array->vals[i][j] = 0.0f;
        }
    }
    init_array_values(network_array);
    return network_array;
}

NetworkArray *create_array_from_labels(int batch_size, int *labels, int nb_batchs)
{
    int i, j;
    NetworkArray *network_array = create_random_array(batch_size, nb_batchs);
    for (i = 0; i < network_array->nb_batchs; i++)
    {
        for (j = 0; j < network_array->batch_size; j++)
        {
            if (j == labels[i])
            {
                network_array->vals[i][j] = 1.0;
            }
            else
            {
                network_array->vals[i][j] = 0.0;
            }
        }
    }
    return network_array;
}


/* Initialization */

void init_array_values(NetworkArray *network_array)
{
    int i, j;
    for (i = 0; i < network_array->nb_batchs; i++)
    {
        for (j = 0; j < network_array->batch_size; j++)
        {
            network_array->vals[i][j] = get_random_value();
        }
    }
}


/* Getters and Setters */

int is_valid_index(NetworkArray *network_array, int batch_id, int val_id)
{
    if (0 <= batch_id && batch_id < network_array->nb_batchs && 0 <= val_id && val_id < network_array->batch_size)
    {
        return 1;
    }
    return 0;
}

int set_val(NetworkArray *network_array, int batch_id, int val_id, double new_val)
{
    if (is_valid_index(network_array, batch_id, val_id))
    {
        network_array->vals[batch_id][val_id] = new_val;
        return 1;
    }
    return -1;
}

double get_val(NetworkArray *network_array, int batch_id, int val_id)
{
    if (is_valid_index(network_array, batch_id, val_id))
    {
        return network_array->vals[batch_id][val_id];
    }
    return NAN;
}


/* Comparators  */

int compare_size(NetworkArray *network_array_1, NetworkArray *network_array_2)
{
    if (network_array_1->batch_size != network_array_2->batch_size)
    {
        return 0;
    }
    if (network_array_1->nb_batchs != network_array_2->nb_batchs)
    {
        return 0;
    }
    return 1;
}

double *MSE(NetworkArray *prediction, NetworkArray *truth)
{
    if (!compare_size(prediction, truth))
    {
        return NULL;
    }
    double *mse_array = (double *)malloc(sizeof(double) * prediction->nb_batchs);
    double error_sum, diff;
    for (int i = 0; i < prediction->nb_batchs; i++)
    {
        error_sum = 0.0;
        for (int j = 0; j < prediction->batch_size; j++)
        {
            diff = prediction->vals[i][j] - truth->vals[i][j];
            error_sum +=  diff * diff;
        }
        mse_array[i] = error_sum / (double)prediction->nb_batchs;
    }
    return mse_array;
}


/* Utils */

void free_network_array(NetworkArray *network_array)
{
    for (int i = 0; i < network_array->nb_batchs; i++)
    {
        free(network_array->vals[i]);
    }
    free(network_array->vals);
    free(network_array);
}

void display_network_array(NetworkArray *network_array)
{
    int i, j;
    printf("Number of batchs : %d | Batchs size : %d \n", network_array->nb_batchs, network_array->batch_size);
    for (i = 0; i < network_array->nb_batchs; i ++)
    {
        printf("[");
        for (j = 0; j < network_array->batch_size; j ++)
        {
            printf("%f ", network_array->vals[i][j]);
        }
        printf("] \n");

    }
}
