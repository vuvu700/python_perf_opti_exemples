import numpy
import timeit
import time 
from typing import Callable





def bench(statements:"dict[str, str]", nbSecPerTest:int, nbRepeat:int, nbSamples:int)->None:
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



def bench2(statements:"dict[str, str]", nbSecPerTest:int, nbRepeat:int, nbSamples:int)->None:
    results = []
    for name, statement in statements.items():
        print(name, end=" ")
        # samplesRun = timeit.timeit(statement, globals=globals(), number=nbSamples)
        samplesRun = _bench(statement, nbSamples)
        nbLoopsPerRun = int(max((nbSecPerTest / (samplesRun/nbSamples) / nbRepeat), 1))
        #resRuns = timeit.repeat(statement, globals=globals(), repeat=nbRepeat, number=nbLoopsPerRun)
        resRuns = [_bench(statement, nbLoopsPerRun) for _ in range(nbRepeat)]
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

def _bench(statement:str, nbLoops:int)->float:
    perf_counter:"Callable[[], float]" = time.perf_counter
    sumTimeElapsed = 0.
    for _ in range(nbLoops):
        t_start = perf_counter()
        eval(statement)
        sumTimeElapsed += perf_counter() - t_start
    return sumTimeElapsed