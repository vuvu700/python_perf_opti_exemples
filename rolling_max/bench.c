#include <math.h>
#include <stdlib.h>
#include "array.h"


#ifdef __unix__
    #include <sys/time.h>
    #include <sys/resource.h>

    double perf_counter() {
        struct timeval t, tzp;
        gettimeofday(&t, &tzp);
        return t.tv_sec + t.tv_usec*1e-6;
    }
#else
    #include <windows.h>
    double perf_counter() {
        LARGE_INTEGER t, f;
        QueryPerformanceCounter(&t);
        QueryPerformanceFrequency(&f);
        return (double)t.QuadPart/(double)f.QuadPart;
    }
#endif

#define U_INT unsigned int





double _average(double array[], U_INT size) {
    double average = 0.;
    U_INT index;
    for (index = 0; index < size; index++) {
        average += array[index];
    }
    return average / (double)size;
}

double _stdDev(double array[], U_INT size) {
    double average = _average(array, size);
    double standardDeviation = 0.;

    U_INT index;
    for (index = 0; index < size; index++) {
        standardDeviation += pow(array[index] - average, 2.0);
    }
    return sqrt(standardDeviation / (double)size);
}








double* bench_int( int* (*funcToBench)(int *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    int *array_test = generateRandomArray_int(sizeOfArray);
    int *array_func_out;

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        array_func_out = funcToBench(array_test, window, sizeOfArray);
        sumTimeElapsed += perf_counter() - t_start;
        free(array_func_out);
    }

    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }


    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_int(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            array_func_out = funcToBench(array_test, window, sizeOfArray);
            sumTimeElapsed += perf_counter() - t_start;
            free(array_func_out);
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}


double* bench_lf( double* (*funcToBench)(double *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    double *array_test = generateRandomArray_lf(sizeOfArray);
    double *array_func_out;

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        array_func_out = funcToBench(array_test, window, sizeOfArray);
        sumTimeElapsed += perf_counter() - t_start;
        free(array_func_out);
    }
    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }

    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_lf(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            array_func_out = funcToBench(array_test, window, sizeOfArray);
            sumTimeElapsed += perf_counter() - t_start;
            free(array_func_out);
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}



double* bench_f( float* (*funcToBench)(float *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    float *array_test = generateRandomArray_f(sizeOfArray);
    float *array_func_out;

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        array_func_out = funcToBench(array_test, window, sizeOfArray);
        sumTimeElapsed += perf_counter() - t_start;
        free(array_func_out);
    }
    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }

    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_f(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            array_func_out = funcToBench(array_test, window, sizeOfArray);
            sumTimeElapsed += perf_counter() - t_start;
            free(array_func_out);
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}
















double* bench_ip_int( void (*funcToBench)(int *array, U_INT window, U_INT size, int *array_out), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    int *array_test = generateRandomArray_int(sizeOfArray);
    int *array_func_out = createNewArray_int(sizeOfArray);

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        funcToBench(array_test, window, sizeOfArray, array_func_out);
        sumTimeElapsed += perf_counter() - t_start;
    }

    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }


    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_int(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            funcToBench(array_test, window, sizeOfArray, array_func_out);
            sumTimeElapsed += perf_counter() - t_start;
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}


double* bench_ip_lf( void (*funcToBench)(double *array, U_INT window, U_INT size, double *array_out), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    double *array_test = generateRandomArray_lf(sizeOfArray);
    double *array_func_out = createNewArray_lf(sizeOfArray);

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        funcToBench(array_test, window, sizeOfArray, array_func_out);
        sumTimeElapsed += perf_counter() - t_start;
    }
    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }

    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_lf(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            funcToBench(array_test, window, sizeOfArray, array_func_out);
            sumTimeElapsed += perf_counter() - t_start;
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}



double* bench_ip_f( void (*funcToBench)(float *array, U_INT window, U_INT size, float *array_out), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun) {
    U_INT index;
    float *array_test = generateRandomArray_f(sizeOfArray);
    float *array_func_out = createNewArray_f(sizeOfArray);

    // run the sampling to estimate how much loops to do every run
    double sumTimeElapsed = 0.;
    double t_start;
    for (index = 0; index < nbSamples; index++) {
        t_start = perf_counter();
        funcToBench(array_test, window, sizeOfArray, array_func_out);
        sumTimeElapsed += perf_counter() - t_start;
    }
    int nbLoops = (int)(benchDuration / (sumTimeElapsed/(double)nbSamples) / nbRuns);
    if (nbLoops <= 0) {nbLoops = 1;}
    if (nbLoopPerRun != NULL) {
        *(nbLoopPerRun) = (U_INT)nbLoops;
    }

    // do the complet bench
    U_INT runCount;
    double *average_SumTimeElapsed_perRuns = createNewArray_lf(nbRuns);
    for (runCount = 0; runCount < nbRuns; runCount++) {

        // each run
        randomizeArray_f(array_test, sizeOfArray); // different array for each run
        sumTimeElapsed = 0.;
        for (index = 0; index < nbLoops; index++) {
            t_start = perf_counter();
            funcToBench(array_test, window, sizeOfArray, array_func_out);
            sumTimeElapsed += perf_counter() - t_start;
        }
        average_SumTimeElapsed_perRuns[runCount] = sumTimeElapsed / (double)nbLoops;
    }
    
    free(array_test);
    return average_SumTimeElapsed_perRuns;
}