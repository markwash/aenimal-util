#include "au_basic.h"

#include <stdlib.h>

#define POWER_CACHE_CAP 128

struct au_power_cache_ctx {
	double base;
	uint32_t len, cap;
	uint32_t powers[POWER_CACHE_CAP];
	double results[POWER_CACHE_CAP];
};

static struct au_power_cache_ctx *default_power_cache_ctx;

struct au_power_cache_ctx *au_power_cache_new()
{
	struct au_power_cache_ctx *ctx;
	ctx = calloc(1, sizeof(struct au_power_cache_ctx));
	if (ctx == NULL) {
		return NULL;
	}

	ctx->base = 0.0;
	ctx->len = 0;
	ctx->cap = POWER_CACHE_CAP;

	return ctx;
}

void au_power_cache_free(struct au_power_cache_ctx *ctx)
{
	free(ctx);
}

double _au_basic_power(struct au_power_cache_ctx *ctx,
			double base, uint32_t power)
{
	double result;
	uint32_t next_power;
	int i;

	if (ctx == NULL) {
		if (default_power_cache_ctx == NULL) {
			default_power_cache_ctx = au_power_cache_new();
		}
		ctx = default_power_cache_ctx;
	}

	// avoid caching useless cases
	if (power > 1 && base > 1.0) {
	} else if (power == 0) {
		return 1.0;
	} else if (power == 1) {
		return base;
	} else if (base == 0.0) {
		return 0.0;
	} else if (base == 1.0) {
		return 1.0;
	}

	// invalidate cache if the base changed
	if (base != ctx->base) {
		ctx->len = 1;
		ctx->base = base;
		ctx->powers[0] = 1;
		ctx->results[0] = base;
	}
	
	// prefill the cache
	next_power = 2 * ctx->powers[ctx->len - 1];
	while (next_power <= power && ctx->len <= ctx->cap) {
		ctx->powers[ctx->len] = next_power;
		ctx->results[ctx->len] = ctx->results[ctx->len - 1] * ctx->results[ctx->len - 1];
		next_power *= 2;
		ctx->len += 1;
	}

	// calculate the requested power
	result = 1.0;
	while (power >= ctx->powers[ctx->len - 1]) {
		result *= ctx->results[ctx->len - 1];
		power -= ctx->powers[ctx->len - 1];
	}

	for (i = 0; power > 0 && i < ctx->len - 1; i++) {
		if (power & ctx->powers[i]) {
			result *= ctx->results[i];
			power -= ctx->powers[i];
		}
	}

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

