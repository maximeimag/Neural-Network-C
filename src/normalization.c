#include "normalization.h"
#include "utils.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Implemntation on simple arrays

int standardization(double **array, int array_size)
{
    double mean_value = get_mean(*array, array_size);
    double std_value = get_std(*array, array_size);
    for (int i = 0; i < array_size; i++)
    {
        array[0][i] = (array[0][i] - mean_value) / std_value;
    }
    return SUCCESS;

}

int minmax_normalization(double **array, int array_size)
{
    double min_value = get_min(*array, array_size);
    double max_value = get_max(*array, array_size);
    double upper = 1.0, lower = 0.0;
    double factor = (upper - lower) / (max_value - min_value);
    for (int i = 0; i < array_size; i++)
    {
        array[0][i] = ((array[0][i] - min_value) * factor) + lower;
    }
    return SUCCESS;
}

int normalize(double **array, int array_size, int normalization_type)
{
    int end_status = 0;
    switch (normalization_type)
    {
        case STANDARDIZATION:
            end_status = standardization(array, array_size);
            break;

        case MIN_MAX:
            end_status = minmax_normalization(array, array_size);
            break;

        default:
            end_status = UNDEFINED;
    }
    return end_status;
}

// Implementation on network array

int normalize_network_array(NetworkArray *network_array, int normalization_type)
{
    int end_status;
    double *batch;
    for (int i = 0; i < network_array->nb_batchs; i++) {
        batch = get_batch(network_array, i);
        if (batch == NULL)
        {
            return INVALID_BATCH_ID;
        }
        end_status = normalize(&batch, network_array->batch_size, normalization_type);
        if (end_status != SUCCESS)
        {
            return end_status;
        }
    }
    return SUCCESS;
}
