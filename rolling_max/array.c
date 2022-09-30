#include <stdio.h>
#include <stdlib.h>

#define U_INT unsigned int




int* createNewArray_int(U_INT size) {
    int *array = (int*) malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "createNewArray_int : allocation error, not enough memory ");
        exit(EXIT_FAILURE);
    }
    return array;
}

double* createNewArray_lf(U_INT size) {
    double *array = (double*) malloc(size * sizeof(double));
    if (array == NULL) {
        fprintf(stderr, "createNewArray_lf : allocation error, not enough memory");
        exit(EXIT_FAILURE);
    }
    return array;
}

float* createNewArray_f(U_INT size) {
    float *array = (float*) malloc(size * sizeof(float));
    if (array == NULL) {
        fprintf(stderr, "createNewArray_f : allocation error, not enough memory");
        exit(EXIT_FAILURE);
    }
    return array;
}






int* generateRandomArray_int(U_INT size) {
    int *array = createNewArray_int(size);
    int index;
    for (index = 0; index < size; index++) {
        array[index] = rand();
    }
    return array;
}

double* generateRandomArray_lf(U_INT size) {
    double *array = createNewArray_lf(size);
    int index;
    for (index = 0; index < size; index++) {
        array[index] = (double)rand() / 11.0;
    }
    return array;
}

float* generateRandomArray_f(U_INT size) {
    float *array = createNewArray_f(size);
    int index;
    for (index = 0; index < size; index++) {
        array[index] = (float)rand() / 11.0F;
    }
    return array;
}





void randomizeArray_int(int *array, U_INT size) {
    if (array == NULL) {
        fprintf(stderr, "NULL pointer: randomize impossible");
        exit(EXIT_FAILURE);
    }
    int index;
    for (index = 0; index < size; index++) {
        array[index] = rand(); 
    }
}
void randomizeArray_lf(double *array, U_INT size) {
        if (array == NULL) {
        fprintf(stderr, "NULL pointer: randomize impossible");
        exit(EXIT_FAILURE);
    }
    int index;
    for (index = 0; index < size; index++) {
        array[index] = (double)rand() / 11.0;
    }
}

void randomizeArray_f(float *array, U_INT size) {
        if (array == NULL) {
        fprintf(stderr, "NULL pointer: randomize impossible");
        exit(EXIT_FAILURE);
    }
    int index;
    for (index = 0; index < size; index++) {
        array[index] = (float)rand() / 11.0F;
    }
}




