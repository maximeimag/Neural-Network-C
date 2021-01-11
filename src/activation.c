#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "activation.h"
#include "utils.h"

/* Activation implementation and their derivative */

double Sigmoid(double x)
{
    return 1.0 / (double)(1.0 + exp(-x));
}

double dSigmoid(double x)
{
    return (double)(x * (1.0 - x));
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

/* Get activation value or derivative */

double get_activation_value(double x, int activation_name, int value_type)
{
    double activation_value = get_nan();
    switch(activation_name)
    {
        case ACTIVATION_ReLU:
            if (value_type == DERIVATIVE)
            {
                activation_value = dReLU(x);
            }
            else if (value_type == ACTIVATION)
            {
                activation_value = ReLU(x);
            }
            break;

        case ACTIVATION_sigmoid:
            if (value_type == DERIVATIVE)
            {
                activation_value = dSigmoid(x);
            }
            else if (value_type == ACTIVATION)
            {
                activation_value = Sigmoid(x);
            }
            break;
        default:
            activation_value = get_nan();
    }
    return activation_value;
}
