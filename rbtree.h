#ifndef RBTREE_H_
#define RBTREE_H_

#include <stdbool.h>
#include <stddef.h>

struct rbtree_node {
    struct rbtree_node *childs[2];
    struct rbtree_node *parent;
    int                 key;
    bool                is_red;
};

struct rbtree {
    struct rbtree_node *root;
    size_t              size;
};

void rbtree_init(struct rbtree *tree);
void rbtree_insert(struct rbtree *tree, struct rbtree_node *node);
bool rbtree_contains(struct rbtree *tree, int key);

#endif
