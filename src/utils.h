#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/* Random Array */
int *create_random_labels_array(int nb_labels, int array_size);
double get_random_double(double lower, double upper);
int get_randint(int a, int b);

/* Dot product */
double dot_product(double *X1, double *X2, int array_sizes);

/* Get min, max, mean, sum and average of double array */
double get_mean(double *array, int array_size);
double get_sum(double *array, int array_size);
double get_std(double *array, int array_size);
double get_min(double *array, int array_size);
double get_max(double *array, int array_size);


/* Nan Value if error */
double get_nan();

#endif // UTILS_H_INCLUDED
