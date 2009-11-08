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
	for (i = 0; i < 20; i++)
		fail_unless(au_basic_power(0.0, i) == 0.0, NULL);
} END_TEST

Suite *basic_suite(void) {

	Suite *s = suite_create("basic");

	TCase *tc_core = tcase_create("core");
	tcase_add_test(tc_core, test_basic_power);
	tcase_add_test(tc_core, test_basic_power_lto);

	TCase *tc_edge = tcase_create("edge");
	tcase_add_test(tc_edge, test_basic_power_base_one);
	tcase_add_test(tc_edge, test_basic_power_base_zero);

	suite_add_tcase(s, tc_core);

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
