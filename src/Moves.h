/*********************************************************************/
/*                                                                   */
/* Author: Marvin Neil Sabas                                         */
/* Date: 01/13/2019                                                  */
/*                                                                   */
/* Moves.h: header file for Moves chess module                       */
/*                                                                   */
/*********************************************************************/

#ifndef MOVES_H
#define MOVES_H
#include "Pieces.h"
#include "Possibilities.h" 

PIECE *deadPieces[32];

char numToLetter(int num);

int letterToNum(char letter); 

int checkValid(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn,char AIColor, int PlayerorAI);

void movePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn,int mPPlayerorAI);

void AImovePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn);

void CastlemovePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn,int CmPPlayerorAI);

int basicCheck(PIECE *board[8][8],int sRow,int sColumn,int tColumn,int tRow);

void knight(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]);

void rook(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]);

void bishop(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]);

void pawn(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int tracker); 

void queen(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]);

void king(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int QSWhiteCastlingEnabled, int KSWhiteCastlingEnabled, int QSBlackCastlingEnabled, int KSBlackCastlingEnabled);

void AIking(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int AIQSWhiteCastlingEnabled, int AIKSWhiteCastlingEnabled, int AIQSBlackCastlingEnabled, int AIKSBlackCastlingEnabled);

int checkCheck(PIECE *board[8][8], char color);

void pawnUpgrade(PIECE *board[8][8], int tRow, int tColumn, int pOrAI);

int checkCheckMate(PIECE *board[8][8],char color,int CCMPlayerorAI);

int enPassantTracker(PIECE *board[8][8], int sRow, int sColumn, int tRow, int tColumn);


#endif /* MOVES_H */ 

/* EOF MOVES.h */