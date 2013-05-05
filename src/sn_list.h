#if !defined (_SN_LIST_H)
#define _SN_LIST_H

typedef struct sn_list_node sn_list_node;

struct sn_list_node {
	void * node_data;
	sn_list_node * next;
};

typedef struct {
	sn_list_node * head;
	sn_list_node * tail;
} sn_list_head;


#endif
