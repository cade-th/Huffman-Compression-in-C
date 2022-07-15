#include <stdio.h>
#include <stdlib.h> // malloc

struct tnode {
  double weight;
  int c;
  struct tnode* left;
  struct tnode* right;
  struct tnode* parent;
}; typedef struct tnode tnode;

typedef struct node {
  struct node* next;
  tnode* value;
} LinkedList;

LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, tnode* newValue);
void llFree(LinkedList* ll);
void list_add_in_order(LinkedList** ll, tnode* newValue);
tnode* remove_first(LinkedList** ll);