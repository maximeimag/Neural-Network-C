#include "network_array.h"
#include "utils_func.h"
#include "constants.h"
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
    if (batch_id < 0 || batch_id >= network_array->nb_batchs)
    {
        return INVALID_BATCH_ID;
    }
    if (val_id < 0 || val_id >= network_array->batch_size)
    {
        return INVALID_VAL_ID;
    }
    return VALID_INDEX;
}

int set_val(NetworkArray *network_array, int batch_id, int val_id, double new_val)
{
    int check_index = is_valid_index(network_array, batch_id, val_id);
    if (check_index == VALID_INDEX)
    {
        network_array->vals[batch_id][val_id] = new_val;
        return SUCCESS;
    }
    return check_index;
}

double get_val(NetworkArray *network_array, int batch_id, int val_id)
{
    if (is_valid_index(network_array, batch_id, val_id) == VALID_INDEX)
    {
        return network_array->vals[batch_id][val_id];
    }
    return get_nan();
}


/* Comparators  */

int compare_size(NetworkArray *network_array_1, NetworkArray *network_array_2)
{
    if (network_array_1->batch_size != network_array_2->batch_size)
    {
        return INCOMPATIBLE_BATCH_SIZE;
    }
    if (network_array_1->nb_batchs != network_array_2->nb_batchs)
    {
        return INCOMPATIBLE_NB_BATCHS;
    }
    return COMPATIBLE_SIZES;
}

int compute_MSE(NetworkArray *prediction, NetworkArray *truth, double **mse_array)
{
    int check_size = compare_size(prediction, truth);
    if (check_size != COMPATIBLE_SIZES)
    {
        return COMPATIBLE_SIZES;
    }
    double *array = (double *)malloc(sizeof(double) * prediction->nb_batchs);
    double error_sum, diff;
    for (int i = 0; i < prediction->nb_batchs; i++)
    {
        error_sum = 0.0;
        for (int j = 0; j < prediction->batch_size; j++)
        {
            diff = prediction->vals[i][j] - truth->vals[i][j];
            error_sum +=  diff * diff;
        }
        array[i] = error_sum / (double)prediction->nb_batchs;
    }
    *mse_array = array;
    return SUCCESS;
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
