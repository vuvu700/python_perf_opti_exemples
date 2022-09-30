# how to perfome the bechmarks ?
C version :
```
$ make
$ ./bench_rolling_max.out   (if on linux)
$ bench_rolling_max.out     (if on window)
```
py version : (ps: you need numba)
```
$ python bench_rollingMax.py
```

# how to tune the bench ?
if you dont whant to tune the benchmarks yoursel, they are alredy tuned to :
- ~10sec / bench (20 runs , the number of loop for each run is estimated with 100 func calls for callibration)
- the array is 5000 elements long
- the rolling window is 10 long

for the python version : the parameters ar at line 58 and 72<br>
for the C version : the parameters ar at line 16 to 23<br>

