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

#endif /* ROLLING_MAX_H */