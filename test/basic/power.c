#include <signal.h>
#include <stdio.h>
#include <stdint.h>

#include "../../src/basic/au_basic.h"

static int stop = 0;

void handle_alarm(int i)
{
	if (i == SIGALRM)
		stop = 1;
}

static struct sigaction sa;

void init_signals() {
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_alarm;
	sigaction(SIGALRM, &sa, NULL);
}	

double naive_power(void *ctx, double base, uint32_t power)
{
	double result = 1.0;
	for (; power > 0; result *= base, power--);
	return result;
}

double better_power(void *ctx, double base, uint32_t power)
{
	double cache[128];
	uint32_t powers[128];
	double result;
	int i, p, next;

	cache[0] = base;
	powers[0] = 1;
	for (i = 1, p = 1, next = 2; power > next && i < 128; i++, p = next, next *= 2) {
		powers[i] = next;
		cache[i] = cache[i - 1] * cache[i - 1];
	}
	powers[i] = next;

	result = 1.0;
	while (power > 0) {
		if (powers[i] <= power) {
			result *= cache[i];
			power -= powers[i];
		} else {
			i -= 1;
		}
	}

	return result;
}

typedef double (*powfn)(void *, double, uint32_t);

void run(const char *name, powfn pow, int seconds)
{
	uint32_t i;
	uint64_t count = 0;

	init_signals();
	alarm(seconds);
	while (!stop) {
		for (i = 0; i < 10000 && !stop; i++) {
			pow(NULL, 0.5, i);
			count += 1;
		}
	}

	printf("%s: %llu in %d second(s)\n", name, count, seconds);
	stop = 0;		
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Usage: %s <seconds per test>\n", argv[0]);
		return 0;
	}

	int time = atoi(argv[1]);
	run("naive", naive_power, time);	
	run("smart", better_power, time);
	run("cache", _au_basic_power, time);

	return 0;
}
