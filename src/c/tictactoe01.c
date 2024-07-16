#include <stdio.h>
#include <time.h>
#include "magicsquare.h"

#define BOARDLEN 6
#define HANDS 2
#define MINBINGOLEN 4

#define MAXHANDS 8
enum hands {HAND1 = 'O', HAND2 = 'X', HAND3 = 'N', HAND4 = 'H', HAND5 = 'A', HAND6 = 'S', 
            HAND7  = 'Z', HAND8 = 'I'};
/* the struct below is making hands enum iterable */
struct psymbols{
    enum hands s[MAXHANDS];
}sym ={HAND1, HAND2, HAND3, HAND4, HAND5, HAND6, HAND7, HAND8};
enum cellstatus {OUTSIDE = -1, TAKEN = 0, FREE};
enum bingostyle { HORIZONTAL = 0, VERTICAL, DIAGONALDOWN, DIAGONALUP };

/* Tic tac toe board */
struct tboard{
    int cells[BOARDLEN][BOARDLEN]; /* board itself */
    int hands[HANDS]; /* how many players */
    int cur_hand; /* whose turn? */
    int freeval;  /* indicator for free cell, free cell has this value */
    int minbingolen; /* minimal length for bingo (win) */
    int bingo_idx[3]; /* found bingo at row, column, bingo style */
};

/* initialize board, clear board */
int init_board(struct tboard *bd, int init_val);
/* initialize players' pieces */
int init_pieces(struct tboard *bd, enum hands fhand, enum hands shand);
/* set hands if it is more than 2 players */
int set_hands(struct tboard *bd, int nhands);
/* check the call is free or already taken */
enum cellstatus cellfree(struct tboard *bd, int row, int col);
/* Check whether board is all filled up or not */
int filled(struct tboard *bd);
/* Trying to put the tile on the board [row, col] ([rown][column])*/
int fill(struct tboard *bd, int row, int col);
/* check a cell has valid hand or not */
int hashand(struct tboard *bd, int row, int col);
/* Set minimum bingo length for winner */
int set_min_bingolen(struct tboard *bd, int minlen);
/* check bingo */
int check_bingo(struct tboard *bd);
/* horizontal/vertical bingo check */
int horizvertical_check(struct tboard *bd);
/* diagonal check for bingo */
int diagonal_check(struct tboard *bd);
/* diagonal (# spelling error #) */
/* int digonal_bingo(struct tboard *bd); */

/* Non-essential debugging functions */
/* randomly fill the board for debugging functions above */
int random_fill(struct tboard *bd);
/* print board for debugging */
int print(struct tboard *bd);
/* read input from stdin for */
int input_board(struct tboard *bd);

int main(int argc, char *argv[]) {
    seedrand(time(NULL));
    struct tboard board;
    init_board(&board, '\0');
    set_min_bingolen(&board, MINBINGOLEN);
    random_fill(&board);
    /*input_board(&board);*/ 
    print(&board);
    if(check_bingo(&board)){
        printf("Found bingo at [%d][%d] and it is %s. \n", board.bingo_idx[0], board.bingo_idx[1], 
            board.bingo_idx[2] == HORIZONTAL? "horizontal" : (board.bingo_idx[2] == VERTICAL ? "vertical" : (board.bingo_idx[2] == DIAGONALDOWN ? "diagonal downward" : "diagonal upward")));
    }
    else{
        printf("%s", "No winner! it is tie!\n");
    }
    return 0;
}

/* initialize board:
        1. fill the board with empty cell value (init_val) 
        2. initialize hand (randomly select hand) 
*/
int init_board(struct tboard *bd, int init_val){
    for(int i = 0; i < BOARDLEN; i++){
        for(int j=0; j < BOARDLEN; j++){
            bd->cells[i][j] = init_val;
        }
    }
    bd->cur_hand = pseudo_random_floor(HANDS);
    set_hands(bd, HANDS);
    /*init_pieces(bd, HAND1, HAND2);*/
    return bd->freeval = init_val;
}

/* initialize player pieces (for 2 players 'O' and 'X') */
int init_pieces(struct tboard *bd, enum hands fhand, enum hands shand){
    bd->hands[0] = fhand;
    bd->hands[1] = shand;
    return 2;
}

/* set all the player's symbol (hands) if it is more than 2 (players) */
int set_hands(struct tboard *bd, int nhands){
    /* not able to set more than 8 player since n symbol is 8 max
        set 2 if more than 8 */
    int hands = init_pieces(bd, HAND1, HAND2); 
    if(nhands > MAXHANDS)
        return hands;
    for(int i=2; i < nhands; i++){
        bd->hands[i] = sym.s[i];
    }
    return nhands;
}

/* return FREE (1) if the cell is empty, otherwise TAKEN (0) 
    it can also check if row and col are outside the square (index out of bound)
*/
enum cellstatus cellfree(struct tboard *bd, int row, int col){
    if(col >= 0 && row >= 0 && row < BOARDLEN && col < BOARDLEN)
        return bd->cells[row][col] == bd->freeval;
    return OUTSIDE;
}

