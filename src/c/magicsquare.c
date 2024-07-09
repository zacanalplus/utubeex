//
// magicsquare.c
// Created by Burmese Coder on 2/9/24.

#include <stdio.h>
#include "magicsquare.h"

unsigned long int next = 1331;

enum rc { ROW, COL };
enum {NOTEMPTY = -11, OVEREXCESS = -1, NOTFIT = 0};

struct anomalies{
	int mid;
	int r;
	int c;
	int rsum;
	int csum;
	int digsum_d;
	int digsum_u;
}anom = {0, 0, 0, 0, 0, 0, 0};

int pseudo_random(){
	next = next * 1103515245 + 12345;
	return (unsigned int) (next / 65536) % 32768;
}

int pseudo_random_floor(int limit){
	return pseudo_random() % limit;
}

int pseudo_random_range(int x, int y){
	return (x > y ? (pseudo_random() % x) + y : (pseudo_random() % y) + x);
}

void seedrand(unsigned long int seed){
	next = seed;
}

int *shuffle(int list[], size_t len){
	if(list == NULL || len < 1)
		return 0;
	for(register int i = 0; i < len; i++){
		register int idx = pseudo_random_floor(len);
		int tmp = list[i];
		list[i] = list[idx];
		list[idx] = tmp;
	}
	return list;
}

void printsquare(int *square, size_t length){
	if(length < 1 || square == NULL)
		return;
	for(int i=0; i<length; i++){
		for(int j=0; j<length; j++){
			printf("%d ", square[i * length + j]);
		}
		printf("\n");
	}
	printf("-----\n");
}

int inputsquare(int *square, size_t length){
	int cc = 0;
	for(int r=0; r < length; r++)
		for(int c=0; c < length; c++){
			int idata;
			cc += scanf("%d", &idata);
			/* -1 input from keyboard to stop reading stdin or redirected input */
			if(idata == -1)
				return idata;
			square[r * length + c] = idata;
		}
	return cc;
}

int check_magic(int *square, size_t length, int center){
	int key_sum;
	int col_sum = 0, row_sum = 0;
	if((length < 1) || (square == NULL))
		return 0;
	int arrmid = (length * length) / 2;
	/* the (even) size of the square divided by 2 multiplied by the lowest plus the highest number:
	for example 4x4 magic square, 4 / 2 x (1 + 16) = 34. */
	if((length & 1) == 0){
		key_sum = (length / 2) * (1 + (length * length));
	}
	/* For each pure magic square you can calculate the magic sum. 
	The magic sum is [(1 + n x n) / 2] x n. 
	For example the sum of the 3x3 magic square is: 
	[(1 + 3 x 3) / 2) x 3 = 15. */
	else{
		key_sum = ((1 + length * length) / 2) * length;
		if(center == 1){
			if(square[arrmid] != (arrmid + 1)){
				anom.mid = arrmid + 1;
				anom.c = arrmid;
				return 0;
			}
		}
	}
	for(register int i=0; i<length; i++){
		int chk_j;
		for(register int j=0; j<length; j++){
			chk_j = j;
			col_sum+=square[i * length + j]; /* column sum of matrix */
			row_sum+=square[j * length + i]; /* row sum of matrix */
		}
		if(col_sum != key_sum || row_sum != key_sum){
			anom.r = i;
			anom.c = chk_j;
			anom.csum = key_sum - col_sum;
			anom.rsum = key_sum - row_sum;
			return 0;
		}
		col_sum = row_sum = 0;
	}
	/* First check is left to right (up to down) diagonal check. 
	Second line is left to right (down to up) diagonal check. */
	for(register int i = 0; i < length; i++){
		row_sum += square[i * (length-1) + i]; /*[0][0], [1][1], [2][2],..*/
		col_sum += square[(length - 1 - i) * length  + i]; /* [2][0], [1][1], [0][2] */
	}
	if(col_sum == key_sum && row_sum == key_sum)
		return 1;/* now it is magic square */
	if(row_sum != key_sum){
		anom.r=0;
		anom.c=0;
		anom.digsum_d = key_sum - row_sum;
	}
	if(col_sum != key_sum){
		anom.r=length-1;
		anom.c=0;
		anom.digsum_u = key_sum - col_sum;
	}
	return 0;
}

