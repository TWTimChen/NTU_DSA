#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "avl.h"
#include "rb.h"
#define MAX_LIMIT 1000

void postorder_string_bst(const struct bst_node *node){
  if (node == NULL)
    return;

  printf ("%s ", ((char *)node->bst_data));
  if (node->bst_link[0] != NULL || node->bst_link[1] != NULL){
      putchar('(');

      postorder_string_bst(node->bst_link[0]);
      putchar(',');
      putchar(' ');
      postorder_string_bst(node->bst_link[1]);
      putchar(')');
  }
}

void postorder_string_avl(const struct avl_node *node){
  if (node == NULL)
    return;

  printf ("%s ", ((char *)node->avl_data));
  if (node->avl_link[0] != NULL || node->avl_link[1] != NULL){
      putchar('(');

      postorder_string_avl(node->avl_link[0]);
      putchar(',');
      putchar(' ');
      postorder_string_avl(node->avl_link[1]);
      putchar(')');
  }
}

void postorder_string_rb(const struct rb_node *node){
  if (node == NULL)
    return;

  printf ("%s ", ((char *)node->rb_data));
  if (node->rb_link[0] != NULL || node->rb_link[1] != NULL){
      putchar('(');

      postorder_string_rb(node->rb_link[0]);
      putchar(',');
      putchar(' ');
      postorder_string_rb(node->rb_link[1]);
      putchar(')');
  }
}

int string_compare(const void *pa, const void *pb, void *param)
{
  int cmp = strcmp((const char *)pa, (const char *)pb);
  if (cmp < 0)
    return -1;
  else if (cmp > 0)
    return +1;
  else
    return 0;
}

int main(){
  struct bst_table *tree_bst;  
  tree_bst = bst_create(string_compare, NULL, NULL);
  struct avl_table *tree_avl;  
  tree_avl = avl_create(string_compare, NULL, NULL);
  struct rb_table *tree_rb;  
  tree_rb = rb_create(string_compare, NULL, NULL);

  char str[MAX_LIMIT];
  scanf("%s", str);
  while (scanf("%s", str)!=EOF)
  {
    char* element = (char*) malloc((strlen(str))*sizeof(char));
    strcpy(element, str);

    void **p1 = bst_probe(tree_bst, element);
    void **p2 = avl_probe(tree_avl, element);
    void **p3 = rb_probe(tree_rb, element);
  }

  postorder_string_bst(tree_bst->bst_root);
  puts("");
  postorder_string_avl(tree_avl->avl_root);
  puts("");
  postorder_string_rb(tree_rb->rb_root);
  puts("");
  return 0;
}
