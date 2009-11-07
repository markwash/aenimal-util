#include "au_basic.h"

double au_basic_power(double base, uint32_t power)
{
	double result = 1.0;
	for ( ; power > 0; result *= base, power--);
	return result;
}

double au_basic_factorial(uint32_t n)
{
	double result;
	for (result = 1.0; n > 1; result *= n, n--);
	return result;
}

double au_basic_permutation(uint32_t n, uint32_t m)
{
	double result;
	for (result = 1.0; n > m; result *= n, n--);
	return result;
}

double au_basic_combination(uint32_t n, uint32_t m)
{
	if (m < n - m)
		m = n - m;
	return au_basic_permutation(n, m) / au_basic_factorial(m);
}

