# Parallel Compression - Project 1

The objective of this assignment was to utilize multithreaded programming in order to efficiently compress large chunks of
data. Compression was accomplished through Facebook's open sourced ZSTD library.

## Installation and Environment

### GNU Compiler

### ZSTD Library
In your terminal send the following command:
```
sudo apt-get install libzstd-dev
```

## Compilation

### Build

The program can be compiled using `gcc` or `g++`
```
g++ -g zstd_compression.c -o a.out -Wall -Wextra -pthread -lzstd
```
```
INSERT YOUR "gcc" COMPILATION HERE
```

### Execution

```
./a.out <num_of_threads> <compression_size>
```

## Code Description

## Testing and Analysis

Testing consisted of the efficiency associated with the number of threads as well as the amount of data that needs to be
compressed.

| Filename	| Size(KB)	| # Threads	| Compression Time(s)	|
|---------------|---------------|---------------|-----------------------|
| wot.txt	| 24400         | 4          	| 0.26367	        |
| 		|	        | 8          	| 0.25668	        |
| 		|	        | 12          	| 0.25221	        |
| 		|	        | 16          	| 0.25556	        |
| 		|	        | 20          	| 0.25016	        |
| LI_short.txt	| 103228        | 4          	| 0.06994	        |
| 		|	        | 8          	| 0.07415	        |
| 		|	        | 12          	| 0.06342	        |
| 		|	        | 16          	| 0.06187	        |
| 		|	        | 20          	| 0.06369	        |
| LI_long.txt	| 619366        | 4          	| 0.32485	        |
| 		|	        | 8          	| 0.33599	        |
| 		|	        | 12          	| 0.35398	        |
| 		|	        | 16          	| 0.37728	        |
| 		|	        | 20          	| 0.33719	        |


## Conclusion

