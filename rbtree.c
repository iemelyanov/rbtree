#include <assert.h>
#include <stdio.h>
#include "rbtree.h"

#define parent(node) ((node)->parent)

#define gparent(node) (parent(parent(node)))

#define uncle(node, direct) (gparent(node)->childs[direct])

#define sibling(node, direct) (parent(node)->childs[direct])

#define set_red(node) ((node)->is_red = true)

#define is_red(node) ((node)->is_red)

#define set_black(node) ((node)->is_red = false)

static inline void
single_rotate(struct rbtree_node **root, struct rbtree_node *curr, int direct)
{
    assert(curr != NULL);

    struct rbtree_node *rnode = curr->childs[direct];

    curr->childs[direct] = rnode->childs[!direct];

    if (rnode->childs[!direct] != NULL) {
        rnode->childs[!direct]->parent = curr;
    }

    rnode->parent = curr->parent;
    
    if (curr->parent != NULL) {
        if (curr == curr->parent->childs[!direct]) {
            curr->parent->childs[!direct] = rnode;
        } else {
            curr->parent->childs[direct] = rnode;
        }
    }

    if (curr == *root) {
        *root = rnode;
    }

    rnode->childs[!direct] = curr;
    curr->parent           = rnode;
}

static inline void
fixup(struct rbtree_node **root, struct rbtree_node *node)
{
    assert(node);
    
    struct rbtree_node *t = node;
    struct rbtree_node *u = NULL;
    int direct            = 0;
    
    while (t != *root && is_red(parent(t))) {
        direct = (parent(t) == uncle(t, 0));
        u = uncle(t, direct);
        if (u != NULL && is_red(u)) {
            set_red(gparent(t));
            set_black(parent(t));
            set_black(u);
            t = gparent(t);
        } else {
            if (t == sibling(t, direct)) {
                t = parent(t);
                single_rotate(root, t, direct);
            }
            set_red(gparent(t));
            set_black(parent(t));
            single_rotate(root, gparent(t), !direct);
        }
    }
    
    set_black(*root);
}

void
rbtree_init(struct rbtree *tree)
{
    assert(tree != NULL);

    tree->root = NULL;
    tree->size = 0;
}

inline void
rbtree_insert(struct rbtree *tree, struct rbtree_node *node)
{
    assert(tree);

    struct rbtree_node **root  = &tree->root;
    struct rbtree_node *parent = NULL;
    int direct                 = 0;

    while (*root != NULL) {
        if (node->key == (*root)->key) {
            return;
        }
        parent = *root;
        direct = node->key > (*root)->key;
        root   = &(*root)->childs[direct];
    }

    node->is_red = true;
    node->parent = parent;
    *root        = node;

    fixup(&tree->root, node);
}

bool
rbtree_contains(struct rbtree *tree, int key)
{
    assert(tree);

    struct rbtree_node *root = tree->root;
    int direct               = 0;
    
    while (root != NULL) {
        if (root->key == key) {
            return true;
        }
        direct = key > root->key;
        root   = root->childs[direct]; 
    }
    return false;
}
