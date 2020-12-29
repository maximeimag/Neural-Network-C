#include "utils_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Activation function and its derivative
double Sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double dSigmoid(double x)
{
    return x * (1 - x);
}


double ReLU(double x)
{
    if (x > 0)
    {
        return x;
    }
    return 0;
}

double dReLU(double x)
{
    if (x > 0)
    {
        return 1;
    }
    return 0;
}

int *create_random_labels_array(int nb_labels, int array_size)
{
    int *labels_array = (int *)malloc(sizeof(int) * array_size);
    for (size_t i = 0; i < array_size; i++)
    {
        labels_array[i] = get_randint(0, nb_labels - 1);
    }
    return labels_array;
}

double dot_product(double *X1, double *X2, int array_sizes)
{
    double product = 0.0;
    for (size_t i = 0; i < array_sizes; i++)
    {
        product += X1[i] * X2[i];
    }
    return product;
}

// Get activation and derivative
double get_activation_value(double x, int activation_name, int get_derivative)
{
    double activation_value = 0.0;
    switch(activation_name)
    {
        case ACTIVATION_ReLU:
            if (get_derivative)
            {
                activation_value = dReLU(x);
            }
            else
            {
                activation_value = ReLU(x);
            }
            break;

        case ACTIVATION_sigmoid:
            if (get_derivative)
            {
                activation_value = dSigmoid(x);
            }
            else
            {
                activation_value = Sigmoid(x);
            }
            break;

        default:
            activation_value = NAN;
    }
    return activation_value;
}

// pick a random int in [0, 1]
double get_random_value()
{
    return ((double)rand())/((double)RAND_MAX);
}


// pick a random int in [a, b]
int get_randint(int a, int b)
{
    return a + ((int)rand() % (int)(b - a + 1));
}
