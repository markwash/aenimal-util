#ifndef au_perm_h
#define au_perm_h

#include <stdint.h>

void au_perm_init(uint32_t *perm, uint32_t size);
/* Get next permutation of <size> integers from 1..<max>,
	return 1 if there are more permutations, 0 otherwise */
int au_perm_next(uint32_t *perm, uint32_t size, uint32_t max);

/* example for loop usage

uint32_t perm[4];
for (au_perm_init(&perm, 4); au_perm_next(&perm, 4, 10); )
	...

*/


#endif