/* check whether all cell in square is filled
*/
int filled(struct tboard *bd){
    for(int i = 0; i < BOARDLEN; i++){
        for(int j = 0; j < BOARDLEN; j++){
            if(cellfree(bd, i, j))
                return 0;
        }
    }
    return 1;
}

/* fill the [row, col] with current player's symbol
    then change the turn of symbol to next player's one
*/
int fill(struct tboard *bd, int row, int col){
    if(!cellfree(bd, row, col))
        return -1;
    bd->cells[row][col] = bd->hands[bd->cur_hand];
    bd->cur_hand = (bd->cur_hand + 1) % HANDS;
    return 1;
}

/* for a square, set minimum bingo length
    example for 5x5 square, bingo length can be 5(full length) or 4 or 3
*/
int set_min_bingolen(struct tboard *bd, int minlen){
    if(minlen < 2 || minlen > BOARDLEN)
        return bd->minbingolen = BOARDLEN;
    return bd->minbingolen = minlen;
}

/* check bingo function look for first bingo in square
    using horizontal, vertical and diagonal check
*/
int check_bingo(struct tboard *bd){
    return (horizvertical_check(bd) == 1 || diagonal_check(bd) == 1);
}

/* horizontal and vertical check and look up for *first* bingo */
int horizvertical_check(struct tboard *bd){
    int times = BOARDLEN - bd->minbingolen + 1;
    for(int i = 0; i < BOARDLEN; i++){
        int heqcount =  0, veqcount = 0; /* horizontal and vertical equivalent count */
        for(int t = 0; t < times; t++){
            if(hashand(bd, i, t)){
                heqcount=1;
            }
            else{
                heqcount = 0;
                continue; /* do not check further, look for more bingo */
            }
            for(int j = 1+t; j < (bd->minbingolen + t); j++){
                if(bd->cells[i][t] == bd->cells[i][j]){
                    heqcount++;
                }
                else{
                    heqcount = 0;
                    break; // same! do not check further, look for more bingo for next *times*
                }
            }
            /* found a bingo, skip further checking! */
            if(heqcount == bd->minbingolen){
                bd->bingo_idx[0] = i; // bingo row
                bd->bingo_idx[1] = t; // bingo column
                bd->bingo_idx[2] = HORIZONTAL; // bingo style
                return 1;
            }
        }
        for(int t = 0; t < times; t++){
            if(hashand(bd, t, i)){
                veqcount=1;
            }
            else{
                veqcount = 0;
                continue; /* do not check further, look for more bingo */
            }
            for(int j = 1+t; j < (bd->minbingolen + t); j++){
                if(bd->cells[t][i] == bd->cells[j][i]){
                    veqcount++;
                }
                else{
                    veqcount = 0;
                    break; // same! do not check further, look for more bingo for next *times*
                }
            }
            /* found a bingo, skip further checking! */
            if(veqcount == bd->minbingolen){
                bd->bingo_idx[0] = t; // bingo row
                bd->bingo_idx[1] = i; // bingo column
                bd->bingo_idx[2] = VERTICAL; // bingo style
                return 1;
            }
        }
    }
    /* exhausted! no bingo found! */
    return 0;
}

/* check whether cell has player symbol(hand) 
    if there is possibilities of dirty data in square
*/
int hashand(struct tboard *bd, int row, int col){
    for(int i=0; i<HANDS; i++){
        if(bd->cells[row][col] == bd->hands[i])
            return 1;
    }
    return 0;
}

/* old diagonal check function, too complicated and abandomed */
int diagonal_check__unused__(struct tboard *bd){
    /* equal count */
    int eqcnt = 0;
    /* if bingo length is less than board length */
    int tdif = BOARDLEN - bd->minbingolen;
    int times = tdif * 2 + 1;
    /* starting from small diagonal down along first row */
    int r = 0, c = tdif;
    
    /* down diagonal */
    while(times--){
        /* first cell */
        int fcell = bd->cells[r][c];
        for(int i=0; i<BOARDLEN; i++){
            if(fcell == bd->cells[r + i][c + i]){
                eqcnt++;
                if(eqcnt == bd->minbingolen){
                    bd->bingo_idx[0] = r;
                    bd->bingo_idx[1] = c;
                    bd->bingo_idx[2] = DIAGONALDOWN;
                    return 1;
                }
            }
            else{
                eqcnt = 0;
                break;
            }
            int c1 = c, r1 = r;
            while(r1 != c1){
                r1 > c1 ? c1++ : r1++;
                for(int i=0; i<BOARDLEN; i++){
                    if(fcell == bd->cells[r1 + i][c1 + i]){
                        eqcnt++;
                        if(eqcnt == bd->minbingolen){
                            bd->bingo_idx[0] = r1;
                            bd->bingo_idx[1] = c1;
                            bd->bingo_idx[2] = DIAGONALDOWN;
                            return 1;
                        }
                    }
                    else{
                        eqcnt = 0;
                        break;
                    }
                }
            }
        }
        /* if it is small down diagonal around main diagonal down */
        if(c > 0){
            c--;
        }
        /* if it is main diagonal down, go down to samll diagonal(s) on first column */
        else{
            r++;
        }
    }
    /* reset for diagonal upward */
    times = tdif * 2 + 1;
    r = BOARDLEN - 1 - tdif; 
    eqcnt = c = 0;
    /* up diagonal */
    while(times--){
        if(!hashand(bd, r, c))
            break;
        /* first cell */
        int fcell = bd->cells[r][c];
        for(int i=0; i<BOARDLEN; i++){
            if(fcell == bd->cells[r - i][c + i]){
                eqcnt++;
                if(eqcnt == bd->minbingolen){
                    bd->bingo_idx[0] = r;
                    bd->bingo_idx[1] = c;
                    bd->bingo_idx[2] = DIAGONALUP;
                    return 1;
                }
            }
            else{
                eqcnt = 0;
                break;
            }
            int c1 = c, r1 = r;
            while(r1 != c1){
                (BOARDLEN - r1) > c1 ? c1++ : r1--;
                for(int i=0; i<BOARDLEN; i++){
                    if(fcell == bd->cells[r1 - i][c1 + i]){
                        eqcnt++;
                        if(eqcnt == bd->minbingolen){
                            bd->bingo_idx[0] = r1;
                            bd->bingo_idx[1] = c1;
                            bd->bingo_idx[2] = DIAGONALUP;
                            return 1;
                        }
                    }
                    else{
                        eqcnt = 0;
                        break;
                    }
                }
            }
        }
        /* if it is small diagonal up around main diagonal up */
        if(r < (BOARDLEN - 1)){
            r++;
        }
        /* if it is main diagonal up, go right to samll diagonal(s) on last column */
        else{
            c++;
        }
    }
    
    return 0;
}

