#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "Pieces.h"

int gameOver;
//Allocate memory for each member (color, piece, and value) in the PIECE struct
PIECE *createPiece(char color,char piece, int value) {
	PIECE *p=malloc(sizeof(PIECE));

	if(p==NULL) {
        printf("The memory allocation failed");
        return NULL;
    }
    else {
    	p->color=color;
    	p->piece=piece;
        p->value=value;
    	return p;
    }
}
//Delete each chess piece to avoid memory leaks
void deletePiece(PIECE *p) {
	if(p!=NULL) {
		assert(p);
		free(p);
	}
}
