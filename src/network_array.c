#include <stdio.h>
#include <stdlib.h>

#include "network_array.h"
#include "utils.h"
#include "constants.h"

/* Contructors */

NetworkArray *create_array(int batch_size, int nb_batchs)
{
    NetworkArray *network_array = (NetworkArray *)malloc(sizeof(NetworkArray));
    network_array->batch_size = batch_size;
    network_array->nb_batchs = nb_batchs;
    network_array->vals = (double **)malloc(sizeof(double *) * nb_batchs);
    for (int i = 0; i < nb_batchs; i++)
    {
        network_array->vals[i] = (double *)malloc(sizeof(double) * batch_size);
    }
    return network_array;
}

NetworkArray *create_fixed_array(int batch_size, int nb_batchs, double init_value)
{
    NetworkArray *network_array = create_array(batch_size, nb_batchs);
    set_fixed_value(network_array, init_value);
    return network_array;
}

NetworkArray *create_random_array(int batch_size, int nb_batchs, double upper, double lower)
{
    NetworkArray *network_array = create_array(batch_size, nb_batchs);
    set_random_values(network_array, lower, upper);
    return network_array;
}

NetworkArray *create_array_from_labels(int batch_size, int *labels, int nb_batchs)
{
    int i, j;
    NetworkArray *network_array = create_fixed_array(batch_size, nb_batchs, 0.0);
    for (i = 0; i < network_array->nb_batchs; i++)
    {
        for (j = 0; j < network_array->batch_size; j++)
        {
            if (j == labels[i])
            {
                network_array->vals[i][j] = 1.0;
            }
        }
    }
    return network_array;
}


/* Initialization */

void set_fixed_value(NetworkArray *network_array, double fixed_value)
{
    int i, j;
    for (i = 0; i < network_array->nb_batchs; i++)
    {
        for (j = 0; j < network_array->batch_size; j++)
        {
            network_array->vals[i][j] = fixed_value;
        }
    }
}

void set_random_values(NetworkArray *network_array, double lower, double upper)
{
    int i, j;
    for (i = 0; i < network_array->nb_batchs; i++)
    {
        for (j = 0; j < network_array->batch_size; j++)
        {
            network_array->vals[i][j] = get_random_double(lower, upper);
        }
    }
}

/* Copy */
int copy_network_array(NetworkArray *src, NetworkArray *dest)
{
    int check_size = compare_size(src, dest);
    if (check_size != COMPATIBLE_SIZES)
    {
        return check_size;
    }
    for (int i = 0; i < src->nb_batchs; i++) {
        for (int j = 0; j < src->batch_size; j++) {
            dest->vals[i][j] = src->vals[i][j];
        }
    }

    return SUCCESS;
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

double *get_batch(NetworkArray *network_array, int batch_id)
{
    double *batch = NULL;
    if (is_valid_index(network_array, batch_id, 0) == VALID_INDEX)
    {
        batch = network_array->vals[batch_id];
    }
    return batch;
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
        return check_size;
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
        array[i] = error_sum / (double)(prediction->batch_size * 2);
    }
    *mse_array = array;
    return SUCCESS;
}


/* diff <- network_array_1 - network_array_2 */
int compute_diff(NetworkArray *network_array_1, NetworkArray *network_array_2, NetworkArray *diff)
{
    // Check sizes
    int check_size_1 = compare_size(network_array_1, diff), check_size_2 = compare_size(network_array_2, diff);
    if (check_size_1 != COMPATIBLE_SIZES || check_size_2 != COMPATIBLE_SIZES)
    {
        return min(check_size_1, check_size_2);
    }
    // Compute diff
    for (int i = 0; i < diff->nb_batchs; i++) {
        for (int j = 0; j < diff->batch_size; j++) {
            diff->vals[i][j] = network_array_1->vals[i][j] - network_array_2->vals[i][j];
        }
    }
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
