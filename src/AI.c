#include <stdio.h>
#include "AI.h"
#include "Moves.h"

extern int tracker;

//Copies the score count of a piece
void copyIntBoard(int s[8][8],int d[8][8]) {
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			d[i][j]=s[i][j];
		}
	}
}

//Copies the board into a temporary board
void copyBoard(PIECE *s[8][8],PIECE *d[8][8]) {
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			d[i][j]=s[i][j];
		}
	}
}

//Gives the score count for each pieces on each position of the board
int scoreCount(PIECE *board[8][8], char AIColor) {
int bKnightBaseVal[8][8]={
	{0, 1, 2, 3, 3, 2, 1, 0},
	{1, 2, 5, 6, 6, 5, 2, 1},
	{2, 5, 8, 8, 8, 8, 5, 2},
	{3, 6, 8,10,10, 8, 6, 3},
	{3, 6, 8,10,10, 8, 6, 3},
	{2, 5, 8, 8, 8, 8, 5, 2},
	{1, 2, 5, 6, 6, 5, 2, 1},
	{0, 1, 2, 3, 3, 2, 1, 0}
};

int wKnightBaseVal[8][8]={
	{0, 1, 2, 3, 3, 2, 1, 0},
	{1, 2, 5, 6, 6, 5, 2, 1},
	{2, 5, 8, 8, 8, 8, 5, 2},
	{3, 6, 8,10,10, 8, 6, 3},
	{3, 6, 8,10,10, 8, 6, 3},
	{2, 5, 8, 8, 8, 8, 5, 2},
	{1, 2, 5, 6, 6, 5, 2, 1},
	{0, 1, 2, 3, 3, 2, 1, 0}
};

int wPawnBaseVal[8][8]={
	{8, 9,10,10,10,10, 9, 8},
	{5, 6, 7, 8, 8, 7, 6, 5},
	{4, 5, 6, 7, 7, 6, 5, 4},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{2, 3, 4, 5, 5, 4, 3, 2},
	{1, 2, 3, 4, 4, 3, 2, 1},
	{1, 1, 2, 3, 3, 2, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int bPawnBaseVal[8][8]={
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 2, 3, 3, 2, 1, 1},
	{1, 2, 3, 4, 4, 3, 2, 1},
	{2, 3, 4, 5, 5, 4, 3, 2},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{4, 5, 6, 7, 7, 6, 5, 4},
	{5, 6, 7, 8, 8, 7, 6, 5},
	{8, 9,10,10,10,10, 9, 8}
};

int wKingBaseVal[8][8]= {
	{3, 2, 1, 0, 0, 1, 2, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 4, 3, 3, 3, 3, 4, 3},
	{4, 4, 4, 3, 3, 4, 4, 4},
	{6, 6, 4, 4, 4, 4, 6, 6},
	{9,10, 7, 6, 6, 7,10, 9}
};

int bKingBaseVal[8][8]= {
	{9,10, 7, 6, 6, 7,10, 9},
	{6, 6, 4, 4, 4, 4, 6, 6},
	{4, 4, 4, 3, 3, 4, 4, 4},
	{3, 4, 3, 3, 3, 3, 4, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 2, 3, 0, 0, 1, 2, 3},
	{3, 2, 1, 0, 0, 1, 2, 3}
};

int wQueenBaseVal[8][8]= {
	{2, 3, 4, 5, 5, 4, 3, 2},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{4, 4, 6, 7, 7, 6, 5, 4},
	{5, 4, 7, 8, 8, 7, 6, 5},
	{5, 2, 7, 8, 8, 7, 6, 5},
	{4, 2, 6, 7, 7, 6, 5, 4},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{2, 3, 4, 5, 5, 4, 3, 2}
};

int bQueenBaseVal[8][8]= {
	{2, 3, 4, 5, 5, 4, 3, 2},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{4, 4, 6, 7, 7, 6, 5, 4},
	{5, 4, 7, 8, 8, 7, 6, 5},
	{5, 2, 7, 8, 8, 7, 6, 5},
	{4, 2, 6, 7, 7, 6, 5, 4},
	{3, 4, 5, 6, 6, 5, 4, 3},
	{2, 3, 4, 5, 5, 4, 3, 2}
};

int wRookBaseVal[8][8]= {
	{5, 5, 5, 5, 5, 5, 5, 5},
	{6, 7, 7, 7, 7, 7, 7, 6},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{5, 5, 5, 7, 7, 5, 5, 5}
};

int bRookBaseVal[8][8]= {
	{5, 5, 5, 7, 7, 5, 5, 5},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{6, 7, 7, 7, 7, 7, 7, 6},
	{5, 5, 5, 5, 5, 5, 5, 5}
};

int wBishopBaseVal[8][8]= {
	{2, 3, 3, 3, 3, 3, 3, 2},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{3, 5, 7, 9, 9, 7, 5, 3},
	{3, 7, 7, 9, 9, 7, 7, 3},
	{3, 7, 9, 9, 9, 9, 7, 3},
	{3, 9, 9, 9, 9, 9, 9, 3},
	{3, 7, 5, 5, 5, 5, 7, 3},
	{2, 3, 3, 3, 3, 3, 3, 2}
};

int bBishopBaseVal[8][8]= {
	{2, 3, 3, 3, 3, 3, 3, 2},
	{3, 7, 5, 5, 5, 5, 7, 3},
	{3, 9, 9, 9, 9, 9, 9, 3},
	{3, 7, 9, 9, 9, 9, 7, 3},
	{3, 7, 7, 9, 9, 7, 7, 3},
	{3, 5, 7, 9, 9, 7, 5, 3},
	{3, 5, 5, 5, 5, 5, 5, 3},
	{2, 3, 3, 3, 3, 3, 3, 2}
};

	PIECE *piece;
	int baseVal[8][8]= {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};
	int AITotal=0;
	int pTotal=0;
	int valMove=0;
	int tScore;

	//Copies the score count of a piece
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			if(board[i][j]!=NULL) {
				piece=board[i][j];
				if(piece->color==AIColor) {
					if(piece->piece=='P') {
						copyIntBoard(bPawnBaseVal,baseVal);
					}
					else if(piece->piece=='R') {
						copyIntBoard(bRookBaseVal,baseVal);
					}
					else if(piece->piece=='H') {
						copyIntBoard(bKnightBaseVal,baseVal);
					}
					else if(piece->piece=='B') {
						copyIntBoard(bBishopBaseVal,baseVal);
					}
					else if(piece->piece=='Q') {
						copyIntBoard(bQueenBaseVal,baseVal);
					}
					else if(piece->piece=='K') {
						copyIntBoard(bKingBaseVal,baseVal);

					}
					AITotal+=(piece->value+baseVal[i][j]);
				}
				else {
					if(piece->piece=='P') {
						copyIntBoard(wPawnBaseVal,baseVal);
					}
					else if(piece->piece=='R') {
						copyIntBoard(wRookBaseVal,baseVal);
					}
					else if(piece->piece=='H') {
						copyIntBoard(wKnightBaseVal,baseVal);
					}
					else if(piece->piece=='B') {
						copyIntBoard(wBishopBaseVal,baseVal);
					}
					else if(piece->piece=='Q') {
						copyIntBoard(wQueenBaseVal,baseVal);
					}
					else if(piece->piece=='K') {
						copyIntBoard(wKingBaseVal,baseVal);
					}
					pTotal+=(piece->value+baseVal[i][j]);
				}
				//The above code gets the base score of the piece
				//it also gives it points based on its positioning
				for(int k=0;k<8;k++) {
					for(int m=0;m<8;m++) {
						valMove=checkValid(board,i,j,k,m,piece->color,1);
						if(valMove == 1) {
							if(board[k][m]==NULL) {
								if(piece->color!=AIColor) {
									AITotal+=5;							//add 5 for every open square threatened
								}
								else {
									pTotal+=5;
								}
							}
							else {
								if(board[k][m]->color!=AIColor) {
									AITotal+=board[k][m]->value/5;
								}
								else {
									pTotal+=board[k][m]->value/5; 		//adds value of piece being threatened
								}	
							}
						}
					}
				}
				//Above code checks threatened squares and pieces and awards points
			}	
		}
	}
	//printf("pTotal is: %d, AITotal is %d \n",pTotal,AITotal);
	tScore=-pTotal+AITotal;
	return tScore;
}

