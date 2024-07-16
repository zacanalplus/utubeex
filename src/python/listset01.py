#!/usr/bin/env python3

LIMIT = 1000
FIRSTNUM = 17
SECONDNUM = 19

def multipleof(n, limit = LIMIT):
    multiple = 1
    listn = []
    while(True):
        curval = n * multiple 
        if(curval >= limit):
            break;
        listn.append(curval)
        multiple += 1
    return listn 

mulof_17 = multipleof(17)
mulof_19 = multipleof(19)

def unionlist(list1, list2):
    return list(set(list1) | set(list2))

mulof_17_19 = unionlist(mulof_17, mulof_19)

print(f"{sorted(mulof_17_19)} \n The total number of multiples is {mulof_17_19.__len__()}\n")
print(f"The sum of multiple of {FIRSTNUM} and {SECONDNUM} is {sum(mulof_17_19)}\n")