/* diagonal check and look up function, find *first* bingo diagonally
*/
int diagonal_check(struct tboard *bd){
    int times = BOARDLEN - bd->minbingolen;
    /*
        corner square
    */
    int eqcnt = 0;
    for(int r = 0; r <= times; r++){
        for(int c = 0; c <= times; c++){
            /* upper left small square or single cell to start look for bingo */
            int ulcell = bd->cells[r][c];
            for(int i = 0; (r+i) < BOARDLEN && (c+i) < BOARDLEN; i++){
                if(bd->cells[r+i][c+i] == ulcell){
                    eqcnt++;
                    if(bd->minbingolen == eqcnt){
                        bd->bingo_idx[0] = r;
                        bd->bingo_idx[1] = c;
                        bd->bingo_idx[2] = DIAGONALDOWN;
                        return 1;
                    }
                }
                else{
                    /* a difference stop further checking */
                    break;
                }
            }
            /* lower left small square or cell
                  ✴︎ BOARDLEN - 1 is last row/last column
                  ✴︎ BOARDLEN - 1 - times = lower left uppermost row to look for bingo
            */
            eqcnt = 0;
            int lowr = BOARDLEN- 1- times;
            int startr = lowr + r;
            /* lower left small square bingo check */
            int llcell = bd->cells[lowr + r][c];
            for(int i = 0; i < BOARDLEN; i++){
                int ir = lowr - r - i;
                int ic = c + i;
                /* defensive coding for not to go array index out of bound */
                if(ir < 0 || ic >= BOARDLEN){
                    break;
                }
                if(bd->cells[ir][ic] == llcell){
                    eqcnt++;
                    if(bd->minbingolen == eqcnt){
                        bd->bingo_idx[0] = startr;
                        bd->bingo_idx[1] = c;
                        bd->bingo_idx[2] = DIAGONALUP;
                        return 1;
                    }
                }
                else{
                    break;
                }
            }
            eqcnt = 0;
        }
    }
    
    return 0;
}

/* randomly fill the square with hands using fill function for player turns 
    _debugging purpose_
*/
int random_fill(struct tboard *bd){
    for(int i = 0; i < BOARDLEN; i++){
        for(int j = 0; j < BOARDLEN; j++){
            int row, col;
            do{
                row = pseudo_random_floor(BOARDLEN);
                col = pseudo_random_floor(BOARDLEN);
            }while(fill(bd, row, col)==-1);
        }
    }
    return 1;
}

/* this function print bare minimum board printing on console
    __debugging purpose__
*/
int print(struct tboard *bd){
    for(int i = 0; i < BOARDLEN; i++){
        for(int i=0; i < BOARDLEN; i++){
            printf("---");
        }
        printf("\n");
        for(int j = 0; j < BOARDLEN; j++){
            char c = bd->cells[i][j];
            
            if(cellfree(bd, i, i) == TAKEN)
                printf(" %c ", c);
            else 
                printf("   ");
        }
        printf("\n");
    }
    for(int i=0; i < BOARDLEN; i++){
        printf("---");
    }
    printf("\n");
    return 0;
}

/* input data from keyboard to square
    __debugging purpose__
*/
int input_board(struct tboard *bd){
    int cnt;
    for(int i = 0; i < BOARDLEN; i++){
        for(int j = 0; j < BOARDLEN; j++){
            int n;
            cnt += scanf("%d", &n);
            bd->cells[i][j] = n;
        }
    }
    return cnt == (BOARDLEN * BOARDLEN);
}