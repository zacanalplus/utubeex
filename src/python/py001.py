#!/usr/bin/env python3

def check_prime(x):
    if(x < 2):
        return False
    if(x % 2 == 0):
        return x == 2
    if(x % 3 == 0):
        return x == 3
    for div in range(5, x, 4):
        if(div * div > x):
            break;
        if(x % div == 0):
            return False
        div += 2
        if(x % div == 0):
            return False
    return True

pcount = 0
for num in range (1, 10000):
    if(check_prime(num)):
        print(f"{num} is prime number. ")
        pcount += 1
    else:
        print(f"{num} is not prime number. ")
print (f"Found {pcount} prime numbers for the range 1..10000")
        