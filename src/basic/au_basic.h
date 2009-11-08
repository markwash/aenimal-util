#ifndef AU_BASIC_H
#define AU_BASIC_H

#include <stdint.h>

struct au_power_cache_ctx;

struct au_power_cache_ctx *au_power_cache_new(void);
void au_power_cache_free(struct au_power_cache_ctx *ctx);

double _au_basic_power(struct au_power_cache_ctx *ctx,
			double base, uint32_t power);
#define au_basic_power(base, power) \
	_au_basic_power(NULL, base, power)
double au_basic_factorial(uint32_t n);
double au_basic_permutation(uint32_t m, uint32_t n);
double au_basic_combination(uint32_t m, uint32_t n);

#endif
