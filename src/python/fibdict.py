#!/usr/bin/env python3

MAXNUM = 1000000

def fibonacci(n):
    fib0 = 0
    fib1 = 1
    fibn = 0
    if(n == 0):
        return fib0
    if(n == 1):
        return 1
    for i in range (2, n):
        fibn = fib0 + fib1
        fib0 = fib1
        fib1 = fibn 
    return fibn 

def evenfibs (upperbound):
    evfibs = {}
    for i in range (2, upperbound):
        fib = fibonacci(i)
        if(fib > upperbound):
            break
        if(fib % 2 == 0):
            evfibs[str(i)] = fib
    return evfibs

evnfibs = evenfibs(MAXNUM)
print (evnfibs)
print (f"The sum of all even fibonacci number is {sum(evnfibs.values())}.\n")