int *flatmatrix(size_t length){
	int max = length * length;
	int *flat = (int*) malloc (sizeof(int) * max);
	for(register int i = 0; i < max; i++){
		flat[i] = i + 1;
	}
	shuffle(flat, length);
	return flat;
}

int *newsquare(int *square, size_t length){
	if(length < 1 || square == NULL)
		return NULL;
	int *flat = flatmatrix(length);
	int max = length * length;
	for(register int i = 0; i < max; i++){
		square[i] = flat[i];
	}
	/* release flatmatrix function allocated number array. */
	free(flat);
	return square;
}

size_t magicsum(size_t length){
	/* the (even) size of the square divided by 2 multiplied by the lowest plus the highest number:
	for example 4x4 magic square, 4 / 2 x (1 + 16) = 34. */
	if((length & 1) == 0){
		return (length / 2) * (1 + (length * length));
	}
	/* For each pure magic square you can calculate the magic sum. 
	The magic sum is [(1 + n x n) / 2] x n. 
	For example the sum of the 3x3 magic square is: 
	[(1 + 3 x 3) / 2) x 3 = 15. */
	else{
		return ((1 + length * length) / 2) * length;
	}
}

int init(int *square, size_t length){
	if(length < 1 || square == NULL)
		return -1;
	int len = length * length;
	for(register int i = 0; i < len; i++){
		square[i] = 0;
	}
	return 0;
}

int check_rc(int *square, size_t length, size_t r, size_t c, size_t msum){
	int rowsum = 0, colsum =0, zinc = 0, zinr = 0;
	for(int i = 0; i < length; i++){
		int rindx = r * length + i;
		int cindx = i * length + c;
		if(!square[rindx])
			zinr++;
		if(!square[cindx])
			zinc++;
		rowsum += square[rindx];
		colsum += square[cindx];
	}
	if((rowsum < msum) && (colsum < msum))
		return 1;
	else if(rowsum == msum && !zinr)
		return 1; /* half true */
	else if(colsum == msum && !zinc)
		return 1; /* half true */
	return 0;
}

size_t rcsum(int *square, size_t length, int idx, size_t rc){
	if(rc > 1u)
		return 0;
	int rowsum = 0, colsum =0;
	for(int i = 0; i < length; i++){
		if(rc == COL){
			colsum += square[idx * length + i];
		}
		else{
			rowsum += square[i * length + idx];
		}
	}
	if(rc == COL)
		return colsum;
	else
		return rowsum;
}

int notfit(int *square, size_t length, size_t r, size_t c, int val, size_t msum){
	int idx = r * length + c;
	/* if cell is not free, not fit */
	if(square[idx])
		return NOTEMPTY;
	int rowsum = rcsum(square, length, r, ROW);
	int colsum = rcsum(square, length, c, COL);
	if(rowsum + val > msum){
		int dif = msum - rowsum;
		return (dif > 0 ? dif : OVEREXCESS); 
	}
	if(colsum + val > msum){
		int dif = msum - colsum;
		return (dif > 0 ? dif : OVEREXCESS);
	}
	return NOTFIT; /* 'val' is fit in square[r, c] */
}

/* find specific number 'num' in the square array */
int find(int *square, size_t length, int num){
	int len = length * length;
	for(int i = 0; i<len; i++){
		if(square[i] == num)
			return 1;
	}
	return 0;
}

int *compsquare(int *square, size_t length){
	if(length < 1 || square == NULL)
		return NULL;
	init(square, length);
	int len = length * length;
	size_t msum = magicsum(length);
	for(register int r=0; r<length; r++){
		for(register int c=0; c<length; c++){
			int num = pseudo_random_floor(len);
			int rcidx = r * length + c;
			while(check_rc(square, length, r, c, msum) == 0 || find(square, length, num)){
				num = pseudo_random_floor(len);
				if(notfit(square, length, r, c, num, msum)==0){
					break;
				}
			}
			square[rcidx] = num;
		}
	}
	return square;
}

