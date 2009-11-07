#include "au_binomial.h"

#include <assert.h>
#include <stdlib.h>

struct au_binomial {
	uint32_t n;
	double p, q;
};

struct au_binomial *au_binomial_new(uint32_t n, double p)
{
	struct au_binomial *bin;

	assert(0.0 <= p);
	assert(p <= 1.0);

	if ((bin = calloc(1, sizeof(struct au_binomial))) == NULL)
		return NULL;
	
	bin->n = n;
	bin->p = p;
	bin->q = 1.0 - p;

	return bin;
}

void au_binomial_free(struct au_binomial *bin)
{
	free(bin);
}

double au_binomial_pmf(struct au_binomial *bin, uint32_t x)
{
	return 0.0;
}

double au_binomial_cdf(struct au_binomial *bin, uint32_t x)
{
	return 0.0;
}
