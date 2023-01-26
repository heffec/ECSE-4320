for best results use gcc

gcc -o <program name> zstd_compression.c -lzstd -pthread

ensure that common.h is in the directory with zstd_compression.c

ensure that you have libzstd-dev installed

run with ./<program name> <# desired threads> <# desired level of compression (5 was used when testing)> <path to file to be compressed>

will out put file in the directory it is currently stored in and will output the time elapsed in the console