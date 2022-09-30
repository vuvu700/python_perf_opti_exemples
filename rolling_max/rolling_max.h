#ifndef ROLLING_MAX_H
#define ROLLING_MAX_H

#include "array.h"

#ifndef U_INT
#define U_INT unsigned int
#endif /* U_INT */



// return the rolling average of the array, with a sliding window
int* rolling_max_int(int array[], U_INT windowSize, U_INT size);

// return the rolling average of the array, with a sliding window
double* rolling_max_lf(double array[], U_INT windowSize, U_INT size);

// return the rolling average of the array, with a sliding window
float* rolling_max_f(float array[], U_INT windowSize, U_INT size);



// compute the rolling average of the array in the array_out, with a sliding window
void rolling_max_ip_int(int array[], U_INT windowSize, U_INT size, int array_out[]);

// compute the rolling average of the array in the array_out, with a sliding window
void rolling_max_ip_lf(double array[], U_INT windowSize, U_INT size, double array_out[]);

// compute the rolling average of the array in the array_out, with a sliding window
void rolling_max_ip_f(float array[], U_INT windowSize, U_INT size, float array_out[]);



#endif /* ROLLING_MAX_H */