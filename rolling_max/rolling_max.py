import numpy
import numba


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