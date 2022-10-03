CC=gcc  #compiler
LDLIBS= -lm  #libs 
CFLAGS= -Wall
OPTFLAGS= -O3 # optimisation flags

ALL: bench_rolling_max	


bench_rolling_max : bench_rolling_max.c array.c rolling_max.c bench.c
	$(CC) $(CFLAGS) $(OPTFLAGS)  bench_rolling_max.c array.c rolling_max.c bench.c    -o bench_rolling_max.out $(LDLIBS)





.PHONY: clean dep
clean:
	rm -f bench_rolling_max.out

dep:
	gcc -MM *.c