//More advanced version of AI
void AIMove(PIECE *board[8][8],char AIColor) {
	NODE *root=createNode();
	NODE *old=NULL;

	int valMove;;
	int score;

	PIECE *piece;

	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			piece=board[i][j];
			if(piece!=NULL) {
				if(piece->color==AIColor) {
					for(int k=0;k<8;k++) {
						for(int m=0;m<8;m++) {
							valMove=checkValid(board,i,j,k,m,AIColor,1);
							if(valMove==1) {
								PIECE *temp[8][8];
								copyBoard(board,temp);
								movePiece(temp,i,j,k,m,1);
								score=scoreCount(temp,AIColor);
								NODE *new=createNode();
								new->score=score;
								copyBoard(temp,new->board);
								new->sRow=i;
								new->sColumn=j;
								new->tRow=k;
								new->tColumn=m;
								new->prev=old;
								root->child=new;
								old=new;
							}
						}
					}
				}
			}
		}
	}
	NODE *best;
	NODE *current;
	NODE *temp;
	current=root->child;
	best=current;
	int topScore=current->score;
	//printf("Scores are:%d for (%c,%d) to (%c,%d)\n",current->score,numToLetter(current->sColumn),8-current->sRow,numToLetter(current->tColumn),8-current->tRow);
	
	while(current->prev!=NULL) {
		current=current->prev;
		//printf("Scores are:%d for (%c,%d) to (%c,%d)\n",current->score,numToLetter(current->sColumn),8-current->sRow,numToLetter(current->tColumn),8-current->tRow);

		if(current->score > topScore) {
			temp=best;
			best=current;
			deleteNode(temp);
			topScore=current->score;
		}
		else {
			deleteNode(current);
		}
	}
	deleteNode(root);
	printf("AI Moves %c from (%c,%d) to (%c,%d)\n",board[best->sRow][best->sColumn]->piece,numToLetter(best->sColumn),8-best->sRow,numToLetter(best->tColumn),8-best->tRow);
	movePiece(board,best->sRow,best->sColumn,best->tRow,best->tColumn,1);
	pawnUpgrade(board, best->tRow, best->tColumn,0);
	tracker = enPassantTracker(board, best->sRow, best->sColumn, best->tRow, best->tColumn);
	deleteNode(best);
}

//easy version of AI
void randomMove(PIECE *board[8][8],char AIColor) {
	int checkVal=0;
	int tRow,tColumn,sRow,sColumn;
	char color;
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			if(board[i][j]!=NULL) {
				if(board[i][j]->color == AIColor){
					for(int k=0;k<8;k++) {
						for(int m=0;m<8;m++) {
							if(AIColor=='B') {
								color='W';
							}
							else {
								color='B';
							}
							checkVal=checkValid(board,i,j,k,m,color,1);
							if(checkVal==1) {
								sRow=i;
								sColumn=j;
								tRow=k;
								tColumn=m;
								break;
							}
						}
						if(checkVal==1) {
							break;
						}
					}
				}
			}
			if(checkVal==1) {
				break;
			}
		}
		if(checkVal==1) {
			break;
		}		
	}
	if(checkVal==1) {
		movePiece(board,sRow,sColumn,tRow,tColumn,1);
	}
}