#include <x86intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define SHORT_SIZE 16
#define FLOAT_SIZE 8

/*
void SIMD_mult_float(const float *A, const float *B, float *C, int n)
{
    clock_t t = clock();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {}
                __m128 a = _mm_set1_ps(A[i][k]);
                __m128 b = _mm_loadu_ps(B[k] + j);
                res = _mm_add_ps(res, _mm_mul_ps(a, b));
            }
            _mm_storeu_ps(C[i] + j, res);
        }
    }

    t = clock()-t;
    printf("SIMD time of execution: (%f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
}
//*/
//*
void SIMD_mult_short(const short *A, const short *B, short *C, int n)
{
    //the problem is it does the right multiplication, but only for the first 16 columns
    __m256i a, b, c, d, sum;
    int chunks = n / SHORT_SIZE;
    int remainder = n%SHORT_SIZE;
    //remainder variable will add an extra 'chunk' if it's not equal to zero
    short sSum;
    clock_t t = clock();
    // Matrix multiplication with AVX2 instructions
    int index = 0;
    for (int i = 0; i < n; i++) {   //'i' represents each row of the matrix
        for (int h = 0; h < chunks; h ++) { //'h' represents each size-16 chunk that can fit in 1 row/column of the matrix
            sSum = 0;
            for (int j = 0; j < SHORT_SIZE; j++) {  //'j' represents each individual element in the matrix
                sum = _mm256_setzero_si256();
                // a = row, b = column
                a = _mm256_set_epi16(A[i*n+h*SHORT_SIZE+0], A[i*n+h*SHORT_SIZE+1],
                                      A[i*n+h*SHORT_SIZE+2], A[i*n+h*SHORT_SIZE+3],
                                      A[i*n+h*SHORT_SIZE+4], A[i*n+h*SHORT_SIZE+5],
                                      A[i*n+h*SHORT_SIZE+6], A[i*n+h*SHORT_SIZE+7],
                                      A[i*n+h*SHORT_SIZE+8], A[i*n+h*SHORT_SIZE+9],
                                      A[i*n+h*SHORT_SIZE+10], A[i*n+h*SHORT_SIZE+11],
                                      A[i*n+h*SHORT_SIZE+12], A[i*n+h*SHORT_SIZE+13],
                                      A[i*n+h*SHORT_SIZE+14], A[i*n+h*SHORT_SIZE+15]);
                b = _mm256_set_epi16(B[0*n+n*h+j], B[1*n+n*h+j],
                                      B[2*n+n*h+j], B[3*n+n*h+j],
                                      B[4*n+n*h+j], B[5*n+n*h+j],
                                      B[6*n+n*h+j], B[7*n+n*h+j],
                                      B[8*n+n*h+j], B[9*n+n*h+j],
                                      B[10*n+n*h+j], B[11*n+n*h+j],
                                      B[12*n+n*h+j], B[13*n+n*h+j],
                                      B[14*n+n*h+j], B[15*n+n*h+j]);
                c = _mm256_add_epi32(_mm256_mulhi_epi16(a, b), _mm256_mullo_epi16(a, b)); 

                sum += _mm256_add_epi32(sum, c);
                C[i*n+j] += _mm256_extract_epi16(sum, 15)+ _mm256_extract_epi16(sum, 14)+ _mm256_extract_epi16(sum, 13)+ _mm256_extract_epi16(sum, 12)+ _mm256_extract_epi16(sum, 11)+ _mm256_extract_epi16(sum, 10)+ _mm256_extract_epi16(sum, 9)+ _mm256_extract_epi16(sum, 8)+ _mm256_extract_epi16(sum, 7)+ _mm256_extract_epi16(sum, 6)+ _mm256_extract_epi16(sum, 5)+ _mm256_extract_epi16(sum, 4)+ _mm256_extract_epi16(sum, 3)+ _mm256_extract_epi16(sum, 2)+ _mm256_extract_epi16(sum, 1)+ _mm256_extract_epi16(sum, 0);
            }
        }
    }
    t = clock()-t;
    printf("SIMD time of execution: (%f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
}
//*/

void trivial_mult_short(const short *A, const short *B, short *C, int n) {
    clock_t t = clock();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i*n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];
            }
        }
    }
    t = clock()-t;
    printf("SIMD time of execution: (%f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
}
void trivial_mult_float(const float *A, const float *B, float *C, int n) {
    clock_t t = clock();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i*n + j] = 0;
            for (int k = 0; k < n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];
            }
        }
    }
    t = clock()-t;
    printf("SIMD time of execution: (%f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int chunks, remainder;
    if (argv[2][0] == 'f') {
        //implementing th float should be the same as implementing the short
        //just reevaluating the size of register contents
    }
    else if (argv[2][0] == 's') {
        //2D array represented as a 1D array
        short *A = (short *)malloc(n * n * sizeof(short));
        short *B = (short *)malloc(n * n * sizeof(short));
        short *C = (short *)malloc(n * n * sizeof(short));
        short *D = (short *)malloc(n * n * sizeof(short));

        //assigning values to the matrices to be multiplied
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i*n+j] = 1;//(short)rand();
                B[i*n+j] = 1;//(short)rand();
            }
        }
        //prints the contents of the arrays, easy since I'm only inputting arrays of size 16/32 at the moment
        //__________________________________________________
        printf("A\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", A[i*n+j]);
            }
            printf("\n");
        }
        printf("\nB\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", B[i*n+j]);
            }
            printf("\n");
        }
        //__________________________________________________


        SIMD_mult_short(A, B, C, n);
        printf("\nC\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", C[i*n+j]);
            }
            printf("\n");
        }

    }
    return 0;
}
