#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> //-lm
#include "linkedList.h"

//protoype methods
tnode* createFreqTable(char* txt);
tnode* createHuffmanTree(tnode* leafNodes);
void displayFreqTable(tnode* freqTable);
void displayAllFreqs(tnode* freqTable);
void encodeFile(char argv[], tnode* leafNodes);
void decodeFile(char argv[], tnode* treeRoot);
void reverseArray(int arr[], int start, int end);



int main(int argc, char *argv[]) {

  // Check the make sure the input parameters are correct

   if (argc != 3) {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);

    exit(1);

  }

  // Create the frequency table by reading the generic file

  struct tnode* leafNodes = createFreqTable("nums"); //make using array

  printf("FREQENCY TABLE -----------------\n");
  displayFreqTable(leafNodes);
  
  //printf("UNFILTERED FREQENCY TABLE -----------------\n"); 
  //displayAllFreqs(leafNodes);
  //Create the huffman tree from the frequency table

  struct tnode* treeRoot = createHuffmanTree(leafNodes); //linked list
  
  // encode

  if (strcmp(argv[1], "-e") == 0) {

    // Pass the leafNodes since it will process bottom up

    encodeFile("nums", leafNodes);

  } else { // decode

    // Pass the tree root since it will process top down

    decodeFile("nums", treeRoot);

  }

  return 0;

}

tnode* createFreqTable(char* txt) {

    tnode* freqTable = (tnode*)malloc(128*sizeof(tnode));

    //file pointer
    FILE* fp = fopen(txt, "r");

    //int for keeping track of index
    int index;

    for (int i = 0; i < 127; i++) {
      //initalize frequency table
       freqTable[i].c = i;
       freqTable[i].weight = 0;
    }

    //loop through all frequencies and add weight to characters in the file
    while ((index = fgetc(fp)) > 0) { //-1
       freqTable[index].weight++;
    }
    fclose(fp);
    return freqTable;
}

void displayFreqTable(tnode* freqTable) {
    for(int i = 0; i < 127; i++) {
        //only print character if its a character and it has a frequency greater than 1
        if (freqTable[i].weight >= 1) {
            printf("letter %c: freq %f\n", freqTable[i].c, freqTable[i].weight);
        }
    }

}
void displayAllFreqs(tnode* freqTable) {
  for(int i = 32; i < 127; i++) {
    printf("letter %c: freq %f\n", freqTable[i].c, freqTable[i].weight);
  } 
}

tnode* createHuffmanTree(tnode* leafNodes) {
    
    //make linkedlist first?
  LinkedList* huffTree = llCreate();

  //inital linked list
  for (int i = 0; i < 128; i++) {
  
    //if (leafNodes[i].weight > 0) {
    list_add_in_order(&huffTree , &leafNodes[i]);
    // }
  }
  

  //loop until there's one node
  for (int i = 0; i < 127; i++) {

    //remove first two lowest nodes and assign to temp nodes
    tnode* temp1 = remove_first(&huffTree);
    tnode* temp2 = remove_first(&huffTree);

    //combined weight of two removed nodes
    int weightC = temp1->weight + temp2->weight;

    //temp node to be added
    tnode* newLnode = (tnode*)malloc(1*sizeof(tnode));
    newLnode->weight = weightC;

    //change left and right
    newLnode->left = temp1;
    newLnode->right = temp2;
    temp1->parent = newLnode;
    temp2->parent = newLnode;


    //add new parent
    list_add_in_order(&huffTree , newLnode);
  
    }
  
   //printf("    %d \n",huffTree->value->c);
  // printf("  %d        %d\n",huffTree->value->left->c, huffTree->value->right->c);
   //printf("%d   %d\n",huffTree->value->left->left->c, huffTree->value->left->right->c);
   
  return remove_first(&huffTree);
 
}

void encodeFile(char* txt, tnode* leafNodes) {
  
  FILE* fp = fopen(txt, "r");
  FILE* fp2 = fopen("new", "w");
  int index;
  int byte[100];
  int byteSize = 0;

  for (int h = 0; h < 50; h++) {
    byte[h] = 0;
  }
  
  //loop to find and get characters until end of file
  while ((index = fgetc(fp)) != EOF) {
    int charcount;
    int count2 = 0;
    int bits[100];
    
    tnode* p = &leafNodes[index];



    //find character in leaf nodes array, then walk up tree and make code
    while (p->parent != NULL) {
      
      //see if the count node is the left of its parent and assignt the bit accordingly
      if (p == p->parent->left) {
         bits[count2] = 0;
      }

      else {
        bits[count2] = 1;
      }
    
      //go to the next bit in the array and set the pointer 
      count2++;
      p = p->parent;
    }
     
    //reverse bits
        for (int i = 0; i < count2/2; i++)
          {
            int temp = bits[i];
            bits[i] = bits[ count2- 1 - i];
            bits[count2 - 1 - i] = temp;
          }
     
    //loop that puts the bits into the byte
     for (int i = 0; i < count2; i++) {
      
      byte[byteSize] = bits[i];
      byteSize++;
      

      //if the byte array is greater than 8, write it to the file
      if (byteSize == 8 || index == EOF) {
          
          //print the array
          for (int e = 0; e < 8; e++) {
           fprintf(fp2,"%d",byte[e]);
           } 

           //clear the byte array
          for (int j = 0; j < 8; j++) {
            byte[j] = 0;
            }

          byteSize = 0;
          
        } 
      }
  }
   for (int e = 0; e < 8; e++) {
           fprintf(fp2,"%d",byte[e]);
           } 
}
void decodeFile(char* txt, tnode* treeRoot) {

FILE* fp = fopen(txt, "r");
FILE* fp2 = fopen("new", "w");


int index;
  int byte[100];
  int byteSize = 0;

  for (int h = 0; h < 50; h++) {
    byte[h] = 0;
  }
  
  //loop to find and get characters until end of file
  while ((index = fgetc(fp)) != EOF) {
    int charcount;
    int count2 = 0;
    int bits[100];
    
    tnode* p = &treeRoot;

//this is the same I just couldn' figure out encode in time
}
}

   

