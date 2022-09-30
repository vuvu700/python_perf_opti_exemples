#include "array.h"
/*
    warrning: the code might not be perfectly safe
*/

#define U_INT unsigned int



int* rolling_max_int(int array[], U_INT windowSize, U_INT size) {
    //int *array_result = createNewArray_int(size);
    int *array_result;

    int maxi;
    U_INT index, shiftIndex;
    for (index = 0; index < size-windowSize; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }
    
    U_INT deltaShift = 0;
    for (index = size-windowSize; index < size; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize-deltaShift; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }

    return array_result;
}


double* rolling_max_lf(double array[], U_INT windowSize, U_INT size) {
    //double *array_result = createNewArray_lf(size);
    double *array_result;

    double maxi;
    U_INT index, shiftIndex;
    for (index = 0; index < size-windowSize; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }
    
    U_INT deltaShift = 0;
    for (index = size-windowSize; index < size; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize-deltaShift; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }

    return array_result;
}

float* rolling_max_f(float array[], U_INT windowSize, U_INT size) {
    //float *array_result = createNewArray_f(size);
    float *array_result;

    int maxi;
    U_INT index, shiftIndex;
    for (index = 0; index < size-windowSize; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }
    
    U_INT deltaShift = 0;
    for (index = size-windowSize; index < size; index++) {
    
        maxi = array[index]; // calc the max of window-next elts 
        for (shiftIndex = 1; shiftIndex < windowSize-deltaShift; shiftIndex++) {
            if (maxi < array[index + shiftIndex]) {
                maxi = array[index + shiftIndex];
            }
        }
        //array_result[index] = maxi;
    }

    return array_result;
}