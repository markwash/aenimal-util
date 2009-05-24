#ifndef au_rand_h
#define au_rand_h

#include <sys/types.h>
#include <stdint.h>

size_t au_rand_seed_len();
void au_rand_set_seed(const void *seed);
const void *au_rand_get_seed();

void au_rand_seed_from_uint32(uint32_t seed);
void au_rand_seed_from_time();
void au_rand_seed_default();

uint32_t au_rand_uint32();
double au_rand_double();
uint32_t au_rand_range(uint32_t start, uint32_t len);


#endif
