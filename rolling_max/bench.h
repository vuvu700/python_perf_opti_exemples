#ifndef BENCH_H
#define BENCH_H

#include "array.h"

#ifndef U_INT
#define U_INT unsigned int
#endif /* U_INT */


// return a clock time with 1e-6 precision
double perf_counter();

// compute the average of an array
double _average(double array[], U_INT size);
// compute the standard deviation of an array
double _stdDev(double array[], U_INT size) ;


/// @brief 
/// @param funcToBench the function that will be benched
/// @param benchDuration the aproximative duration of the total bench
/// @param nbRuns the number of bench run to do (the array will be randomized each time)
/// @param nbSamples the number of unique run, in order to determinate the number of loops per bench run
/// @param window the size of the window used in the benchmark
/// @param sizeOfArray the size of the test array generated
/// @param nbLoopPerRun is a pointer to get the number of loops per run (if NULL given, ignore) 
/// @return return the average time of each run
double* bench_int( int* (*funcToBench)(int *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun);

/// @brief 
/// @param funcToBench the function that will be benched
/// @param benchDuration the aproximative duration of the total bench
/// @param nbRuns the number of bench run to do (the array will be randomized each time)
/// @param nbSamples the number of unique run, in order to determinate the number of loops per bench run
/// @param window the size of the window used in the benchmark
/// @param sizeOfArray the size of the test array generated
/// @param nbLoopPerRun is a pointer to get the number of loops per run (if NULL given, ignore) 
/// @return return the average time of each run
double* bench_lf( double* (*funcToBench)(double *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun);

/// @brief 
/// @param funcToBench the function that will be benched
/// @param benchDuration the aproximative duration of the total bench
/// @param nbRuns the number of bench run to do (the array will be randomized each time)
/// @param nbSamples the number of unique run, in order to determinate the number of loops per bench run
/// @param window the size of the window used in the benchmark
/// @param sizeOfArray the size of the test array generated
/// @param nbLoopPerRun is a pointer to get the number of loops per run (if NULL given, ignore) 
/// @return return the average time of each run
double* bench_f( float* (*funcToBench)(float *array, U_INT window, U_INT size), double benchDuration, U_INT nbRuns, U_INT nbSamples, U_INT window, U_INT sizeOfArray, U_INT *nbLoopPerRun);


#endif /* BENCH_H */