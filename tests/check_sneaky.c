#include <stdlib.h>
#include <check.h>

extern Suite * sn_list_suite();

int main(void)
{
	Suite * s = sn_list_suite();
	SRunner * runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);

	srunner_free(runner);
	return 0;
}
