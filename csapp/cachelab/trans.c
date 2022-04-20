/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void trans(int M, int N, int A[N][M], int B[M][N]);
void trans_32x32(int M, int N, int A[N][M], int B[M][N]);
void trans_4x4_block(int M, int N, int A[N][M], int B[M][N]);
void trans_64x64(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	if (M == 32 && N == 32) trans_32x32(M, N, A, B);
	else if (M == 64 && N == 64) trans_64x64(M, N, A, B);
	else trans(M, N, A, B);
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 
char trans_32x32_desc[] = "Transpose for 32 x 32 matrix";
void trans_32x32(int M, int N, int A[N][M], int B[M][N]) {
	const int bsize = 8;
	for (int ii = 0; ii < N; ii += bsize) {
		for (int jj = 0; jj < M; jj += bsize) {
			const int ilmt = ii + bsize;
			for (int i = ii; i < ilmt; ++i) {
				const int x0 = A[i][0 + jj];
				const int x1 = A[i][1 + jj];
				const int x2 = A[i][2 + jj];
				const int x3 = A[i][3 + jj];
				const int x4 = A[i][4 + jj];
				const int x5 = A[i][5 + jj];
				const int x6 = A[i][6 + jj];
				const int x7 = A[i][7 + jj];
				B[0 + jj][i] = x0;
				B[1 + jj][i] = x1;
				B[2 + jj][i] = x2;
				B[3 + jj][i] = x3;
				B[4 + jj][i] = x4;
				B[5 + jj][i] = x5;
				B[6 + jj][i] = x6;
				B[7 + jj][i] = x7;
			}
		}
	}
}

char trans_4x4_block_desc[] = "Transpose 4 x 4 blocks";
void trans_4x4_block(int M, int N, int A[N][M], int B[M][N]) {
	const int bsize = 4;
	for (int ii = 0; ii < N; ii += bsize) {
		for (int jj = 0; jj < M; jj += bsize) {
			const int ilmt = ii + bsize;
			for (int i = ii; i < ilmt; ++i) {
				const int x0 = A[i][0 + jj];
				const int x1 = A[i][1 + jj];
				const int x2 = A[i][2 + jj];
				const int x3 = A[i][3 + jj];
				B[0 + jj][i] = x0;
				B[1 + jj][i] = x1;
				B[2 + jj][i] = x2;
				B[3 + jj][i] = x3;
			}
		}
	}
}

char trans_64x64_desc[] = "Transpose for 64 x 64 matrix";
void trans_64x64(int M, int N, int A[N][M], int B[M][N]) {
	const int bsize = 8;
	for (int ii = 0; ii < N; ii += bsize) {
		for (int jj = 0; jj < M; jj += bsize) {
			// transpose 4 x 4 sub-matrix first
			for (int i = ii; i < ii + 4; ++i) {
				for (int j = jj; j < jj + 4; ++j) {
					B[j][i] = A[i][j];
				}
			}

			// store tmp
			int x0 = A[ii + 0][jj + 4];
			int x1 = A[ii + 1][jj + 4];
			int x2 = A[ii + 2][jj + 4];
			int x3 = A[ii + 3][jj + 4];
			int x4 = A[ii + 0][jj + 5];
			int x5 = A[ii + 1][jj + 5];
			int x6 = A[ii + 2][jj + 5];
			int x7 = A[ii + 3][jj + 5];

			// copy b data
			for (int j = jj + 6; j < jj + 8; ++j) {
				for (int i = ii; i < ii + 4; ++i) {
					B[j - 4][i + 4] = A[i][j];
				}
			}
			
			// 4 x 4 area d's half
			for (int j = jj + 4; j < jj + 6; ++j) {
				for (int i = ii + 4; i < ii + 8; ++i) {
					B[j][i] = A[i][j];
				}
			}

			// store tmp
			B[jj + 4][ii + 0] = x0;
			B[jj + 4][ii + 1] = x1;
			B[jj + 4][ii + 2] = x2;
			B[jj + 4][ii + 3] = x3;
			B[jj + 5][ii + 0] = x4;
			B[jj + 5][ii + 1] = x5;
			B[jj + 5][ii + 2] = x6;
			B[jj + 5][ii + 3] = x7;

			// data -> tmp
			x0 = B[jj + 2][ii + 4];
			x1 = B[jj + 2][ii + 5];
			x2 = B[jj + 2][ii + 6];
			x3 = B[jj + 2][ii + 7];
			x4 = B[jj + 3][ii + 4];
			x5 = B[jj + 3][ii + 5];
			x6 = B[jj + 3][ii + 6];
			x7 = B[jj + 3][ii + 7];

			// store tmp
			B[jj + 6][ii + 0] = x0;
			B[jj + 6][ii + 1] = x1;
			B[jj + 6][ii + 2] = x2;
			B[jj + 6][ii + 3] = x3;
			B[jj + 7][ii + 0] = x4;
			B[jj + 7][ii + 1] = x5;
			B[jj + 7][ii + 2] = x6;
			B[jj + 7][ii + 3] = x7;

			// 4 x 4 area d's another half
			for (int j = jj + 6; j < jj + 8; ++j) {
				for (int i = ii + 4; i < ii + 8; ++i) {
					B[j][i] = A[i][j];
				}
			}

			// copy area c directly
			for (int i = ii + 4; i < ii + 8; ++i) {
				for (int j = jj; j < jj + 4; ++j) {
					B[j][i] = A[i][j];
				}
			}
		}
	}
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

