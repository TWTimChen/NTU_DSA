#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"

void postorder_integer_bst(const struct bst_node *node, int depth, int *maxDepth){
  if (node == NULL)
    return;

  if (depth > *maxDepth)
    *maxDepth = depth;
  if (node->bst_link[0] != NULL || node->bst_link[1] != NULL){
      postorder_integer_bst(node->bst_link[0], depth+1, maxDepth);
      postorder_integer_bst(node->bst_link[1], depth+1, maxDepth);
  }
}

void postorder_integer_avl(const struct avl_node *node, int depth, int *maxDepth){
  if (node == NULL)
    return;

  if (depth > *maxDepth)
    *maxDepth = depth;
  if (node->avl_link[0] != NULL || node->avl_link[1] != NULL){
      postorder_integer_avl(node->avl_link[0], depth+1, maxDepth);
      postorder_integer_avl(node->avl_link[1], depth+1, maxDepth);
  }
}

void postorder_integer_rb(const struct rb_node *node, int depth, int *maxDepth){
  if (node == NULL)
    return;

  if (depth > *maxDepth)
    *maxDepth = depth;
  if (node->rb_link[0] != NULL || node->rb_link[1] != NULL){
      postorder_integer_rb(node->rb_link[0], depth+1, maxDepth);
      postorder_integer_rb(node->rb_link[1], depth+1, maxDepth);
  }
}

int int_compare(const void *pa, const void *pb, void *param)
{
  int a = *(const int *)pa;
  int b = *(const int *)pb;

  if (a < b)
    return -1;
  else if (a > b)
    return +1;
  else
    return 0;
}

int main(){
  struct bst_table *tree_bst;  
  tree_bst = bst_create(int_compare, NULL, NULL);
  struct avl_table *tree_avl;  
  tree_avl = avl_create(int_compare, NULL, NULL);
  struct rb_table *tree_rb;  
  tree_rb = rb_create(int_compare, NULL, NULL);

  for (int i=1; i<2049; i++) {
    int* element = (int*)malloc(sizeof(int));
    *element = i;
    void **p1 = bst_probe(tree_bst, element);
    void **p2 = avl_probe(tree_avl, element);
    void **p3 = rb_probe(tree_rb, element);
  }

  int depth=0;
  int *maxdepth = malloc(9*sizeof(int));
  postorder_integer_bst(tree_bst->bst_root, depth, maxdepth);
  postorder_integer_avl(tree_avl->avl_root, depth, maxdepth+3);
  postorder_integer_rb(tree_rb->rb_root, depth, maxdepth+6);

  for (int i=1; i<1025; i++) {
      bst_delete(tree_bst, &i);
      avl_delete (tree_avl, &i);
      rb_delete (tree_rb, &i);
  }

  postorder_integer_bst(tree_bst->bst_root, depth, maxdepth+1);
  postorder_integer_avl(tree_avl->avl_root, depth, maxdepth+4);
  postorder_integer_rb(tree_rb->rb_root, depth, maxdepth+7);

  for (int i=2049; i<4097; i++) {
    int* element = (int*)malloc(sizeof(int));
    *element = i;
    void **p1 = bst_probe(tree_bst, element);
    void **p2 = avl_probe(tree_avl, element);
    void **p3 = rb_probe(tree_rb, element);
  }

  postorder_integer_bst(tree_bst->bst_root, depth, maxdepth+2);
  postorder_integer_avl(tree_avl->avl_root, depth, maxdepth+5);
  postorder_integer_rb(tree_rb->rb_root, depth, maxdepth+8);

  printf("bst %d %d %d\n", maxdepth[0], maxdepth[1], maxdepth[2]);
  printf("avl %d %d %d\n", maxdepth[3], maxdepth[4], maxdepth[5]);
  printf("rb %d %d %d\n", maxdepth[6], maxdepth[7], maxdepth[8]);
  return 0;
}
