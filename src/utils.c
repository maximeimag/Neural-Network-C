#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Random Array */

// Returns an array of size array_size containing values in [0, nb_labels - 1]
int *create_random_labels_array(int nb_labels, int array_size)
{
    int *labels_array = (int *)malloc(sizeof(int) * array_size);
    for (int i = 0; i < array_size; i++)
    {
        labels_array[i] = get_randint(0, nb_labels - 1);
    }
    return labels_array;
}


// pick a random double in [lower, upper]
double get_random_double(double lower, double upper)
{
    double rand_val = ((double)rand())/((double)RAND_MAX);
    return (rand_val * (upper - lower)) + lower;
}


// pick a random int in [a, b]
int get_randint(int a, int b)
{
    return a + ((int)rand() % (int)(b - a + 1));
}


/* Dot product */

// Get dot product of X1 and X2 both of array_sizes
double dot_product(double *X1, double *X2, int array_sizes)
{
    double product = 0.0;
    for (int i = 0; i < array_sizes; i++)
    {
        product += X1[i] * X2[i];
    }
    return product;
}

/* Get mean, sum and average of double array */

double get_sum(double *array, int array_size)
{
    double sum_value = 0.0;
    for (int i = 0; i < array_size; i++) {
        sum_value += array[i];
    }
    return sum_value;
}

double get_mean(double *array, int array_size)
{
    return get_sum(array, array_size) / (double)array_size;
}

double get_std(double *array, int array_size)
{
    double mean_value = get_mean(array, array_size);
    double diff = 0.0;
    double squared_sum = 0.0;
    for (int i = 0; i < array_size; i++) {
        diff = array[i] - mean_value;
        squared_sum += diff * diff;
    }
    return squared_sum / (double)array_size;
}

double get_min(double *array, int array_size)
{
    double min_value = array[0];
    for (int i = 1; i < array_size; i++) {
        min_value = fmin(min_value, array[i]);
    }
    return min_value;
}

double get_max(double *array, int array_size)
{
    double max_value = array[0];
    for (int i = 1; i < array_size; i++) {
        max_value = fmax(max_value, array[i]);
    }
    return max_value;
}


/* Nan value if error */

double get_nan()
{
    return 0.0/0.0;
}
