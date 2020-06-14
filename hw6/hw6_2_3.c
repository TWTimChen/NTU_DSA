#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"
#define INT32_MAX 2147483647
#define INT32_MIN (-INT32_MAX-1)

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

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void genRand(int *array, unsigned seed) 
{
  int nNum = 4096;
  for (int i=0; i<nNum; i++)
      array[i]=i;

  for (int i=nNum-1; i>0; i--){
      int j = rand()%(i+1);
      swap(array+i, array+j);
  }
}

int max(int *start,int *end)
{
    int maxInt=INT32_MIN;
    for (int *i = start; i != end; i+=1)
        if (*i > maxInt)
            maxInt = *i;
    return maxInt;
}

int min(int *start,int *end)
{
    int minInt=INT32_MAX;
    for (int *i = start; i != end; i+=1)
        if (*i < minInt)
            minInt = *i;
    return minInt;
}

int avg(int *start,int *end)
{
    int sum=0;
    for (int *i = start; i != end; i+=1)
        sum += *i;
    return sum/(end-start);
}

int main(){
  int REP = 10000;
  int *randEle = (int *)malloc(4096*sizeof(int));
  int *maxdepth_1 = (int *)calloc(3*REP ,sizeof(int));
  int *maxdepth_2 = (int *)calloc(3*REP, sizeof(int));
  int *maxdepth_3 = (int *)calloc(3*REP, sizeof(int));
  time_t t;
  srand((unsigned) time(&t));

  for (int rep=0; rep<REP; rep++) {
    struct bst_table *tree_bst;  
    tree_bst = bst_create(int_compare, NULL, NULL);
    struct avl_table *tree_avl;  
    tree_avl = avl_create(int_compare, NULL, NULL);
    struct rb_table *tree_rb;  
    tree_rb = rb_create(int_compare, NULL, NULL);

    int i=0;
    genRand(randEle, rep);
    int depth=0;

    for (i=0; i<2048; i++) {
    void **p1 = bst_probe(tree_bst, randEle+i);
    void **p2 = avl_probe(tree_avl, randEle+i);
    void **p3 = rb_probe(tree_rb, randEle+i);
    }

    postorder_integer_bst(tree_bst->bst_root, depth, maxdepth_1+rep);
    postorder_integer_avl(tree_avl->avl_root, depth, maxdepth_1+REP+rep);
    postorder_integer_rb(tree_rb->rb_root, depth, maxdepth_1+2*REP+rep);

    for (i=0; i<1024; i++) {
    bst_delete(tree_bst, randEle+i);
    avl_delete (tree_avl, randEle+i);
    rb_delete (tree_rb, randEle+i);
    }

    postorder_integer_bst(tree_bst->bst_root, depth, maxdepth_2+rep);
    postorder_integer_avl(tree_avl->avl_root, depth, maxdepth_2+REP+rep);
    postorder_integer_rb(tree_rb->rb_root, depth, maxdepth_2+2*REP+rep);

    for (i=2048; i<4096; i++) {
    void **p1 = bst_probe(tree_bst, randEle+i);
    void **p2 = avl_probe(tree_avl, randEle+i);
    void **p3 = rb_probe(tree_rb, randEle+i);
    }

    postorder_integer_bst(tree_bst->bst_root, depth, maxdepth_3+rep);
    postorder_integer_avl(tree_avl->avl_root, depth, maxdepth_3+REP+rep);
    postorder_integer_rb(tree_rb->rb_root, depth, maxdepth_3+2*REP+rep);

  }
  int max_, min_, avg_;

  printf("after first insertion\n");
    max_ = max(maxdepth_1, maxdepth_1+REP-1);
    min_ = min(maxdepth_1, maxdepth_1+REP-1);
    avg_ = avg(maxdepth_1, maxdepth_1+REP-1);
    printf("bst %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_1+REP, maxdepth_1+2*REP-1);
    min_ = min(maxdepth_1+REP, maxdepth_1+2*REP-1);
    avg_ = avg(maxdepth_1+REP, maxdepth_1+2*REP-1);
    printf("avl %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_1+2*REP, maxdepth_1+3*REP-1);
    min_ = min(maxdepth_1+2*REP, maxdepth_1+3*REP-1);
    avg_ = avg(maxdepth_1+2*REP, maxdepth_1+3*REP-1);
    printf("rb %d %d %d\n", max_, min_, avg_);
  printf("after removal\n");
    max_ = max(maxdepth_2, maxdepth_2+REP-1);
    min_ = min(maxdepth_2, maxdepth_2+REP-1);
    avg_ = avg(maxdepth_2, maxdepth_2+REP-1);
    printf("bst %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_2+REP, maxdepth_2+2*REP-1);
    min_ = min(maxdepth_2+REP, maxdepth_2+2*REP-1);
    avg_ = avg(maxdepth_2+REP, maxdepth_2+2*REP-1);
    printf("avl %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_2+2*REP, maxdepth_2+3*REP-1);
    min_ = min(maxdepth_2+2*REP, maxdepth_2+3*REP-1);
    avg_ = avg(maxdepth_2+2*REP, maxdepth_2+3*REP-1);
    printf("rb %d %d %d\n", max_, min_, avg_);
  printf("after 2nd insertion\n");
    max_ = max(maxdepth_3, maxdepth_3+REP-1);
    min_ = min(maxdepth_3, maxdepth_3+REP-1);
    avg_ = avg(maxdepth_3, maxdepth_3+REP-1);
    printf("bst %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_3+REP, maxdepth_3+2*REP-1);
    min_ = min(maxdepth_3+REP, maxdepth_3+2*REP-1);
    avg_ = avg(maxdepth_3+REP, maxdepth_3+2*REP-1);
    printf("avl %d %d %d\n", max_, min_, avg_);
    max_ = max(maxdepth_3+2*REP, maxdepth_3+3*REP-1);
    min_ = min(maxdepth_3+2*REP, maxdepth_3+3*REP-1);
    avg_ = avg(maxdepth_3+2*REP, maxdepth_3+3*REP-1);
    printf("rb %d %d %d\n", max_, min_, avg_);

  return 0;
}
