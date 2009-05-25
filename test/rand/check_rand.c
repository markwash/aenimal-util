#include <check.h>
#include <stdlib.h>
#include "../../src/rand/au_rand.h"

#include <stdint.h>

START_TEST(test_rand_blah) {
} END_TEST

Suite *perm_suite(void) {

	Suite *s = suite_create("rand");

	TCase *tc_core = tcase_create("core");
	tcase_add_test(tc_core, test_rand_init);

	suite_add_tcase(s, tc_core);

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
