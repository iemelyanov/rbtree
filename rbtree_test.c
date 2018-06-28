#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rbtree.h"

#define COUNT 10

#define new_node(k) { .childs={ NULL }, .parent=NULL, .key=k, .is_red=false }

static void
print_tree(struct rbtree_node *root, int space)
{
    if (root == NULL) {
        return;
    }
 
    space += COUNT; 

    print_tree(root->childs[1], space);
 
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }

    if (root->is_red) {
        printf("%dR\n", root->key);
    } else {
        printf("%dB\n", root->key);
    }
 
    print_tree(root->childs[0], space);
}

static inline struct rbtree_node *
alloc_node()
{
    struct rbtree_node *node = (struct rbtree_node*)malloc(
        sizeof(struct rbtree_node));
    return node;
}

static inline void
init_node(struct rbtree_node *node, int key)
{
    node->key = key;
    node->parent = NULL;
    node->childs[0] = 0;
    node->childs[1] = 0;
    node->is_red = true;
}

void
benchmark(int n)
{
    struct rbtree tree;
    rbtree_init(&tree);

    for (int i = 0; i < n; i++) {
        struct rbtree_node *node = alloc_node();
        init_node(node, i);
        rbtree_insert(&tree, node);
    }
}

void
test()
{
    struct rbtree tree;
    rbtree_init(&tree);

    struct rbtree_node node0 = new_node(0);
    struct rbtree_node node1 = new_node(1);
    struct rbtree_node node2 = new_node(2);
    struct rbtree_node node3 = new_node(3);
    struct rbtree_node node4 = new_node(4);
    struct rbtree_node node5 = new_node(5);
    struct rbtree_node node6 = new_node(6);
    struct rbtree_node node7 = new_node(7);
    struct rbtree_node node8 = new_node(8);
    
    rbtree_insert(&tree, &node0);
    rbtree_insert(&tree, &node1);
    rbtree_insert(&tree, &node2);
    rbtree_insert(&tree, &node3);
    rbtree_insert(&tree, &node4);
    rbtree_insert(&tree, &node5);
    rbtree_insert(&tree, &node6);
    rbtree_insert(&tree, &node7);
    rbtree_insert(&tree, &node8);
    
    assert(rbtree_contains(&tree, 0));
    assert(rbtree_contains(&tree, 1));
    assert(rbtree_contains(&tree, 2));
    assert(rbtree_contains(&tree, 3));
    assert(rbtree_contains(&tree, 4));
    assert(rbtree_contains(&tree, 5));
    assert(rbtree_contains(&tree, 6));
    assert(rbtree_contains(&tree, 7));
    assert(rbtree_contains(&tree, 8));

    print_tree(tree.root, 0);
}

int
main(int argc, char **argv)
{
    int n = 0;
    if (argc == 2) {
        n = atoi(argv[1]);
    }
    printf("%d\n", n);
    clock_t begin = clock();
    benchmark(n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    return 0;
}
