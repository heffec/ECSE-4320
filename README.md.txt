#Parallel Compression - Project 1

The objective of this assignment was to utilize multithreaded programming in order to efficiently compress large chunks of
data. Compression was accomplished through Facebook's open sourced ZSTD library.

## Installation and Environment

###GNU Compiler

###ZSTD Library
In your terminal send the following command:
```
sudo apt-get install libzstd-dev
```

##Compilation

###Build

The program can be compiled using `gcc` or `g++`
```
g++ -g zstd_compression.c -o a.out -Wall -Wextra -pthread -lzstd
```

###Execution

```
./a.out <num_of_threads> <compression_size>

##Code Description

##Testing

Testing consisted of the efficiency associated with the number of threads as well as the amount of data that needs to be
compressed.

##Performance Analysis

##Conclusion