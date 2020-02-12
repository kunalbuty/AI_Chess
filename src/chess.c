#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <windows.h>
#include "Pieces.h"
#include "Possibilities.h"
#include "Moves.h"
#include "AI.h"

int tracker;
int gameOver=0;
int pColor, gMode, gOption, gDifficulty;
int restart = 0;
char AIColor;
int move_num = 1;
int turn=0;

void printMenu();
void printBoard();
void initializeBoard();
void AIGame();
void PVPGame();
void quitGame(PIECE *board[8][8]);
void undo();
void blackUndo();


/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KWHT  "\x1B[37m"

PIECE *board[8][8]= {
	{ NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

PIECE *board1[8][8]= {
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

PIECE *board2[8][8]= {
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

PIECE *board3[8][8]= {
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

PIECE *board4[8][8]= {
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
        { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

void printMenu() {
	printf("Select options: \n\n Game mode: \n 1 for Play vs another player\n 2 for Play vs AI\n");
	do{
		scanf("%d",&gMode);
	}while(gMode != 1 && gMode != 2);
	if (gMode==2){
		printf("Choose a difficulty (1 for easy, 2 for hard).\n");
		do{
			scanf("%d",&gDifficulty);
		}while(gDifficulty != 1 && gDifficulty!= 2);
		printf("Player 1 choose a side: \n 1 for White\n 2 for Black\n");
		do{
			scanf("%d",&pColor);
		}while(pColor != 1 && pColor != 2);
	}
}

//prints the chess board
void printBoard(PIECE *board[8][8]) {	
	int i,j;
	printf("\n  +---+---+---+---+---+---+---+---+\n");
	for (i = 0;i < 8;i++) {
		printf("%d ",8-i);
		for (j = 0;j < 8;j++) {
			if(board[i][j]!=NULL) {
				if(board[i][j]->color=='B') {
					printf("| ");
					printf("%sb%c%s",KRED,board[i][j]->piece,KNRM);	//Make black pieces red just to discern colors better 
				}
				else {
					printf("| ");

					printf("%sw%c%s" ,KWHT,board[i][j]->piece,KNRM);
				}
			}
			else {
				printf("|   ");
			}
		}
		printf("|\n  +---+---+---+---+---+---+---+---+\n");
	}
	printf("    a   b   c   d   e   f   g   h   \n \n");
}



void initializeBoard(PIECE *board[8][8]) {
	
	PIECE *p;

	//Black Pieces
	
	p=createPiece('B','R',500);
	board[0][0]=p;
	p=createPiece('B','H',300);
	board[0][1]=p;
	p=createPiece('B','B',300);
	board[0][2]=p;
	p=createPiece('B','Q',900);
	board[0][3]=p;

	p=createPiece('B','K',10000);
	board[0][4]=p;

	p=createPiece('B','R',500);
	board[0][7]=p;
	p=createPiece('B','H',300);
	board[0][6]=p;
	p=createPiece('B','B',300);
	board[0][5]=p;
	p=createPiece('B','P',100);
	board[1][0]=p;
	p=createPiece('B','P',100);
	board[1][1]=p;
	p=createPiece('B','P',100);
	board[1][2]=p;
	p=createPiece('B','P',100);
	board[1][3]=p;
	p=createPiece('B','P',100);
	board[1][4]=p;
	p=createPiece('B','P',100);
	board[1][5]=p;
	p=createPiece('B','P',100);
	board[1][6]=p;
	p=createPiece('B','P',100);
	board[1][7]=p; 
	
	//White pieces
	p=createPiece('W','R',500);
	board[7][0]=p;

	p=createPiece('W','H',300);
	board[7][1]=p;

	p=createPiece('W','B',300);
	board[7][2]=p;

	p=createPiece('W','Q',900);
	board[7][3]=p;

	p=createPiece('W','K',10000);
	board[7][4]=p;

	p=createPiece('W','R',500);
	board[7][7]=p;

	p=createPiece('W','H',300);
	board[7][6]=p;

	p=createPiece('W','B',300);
	board[7][5]=p;

	p=createPiece('W','P',100);
	board[6][0]=p;
	p=createPiece('W','P',100);
	board[6][1]=p;
	p=createPiece('W','P',100);
	board[6][2]=p;
	p=createPiece('W','P',100);
	board[6][3]=p;
	p=createPiece('W','P',100);
	board[6][4]=p;
	p=createPiece('W','P',100);
	board[6][5]=p;
	p=createPiece('W','P',100);
	board[6][6]=p;
	p=createPiece('W','P',100);
	board[6][7]=p;	

	
	int a=0;
	for(int i=0;i<8;i++) {
		for(int j=0;j<8;j++) {
			if(board[i][j]!=NULL) {
				deadPieces[a]=board[i][j];
				a++;
			}
		}
	}
	//printf("a is: %d \n", a);
}
	//saves moves to Log.txt
void logMove(int sColumn, int sRow, int tColumn, int tRow)
{   
	
    FILE *output = fopen("Log.txt", "a"); //write only
    if (output == NULL)
    {
        printf("File could not be found");
	exit(1);
    }
	fprintf(output, " Move #%d \n", move_num);
    fprintf(output, " Piece to Destination: %c%c%d \n\n", board[sRow][sColumn]->piece, numToLetter(tColumn), 8-tRow);
    fclose(output);

    move_num++;

    return;
}

void quitGame(PIECE *board[8][8]){
	printf("You quit the game.\n");
	for(int i=0;i<32;i++) {
		deletePiece(deadPieces[i]);
	}
	exit(10);
}

void undo(){
	if (turn%2==0){
		for(int i=0; i<8; i++){
			for(int j=0;j<8;j++){
				board[i][j]=board2[i][j];
			}
		}
	}
	else if (turn%2==1){
		for(int i=0; i<8; i++){
                        for(int j=0;j<8;j++){
                                board[i][j]=board1[i][j];
                        }
                }
        }
}

void blackUndo(){
        if (turn%2==0){
                for(int i=0; i<8; i++){
                        for(int j=0;j<8;j++){
                                board[i][j]=board4[i][j];
                        }
                }
        }
        else if (turn%2==1){
                for(int i=0; i<8; i++){
                        for(int j=0;j<8;j++){
                                board[i][j]=board3[i][j];
                        }
                }
        }
}

void AIGame() {
	int valid=0;
	char wsource[2];
	char wtarget[2];
	char bsource[2];
	char btarget[2];
	char temp[2];
	int tColumn,tRow,sColumn,sRow;

    if (pColor == 1) {
        AIColor = 'B';		//If player is White, then AI is black 
        while(valid == 0){ 
		int check=checkCheck(board,'W');
			printBoard(board);
			if(check==1) {
				gameOver=checkCheckMate(board,'W',0);  
				if(gameOver == 1){
					printf("Checkmate. Game over!\n");
					quitGame(board);
				}
				else{
					printf("Current player is in check!\n");
				}
			}
			do{					          
				printf("It's White's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\n");
				scanf(" %s", temp);
				if(temp[0] == 'q') {
					quitGame(board);
				}
				else{
					wsource[0] = temp[0];
					wsource[1] = temp[1];
				}
				printf("\nWhere do you want to move it?\n");
				scanf(" %s",wtarget);
				tColumn=letterToNum(wtarget[0]);
				sColumn=letterToNum(wsource[0]);
				tRow=letterToNum(wtarget[1]);
				sRow=letterToNum(wsource[1]);
				if(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1) {
					printf("That is not a valid move!\n");
				}
				else if(board[sRow][sColumn]==NULL){
					printf("No pieces there\n");
				}
			}while(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1 || board[sRow][sColumn]==NULL);
			int checkVal = checkValid(board,sRow,sColumn,tRow,tColumn,'W',0);
			printf("checkVal is: %d\n", checkVal);
			if(checkVal==1){
				printf("\nMade it here\n");
				logMove(sColumn,sRow,tColumn,tRow);
				movePiece(board,sRow,sColumn,tRow,tColumn,0);
				pawnUpgrade(board, tRow, tColumn, 1);
				//printf("\ntracker: %d", tracker);
				tracker = enPassantTracker(board, sRow, sColumn, tRow, tColumn);
				//printf("\ntracker: %d", tracker);
				valid = 1;
			}
		}
		if (gDifficulty == 1){
			randomMove(board,AIColor);
		}
		else{
			AIMove(board,AIColor);
		}
		valid=0;
    }
    else {
        AIColor = 'W'; 	//If player is black, then AI is white 
		if (gDifficulty == 1){
			randomMove(board,AIColor);
		}
		else{
			AIMove(board,AIColor);
		}
        while(valid==0) {           
			int check=checkCheck(board,'B');
			printBoard(board);
			if(check==1) {
				gameOver=checkCheckMate(board,'B',0); 
				if(gameOver == 1){
					printf("Checkmate. Game over!\n");
					quitGame(board);  
				}
				else{
					printf("Current player is in check!\n");
				}
			}
			do{
				printf("It's Black's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\n");
				scanf(" %s", temp);
				if(temp[0]=='q') {
					quitGame(board);
				}
				else{
					bsource[0] = temp[0];
					bsource[1] = temp[1];
				}
				printf("\nWhere do you want to move it? \n");
				scanf(" %s", btarget);
				
				tColumn=letterToNum(btarget[0]);
				sColumn=letterToNum(bsource[0]);
				tRow=letterToNum(btarget[1]);
				sRow=letterToNum(bsource[1]);
				if(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1) {
					printf("That is not a valid move!\n");
				}
				else if (board[sRow][sColumn]==NULL){
					printf("No pieces there\n");
				}
			}while(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1||board[sRow][sColumn]==NULL);
			int checkVal = checkValid(board,sRow,sColumn,tRow,tColumn,'B',0);
			//printf("checkVal is: %d\n", checkVal);
			if(checkVal==1){
				//printf("\nMade it here\n");
				logMove(sColumn,sRow,tColumn,tRow);
				movePiece(board,sRow,sColumn,tRow,tColumn,0);
				pawnUpgrade(board, tRow, tColumn, 1);
				//printf("\ntracker: %d", tracker);
				tracker = enPassantTracker(board, sRow, sColumn, tRow, tColumn);
				//printf("\ntracker: %d", tracker);
				valid = 1;
			}
	}
	valid = 0;
    }
}

void PVPGame(){
    int valid=0;
    char wsource[2];
    char wtarget[2];
    char bsource[2];
    char btarget[2];
    char temp[2];
    int tColumn,tRow,sColumn,sRow;
	
    while(valid==0) {
    	int check=checkCheck(board,'W');
        printBoard(board);
		if(check==1) {
    		gameOver=checkCheckMate(board,'W',0);  
			if(gameOver == 1){
				printf("Checkmate. Game over!\n");
				quitGame(board); 
			}
			else{
				printf("Current player is in check!\n");
			}
    	}
		do{					          
            printf("It's White's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\nEnter 'u' to undo.\n");
            scanf(" %s", temp);
            if(temp[0] == 'q') {
            	quitGame(board);
            }
	    else if (temp[0]=='u'){
			undo();
			printBoard(board);
			printf("It's White's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\n");
			scanf(" %s", temp);
		if(temp[0] == 'q') {
			quitGame(board);
		}
	    }
	    wsource[0] = temp[0];
	    wsource[1] = temp[1];
            printf("\nWhere do you want to move it?\n");
            scanf(" %s",wtarget);
            tColumn=letterToNum(wtarget[0]);
            sColumn=letterToNum(wsource[0]);
            tRow=letterToNum(wtarget[1]);
            sRow=letterToNum(wsource[1]);
            if(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1) {
            	printf("That is not a valid move!\n");
            }
	    else if (board[sRow][sColumn]==NULL) {
		printf("No pieces there\n");
	    }
	}while(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1||board[sRow][sColumn]==NULL);
	int checkVal = checkValid(board,sRow,sColumn,tRow,tColumn,'W',0);
        //printf("checkVal is: %d\n", checkVal);
        if(checkVal==1){
		logMove(sColumn,sRow,tColumn,tRow);
        movePiece(board,sRow,sColumn,tRow,tColumn,0);
        pawnUpgrade(board, tRow, tColumn, 1);
	    tracker = enPassantTracker(board, sRow, sColumn, tRow, tColumn);
	    valid = 1;
        }
		/*else if(checkVal == 0){
			printf("Moving your king there will put you in check!\n"); 
		}*/
    }
    if (turn%2==1){
    	for (int i=0; i<8;i++){
            for(int j=0;j<8;j++){
        	board4[i][j]=board[i][j];
	    }
	}
    }
    else{
        for (int i=0; i<8;i++){
            for(int j=0;j<8;j++){
        	board3[i][j]=board[i][j];
            }
        }
    }
    valid=0;
    while(valid==0) { 
    	int check=checkCheck(board,'B');
        printBoard(board);
		if(check==1) {
    		gameOver=checkCheckMate(board,'B',0); 
			if(gameOver == 1){
				printf("Checkmate. Game over!\n");
				quitGame(board); 
			}
			else{
				printf("Current player is in check!\n");
			}
		}
	do{
            printf("It's Black's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\nEnter 'u' to undo.\n");
            scanf(" %s", temp);
            if(temp[0]=='q') {
                quitGame(board);
	    }
	    else if(temp[0]=='u'){
	    	blackUndo();
	    	printBoard(board);
	    	printf("It's Black's turn.\nWhere is the piece you want to move? \nEnter 'q' to quit the game.\n");
	    	scanf(" %s", temp);
	    	if(temp[0]=='q') {
		    quitGame(board);
	    	}
	    }
	    bsource[0] = temp[0];
	    bsource[1] = temp[1];
            printf("\nWhere do you want to move it? \n");
            scanf(" %s", btarget);
        
            tColumn=letterToNum(btarget[0]);
            sColumn=letterToNum(bsource[0]);
            tRow=letterToNum(btarget[1]);
            sRow=letterToNum(bsource[1]);
            if(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1) {
            	printf("That is not a valid move!\n");
            }
	    else if (board[sRow][sColumn]==NULL){
		printf("No pieces there\n");
	    }
	}while(tColumn==-1 || tRow==-1 || sRow==-1 || sColumn==-1||board[sRow][sColumn]==NULL);
	
        int checkVal = checkValid(board,sRow,sColumn,tRow,tColumn,'B',0);
        //printf("checkVal is: %d\n", checkVal);
        if(checkVal==1){
	    logMove(sColumn,sRow,tColumn,tRow);
       	movePiece(board,sRow,sColumn,tRow,tColumn,0);
	    pawnUpgrade(board, tRow, tColumn, 1);
	    tracker = enPassantTracker(board, sRow, sColumn, tRow, tColumn);
	    valid = 1;
        }
		/*else if(checkVal == 0 && board[sRow][sColumn]->piece=='K'){
			printf("Moving your king there will put you in check!\n"); 
		}*/
    }
}
int main() {
	initializeBoard(board);
	initializeBoard(board1);
	initializeBoard(board2);
	initializeBoard(board3);
	initializeBoard(board4);
	printMenu();
	while(gameOver == 0){
		if (gMode ==2){
			AIGame();
		}
		else if (gMode == 1){
			PVPGame();
			if (turn%2==1){
				for (int i=0; i<8;i++){
					for(int j=0;j<8;j++){
						board1[i][j]=board[i][j];
					}
				}
			}
			else{
				for (int i=0; i<8;i++){
                    for(int j=0;j<8;j++){
                        board2[i][j]=board[i][j];
                    }
                }
            }
			turn+=1;
		}
	}
}
