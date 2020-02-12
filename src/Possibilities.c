#include "Possibilities.h"
#include <stdio.h>
#include <stdlib.h>
//Creates a NODE struct and allocates memory for all of its members.
NODE *createNode() {
	NODE *n=malloc(sizeof(NODE));

	if(n==NULL) {
        printf("The memory allocation failed");
        return NULL;
    }
    else {
    	n->score=0;
    	n->sRow=0;
    	n->sColumn=0;
    	n->tColumn=0;
    	n->tRow=0;
    	//n->board=NULL;
        n->next=NULL;
        n->prev=NULL;
        n->child=NULL;
        n->parent=NULL;
    	return n;
    }
}
//Deletes a NODE struct along with its members so as to avoid memory leaks. 
void deleteNode(NODE *n) {
	if(n!=NULL) {
		assert(n);
		free(n);
	}
}
