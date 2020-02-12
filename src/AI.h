/*********************************************************************/
/*                                                                   */
/* Author: Marvin Neil Sabas                                         */
/* Date: 01/13/2019                                                  */
/*                                                                   */
/* AI.h: header file for AI chess module                            */
/*                                                                   */
/*********************************************************************/

#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include "Pieces.h"
#include "Moves.h"
#include "Possibilities.h"

void copyIntBoard(int s[8][8],int d[8][8]);

void copyBoard(PIECE *s[8][8],PIECE *d[8][8]);

int scoreCount(PIECE *board[8][8], char AIColor) ;

void AIMove(PIECE *board[8][8],char AIColor) ;

void randomMove(PIECE *board[8][8],char AIColor) ;

#endif /* AI_H */ 

/* EOF AI.h */
