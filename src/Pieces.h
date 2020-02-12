/*********************************************************************/
/*                                                                   */
/* Author: Marvin Neil Sabas                                         */
/* Date: 01/13/2019                                                  */
/*                                                                   */
/* Pieces.h: header file for Pieces chess module                       */
/*                                                                   */
/*********************************************************************/

#ifndef PIECES_H
#define PIECES_H

typedef struct {  //PIECE struct contains members: color, piece, and value. These members make each chess piece distinguishable. 
        char color;
        char piece;
        int value;
} PIECE;

PIECE *createPiece(char color,char piece, int value); //Function to create each chess piece. 

void deletePiece(PIECE *p);  //deletePiece function in charge of deleting/freeing memory alloc'ed for chess pieces. 

#endif /* PIECES_H */ 

/* EOF PIECES.h */
