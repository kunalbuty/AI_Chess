/*********************************************************************/
/*                                                                   */
/* Author: Marvin Neil Sabas                                         */
/* Date: 01/13/2019                                                  */
/*                                                                   */
/* Possibilities.h: header file for Possibilities chess module       */
/*                                                                   */
/*********************************************************************/

#ifndef POSSIBILITIES_H
#define POSSIBILITIES_H
#include "Pieces.h"
#include <assert.h>

typedef struct NODE { //NODE struct contains members for the score and the source/destination of the board along with pointers for the AI's moves.
	int score;
	PIECE *board[8][8];
	int sColumn;
	int sRow;
	int tColumn;
	int tRow;
 	struct NODE *next;
	struct NODE *prev;
	struct NODE *child;
	struct NODE *parent;
}NODE;

NODE *createNode(); //Function to create a NODE.

void deleteNode(NODE *n); //Function to deleteNODE and its members.
	
#endif /* POSSIBILITIES_H */ 

/* EOF POSSIBILITIES.h */
