
from rolling_max import *
from typing import Callable
import timeit

# setup and test function

        
def testSameResults(listFuncs:"list[Callable[[numpy.ndarray, int], numpy.ndarray]]",
                    testArray:numpy.ndarray, nbPeriodes:int)->bool:
    
    for indexFunc in range(1, len(listFuncs)):
        func1 = listFuncs[indexFunc-1]
        func2 = listFuncs[indexFunc]
        if all(func1(testArray, nbPeriodes) != func2(testArray, nbPeriodes)):
            print(f"{func1} and {func2} didn't gave the same result")
            return False
        return True

def bench(statements:"dict[str, str]", nbSecPerTest:int,
          nbRepeat:int, nbSamples:int,
          sizeOfArray:int)->None:
    global testSerie # in order to randomize the array
    results = []
    for name, statement in statements.items():
        print(name, end=" ")
        samplesRun = timeit.timeit(statement, globals=globals(), number=nbSamples)
        nbLoopsPerRun = int(max((nbSecPerTest / (samplesRun/nbSamples) / nbRepeat), 1))
        testSerie = numpy.random.random((sizeOfArray, ))
        resRuns = timeit.repeat(statement, globals=globals(), repeat=nbRepeat, number=nbLoopsPerRun)
        resRuns = numpy.array(resRuns) / nbLoopsPerRun
        avg, std = numpy.average(resRuns), numpy.std(resRuns)
        print(f"{avg*1e6:_.2f} \u00b5s \u00b1 {std*1e6:_.2f} \u00b5s (mean \u00b1 stdDev, with {nbRepeat} runs, {nbLoopsPerRun} loop each run)")
        results.append([avg, name])
    sumResults = sum([t for t,_ in results])
    print(f"cum time={sumResults} sec")
    print("\n[avg time, % of cumtime, name]")
    res = sorted([[round(v, 6), round(100*v/sumResults, 2), name] for v, name in results])
    for line in res:
        print(line)



# test if all function give the same results
testSerie = numpy.random.random( (5000, ) )
allSeriesEqual = testSameResults([rollingMax1_py, rollingMax1_numba,
                 rollingMax2_py, rollingMax2_numba,
                 rollingMax3_py, rollingMax3_numba,
                 rollingMax4_py, rollingMax4_numba,
                 ], testSerie, 10
)
assert allSeriesEqual, "some series aren't equal"
print("all results are the same")




windowSize = 10
listOfCalcs = {
    "R1_py"    : f"rollingMax1_py(testSerie, {windowSize})",
    "R1_numba" : f"rollingMax1_numba(testSerie, {windowSize})",
    "R2_py"    : f"rollingMax2_py(testSerie, {windowSize})",
    "R2_numba" : f"rollingMax2_numba(testSerie, {windowSize})",
    "R3_py"    : f"rollingMax3_py(testSerie, {windowSize})",
    "R3_numba" : f"rollingMax3_numba(testSerie, {windowSize})",
    "R4_py"    : f"rollingMax4_py(testSerie, {windowSize})",
    "R4_numba" : f"rollingMax4_numba(testSerie, {windowSize})",
    "R5_py"    : f"rollingMax5_py(testSerie, {windowSize})",
    "R5_numba" : f"rollingMax5_numba(testSerie, {windowSize})",
}

bench(listOfCalcs, nbSecPerTest=10, nbRepeat=20, nbSamples=20, sizeOfArray=5000)

