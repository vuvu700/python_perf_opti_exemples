
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
          nbRepeat:int, nbSamples:int)->None:
    results = []
    for name, statement in statements.items():
        print(name, end=" ")
        samplesRun = timeit.timeit(statement, globals=globals(), number=nbSamples)
        nbLoopsPerRun = int(max((nbSecPerTest / (samplesRun/nbSamples) / nbRepeat), 1))
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

sizeArray = 5000
testSerie = numpy.random.random( (sizeArray, ) )
bench(listOfCalcs, nbSecPerTest=10, nbRepeat=20, nbSamples=10)



