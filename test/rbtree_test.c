#include <stdio.h>
#include <ez_rbtree.h>
#include <ez_malloc.h>
#include <ez_macro.h>
#include <ez_util.h>

#define NODES 100

#define cast_to_type_ptr(ptr, type)     EZ_CONTAINER_OF(ptr, type, rb_node)
#define rb_node_addr(type_ptr)         ((ezRBTreeNode*)(&(type_ptr->rb_node)))

typedef struct test_t {
    ezRBTreeNode rb_node;
    int age;
} test;

static ezRBTree rbtree;
static ezRBTreeNode sentinel;

static test *nodes[NODES];

static int student_compare_proc(ezRBTreeNode *new_node, ezRBTreeNode *exists_node) {
    test *n = cast_to_type_ptr(new_node, test);
    test *o = cast_to_type_ptr(exists_node, test);
    return n->age == o->age ? 0 : (n->age > o->age ? 1 : -1);
}

static int student_find_proc(ezRBTreeNode *node, void *find_args) {
    int age = *((int *) find_args);
    test *o = cast_to_type_ptr(node, test);
    return o->age == age ? 0 : (o->age > age ? 1 : -1);
}

int main(int argc, char **argv) {
    ezRBTreeNode *node = NULL;
    rbtree_init(&rbtree, &sentinel, student_compare_proc);

    for (int i = 0; i < NODES; ++i) {
        nodes[i] = (test *) ez_malloc(sizeof(test));
        nodes[i]->age = i;
    }

    for (int i = 0; i < NODES; ++i) {
        rbtree_insert(&rbtree, rb_node_addr(nodes[i]));
    }
    int find_age = 100;
    node = rbtree_find_node(&rbtree, student_find_proc, &find_age);
    if (node != NULL) {
        fprintf(stdout, "error:::>find test_t 100 :>!\n");
    }
    find_age = 50;
    node = rbtree_find_node(&rbtree, student_find_proc, &find_age);
    if (node == NULL || cast_to_type_ptr(node, test)->age != find_age) {
        fprintf(stdout, "error::>not find test_t 50 :>!\n");
    }
    node = rbtree_min_node(&rbtree);
    while (node != NULL) {
        fprintf(stdout, "delete min test_t.age = %d\n", cast_to_type_ptr(node, test)->age);
        rbtree_delete(&rbtree, node);
        node = rbtree_min_node(&rbtree);
    }
    fprintf(stdout, "------------------------------> test malloc <----------------------------------------\n");
    void *align_ptr = NULL;
    for (int i = 0; i < NODES; ++i) {
        align_ptr = EZ_ALIGN_PTR(nodes[i]);
        fprintf(stdout, "ptr:%p, align_ptr:%p, use mem:%8lu\n", (void *) nodes[i], align_ptr, zmalloc_used_memory());
        ez_free(nodes[i]);
    }
    fprintf(stdout, "ez_free over, use mem:%8lu\n", zmalloc_used_memory());
    fprintf(stdout, "------------------------------> test malloc <----------------------------------------\n");
    return 0;
}
