import numpy
import numba
import timeit

# setup and test function
testSerie = numpy.random.random( (5000, ) )

def testSameResults(listFuncs:"list[Callable[[numpy.ndarray, int], numpy.ndarray]]",
                    testArray:numpy.ndarray, nbPeriodes:int)->bool:
    
    for indexFunc in range(1, len(listFuncs)):
        func1 = listFuncs[indexFunc-1]
        func2 = listFuncs[indexFunc]
        if all(func1(testArray, nbPeriodes) != func2(testArray, nbPeriodes)):
            print(f"{func1} and {func2} didn't gave the same result")
            return False
        return True

def bench(listSatements:"list[str]", nbSecPerTest:int, nbRepeat:int, nbSamples:int)->None:
    results = []
    for name, statement in listOfCalcs.items():
        print(name, end=" ")
        samplesRun = timeit.timeit(statement, globals=globals(), number=nbSamples)
        nbLoopsPerRun = int(max((nbSecPerTest / (samplesRun/nbSamples) / nbRepeat), 1))
        resRuns = timeit.repeat(statement, globals=globals(), repeat=nbRepeat, number=nbLoopsPerRun)
        resRuns = numpy.array(resRuns) / nbLoopsPerRun
        avg, std = numpy.average(resRuns), numpy.std(resRuns)
        print(f"{avg*1e6:_.2f} \u00b5s \u00b1 {std*1e6:_.2f} \u00b5s (mean \u00b1 stdDev, with {nbRepeat} runs, {nbLoopsPerRun} loop each run)")
        results.append([avg, name])
    sumResults = sum([t for t,name in results])
    print(f"cum time={sumResults} sec")
    print("\n[avg time, % of cumtime, name]")
    res = sorted([[round(v, 6), round(100*v/sumResults, 2), name] for v, name in results])
    for line in res:
        print(line)



########### python funcs
def rollingMax_py(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = numpy.empty(array.shape)
    
    for index in range(0, array.size - nbPeriodes):
        maxi = array[index]
        for shiftIndex in range(1, nbPeriodes):
            if maxi < array[index + shiftIndex]:
                maxi = array[index + shiftIndex]
        maximum_serie[index] = maxi
        
    deltaShift = 0
    for index in range(array.size - nbPeriodes, array.size):
        maxi = array[index]
        for shiftIndex in range(1, nbPeriodes - deltaShift):
            if maxi < array[index + shiftIndex]:
                maxi = array[index + shiftIndex]
        maximum_serie[index] = maxi
        deltaShift += 1
    
    return maximum_serie







def rollingMax2_py(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for shiftIndex in range(1, nbPeriodes):
        for index in range(0, array.size - shiftIndex):
            maximum_serie[index] = max(maximum_serie[index], array[index + shiftIndex])
            
    return maximum_serie







def rollingMax3_py(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for shiftIndex in range(1, nbPeriodes):
        numpy.maximum(maximum_serie[: -shiftIndex], array[shiftIndex: ],
                      out=maximum_serie[: -shiftIndex])
        
    return maximum_serie







def rollingMax4_py(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for index in range(0, array.size):
        maximum_serie[index] = numpy.max(array[index: index + nbPeriodes])
        
    return maximum_serie

########### 




########### numba funcs

@numba.jit((numba.float64[:], numba.int64), nopython=True, nogil=True)
def rollingMax_numba(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = numpy.empty(array.shape)
    
    for index in range(0, array.size - nbPeriodes):
        maxi = array[index]
        for shiftIndex in range(1, nbPeriodes):
            if maxi < array[index + shiftIndex]:
                maxi = array[index + shiftIndex]
        maximum_serie[index] = maxi
        
    deltaShift = 0
    for index in range(array.size - nbPeriodes, array.size):
        maxi = array[index]
        for shiftIndex in range(1, nbPeriodes - deltaShift):
            if maxi < array[index + shiftIndex]:
                maxi = array[index + shiftIndex]
        maximum_serie[index] = maxi
        deltaShift += 1
    
    return maximum_serie


@numba.jit((numba.float64[:], numba.int64), nopython=True, nogil=True)
def rollingMax2_numba(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for shiftIndex in range(1, nbPeriodes):
        for index in range(0, array.size - shiftIndex):
            maximum_serie[index] = max(maximum_serie[index], array[index + shiftIndex])
            
    return maximum_serie


@numba.jit((numba.float64[:], numba.int64), nopython=True, nogil=True)
def rollingMax3_numba(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for shiftIndex in range(1, nbPeriodes):
        maximum_serie[: -shiftIndex] = numpy.maximum(maximum_serie[: -shiftIndex], array[shiftIndex: ])
        
    return maximum_serie


@numba.jit((numba.float64[:], numba.int64), nopython=True, nogil=True)
def rollingMax4_numba(array:numpy.ndarray, nbPeriodes:int)->numpy.ndarray:
    maximum_serie = array.copy()
    
    for index in range(0, array.size):
        maximum_serie[index] = numpy.max(array[index: index + nbPeriodes])
        
    return maximum_serie
###########




allSeriesEqual = testSameResults([rollingMax_py, rollingMax_numba,
                 rollingMax2_py, rollingMax2_numba,
                 rollingMax3_py, rollingMax3_numba,
                 rollingMax4_py, rollingMax4_numba,
                 ], testSerie, 10
)
assert allSeriesEqual, "some series aren't equal"
print("all results are the same")

listOfCalcs = {
    "R1_py" : "rollingMax_py(testSerie, 10)",
    "R1_numba" : "rollingMax_numba(testSerie, 10)",
    "R2_py" : "rollingMax2_py(testSerie, 10)",
    "R2_numba" : "rollingMax2_numba(testSerie, 10)",
    "R3_py" : "rollingMax3_py(testSerie, 10)",
    "R3_numba" : "rollingMax3_numba(testSerie, 10)",
    "R4_py" : "rollingMax4_py(testSerie, 10)",
    "R4_numba" : "rollingMax4_numba(testSerie, 10)",
}

bench(listOfCalcs, nbSecPerTest=10, nbRepeat=20, nbSamples=10)