enum neighborhood neighbor(const int *square, size_t length, int fidx, int sidx){
	if(fidx == sidx)
		return SAMECELL;
	if(fidx > sidx)
		swapi(fidx, sidx);
	size_t len = length * length;
	if(sidx >= len || fidx >= len)
		return OUT_OF_RANGE;
	/* checking vertical neighbor first */
	if((fidx + length) == sidx)
		return ADJACENT;
	/* checking if fidx is last column of matrix */
	if(((fidx + 1) % length) == 0){
		return NOT_ADJACENT;
	}
	/* check horizontal neighbor */
	if((fidx + 1) == sidx)
		return ADJACENT;
	
	return NOT_ADJACENT;
}

enum neighborhood relativepos(const int *square, size_t length, int fidx, int sidx){
	enum neighborhood nb = neighbor(square, length, fidx, sidx);
	if(nb != NOT_ADJACENT)
		return nb;
	if(fidx > sidx)
		swapi(fidx, sidx);
	/* For adjacent only checking below check are not required (far checkings) */
	if((sidx - fidx) % length == 0){
		return SAME_COL;
	}
	/* Calculate row indices for both */
	int fridx = fidx / length;
	int sridx = sidx / length;
	if(sridx == fridx){
		return SAME_ROW;
	}
	/* Calculate on the same diagonal of upward or downward */
	int diagmoves = sridx - fridx;
	int same_col_down = fidx + (length * diagmoves);
	if((same_col_down - diagmoves) == sidx){
		return DIAGONAL_UP;
	}
	else if((same_col_down + diagmoves) == sidx){
		return DIAGONAL_DOWN;
	}
	return nb;
}
/* intelligent shuffle 
	this shuffle will check both source and destination surrounding cell for 
	over sum and under sum. 
*/
int *ishuffle(int list[], size_t len, size_t sidelen){
	if(list == NULL || len < 1)
		return 0;
	for(register int i = 0; i < len; i++){
		register int idx;
		while(1){
			idx = pseudo_random_floor(len);
			if(idx == i)
				continue;
			if(distant_numbers(list, len, sidelen, i, idx)){
				if(relativepos(list, len, idx, i) == NOT_ADJACENT)
					break;
			}
			else{
				if(relativepos(list, len, idx, i) != NOT_ADJACENT)
					break;
			}
		}      
		int tmp = list[i];
		list[i] = list[idx];
		list[idx] = tmp;
		/* after first exchange, exit immediately for checking magic square */
	}
	return list;
}

/* check whether list[idx1][idx2] has numbers which should not be/should be distant */
int distant_numbers(int list[], size_t len, size_t sidelen, int idx1, int idx2){
	int diff = list[idx1] > list[idx2] ? list[idx1] - list[idx2] : list[idx2] - list[idx1];
	
	if(diff < sidelen && ((list[idx1] * list[idx1]) < len || list[idx1] > (sidelen * (sidelen-1)))){
		return 1;
	}
	return 0;
}

void print_anomalies(){
	if(anom.mid){
		printf("mid number is mis-placed, current %d\n", anom.mid);
	}
	if(anom.rsum){
		printf("row sum is not correct, row %d, difference %d\n", anom.c, anom.rsum);
	}
	if(anom.csum){
		printf("column sum is not correct, column %d, difference %d\n", anom.r, anom.csum);
	}
	if(anom.digsum_u){
		printf("diagonal upward sum is not correct, [%d, %d], difference %d\n", anom.r, anom.c, anom.digsum_u);
	}
	if(anom.digsum_d){
		printf("diagonal downward sum is not correct, [%d, %d], difference %d\n", anom.r, anom.c, anom.digsum_d);
	}
}

int max(int x, int y){
	return x > y ? x : y;
}

int min(int x, int y){
	return x < y ? x : y;
}