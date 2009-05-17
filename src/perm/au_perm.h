#ifndef au_perm_h
#define au_perm_h

#include <stdint.h>

void au_perm_init(uint32_t *perm, uint32_t size);
void au_perm_next(uint32_t *perm, uint32_t size, uint32_t max);

#endif
