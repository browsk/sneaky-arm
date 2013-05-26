#if !defined (_SN_LIST_H)
#define _SN_LIST_H

typedef struct sn_list_node sn_list_node;
typedef int sn_lock_t;

struct sn_list_node
{
	void * data;
	sn_list_node * next;
};

typedef struct 
{
	sn_list_node * head;
	sn_list_node * tail;
  sn_lock_t lock;
} sn_list;

sn_list * sn_create_list();
void sn_list_add_tail(sn_list * head, void * data);

void sn_destroy_list();

#endif
