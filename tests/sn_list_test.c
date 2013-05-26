#include <stdlib.h>
#include <check.h>
#include "sn_list.h"

START_TEST(test_create_list) {
	sn_list * list = sn_create_list();

	ck_assert(list != 0);
	
	free(list);
}
END_TEST

START_TEST(test_destroy_empty) {
	sn_list * list = sn_create_list();

	sn_destroy_list(list);
}
END_TEST

START_TEST(test_insert_int) {
  sn_list *list = sn_create_list();

  int n;
  for (n = 0; n < 2000; ++n) {
    int *p = malloc(sizeof(int));
    *p = n;
    sn_list_add_tail(list, p);
  }

  sn_destroy_list(list);
}
END_TEST

Suite * sn_list_suite() {
	Suite *s = suite_create("sn_list");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_create_list);
	tcase_add_test(tc_core, test_destroy_empty);
	tcase_add_test(tc_core, test_insert_int);

	suite_add_tcase(s, tc_core);

	return s;
}

