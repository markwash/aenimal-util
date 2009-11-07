#ifndef AU_BINOMIAL_H
#define AU_BINOMIAL_H

#include <stdint.h>

struct au_binomial;

struct au_binomial *au_binomial_new(uint32_t n, double p);
void au_binomial_free(struct au_binomial *bin);

double au_binomial_pmf(struct au_binomial *bin, uint32_t x);
double au_binomial_cdf(struct au_binomial *bin, uint32_t x);

#endif
