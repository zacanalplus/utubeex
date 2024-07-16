#!/usr/bin/env python3

def check_prime(x):
    if(x < 2):
        return False
    if(x % 2 == 0):
        return x == 2
    if(x % 3 == 0):
        return x == 3
    for div in range (5, x, 4):
        if(div * div > x):
            break;
        if(x % div == 0):
            return False
        div = div + 2
        if(x % div == 0):
            return False
    return True

def prime_list(upperbound):
    num = 1
    while(num <= upperbound):
        if(check_prime(num)):
            yield num;
        num += 1

primes = prime_list(1000)

for prime in primes:
    print(prime)