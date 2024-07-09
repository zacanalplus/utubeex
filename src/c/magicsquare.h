//
// magicsquare.h
// Created by Burmese Coder on 2/9/24.

#include <stdlib.h>

#ifndef _magicsquare_h_
#define _magicsquare_h_

#define swapi(x, y) { register int tmp = x; x = y; y = tmp; }

#ifndef __GEN_MAX__
#define __GEN_MAX__ 
int max(int x, int y);
int min(int x, int y);
#endif

enum neighborhood { OUT_OF_RANGE = -1, NOT_ADJACENT = 0, ADJACENT = 1, SAME_ROW=10, SAME_COL, 
					DIAGONAL_UP=20, DIAGONAL_DOWN, SAMECELL = 100};

/* pseudo random generator from K & R C */
int pseudo_random();
/* pseudo random seed from K & R C */
void seedrand(unsigned long int seed);
/* pseudo random generator with range 0-(limit-1) */
int pseudo_random_floor(int limit);
/* pseudo random generator withing range x-y if x < y, y-x if y < x */
int pseudo_random_range(int x, int y);
/* shuffle array content */
int *shuffle(int list[], size_t len);
/* input numbers from std input */
int inputsquare(int *square, size_t length);
/* debug print for matrix square */
void printsquare(int *square, size_t length);
/* Check the matrix is magic square (start number 1) or not */
int check_magic(int *square, size_t length, int center);
/* flat arry generator */
int *flatmatrix(size_t length);
/* get a (pseudo) matrix square */
int *newsquare(int *square, size_t length);
/* check the neighbor cell or not in the scheme of matrix. 
	it can check horizontal and vertical neighbor. 
	*/
enum neighborhood neighbor(const int *square, size_t length, int fidx, int sidx);
/* 	it can check both first index (fidx) and second index(sidx)
		are on same row or same column. 
		TODO: checking for on the same downward diagonal or upward diagonal
	*/
enum neighborhood relativepos(const int *square, size_t length, int fidx, int sidx);

/* intelligent shuffle array content */
int *ishuffle(int list[], size_t len, size_t sidelen);
/* distant numbers check
	impossible to place number like 1 2 3 4 on same row or column
	and diagonal (as well as 16 15 14 13) for 4x4 square. 
*/
int distant_numbers(int list[], size_t len, size_t sidelen, int idx1, int idx2);

/* calculate magic sum based on length of square */
size_t magicsum(size_t length);

/* initialize magic square with 0 to check free cell in it */
int init(int *square, size_t length);

/* calculate row sum and column sum of cell */
size_t rcsum(int *square, size_t length, int idx, size_t rc);

/* find the number 'num' in the matrix square */
int find(int *square, size_t length, int num);

/* debugging functons */
/* if it is NOT magic square, print anomalies */
void print_anomalies();

/* i section */
/* check row and column before inserting the number in square[r, c] */
int check_rc(int *square, size_t length, size_t r, size_t c, size_t msum);

/* check the 'val' is not fit in square[r, c] or not */
int notfit(int *square, size_t length, size_t r, size_t c, int val, size_t msum);

/* computing the new square instead of randon fill like 'newsquare' function */
int *compsquare(int *square, size_t length);

#endif