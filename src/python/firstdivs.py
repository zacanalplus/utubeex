#!/usr/bin/env python3

def check_prime(x):
    if(x < 2):
        return False
    if(x % 2 == 0):
        return x == 2
    if(x % 3 == 0):
        return x == 3
    for div in range (5, x, 4):
        if(div * div > num):
            break;
        if(num % div == 0):
            return False
        div = div + 2
        if(num % div == 0):
            return False
    return True

def first_divisors(n : int) -> tuple:
    n_me = (n, 1)
    if(n < 2):
        return (0, 0)
    for div in range(2, 4):
        numt = (n, div)
        quotient, remainder = divmod(*numt)
        if(remainder == 0):
            return (div, quotient)
        
    for div in range(5, n, 4):
        if(div * div > n):
            return n_me
        numt = (n, div)
        quotient, remainder = divmod(*numt)
        if(remainder == 0):
            return (div, quotient)
        div += 2
        numt = (n, div)
        quotient, remainder = divmod(*numt)
        if(remainder == 0):
            return (div, quotient)
    return n_me
        

pcount = 0
for num in range(1, 10000):   
    #if(check_prime(num)):
    divs = first_divisors(num)
    if(divs[0] == num):
        print(f"{num} is prime")
        pcount += 1
    else:
        print(f"{num} is not prime")
        print(f"{num} is firstly divisible by {divs[0]} and {divs[1]}")
print(f"Found {pcount} numbers of primes 1..10000")