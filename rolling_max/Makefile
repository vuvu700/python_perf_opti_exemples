ALL: bench_rolling_max	

O2 : bench_rolling_max.c array.c rolling_max.c bench.c
	gcc -Wall -O2   bench_rolling_max.c array.c rolling_max.c bench.c    -o bench_rolling_max.out

O0 : bench_rolling_max.c array.c rolling_max.c bench.c
	gcc -Wall -O0   bench_rolling_max.c array.c rolling_max.c bench.c    -o bench_rolling_max.out

bench_rolling_max : bench_rolling_max.c array.c rolling_max.c bench.c
	gcc -Wall -O3   bench_rolling_max.c array.c rolling_max.c bench.c    -o bench_rolling_max.out





.PHONY: clean dep
clean:
	rm -f bench_rolling_max.out

dep:
	gcc -MM *.c
