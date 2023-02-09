#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

#define mSize 1024

float a[mSize][mSize], b[mSize][mSize], c[mSize][mSize];

void matrix_mult(a,b,c){
    //first loop steps through a in 8 value increments
    for (int i = 0; i < mSize; i += 8) {
        //second loop steps through b in 8 value increments
        for (int j = 0; j < mSize; j += 8) {
            //thrid loop increments row for a collum for b
            for (int k = 0; k < mSize; k++) {
                //load 8 values from a or b into one vector
                __m256 va = _mm256_loadu_ps(&a[i][k]);
                __m256 vb0 = _mm256_loadu_ps(&b[k][j]);
                __m256 vb1 = _mm256_loadu_ps(&b[k][j + 8]);
                for (int l = 0; l < 8; l++) {
                    //found this in an example pretty sure there is a better way to do this but it steps through the vectors and loads appropriate values into vc
                    __m256 vc = _mm256_loadu_ps(&c[i + l][j]);
                    vc = _mm256_fmadd_ps(va, vb0, vc);
                    _mm256_storeu_ps(&c[i + l][j], vc);
                    //not sure why example does two rows of b at a time
                    vc = _mm256_loadu_ps(&c[i + l][j + 8]);
                    vc = _mm256_fmadd_ps(va, vb1, vc);
                    _mm256_storeu_ps(&c[i + l][j + 8], vc);
                }
            }
        }
    }

}

int main() {
    //generates three matricies not entirely sure how rand works in c++ so take this with a grain of salt
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            a[i][j] = (float)rand() / RAND_MAX;
            b[i][j] = (float)rand() / RAND_MAX;
            c[i][j] = 0.0f;
        }
    }
    return 0;
}
