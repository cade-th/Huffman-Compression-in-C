#include <stdio.h>
#include <stdlib.h> // malloc
#include "linkedList.h"

LinkedList* llCreate() {
  return NULL;
}
int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}
void llDisplay(LinkedList* ll) {
  
  LinkedList* p = ll;
  printf("[");
  
  while (p != NULL) {
    printf("%d, ", p->value->c);
    p = p->next;
  }
  printf("]\n");
}
void llAdd(LinkedList** ll, tnode* newValue) {
  // Create the new node
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = newValue;
  newNode->next = NULL;
  
  // Find the end of the list
  LinkedList* p = *ll;
  if (p == NULL) {  // Add first element
    *ll = newNode;  // This is why we need ll to be a **
  } else {
    while (p->next != NULL) {
      p = p->next;
    }
    
    // Attach it to the end
    p->next = newNode;
  }
}
void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
    free(oldP);
  }
  
}

//except that it takes the data in question and searches down the linked list 
//from the given point and places the node “in order” into the list.  
//“In order” will be based on weights so that the lowest two weighed nodes will always be at the front

void list_add_in_order(LinkedList** ll, tnode* newValue) {
  
  // Create the new node
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->next = NULL;
  newNode->value = newValue;
  
  //pointer to head
  LinkedList* p = *ll;

  if (p == NULL ){ //empty list case

      //place node at the head
       *ll = newNode;
  }

  //list isn't empty but it's just the head
  //compare weights of head and new node
  else if (p->value->weight > newValue->weight) {
    //new node will point at head
    newNode->next = *ll;
    //head becomes new node
    *ll = newNode;
  }

  else if (p != NULL) {
    //search down list
    while (p->next!= NULL) {
      //condition if next is bigger or if next is the same
      if ((p->next->value->weight) > (newValue->weight)) {
        
        //temp node 
        LinkedList* temp = p->next;

        p->next = newNode;
        newNode->next = temp;
        return;
      }
      else {
        p = p->next; //continue down the line
      }
      }
     llAdd(ll,newValue);
    } 
    
  }

tnode* remove_first(LinkedList** ll) {
  //temporary node pointing to head
  LinkedList* temp = *ll;
   //copy of what was at head node
  tnode* tempT = temp->value; //= *ll->value;

  *ll = temp->next;
  
  //free whatever node was at head
  free(temp);

  return tempT;

  

}



