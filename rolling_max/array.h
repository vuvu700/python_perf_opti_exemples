
#ifndef ARRAY_H
#define ARRAY_H

#ifndef U_INT
#define U_INT unsigned int
#endif /* U_INT */

int* createNewArray_int(U_INT size);
double* createNewArray_lf(U_INT size);
float* createNewArray_f(U_INT size);




int* generateRandomArray_int(U_INT size);
double* generateRandomArray_lf(U_INT size);
float* generateRandomArray_f(U_INT size);




// in place randomization of the array (not a shuffle)
void randomizeArray_int(int *array, U_INT size);

// in place randomization of the array (not a shuffle)
void randomizeArray_lf(double *array, U_INT size);

// in place randomization of the array (not a shuffle)
void randomizeArray_f(float *array, U_INT size);

#endif /* ARRAY_H */