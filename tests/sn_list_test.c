#include <stdlib.h>
#include <check.h>
#include "sn_list.h"

START_TEST(test_create_list)
{
	sn_list_head * head = sn_create_list();

	ck_assert(head != 0);
	
	free(head);
}
END_TEST

Suite * sn_list_suite()
{
	Suite *s = suite_create("sn_list");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_create_list);

	suite_add_tcase(s, tc_core);

	return s;
}

