#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/basic/au_basic.h"

#include <stdint.h>

START_TEST(test_basic_power) {
	fail_unless(au_basic_power(1.5, 2) == 2.25, NULL);
	fail_unless(au_basic_power(3.0, 4) == 81.0, NULL);
} END_TEST
START_TEST(test_basic_power_lto) {
	double diff;
	fail_unless(au_basic_power(0.5, 2) == 0.25, NULL);
	diff = au_basic_power(0.6, 4) - 0.1296;
	fail_unless(diff < 0.00001 && -diff < 0.00001, NULL);
} END_TEST
START_TEST(test_basic_power_base_one) {
	uint32_t i;
	for (i = 0; i < 20; i++)
		fail_unless(au_basic_power(1.0, i) == 1.0, NULL);
} END_TEST
START_TEST(test_basic_power_base_zero) {
	uint32_t i;
	for (i = 1; i < 20; i++)
		fail_unless(au_basic_power(0.0, i) == 0.0, NULL);
} END_TEST
START_TEST(test_basic_power_huge_exponent) {
	double diff;
	diff = au_basic_power(0.9999, 10000) - 0.36786;
	fail_unless(diff < 0.00001 && -diff < 0.00001, NULL);
} END_TEST
START_TEST(test_basic_power_one) {
	double d;
	for (d = 0.1; d < 10; d += 0.33) 
		fail_unless(au_basic_power(d, 1) == d, NULL);
} END_TEST
START_TEST(test_basic_power_zero) {
	double d;
	for (d = 0.1; d < 10; d += 0.33) 
		fail_unless(au_basic_power(d, 0) == 1.0, NULL);
} END_TEST
START_TEST(test_basic_factorial) {
	fail_unless(au_basic_factorial(1) == 1.0, NULL);
	fail_unless(au_basic_factorial(2) == 2.0, NULL);
	fail_unless(au_basic_factorial(3) == 6.0, NULL);
	fail_unless(au_basic_factorial(4) == 24.0, NULL);
	fail_unless(au_basic_factorial(5) == 120.0, NULL);
	fail_unless(au_basic_factorial(6) == 720.0, NULL);
	fail_unless(au_basic_factorial(7) == 5040.0, NULL);
} END_TEST
START_TEST(test_basic_factorial_zero) {
	fail_unless(au_basic_factorial(0) == 1.0, NULL);
} END_TEST

Suite *basic_suite(void) {

	Suite *s = suite_create("basic");

	TCase *tc_power_core = tcase_create("power_core");
	tcase_add_test(tc_power_core, test_basic_power);
	tcase_add_test(tc_power_core, test_basic_power_lto);
	tcase_add_test(tc_power_core, test_basic_power_huge_exponent);

	TCase *tc_power_edge = tcase_create("power_edge");
	tcase_add_test(tc_power_edge, test_basic_power_base_one);
	tcase_add_test(tc_power_edge, test_basic_power_base_zero);
	tcase_add_test(tc_power_edge, test_basic_power_one);
	tcase_add_test(tc_power_edge, test_basic_power_zero);

	TCase *tc_factorial_core = tcase_create("factorial_core");
	tcase_add_test(tc_factorial_core, test_basic_factorial);

	TCase *tc_factorial_edge = tcase_create("factorial_edge");
	tcase_add_test(tc_factorial_edge, test_basic_factorial_zero);

	suite_add_tcase(s, tc_power_core);
	suite_add_tcase(s, tc_power_edge);
	suite_add_tcase(s, tc_factorial_core);
	suite_add_tcase(s, tc_factorial_edge);

	return s;
}

int main() {
	int number_failed;
	Suite *s = basic_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
