#ifndef ACTIVATION_H_INCLUDED
#define ACTIVATION_H_INCLUDED

// Activation names

#define ACTIVATION_ReLU 0
#define ACTIVATION_sigmoid 1

// Derivative or not derivative

#define DERIVATIVE 10
#define ACTIVATION 11

// Activation declaration

double Sigmoid(double x);
double dSigmoid(double x);

double ReLU(double x);
double dReLU(double x);

// Get function

double get_activation_value(double x, int activation_name, int value_type);

#endif // ACTIVATION_H_INCLUDED
