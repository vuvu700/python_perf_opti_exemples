
import bench
from rolling_max import *
from typing import Callable

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

bench.bench(listOfCalcs, nbSecPerTest=10, nbRepeat=20, nbSamples=10)



