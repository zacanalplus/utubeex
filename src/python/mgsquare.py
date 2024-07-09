#!/usr/bin/env python3

import numpy as np
import time

MIDNUM = 5
MAGICSUM = 15

np.random.seed(seed = int(time.time()))

def newsquare():
    basearray = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
    square = np.zeros((3, 3), dtype = int)
    np.random.shuffle(basearray)
    for i in range (0, 3):
        for j in range(0, 3):
            square[i, j] = basearray[i * 3 + j]
    return square

def magicsquare(matrix):
    # it will check if matrix is NOT magic square
    if(matrix[1, 1] != MIDNUM):
        return False
    for i in range(0, 3):
        if(sum(matrix[i]) != MAGICSUM):
            return False
        if(sum(matrix[:, i]) != MAGICSUM):
            return False
    if(matrix[0, 0] + matrix[1, 1] + matrix[2, 2] != MAGICSUM):
        return False
    if(matrix[2, 0] + matrix[1, 1] + matrix[0, 2] != MAGICSUM):
        return False
    return True 

msquare = newsquare()
while(1):
    if(magicsquare(msquare)):
        break;
    msquare = newsquare()
print(msquare)
    