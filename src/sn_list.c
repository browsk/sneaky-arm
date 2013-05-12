#include <stdlib.h>

#include "sn_list.h"


void sn_acquire_lock(sn_list_head *head)
{
	// the lock sits just after head structure
	sn_lock_t * lock = (sn_lock_t *)head++;

	// acquire the lock
	while(0 == __sync_lock_test_and_set(lock, 1));
}

void sn_release_lock(sn_list_head * head)
{
	// the lock sits just after head structure
	sn_lock_t * lock = (sn_lock_t *)head++;

	// release the lock
	*lock = 0;
}


sn_list_head * sn_create_list() 
{
	return calloc(1, sizeof(sn_list_head) + sizeof(sn_lock_t));
}

void sn_list_add_tail(sn_list_head * head, void * data) 
{
	sn_list_node * item = calloc(1, sizeof(sn_list_node));

	sn_acquire_lock(head);

	head->tail->next = item;
	head->tail = item;

	sn_release_lock(head);
}
