#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/rand/au_rand.h"

#include <stdint.h>

START_TEST(test_rand_uint32) {
	au_rand_seed_default();
	uint32_t r;
	r = au_rand_uint32();
	fail_unless(r >= 0, NULL);
	fail_unless(r <= 0xffffffff, NULL);
} END_TEST
START_TEST(test_rand_double) {
	au_rand_seed_default();
	int i;
	double rd;
	for (i = 0; i < 100; i++) {
		rd = au_rand_double();
		fail_unless(rd < 1.0, NULL);
		fail_unless(rd >= 0, NULL);
	}
} END_TEST
START_TEST(test_rand_range) {
	au_rand_seed_default();
	int i, j;
	uint32_t r;
	for (i = 10; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			r = au_rand_range(i, i);
			fail_unless(r >= i, NULL);
			fail_unless(r < 2*i, NULL);
		}
	}
} END_TEST
START_TEST(test_rand_range_edge) {
	au_rand_seed_default();
	fail_unless(au_rand_range(0, 0) == 0, NULL);
	fail_unless(au_rand_range(10, 0) == 10, NULL);
} END_TEST
START_TEST(test_rand_compare) {
	uint32_t iter = 10000;
	uint64_t above_wt = 0, below_wt = 0;
	uint32_t r, p;
	int i;
	au_rand_seed_default();
	r = au_rand_uint32();
	for (i = 0; i < iter; i++) {
		p = r;
		r = au_rand_uint32();
		if (r >= p) {
			above_wt += p;
		} else {
			below_wt += 0xffffffff - p;
		}
	}
	double da = above_wt / (double) iter / 0xffffffff;
	double db = below_wt / (double) iter / 0xffffffff;
	double delta = da > db ? da - db : db - da;
	fail_unless(delta < 0.01, NULL);
} END_TEST
uint32_t extract_bits(uint32_t num, uint32_t bits[], size_t len) {
	uint32_t result = 0;
	int i;
	for (i = 0; i < len; i++) {
			i, bits[i], 1 << bits[i], num & (1 << bits[i]), 1 << i);
		if ((num & (1 << bits[i])) != 0) {
			result += 1 << i;
		}
	}
	return result;
}
START_TEST(test_extract_bits) {
	uint32_t bits[] = {0, 1, 2};
	fail_unless(extract_bits(0xffffffff, bits, 3) == 7, NULL);
	fail_unless(extract_bits(0x00000000, bits, 3) == 0, NULL);
	uint32_t bits2[] = {0, 16, 31};
	fail_unless(extract_bits(0xffffffff, bits2, 3) == 7, NULL);
	fail_unless(extract_bits(0xffff0000, bits2, 3) == 6, NULL);
	fail_unless(extract_bits(0x000f000f, bits2, 3) == 3, NULL);
	fail_unless(extract_bits(0x00000000, bits2, 3) == 0, NULL);
} END_TEST

Suite *perm_suite(void) {

	Suite *s = suite_create("rand");

	TCase *tc_core = tcase_create("core");
	tcase_add_test(tc_core, test_rand_uint32);
	tcase_add_test(tc_core, test_rand_double);
	tcase_add_test(tc_core, test_rand_range);
	tcase_add_test(tc_core, test_rand_compare);
	tcase_add_test(tc_core, test_extract_bits);

	TCase *tc_edge = tcase_create("edge");
	tcase_add_test(tc_edge, test_rand_range_edge);

	suite_add_tcase(s, tc_core);
	suite_add_tcase(s, tc_edge);

	return s;
}

int main() {
	int number_failed;
	Suite *s = perm_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
