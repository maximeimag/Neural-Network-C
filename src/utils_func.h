#ifndef UTILS_FUNC_H_INCLUDED
#define UTILS_FUNC_H_INCLUDED

#define ACTIVATION_ReLU 0
#define ACTIVATION_sigmoid 1

double Sigmoid(double x);
double dSigmoid(double x);

double ReLU(double x);
double dReLU(double x);

double get_nan();

double get_activation_value(double x, int activation_name, int get_derivative);


int *create_random_labels_array(int nb_labels, int array_size);
double dot_product(double *X1, double *X2, int array_sizes);

double get_random_value();
int get_randint(int a, int b);

#endif // UTILS_FUNC_H_INCLUDED
