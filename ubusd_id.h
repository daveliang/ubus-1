#ifndef __UBUSD_ID_H
#define __UBUSD_ID_H

#include <libubox/avl.h>
#include <stdint.h>

struct ubus_id {
	struct avl_node avl;
	uint32_t id;
};

void ubus_init_id_tree(struct avl_tree *tree);
bool ubus_alloc_id(struct avl_tree *tree, struct ubus_id *id);

static inline void ubus_free_id(struct avl_tree *tree, struct ubus_id *id)
{
	avl_delete(tree, &id->avl);
}

static inline struct ubus_id *ubus_find_id(struct avl_tree *tree, uint32_t id)
{
	struct avl_node *avl;

	avl = avl_find(tree, &id);
	if (!avl)
		return NULL;

	return container_of(avl, struct ubus_id, avl);
}

#endif