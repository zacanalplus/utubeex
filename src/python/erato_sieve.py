#!/usr/bin/env python3

import time
from math import isqrt

def timer(func):
	def wrapper(*args, **kwargs):
		before = time.time()
		result = func(*args, **kwargs)
		print('Function took:', time.time() - before, " seconds")
		return result
	return wrapper

@timer
def sieve_of_eratosthenes(upper_bound):
	primes = [True] * upper_bound
	primes[0] = False
	primes[1] = False
	for i in range(2, isqrt(upper_bound)+1):
		if primes[i]:
			for x in range(i*i, upper_bound, i):
				primes[x]=False
	return primes.count(True)

print(sieve_of_eratosthenes(10000000))