#include <stdio.h>
#include <stdlib.h>

struct divisors{
	unsigned long divisor;
	unsigned long quotient;
};

int prime(unsigned long num, struct divisors *pdivs);

int main(int argc, char *argv[])
{
	unsigned long num = 3777111;
	struct divisors divs;
	if (prime(num, &divs))
		printf("%lu is prime number. \n", num);
	else{
		printf("%lu is not prime number. \n", num);
		printf("%lu is first divisor and %lu is quotient. \n", divs.divisor, divs.quotient);
	}
	return 0;
}

int prime(unsigned long num, struct divisors *divs)
{
	if ((num & 1) == 0){
		divs->divisor = 2;
		divs->quotient = num / 2;
		return num == 2;
	}
	ldiv_t d = ldiv(num, 3);
	if (d.rem == 0){
		divs->divisor = 3;
		divs->quotient = d.quot;
		return num == 3;
	}
	unsigned long div;
	for (div = 5; (div * div) <= num; div += 4)
	{
		d = ldiv(num, div);
		if (d.rem == 0){
			divs->divisor = div;
			divs->quotient = d.quot;
			return 0;
		}
		div += 2;
		d = ldiv(num, div);
		if (d.rem == 0){
			divs->divisor = div;
			divs->quotient = d.quot;
			return 0;
		}
	}
	return 1;
}
