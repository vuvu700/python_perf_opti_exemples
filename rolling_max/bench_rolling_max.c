#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "rolling_max.h"
#include "bench.h"

#ifndef u_int
#define u_int unsigned int
#endif /* u_int */
 

int main(void) {
    double t_start = perf_counter();

    
    // bench setup 
    double timePerBench = 10.0; // sec
    u_int nbRuns = 20, nbSamples = 100;
    u_int nbLoopPerRun;
    double *results_run;
    
    // parameters of arrays    
    u_int sizeOfArrays = 50000, windowSize = 10; // sizeOfArrays have to be greater than windowSize
    

    // actual benchs
    printf("bench_int : ");
    results_run = bench_int(rolling_max_int,  timePerBench, nbRuns, nbSamples,   windowSize, sizeOfArrays, &(nbLoopPerRun));
    printf("rolling_max_int : mean=%lf us (sd=%lf us), for %u runs with %u loops per run\n",
                     _average(results_run, nbRuns)*1e6,
                     _stdDev(results_run, nbRuns)*1e6,
                     nbRuns, nbLoopPerRun);

    printf("bench_lf : ");
    results_run = bench_lf(rolling_max_lf,  timePerBench, nbRuns, nbSamples,   windowSize, sizeOfArrays, &(nbLoopPerRun));
    printf("rolling_max_lf : mean=%lf us (sd=%lf us), for %u runs with %u loops per run\n",
                     _average(results_run, nbRuns)*1e6,
                     _stdDev(results_run, nbRuns)*1e6,
                     nbRuns, nbLoopPerRun);

    printf("bench_f : ");
    results_run = bench_f(rolling_max_f,  timePerBench, nbRuns, nbSamples,   windowSize, sizeOfArrays, &(nbLoopPerRun));
    printf("rolling_max_f : mean=%lf us (sd=%lf us), for %u runs with %u loops per run\n",
                     _average(results_run, nbRuns)*1e6,
                     _stdDev(results_run, nbRuns)*1e6,
                     nbRuns, nbLoopPerRun);

    double t_elapsed = perf_counter() - t_start;
    printf("done in %lf sec\n", t_elapsed);
}