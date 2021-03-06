#include <check.h>
#include <stdlib.h>
#include "../../src/perm/au_perm.h"

#include <stdint.h>

START_TEST(test_perm_init) {
	uint32_t perm[10];
	au_perm_init(perm, 3);
	uint32_t i;
	for (i = 0; i < 3; i++) {
		fail_unless(perm[i] == i, NULL);
	}
} END_TEST
START_TEST(test_perm_next) {
	uint32_t perm[10];
	au_perm_init(perm, 3);
	uint32_t i, j, k;
	int result = 1;
	for (i = 0; i < 5; i++) {
		for (j = i + 1; j < 5; j++) {
			for (k = j + 1; k < 5; k++) {
				fail_unless(perm[0] == i, NULL);
				fail_unless(perm[1] == j, NULL);
				fail_unless(perm[2] == k, NULL);
				fail_unless(result == 1, NULL);
				result = au_perm_next(perm, 3, 5);
			}
		}
	}
	fail_unless(result == 0);
} END_TEST
START_TEST(test_perm_last) {
	uint32_t perm[3] = {2, 3, 4};
	fail_unless(au_perm_next(perm, 3, 5) == 0, NULL);
	int i;
	for (i = 0; i < 3; i++) {
		fail_unless(perm[i] == i, NULL);
	}
} END_TEST

Suite *perm_suite(void) {

	Suite *s = suite_create("perm");

	TCase *tc_core = tcase_create("core");
	tcase_add_test(tc_core, test_perm_init);
	tcase_add_test(tc_core, test_perm_next);

	TCase *tc_edge = tcase_create("edge");
	tcase_add_test(tc_core, test_perm_last);

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
