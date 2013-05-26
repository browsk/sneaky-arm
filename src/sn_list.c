#include <stdlib.h>
#include <stdio.h>

#include "sn_list.h"


void sn_acquire_lock(sn_list *list)
{
  // the lock sits just after list structure
  sn_lock_t * lock = &list->lock;

  // acquire the lock
  while(0 == __sync_lock_test_and_set(lock, 1));
}

void sn_release_lock(sn_list * list)
{
  // the lock sits just after list structure
  sn_lock_t * lock = &list->lock;

  // release the lock
  *lock = 0;
}


sn_list * sn_create_list() 
{
  return calloc(1, sizeof(sn_list));
}

void sn_list_add_tail(sn_list * list, void * data) 
{
  sn_list_node * item = calloc(1, sizeof(sn_list_node));

  item->data = data;

  sn_acquire_lock(list);

  if (!list->head) {
    list->head = item;
  }
  else {
    list->tail->next = item;
  }

  list->tail = item;
  sn_release_lock(list);
}

void sn_destroy_list(sn_list * list) {

  sn_acquire_lock(list);

  while(list->head != 0) {
    sn_list_node * node = list->head;
    list->head = node->next;
    free(node->data);
    free(node);
  }

  sn_release_lock(list);

  free(list);
}
