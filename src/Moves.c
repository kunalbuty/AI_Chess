#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Pieces.h"
#include "Possibilities.h"
#include "Moves.h"
#include "AI.h"

/******************************************/
//IF PlayerorAI == 0, it's PVP
//IF PlayerorAI == 1, it's PvAI
/*****************************************/

extern int tracker;
extern int gMode;

int EnableCastleMove = 0;	//starting value for EnableCastleMove; 0 = can't castle, 1 = can castle
int	MadeCastleMove = 0; //variable to avoid overlap of moves in movePiece 

//variables to check if Rook and Kings of each color haven't moved yet (for castling)
int wQsRook = 0; //0 means no previous moves have been made
int wKsRook = 0; //1 means a piece has made a previous move
int bQsRook = 0; 
int bKsRook = 0; 
int wKing = 0;
int bKing = 0;	


//Variables to check validity of queen side and king side castling conditions (QS = Queen side, KS = King side) 
int QSWhiteCastlingEnabled = 0;	//if 1, castling conditions are MET for the respective color and side 
int QSBlackCastlingEnabled = 0;		
int KSWhiteCastlingEnabled = 0;
int KSBlackCastlingEnabled = 0;  		

//SAME CASTLING VARIABLES BUT FOR AI 
int AIEnableCastleMove = 0;	
int	AIMadeCastleMove = 0; 

int AIwQsRook = 0;
int AIwKsRook = 0; 
int AIbQsRook = 0; 
int AIbKsRook = 0; 
int AIwKing = 0;
int AIbKing = 0;	

int AIQSWhiteCastlingEnabled = 0;	
int AIQSBlackCastlingEnabled = 0;		
int AIKSWhiteCastlingEnabled = 0;
int AIKSBlackCastlingEnabled = 0;  	

char numToLetter(int num) {
	char letter;
	if(num==0) {
		letter='a';
	}
	else if(num==1) {
		letter='b';
	}
	else if(num==2) {
		letter='c';
	}
	else if(num==3) {
		letter='d';
	}
	else if(num==4) {
		letter='e';
	}
	else if(num==5) {
		letter='f';
	}
	else if(num==6) {
		letter='g';
	}
	else if(num==7) {
		letter='h';
	}
	else {
		letter='z';
	}
	return letter;
}

int letterToNum(char letter) {
	int num;
	if(letter=='a') {
		num=0;
	}
	else if(letter=='b') {
		num=1;
	}
	else if(letter=='c') {
		num=2;
	}
	else if(letter=='d') {
		num=3;
	}
	else if(letter=='e') {
		num=4;
	}
	else if(letter=='f') {
		num=5;
	}
	else if(letter=='g') {
		num=6;
	}
	else if(letter=='h') {
		num=7;
	}
	else if(letter=='1') {
		num=7;	
	}
	else if(letter=='2') {
		num=6;
	}
	else if(letter=='3') {
		num=5;
	}
	else if(letter=='4') {
		num=4;
	}
	else if(letter=='5') {
		num=3;
	}
	else if(letter=='6') {
		num=2;
	}
	else if(letter=='7') {
		num=1;
	}
	else if(letter=='8') {
		num=0;
	}
	else {
		return -1;
	}
	return num;
}
int checkValid(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn,char AIColor, int PlayerorAI) {
	int valid[30][2];

	//int comp;
	//int checkSafe;

	//int comp;			
	//int checkSafe;

	int isValid=0;
	if(PlayerorAI == 0){
		if (AIColor != board[sRow][sColumn]->color){				//////////
			//printf("You are not allowed to move opponent's pieces\n");	//////////
			return 0;							//////////
		}
	}
	if(PlayerorAI == 0 || PlayerorAI == 1){
		if(tColumn==-1 || tRow==-1 || sColumn==-1 || sRow==-1) {
			printf("Please enter your input in the correct format (example: h8) \n\n");
			return 0;
		}
		if(board[sRow][sColumn]==NULL) {
			printf("There is no piece there! \n");
			return 0;
		}
	}
	if(board[sRow][sColumn]->piece=='H') {
		knight(board,sRow,sColumn,valid);
	}

	if(board[sRow][sColumn]->piece=='R') {
		rook(board,sRow,sColumn,valid);
	}


	if(board[sRow][sColumn]->piece=='B') {
		bishop(board,sRow,sColumn,valid);
	}

	if(board[sRow][sColumn]->piece=='P') {
		pawn(board,sRow,sColumn,valid,tracker);
		//printf("\ntracker: %d\n", tracker);
	}

	if(board[sRow][sColumn]->piece=='Q') {
		queen(board, sRow, sColumn, valid);
	}
	
	if(board[sRow][sColumn]->piece=='K') {
		if(PlayerorAI == 0){ //Checkvalid function used in PvP
			//if White player's turn (PVP)
			if(board[sRow][sColumn]->color == 'W'){
				//printf("Value of wKsRook is: %d, value of wKing is: %d\n", wKsRook,wKing); 
				//if conditions for QS or KS castling are valid for WHITE player ('R' & 'K' no previous moves + no piece btwn K and R)
				if(wQsRook == 0 && wKing == 0){
					//if Queen side (QS) castling conditions met (no pieces between King and Rook)
					if(board[7][1] == NULL && board[7][2] == NULL && board[7][3] == NULL){
						//printf("QS white conditions pass \n"); 
						QSWhiteCastlingEnabled = 1;
					}
					else{
						QSWhiteCastlingEnabled = 0;
					}
				}
				else{
					QSWhiteCastlingEnabled = 0;
				}
				if(wKsRook == 0 && wKing == 0){
					//if King side (KS) castling conditions met (no pieces between King and Rook)
					if(board[7][5] == NULL && board[7][6] == NULL){
						//printf("KS white conditions pass \n"); 
						KSWhiteCastlingEnabled = 1;
					}
					else{
						KSWhiteCastlingEnabled = 0;
					}
				}
				else{
					KSWhiteCastlingEnabled = 0;
				}
			}
			//if Black player's turn (PVP)
			else if(board[sRow][sColumn]->color == 'B'){
				//if conditions for QS or KS castling are valid for BLACK player ('R' & 'K' no previous moves + no piece btwn K and R)
				if(bQsRook == 0 && bKing == 0){
					//if Queen side (QS) castling conditions met 
					if(board[0][1] == NULL && board[0][2] == NULL && board[0][3] == NULL) {
						//printf("QS black conditions pass \n"); 
						QSBlackCastlingEnabled = 1;
					}
					else{
						QSBlackCastlingEnabled = 0;
					}
				}
				else{
					QSBlackCastlingEnabled = 0;
					}
				if(bKsRook == 0 && bKing == 0){
					//if King side (KS) castling conditions met 
					if(board[0][5] == NULL && board[0][6] == NULL){
						//printf("KS black conditions pass \n"); 
						KSBlackCastlingEnabled = 1;	
					}
					else{
						KSBlackCastlingEnabled = 0;
					}
				}
				else{
					KSBlackCastlingEnabled = 0;
				}
			}
		//Pass both WhiteCastlingEnabled and BlackCastlingEnabled values into king function    
		king(board,sRow,sColumn,valid,QSWhiteCastlingEnabled,KSWhiteCastlingEnabled,QSBlackCastlingEnabled,KSBlackCastlingEnabled);
		} 
		else if(PlayerorAI == 1){ //Checkvalid function used for AI game mode 
			if(AIColor == 'B'){
				//printf("KS white conditions pass 1\n"); 
				//AI IS BLACK SO WHITE HUMAN PLAYER MOVES REGULAR VARIABLES AND AI MOVES BLACK AI VARIABLES
				if(board[sRow][sColumn]->color == 'W'){
					//printf("KS white conditions pass 2\n"); 
					//if conditions for QS or KS castling are valid for WHITE player ('R' & 'K' no previous moves + no piece btwn K and R)
					if(wQsRook == 0 && wKing == 0){
						//if Queen side (QS) castling conditions met (no pieces between King and Rook)
						if(board[7][1] == NULL && board[7][2] == NULL && board[7][3] == NULL){
							//printf("QS white conditions pass \n"); 
							QSWhiteCastlingEnabled = 1;
						}
						else{
							QSWhiteCastlingEnabled = 0;
						}
					}
					else{
						QSWhiteCastlingEnabled = 0;
					}
					//printf("wKsRook value is: %d, wKing value is: %d \n", wKsRook, wKing);
					if(wKsRook == 0 && wKing == 0){
						//printf("KS white conditions pass 3\n"); 
						//if King side (KS) castling conditions met (no pieces between King and Rook)
						if(board[7][5] == NULL && board[7][6] == NULL){
							//printf("KS white conditions pass 4\n"); 
							KSWhiteCastlingEnabled = 1;
						}
						else{
							KSWhiteCastlingEnabled = 0;
						}
					}
					else{
						KSWhiteCastlingEnabled = 0;
					}
				king(board,sRow,sColumn,valid,QSWhiteCastlingEnabled,KSWhiteCastlingEnabled,QSBlackCastlingEnabled,KSBlackCastlingEnabled);
				}
				//Black AI's TURN 
				else if(board[sRow][sColumn]->color == 'B'){
					//if conditions for QS or KS castling are valid for BLACK player ('R' & 'K' no previous moves + no piece btwn K and R)
					if(AIbQsRook == 0 && AIbKing == 0){
						//if Queen side (QS) castling conditions met 
						if(board[0][1] == NULL && board[0][2] == NULL && board[0][3] == NULL) {
							//printf("QS black conditions pass \n"); 
							AIQSBlackCastlingEnabled = 1;
						}
						else{
							AIQSBlackCastlingEnabled = 0;
						}
					}
					else{
						AIQSBlackCastlingEnabled = 0;
						}
					if(AIbKsRook == 0 && AIbKing == 0){
						//if King side (KS) castling conditions met 
						if(board[0][5] == NULL && board[0][6] == NULL){
							//printf("KS black conditions pass \n"); 
							AIKSBlackCastlingEnabled = 1;	
						}
						else{
							AIKSBlackCastlingEnabled = 0;
						}
					}
					else{
						AIKSBlackCastlingEnabled = 0;
					}
					AIking(board,sRow,sColumn,valid,AIQSWhiteCastlingEnabled,AIKSWhiteCastlingEnabled,AIQSBlackCastlingEnabled,AIKSBlackCastlingEnabled);
				}
			}
			//AI IS WHITE IN THIS CASE 
			else if(AIColor == 'W'){
				//AI IS WHITE, SO WHITE AI MOVES AI VARIABLES AND PLAYER MOVES BLACK REGULAR VARIABLES
				if(board[sRow][sColumn]->color == 'W'){
					//if conditions for QS or KS castling are valid for WHITE player ('R' & 'K' no previous moves + no piece btwn K and R)
					if(AIwQsRook == 0 && AIwKing == 0){
						//if Queen side (QS) castling conditions met (no pieces between King and Rook)
						if(board[7][1] == NULL && board[7][2] == NULL && board[7][3] == NULL){
							//printf("QS white conditions pass \n"); 
							AIQSWhiteCastlingEnabled = 1;
						}
						else{
							AIQSWhiteCastlingEnabled = 0;
						}
					}
					else{
						AIQSWhiteCastlingEnabled = 0;
					}
					if(AIwKsRook == 0 && AIwKing == 0){
						//if King side (KS) castling conditions met (no pieces between King and Rook)
						if(board[7][5] == NULL && board[7][6] == NULL){
							//printf("KS white conditions pass \n"); 
							AIKSWhiteCastlingEnabled = 1;
						}
						else{
							AIKSWhiteCastlingEnabled = 0;
						}
					}
					else{
						AIKSWhiteCastlingEnabled = 0;
					}
				AIking(board,sRow,sColumn,valid,AIQSWhiteCastlingEnabled,AIKSWhiteCastlingEnabled,AIQSBlackCastlingEnabled,AIKSBlackCastlingEnabled);
				}
				//Black AI's TURN 
				else if(board[sRow][sColumn]->color == 'B'){
					//if conditions for QS or KS castling are valid for BLACK player ('R' & 'K' no previous moves + no piece btwn K and R)
					if(bQsRook == 0 && bKing == 0){
						//if Queen side (QS) castling conditions met 
						if(board[0][1] == NULL && board[0][2] == NULL && board[0][3] == NULL) {
							//printf("QS black conditions pass \n"); 
							QSBlackCastlingEnabled = 1;
						}
						else{
							QSBlackCastlingEnabled = 0;
						}
					}
					else{
						QSBlackCastlingEnabled = 0;
						}
					if(bKsRook == 0 && bKing == 0){
						//if King side (KS) castling conditions met 
						if(board[0][5] == NULL && board[0][6] == NULL){
							//printf("KS black conditions pass \n"); 
							KSBlackCastlingEnabled = 1;	
						}
						else{
							KSBlackCastlingEnabled = 0;
						}
					}
					else{
						KSBlackCastlingEnabled = 0;
					}
					king(board,sRow,sColumn,valid,QSWhiteCastlingEnabled,KSWhiteCastlingEnabled,QSBlackCastlingEnabled,KSBlackCastlingEnabled);
				}
			}
		}
	}

	for(int i=0;i<30;i++) {
		if(valid[i][0]==-1) {
			break;
		}
		//printf("A valid move is: %c%d.\n",numToLetter(valid[i][1]),8-valid[i][0]); 
		if(valid[i][0]==tRow && valid[i][1]==tColumn) {
			//printf("is valid is 1\n");
			isValid=1;
		}
	}
	
	if(isValid==0) {
		if(gMode !=2){
			//printf("The move that you have previously chosen is not a valid move! \n");
			for(int i=0;i<30;i++) {
				if(valid[i][0]==-1) {
					break;
				}
				//HINT function for PVP  
				else if(gMode !=2){
					printf("HINT! A valid move is: %c%d.\n",numToLetter(valid[i][1]),8-valid[i][0]);
				}
			}	
		}
		return 0;
	}
	else {
		PIECE *temp[8][8];
		copyBoard(board,temp);
		temp[tRow][tColumn] = temp[sRow][sColumn];
		temp[sRow][sColumn] = NULL;
		//printf("make it here pleaseeee \n");
		int check=checkCheck(temp,AIColor);
		//printf("make it here pleaseeee 1\n");
		//printf("check is: %d \n",check); 
		if(check==0) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
/*
void AImovePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn) { //just for AI to gather score values
	
	//en passant white
	if(sRow == 3 && tracker != -1) {
		if(board[sRow][tColumn] != NULL) {
			
			board[tRow + 1][tColumn] = NULL;
		}
		
	}
	//en passant black
	if(sRow == 4 && tracker != -1) {
		if(board[sRow][tColumn] != NULL) {
			board[tRow - 1][tColumn] = NULL;
		}
	}
	if(board[tRow][tColumn]!=NULL) {
		board[tRow][tColumn]=board[sRow][sColumn];
		board[sRow][sColumn]=NULL;
			//printf("I love making it here 1\n"); 
	}
	else {
		board[tRow][tColumn]=board[sRow][sColumn];
		board[sRow][sColumn]=NULL;
			//printf("I love making it here 2\n"); 
	}
	
}*/
void movePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn,int mPPlayerorAI) {
	//printf("\ntracker: %d\n", tracker);
	//printf("This should only print twice. \n"); 
	//printf("value of mPPlayerorAI is: %d \n", mPPlayerorAI); 
	if(mPPlayerorAI == 0){
		//Double check if the piece moved was a Rook or a King, to deny castling for that piece in future
		if(board[sRow][sColumn]->piece=='R') {
			if(board[sRow][sColumn]->color=='W') {
				if(sRow==7 && sColumn==0) {
					wQsRook=1;
					//printf("value of wQsRook is: %d \n", wQsRook); 
				}
				else if(sRow==7 && sColumn==7) {
					wKsRook=1;
					//printf("value of wKsRook is: %d \n", wKsRook); 
				}
			}
			else if(board[sRow][sColumn]->color=='B') {
				if(sRow==0 && sColumn==0) {
					bQsRook=1;
					//printf("value of bQsRook is: %d \n", bQsRook); 
				}
				else if(sRow==0 && sColumn==7) {
					bKsRook=1;
					//printf("value of bKsRook is: %d \n", bKsRook); 
				}
			}
		}
		else if(board[sRow][sColumn]->piece=='K') {
			if(board[sRow][sColumn]->color=='W') {
				wKing=1;
				//printf("value of wKing is: %d \n", wKing); 
			}
			else {
				bKing=1;
			}
		}
		
		//en passant white
		if(sRow == 3 && tracker != -1) {
			if(board[sRow][tColumn] != NULL) {
				
				board[tRow + 1][tColumn] = NULL;
			}
			
		}
		//en passant black
		if(sRow == 4 && tracker != -1) {
			if(board[sRow][tColumn] != NULL) {
				board[tRow - 1][tColumn] = NULL;
			}
		}

		//printf("value of EnableCastleMove is: %d \n", EnableCastleMove); 
		if (EnableCastleMove == 1){	//Player has castling enabled, not necessarily will make a castling move
			CastlemovePiece(board, sRow, sColumn, tRow, tColumn,0);
		}
		//printf("value of MadeCastleMove is: %d \n", MadeCastleMove);  
		if (EnableCastleMove == 0 && MadeCastleMove == 0){	//Player wants to make a non-castling move 
			if(board[tRow][tColumn]!=NULL) {
				board[tRow][tColumn]=board[sRow][sColumn];
				board[sRow][sColumn]=NULL;
					//printf("I love making it here 1\n"); 
			}
			else {
				board[tRow][tColumn]=board[sRow][sColumn];
				board[sRow][sColumn]=NULL;
					//printf("I love making it here 2\n"); 
			}
		}
		EnableCastleMove = 0; //Reset EnableCastleMove
		MadeCastleMove = 0; //Reset MadeCastleMove
	}

	else if(mPPlayerorAI == 1){ 
		//Double check if the piece moved was a Rook or a King, to deny castling for that piece in future
		if(board[sRow][sColumn]->piece=='R') {
			if(board[sRow][sColumn]->color=='W') {
				if(sRow==7 && sColumn==0) {
					AIwQsRook=1;
					//printf("value of wQsRook is: %d \n", wQsRook); 
				}
				else if(sRow==7 && sColumn==7) {
					AIwKsRook=1;
					//printf("value of wKsRook is: %d \n", wKsRook); 
				}
			}
			else if(board[sRow][sColumn]->color=='B') {
				if(sRow==0 && sColumn==0) {
					AIbQsRook=1;
					//printf("value of bQsRook is: %d \n", bQsRook); 
				}
				else if(sRow==0 && sColumn==7) {
					AIbKsRook=1;
					//printf("value of bKsRook is: %d \n", bKsRook); 
				}
			}
		}
		else if(board[sRow][sColumn]->piece=='K') {
			if(board[sRow][sColumn]->color=='W') {
				AIwKing=1;
				//printf("value of wKing is: %d \n", wKing); 
			}
			else {
				AIbKing=1;
			}
		}
		
		//en passant white
		if(sRow == 3 && tracker != -1) {
			if(board[sRow][tColumn] != NULL) {
				
				board[tRow + 1][tColumn] = NULL;
			}
			
		}
		//en passant black
		if(sRow == 4 && tracker != -1) {
			if(board[sRow][tColumn] != NULL) {
				board[tRow - 1][tColumn] = NULL;
			}
		}

		//printf("value of AIEnableCastleMove is: %d \n", AIEnableCastleMove); 
		if (AIEnableCastleMove == 1){	//Player has castling enabled, not necessarily will make a castling move
			CastlemovePiece(board, sRow, sColumn, tRow, tColumn,1);
		}
		//printf("value of AIMadeCastleMove is: %d \n", AIMadeCastleMove);  
		if (AIEnableCastleMove == 0 && AIMadeCastleMove == 0){	//Player wants to make a non-castling move 
			if(board[tRow][tColumn]!=NULL) {
				board[tRow][tColumn]=board[sRow][sColumn];
				board[sRow][sColumn]=NULL;
			}
			else {
				board[tRow][tColumn]=board[sRow][sColumn];
				board[sRow][sColumn]=NULL;
			}
		}
		AIEnableCastleMove = 0; //Reset AIEnableCastleMove
		AIMadeCastleMove = 0; //Reset AIMadeCastleMove
	}		
}

void CastlemovePiece(PIECE *board[8][8], int sRow,int sColumn,int tRow,int tColumn, int CmPPlayerorAI){
	
	if(CmPPlayerorAI == 0){
		//White side castling (includes both king and queen side) PVP VERSION
		if(board[sRow][sColumn]->color=='W') {
			if(tRow == 7 && tColumn == 6){
				//King side castling BLACK 
				board[7][6] = board[7][4]; //Move wKing 
				board[7][4] = NULL;
				board[7][5] = board[7][7]; //Move wRook castling
				board[7][7] = NULL;  
				//printf("KS castle success \n");
				KSWhiteCastlingEnabled = 0;	//Deny castling from happening again
				EnableCastleMove = 0; 
				MadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else if(tRow == 7 && tColumn == 2){
				//Queen side castling BLACK
				board[7][2] = board[7][4]; //Move wKing 
				board[7][4] = NULL;
				board[7][3] = board[7][0]; //Move wRook castling
				board[7][0] = NULL; 
				//printf("QS castle success \n"); 
				QSWhiteCastlingEnabled = 0;	//Deny castling from happening again
				EnableCastleMove = 0; 
				MadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else{
				MadeCastleMove = 0 ; //User had castling enabled but chose not to castle, user wants to do regular movePiece 
			}
		}
		//Black side castling (includes both king and queen side)
		else if(board[sRow][sColumn]->color=='B') {
			if(tRow == 0 && tColumn == 6){
				//King side castling BLACK 
				board[0][6] = board[0][4]; //Move wKing 
				board[0][4] = NULL;
				board[0][5] = board[0][7]; //Move wRook castling
				board[0][7] = NULL;  
				//printf("KS castle success \n");
				KSBlackCastlingEnabled = 0;	//Deny castling from happening again
				EnableCastleMove = 0; 
				MadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else if(tRow == 0 && tColumn == 2){
				//Queen side castling BLACK
				board[0][2] = board[0][4]; //Move wKing 
				board[0][4] = NULL;
				board[0][3] = board[0][0]; //Move wRook castling
				board[0][0] = NULL; 
				//printf("QS castle success \n"); 
				QSBlackCastlingEnabled = 0;	//Deny castling from happening again
				EnableCastleMove = 0; 
				MadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else{
				MadeCastleMove = 0 ; //User had castling enabled but chose not to castle, user wants to do regular movePiece 
			}
		}
		// Reset EnableCastleMove in the case that castling is enabled but user wants to move another piece regularly 
		EnableCastleMove = 0;
	}
	
	else if(CmPPlayerorAI == 1){
		//White side castling (includes both king and queen side) AI VERSION
		if(board[sRow][sColumn]->color=='W') {
			if(tRow == 7 && tColumn == 6){
				//King side castling BLACK 
				board[7][6] = board[7][4]; //Move wKing 
				board[7][4] = NULL;
				board[7][5] = board[7][7]; //Move wRook castling
				board[7][7] = NULL;  
				//printf("KS castle success \n");
				AIKSWhiteCastlingEnabled = 0;	//Deny castling from happening again
				AIEnableCastleMove = 0; 
				AIMadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else if(tRow == 7 && tColumn == 2){
				//Queen side castling BLACK
				board[7][2] = board[7][4]; //Move wKing 
				board[7][4] = NULL;
				board[7][3] = board[7][0]; //Move wRook castling
				board[7][0] = NULL; 
				//printf("QS castle success \n"); 
				AIQSWhiteCastlingEnabled = 0;	//Deny castling from happening again
				AIEnableCastleMove = 0; 
				AIMadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else{
				AIMadeCastleMove = 0 ; //User had castling enabled but chose not to castle, user wants to do regular movePiece 
			}
		}
		//Black side castling (includes both king and queen side)
		else if(board[sRow][sColumn]->color=='B') {
			if(tRow == 0 && tColumn == 6){
				//King side castling BLACK 
				board[0][6] = board[0][4]; //Move wKing 
				board[0][4] = NULL;
				board[0][5] = board[0][7]; //Move wRook castling
				board[0][7] = NULL;  
				//printf("KS castle success \n");
				AIKSBlackCastlingEnabled = 0;	//Deny castling from happening again
				AIEnableCastleMove = 0; 
				AIMadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else if(tRow == 0 && tColumn == 2){
				//Queen side castling BLACK
				board[0][2] = board[0][4]; //Move wKing 
				board[0][4] = NULL;
				board[0][3] = board[0][0]; //Move wRook castling
				board[0][0] = NULL; 
				//printf("QS castle success \n"); 
				AIQSBlackCastlingEnabled = 0;	//Deny castling from happening again
				AIEnableCastleMove = 0; 
				AIMadeCastleMove = 1; //variable to avoid overlap of moves in movePiece 
			}
			else{
				AIMadeCastleMove = 0 ; //User had castling enabled but chose not to castle, user wants to do regular movePiece 
			}
		}
		// Reset EnableCastleMove in the case that castling is enabled but user wants to move another piece regularly 
		AIEnableCastleMove = 0;
	}
}

void knight(PIECE *board[8][8],int sRow,int sColumn,int arr[30][2]) {
	int moves[30][2];
	//initialize array
	for(int i=0;i<30;i++) {
		for(int j=0;j<2;j++) {
			moves[i][j]=-1;
		}
	}
	int tRow;
	int tColumn;
	int counter;

	tRow=sRow+1;
	tColumn=sColumn+2;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow-1;
	tColumn=sColumn+2;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow+1;
	tColumn=sColumn-2;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow-1;
	tColumn=sColumn-2;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	tRow=sRow+2;
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow-2;
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow+2;
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}

	//same code as above, but now tRow/tColumn values are changed
	tRow=sRow-2;
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {						//if target is within board
		if(board[tRow][tColumn]!=NULL) {
			//if target is not empty								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				//if target is opposite color
				//for loop finds first open space in moves array
				for(int i=0;i<30;i++) {
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//insert valid move into moves[counter][0/1]
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
		//if target is empty
			//for loop finds first open space in moves array
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//insert valid move into moves[counter][0/1]
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}
	memcpy(arr,moves, sizeof (int) * 30 * 2);
}

void rook(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]) {
	
    int moves[30][2];    
    int tRow;
    int tColumn;
  
    tRow = sRow;
    
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			moves[i][j] = -1;
		}
	}	
    // ensuring within the board
    while (tRow >= 0 && tRow < 8)
    {
		// Setting the move
        tRow = tRow + 1;
		// checking within the board
        if (tRow <0 || tRow >= 8)
        {
            break;
        }
		// if empty
        else if(board[tRow][sColumn] == NULL)
        {
            for (int i = 0; i < 30; i++)
            {
				//record 
                if (moves[i][0] == -1)
                {
                    moves[i][0] = tRow;
                    moves[i][1] = sColumn;
					 
                    break;
                }
            }
        }
		else if (board[tRow][sColumn] != NULL)
		{
			if (board[tRow][sColumn]->color == board[sRow][sColumn]->color)
            {
				//if same color
				break;
			}        
			else if(board[tRow][sColumn]->color != board[sRow][sColumn]->color)
			{
				for (int i = 0; i < 30; i++)
				{
					if (moves[i][0] == -1)
					{
						//not the same color, record once
						moves[i][0] = tRow;
						moves[i][1] = sColumn;
						break;
					}
				}
				break;
			}
		}
    }    

    tRow = sRow;
	//same as above module
    while (tRow >= 0 && tRow < 8)
    {
        tRow = tRow - 1;

        if (tRow <0 || tRow >= 8)
        {
            break;
        }
        else if(board[tRow][sColumn] == NULL)
        {
            for (int i = 0; i < 30; i++)
            {
                if (moves[i][0] == -1)
                {
                    moves[i][0] = tRow;
                    moves[i][1] = sColumn;
					
                    break;
                }
            }
        }
		else if (board[tRow][sColumn] != NULL)
		{
			if (board[tRow][sColumn]->color == board[sRow][sColumn]->color)
            {
				break;
			}
			else if(board[tRow][sColumn]->color != board[sRow][sColumn]->color)
			{
				for (int i = 0; i < 30; i++)
				{
					if (moves[i][0] == -1)
					{
						moves[i][0] = tRow;
						moves[i][1] = sColumn;
						
						break;
					}
				}
				break;
			}
		}
    }    
	//same as above module
	tColumn = sColumn;
	int i;
    while (tColumn >= 0 && tColumn < 8)
    {
        tColumn = tColumn + 1;

        if (tColumn <0 || tColumn >= 8)
        {
            break;
        }
        else if(board[sRow][tColumn] == NULL)
        {
            for (i = 0; i < 30; i++)
            {
                if (moves[i][0] == -1)
                {
                    moves[i][0] = sRow;
                    moves[i][1] = tColumn;
					
                    break;
                }
            }
        }
		else if (board[sRow][tColumn] != NULL)
		{
			if (board[sRow][tColumn]->color == board[sRow][sColumn]->color)
            {
				break;
			}
			else if(board[sRow][tColumn]->color != board[sRow][sColumn]->color)
			{
				for (i = 0; i < 30; i++)
				{
					if (moves[i][0] == -1)
					{
						moves[i][0] = sRow;
						moves[i][1] = tColumn;
						
						break;
					}
				}
				break;
			}
        }
    }    
	//same as above module
	tColumn = sColumn;

    while (tColumn >= 0 && tColumn < 8)
    {
        tColumn = tColumn - 1;

        if (tColumn <0 || tColumn >= 8)
        {
            break;
        }
        else if(board[sRow][tColumn] == NULL)
        {
            for (i = 0; i < 30; i++)
            {
                if (moves[i][0] == -1)
                {
                    moves[i][0] = sRow;
                    moves[i][1] = tColumn;
					
                    break;
                }
            }
        }
		else if (board[sRow][tColumn] != NULL)
		{
			if (board[sRow][tColumn]->color == board[sRow][sColumn]->color)
            {
				break;
			}        
			else if(board[sRow][tColumn]->color != board[sRow][sColumn]->color)
			{
				for (i = 0; i < 30; i++)
				{
					if (moves[i][0] == -1)
					{
						moves[i][0] = sRow;
						moves[i][1] = tColumn;
						
						break;
					}
				}
				break;
			}
		}
    }   
	//CHECKING IF SAVED

    memcpy(arr, moves, sizeof(int)*30*2); 
}

void bishop(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]) {
	int moves[30][2];
	int i,j;
	for (i=0; i<30; i++) {
		for(j=0; j<2; j++) {
			moves[i][j] = -1;
		}
	}
	int tRow;
	int tColumn;
	int counter;
	int steps;
	
	
	for(steps = 1; steps < 8; steps++) {
	tRow = sRow+steps;
	tColumn = sColumn+steps;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8){
		if(board[tRow][tColumn]!= NULL) {
			if(board[tRow][tColumn] -> color!=board[sRow][sColumn] ->color) {
				for (i=0; i<30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;
						}
				}	
			moves[counter][0] = tRow;
			moves[counter][1] = tColumn;
			break;
			}
			else if (board[sRow][sColumn] -> color == board[tRow][tColumn] -> color) {
				break;
			}
			
		}
	
	else {
		for (i=0; i<30; i++) {
			if (moves[i][0] == -1) {
				counter = i;
				break;
			}
		}
		moves[counter][0] = tRow;
		moves[counter][1] = tColumn;
		}	
	}
	}
	
	for(steps = 1; steps < 8; steps++) {
	tRow = sRow-steps;
	tColumn = sColumn-steps;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8){
		if(board[tRow][tColumn]!= NULL) {
			if(board[tRow][tColumn] -> color!=board[sRow][sColumn] ->color) {
				for (i=0; i<30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;
			}
		}	
			moves[counter][0] = tRow;
			moves[counter][1] = tColumn;
			break;
		}
		else if (board[sRow][sColumn] -> color == board[tRow][tColumn] -> color) {
				break;
			}
	}
	
	else {
		for (i=0; i<30; i++) {
			if (moves[i][0] == -1) {
				counter = i;
				break;
			}
		}
		moves[counter][0] = tRow;
		moves[counter][1] = tColumn;
		}	
	}
	}
	
	for(steps = 1; steps < 8; steps++) {
	tRow = sRow+steps;
	tColumn = sColumn-steps;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8){
		if(board[tRow][tColumn]!= NULL) {
			if(board[tRow][tColumn] -> color!=board[sRow][sColumn] ->color) {
				for (i=0; i<30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;
			}
		}	
			moves[counter][0] = tRow;
			moves[counter][1] = tColumn;
			break;
		}
		else if (board[sRow][sColumn] -> color == board[tRow][tColumn] -> color) {
				break;
			}
	}
	
	else {
		for (i=0; i<30; i++) {
			if (moves[i][0] == -1) {
				counter = i;
				break;
			}
		}
		moves[counter][0] = tRow;
		moves[counter][1] = tColumn;
		}	
	}
	}
	
	for(steps = 1; steps < 8; steps++) {
	tRow = sRow-steps;
	tColumn = sColumn+steps;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8){
		if(board[tRow][tColumn]!= NULL) {
			if(board[tRow][tColumn] -> color!=board[sRow][sColumn] ->color) {
				for (i=0; i<30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;
			}
		}	
			moves[counter][0] = tRow;
			moves[counter][1] = tColumn;
			break;
		}
		else if (board[sRow][sColumn] -> color == board[tRow][tColumn] -> color) {
				break;
			}
		}
	
	else {
		for (i=0; i<30; i++) {
			if (moves[i][0] == -1) {
				counter = i;
				break;
			}
		}
		moves[counter][0] = tRow;
		moves[counter][1] = tColumn;
			}	
		}
	}

	memcpy(arr,moves, sizeof (int) * 30 * 2);
}

void pawn(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int tracker) {

	int moves[30][2];
	for(int i = 0; i < 30; i++) {
		for(int j = 0; j < 2; j++) {
			moves[i][j] = -1;
		}
	}
	
	int tRow;
	int tColumn;
	int counter;

	//black pawn
	if(board[sRow][sColumn]->color == 'B') {
		tRow = sRow + 1;
		tColumn = sColumn;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target is empty
			if(board[tRow][tColumn] == NULL) {
				//find first open space
				for(int i = 0; i < 30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;	
					}
				}
				//insert valid move
				moves[counter][0] = tRow;
				moves[counter][1] = tColumn;
			}
		}

		tRow = sRow + 1;
		tColumn = sColumn + 1;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target not empty
			if(board[tRow][tColumn] != NULL) {
				//target opposite color
				if(board[tRow][tColumn]->color != board[sRow][sColumn]->color) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}
		//en passant
		if(tracker == tColumn) {
			//pawn appropriate rank
			if(sRow == 4) {
				//target within board
				if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
					//target empty
					if(board[tRow][tracker] == NULL) {
						//opponent pawn adjacent
						if(board[sRow][tracker]->piece == 'P') {
							//pawn opposite color
							if(board[sRow][tracker]->color != board[sRow][sColumn]->color) {
								//find first open space
								for(int i = 0; i < 30; i++) {
									if(moves[i][0] == -1) {
										counter = i;
										break;
									}
								}
								//insert valid move
								moves[counter][0] = tRow;
								moves[counter][1] = tColumn;
							}
						}	
					}
				}
			}
		}

		tRow = sRow + 1;
		tColumn = sColumn - 1;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target not empty
			if(board[tRow][tColumn] != NULL) {
				//target opposite color
				if(board[tRow][tColumn]->color != board[sRow][sColumn]->color) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}
		//en passant
		if(tracker == tColumn) {
			//pawn appropriate rank
			if(sRow == 4) {
				//target within board
				if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
					//target empty
					if(board[tRow][tracker] == NULL) {
						//opponent pawn adjacent
						if(board[sRow][tracker]->piece == 'P') {
							//pawn opposite color
							if(board[sRow][tracker]->color != board[sRow][sColumn]->color) {
								//find first open space
								for(int i = 0; i < 30; i++) {
									if(moves[i][0] == -1) {
										counter = i;
										break;
									}
								}
								//insert valid move
								moves[counter][0] = tRow;
								moves[counter][1] = tColumn;
							}
						}	
					}
				}
			}
		}	

		tRow = sRow + 2;
		tColumn = sColumn;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//pawn in starting position
			if(sRow == 1) {
				//space in front empty
				if(board[tRow - 1][tColumn] == NULL && board[tRow][tColumn] == NULL) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}

	}

	//white pawn
	else if(board[sRow][sColumn]->color == 'W') {
		tRow = sRow - 1;
		tColumn = sColumn;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target is empty
			if(board[tRow][tColumn] == NULL) {
				//find first open space
				for(int i = 0; i < 30; i++) {
					if(moves[i][0] == -1) {
						counter = i;
						break;	
					}
				}
				//insert valid move
				moves[counter][0] = tRow;
				moves[counter][1] = tColumn;
			}
		}

		tRow = sRow - 1;
		tColumn = sColumn + 1;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target not empty
			if(board[tRow][tColumn] != NULL) {
				//target opposite color
				if(board[tRow][tColumn]->color != board[sRow][sColumn]->color) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}
		//en passant
		if(tracker == tColumn) {
			//pawn appropriate rank
			if(sRow == 3) {
				//target within board
				if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
					//target empty
					if(board[tRow][tracker] == NULL) {
						//opponent pawn adjacent
						if(board[sRow][tracker]->piece == 'P') {
							//pawn opposite color
							if(board[sRow][tracker]->color != board[sRow][sColumn]->color) {
								//find first open space
								for(int i = 0; i < 30; i++) {
									if(moves[i][0] == -1) {
										counter = i;
										break;
									}
								}
								//insert valid move
								moves[counter][0] = tRow;
								moves[counter][1] = tColumn;
							}
						}	
					}
				}
			}
		}


		tRow = sRow - 1;
		tColumn = sColumn - 1;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//target not empty
			if(board[tRow][tColumn] != NULL) {
				//target opposite color
				if(board[tRow][tColumn]->color != board[sRow][sColumn]->color) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}
		//en passant
		if(tracker == tColumn) {
			//pawn appropriate rank
			if(sRow == 3) {
				//target within board
				if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
					//target empty
					if(board[tRow][tracker] == NULL) {
						//opponent pawn adjacent
						if(board[sRow][tracker]->piece == 'P') {
							//pawn opposite color
							if(board[sRow][tracker]->color != board[sRow][sColumn]->color) {
								//find first open space
								for(int i = 0; i < 30; i++) {
									if(moves[i][0] == -1) {
										counter = i;
										break;
									}
								}
								//insert valid move
								moves[counter][0] = tRow;
								moves[counter][1] = tColumn;
							}
						}	
					}
				}
			}
		}

		tRow = sRow - 2;
		tColumn = sColumn;
		//target within board
		if(tRow >= 0 && tRow < 8 && tColumn >= 0 && tColumn < 8) {
			//pawn in starting position
			if(sRow == 6) {
				//space in front empty
				if(board[tRow + 1][tColumn] == NULL && board[tRow][tColumn] == NULL) {
					//find first open space
					for(int i = 0; i < 30; i++) {
						if(moves[i][0] == -1) {
							counter = i;
							break;
						}
					}
					//insert valid move
					moves[counter][0] = tRow;
					moves[counter][1] = tColumn;
				}
			}
		}
	}
	memcpy(arr, moves, sizeof (int) * 30 * 2);		
}

void queen(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2]) {
	int moves[30][2];

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 2; j++) {
				moves[i][j] = -1;
		}
	}
	int valid1[30][2];
	int valid[30][2];
	int x = 0;
	int j = 0;
	int a = 0;
	
	rook(board,sRow,sColumn,valid);
	bishop(board,sRow,sColumn,valid1);
	
	while (valid[x][j] != -1)
	{
		x++;
	}
	for (int i=x; i < 30; i++)
	{
		for (j=0; j < 2; j++)
		{
			valid[i][j] = valid1[a][j];
		}
		a++;
	}
	memcpy(arr, valid, sizeof (int) * 30 * 2);		

}

void AIking(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int AIQSWhiteCastlingEnabled, int AIKSWhiteCastlingEnabled, int AIQSBlackCastlingEnabled, int AIKSBlackCastlingEnabled){
	
	int moves[30][2];													

	for(int i=0;i<30;i++) {
		for(int j=0;j<2;j++) {
			moves[i][j]=-1;
		}
	}
	int tRow;
	int tColumn;
	int counter;
	//King moves right one space  
	tRow=sRow;				
	tColumn=sColumn+1; 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {														
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move right one space by king is valid\n");
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
		
			}
		}
		else {


			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move right one space by king is valid\n");
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}
	
	tRow=sRow;				 
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {							
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move left one space by king is valid\n");
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move left one space by king is valid\n");
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}
	//Move King down one space 
	tRow=sRow+1;				 
	tColumn=sColumn;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {			
		//printf("PASSES here\n");
		if(board[tRow][tColumn]!=NULL) {																		
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move down one space by king is valid\n");
				AIEnableCastleMove = 0; 
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move down one space by king is valid\n");	
			AIEnableCastleMove = 0; 
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}
	//Move King up one space 
	tRow=sRow-1;			   
	tColumn=sColumn;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {										
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 		
				for(int i=0;i<30;i++) {						
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move up one space by king is valid\n");		
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move up one space by king is valid\n");	
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}
  
	tRow=sRow+1;				
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {										
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 	
				for(int i=0;i<30;i++) {					
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
		
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}
	
	tRow=sRow+1;				
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {			
		if(board[tRow][tColumn]!=NULL) {								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {				
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}

	tRow=sRow-1;			  
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 	
				for(int i=0;i<30;i++) {					
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}
  
	tRow=sRow-1;				
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				for(int i=0;i<30;i++) {	
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
			
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				AIEnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}

			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			AIEnableCastleMove = 0; 
		}
	}

	//King side castling WHITE
	tRow= 7; 			//King destination for king side
	tColumn= 6; 
	//printf("Value of AIKSWhiteCastling enabled is: %d \n", AIKSWhiteCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(AIKSWhiteCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=7;
						moves[counter][1]=6; 
						AIEnableCastleMove = 1; 
						//printf("Enabled 1\n"); 
					}
				}
			}
		}
		else if(AIKSWhiteCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=7;
			moves[counter][1]=6; 
			AIEnableCastleMove = 1; 
			//printf("Enabled 2\n"); 
		}
	}

	//King side castling BLACK
	tRow= 0; 			//King destination for king side
	tColumn= 6; 
	//printf("Value of AIKSBlackCastlingEnabled enabled is: %d \n", AIKSBlackCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(AIKSBlackCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=0;
						moves[counter][1]=6; 
						AIEnableCastleMove = 1; 
						//printf("Enabled 1\n"); 
					}
				}
			}
		}
		else if(AIKSBlackCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=0;
			moves[counter][1]=6; 
			AIEnableCastleMove = 1; 
			//printf("Enabled 2\n"); 
		}
	}		

	//Queen side castling WHITE
	tRow= 7; 			//King destination for queen side  
	tColumn= 2; 
	//printf("Value of AIQSWhiteCastling enabled is: %d \n", AIQSWhiteCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(AIQSWhiteCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=7;
						moves[counter][1]=2; 
						AIEnableCastleMove = 1; 
					}
				}
			}
		}
		else if(AIQSWhiteCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=7;
			moves[counter][1]=2; 
			AIEnableCastleMove = 1; 
		}
	}
	
	//Queen side castling BLACK
	tRow= 0; 			//King destination for queen side  
	tColumn= 2; 
	//printf("Value of AIQSBlackCastlingEnabled enabled is: %d \n", AIQSBlackCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(AIQSBlackCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=0;
						moves[counter][1]=2; 
						AIEnableCastleMove = 1; 
					}
				}
			}
		}
		else if(AIQSBlackCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=0;
			moves[counter][1]=2; 
			AIEnableCastleMove = 1; 
		}
	}
	//printf("reach here 1 \n"); 
	memcpy(arr,moves, sizeof (int) * 30 * 2);
}

void king(PIECE *board[8][8],int sRow,int sColumn, int arr[30][2], int QSWhiteCastlingEnabled, int KSWhiteCastlingEnabled, int QSBlackCastlingEnabled, int KSBlackCastlingEnabled) { 

	int moves[30][2];													

	for(int i=0;i<30;i++) {
		for(int j=0;j<2;j++) {
			moves[i][j]=-1;
		}
	}
	int tRow;
	int tColumn;
	int counter;
	//King moves right one space  
	tRow=sRow;				
	tColumn=sColumn+1; 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {														
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move right one space by king is valid\n");
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
		
			}
		}
		else {


			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move right one space by king is valid\n");
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}
	
	tRow=sRow;				 
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {							
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move left one space by king is valid\n");
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move left one space by king is valid\n");
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}
	//Move King down one space 
	tRow=sRow+1;				 
	tColumn=sColumn;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {			
		//printf("PASSES here\n");
		if(board[tRow][tColumn]!=NULL) {																		
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				for(int i=0;i<30;i++) {			
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move down one space by king is valid\n");
				EnableCastleMove = 0; 
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move down one space by king is valid\n");	
			EnableCastleMove = 0; 
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
		}
	}
	//Move King up one space 
	tRow=sRow-1;			   
	tColumn=sColumn;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {										
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 		
				for(int i=0;i<30;i++) {						
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				//printf("Move up one space by king is valid\n");		
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			//printf("Move up one space by king is valid\n");	
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}
  
	tRow=sRow+1;				
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {		
		if(board[tRow][tColumn]!=NULL) {										
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 	
				for(int i=0;i<30;i++) {					
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
		
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}
	
	tRow=sRow+1;				
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {			
		if(board[tRow][tColumn]!=NULL) {								
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 
				for(int i=0;i<30;i++) {				
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}

	tRow=sRow-1;			  
	tColumn=sColumn-1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) { 	
				for(int i=0;i<30;i++) {					
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}
  
	tRow=sRow-1;				
	tColumn=sColumn+1;
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				for(int i=0;i<30;i++) {	
					if(moves[i][0]==-1) {
						counter=i;
						break;
					}
				}
			
				moves[counter][0]=tRow;
				moves[counter][1]=tColumn;
				EnableCastleMove = 0; 
			}
		}
		else {
			for(int i=0;i<30;i++) {
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}

			moves[counter][0]=tRow;
			moves[counter][1]=tColumn;
			EnableCastleMove = 0; 
		}
	}

	//King side castling WHITE
	tRow= 7; 			//King destination for king side
	tColumn= 6; 
	//printf("Value of KSWhiteCastling enabled is: %d \n", KSWhiteCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(KSWhiteCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=7;
						moves[counter][1]=6; 
						EnableCastleMove = 1; 
						//printf("Enabled 1\n"); 
					}
				}
			}
		}
		else if(KSWhiteCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=7;
			moves[counter][1]=6; 
			EnableCastleMove = 1; 
			//printf("Enabled 2\n"); 
		}
	}

	//King side castling BLACK
	tRow= 0; 			//King destination for king side
	tColumn= 6; 
	//printf("Value of KSBlackCastlingEnabled enabled is: %d \n", KSBlackCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(KSBlackCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=0;
						moves[counter][1]=6; 
						EnableCastleMove = 1; 
						//printf("Enabled 1\n"); 
					}
				}
			}
		}
		else if(KSBlackCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=0;
			moves[counter][1]=6; 
			EnableCastleMove = 1; 
			//printf("Enabled 2\n"); 
		}
	}		

	//Queen side castling WHITE
	tRow= 7; 			//King destination for queen side  
	tColumn= 2; 
	//printf("Value of QSWhiteCastling enabled is: %d \n", QSWhiteCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(QSWhiteCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=7;
						moves[counter][1]=2; 
						EnableCastleMove = 1; 
					}
				}
			}
		}
		else if(QSWhiteCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=7;
			moves[counter][1]=2; 
			EnableCastleMove = 1; 
		}
	}
	
	//Queen side castling BLACK
	tRow= 0; 			//King destination for queen side  
	tColumn= 2; 
	//printf("Value of QSBlackCastlingEnabled enabled is: %d \n", QSBlackCastlingEnabled); 
	if(tRow>=0 && tRow<8 && tColumn>=0 && tColumn<8) {
		if(board[tRow][tColumn]!=NULL) {									
			if(board[tRow][tColumn]->color!=board[sRow][sColumn]->color) {
				if(QSBlackCastlingEnabled == 1){
					for(int i=0;i<30;i++) {	
						if(moves[i][0]==-1) {
							counter=i;
							break;
						}
						moves[counter][0]=0;
						moves[counter][1]=2; 
						EnableCastleMove = 1; 
					}
				}
			}
		}
		else if(QSBlackCastlingEnabled == 1){
			for(int i=0;i<30;i++) {	
				if(moves[i][0]==-1) {
					counter=i;
					break;
				}
			}
			moves[counter][0]=0;
			moves[counter][1]=2; 
			EnableCastleMove = 1; 
		}
	}
	//printf("reach here 1 \n"); 
	memcpy(arr,moves, sizeof (int) * 30 * 2);
}

void resetValid(int arr[30][2]) {
	for(int i=0;i<30;i++) {
		arr[i][0]=-1;
		arr[i][1]=-1;

	}
} 

int checkCheck(PIECE *board[8][8], char color) {		//Checks if current player is in check
	int valid[30][2];
	int i,j = 0; 
	int x,y = 0; 
	int KRow, KColumn = 0; 
	int ValidCheck = 0;
	
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			//Iterate through 64 squares in board to find king 
			if(board[i][j]!=NULL) {
				if(board[i][j]->piece =='K' && board[i][j]->color==color){						
					//save x,y coordinate of King piece
					KRow = i;			
					KColumn = j;
					break;
				}
			}
		} 
	}
	//above finds king coordinates
	//printf("The kings position is: %c,%d \n",numToLetter(KColumn),8-KRow);
	for(x = 0; x < 8; x++) {
		for(y = 0; y < 8; y++) {
			resetValid(valid);
			//Check if valid move puts player into check 
			if(board[x][y] != NULL){								//if theres a piece 
				if(board[KRow][KColumn]->color != board[x][y]->color){			//if piece is opposing color
					//printf("made it inside if");
					//run if check on all pieces and if a valid move of a piece can kill the king
					if(board[x][y]->piece=='H'){
						knight(board,x,y,valid);
					}
					else if(board[x][y]->piece=='R'){
						rook(board,x,y,valid);
					}
					else if(board[x][y]->piece=='B'){
						bishop(board,x,y,valid);
					}
					else if(board[x][y]->piece=='P'){
						pawn(board,x,y,valid,tracker);
					}
					else if(board[x][y]->piece=='Q'){
						queen(board,x,y,valid);
						//printf("madeitheretoqueen\n");
					}
					else if(board[x][y]->piece=='K'){
						king(board,x,y,valid,QSWhiteCastlingEnabled,KSWhiteCastlingEnabled,QSBlackCastlingEnabled,KSBlackCastlingEnabled);
					}
					
					for(int i=0;i<30;i++) {
						//printf("in for loop");
						if(valid[i][0]==KRow && valid[i][1]==KColumn ){
							if(KSWhiteCastlingEnabled != 1 || KSBlackCastlingEnabled != 1 || QSWhiteCastlingEnabled != 1 || QSBlackCastlingEnabled != 1 || AIKSWhiteCastlingEnabled != 1 || AIKSBlackCastlingEnabled != 1 || AIQSWhiteCastlingEnabled != 1 || AIQSBlackCastlingEnabled != 1 ){
								ValidCheck = 1;
								//return 1;
							}
						}
						
						if(valid[i][0]!=-1) {
							//printf("Valid moves are: %c%d\n", numToLetter(valid[i][0]),8-valid[i][1]);
						}
						else {
							//printf("\nbreaks here\n");
							break;
						}
					}
				}
			}	
		}
	}
	
	//int validCheck=1;
	if(ValidCheck == 1){
		return 1;												
	}
	else {
		return 0;
	}
}

void pawnUpgrade(PIECE *board[8][8], int tRow, int tColumn, int pOrAI) {

	char upgrade;
	
	//upgrade black pawn
	if(board[tRow][tColumn]->piece == 'P' && board[tRow][tColumn]->color == 'B' && tRow == 7) {
		if(pOrAI == 1) {
			printf("Select piece to upgrade pawn into (IN CAPITAL LETTERS: H, B, R, or Q): \n");
			scanf(" %c", &upgrade);
		}
		else {
			upgrade = 'Q';
		}
		if(upgrade == 'H') {
			board[tRow][tColumn]->value = 30;
			board[tRow][tColumn]->piece = 'H';
		}
		if(upgrade == 'B') {
			board[tRow][tColumn]->value = 30;
			board[tRow][tColumn]->piece = 'B';
		}
		if(upgrade == 'R') {
			board[tRow][tColumn]->value = 50;
			board[tRow][tColumn]->piece = 'R';
		}
		if(upgrade == 'Q') {
			board[tRow][tColumn]->value = 90;
			board[tRow][tColumn]->piece = 'Q';
		}
	}
	//upgrade white pawn
	else if(board[tRow][tColumn]->piece == 'P' && board[tRow][tColumn]->color == 'W' && tRow == 0) {
		if(pOrAI == 1) {
			printf("Select piece to upgrade pawn into (IN CAPITAL LETTERS: H, B, R, or Q): \n");
			scanf(" %c", &upgrade);
		}
		else {
			upgrade = 'Q';
		}
		if(upgrade == 'H') {
			board[tRow][tColumn]->value = 30;
			board[tRow][tColumn]->piece = 'H';
		}
		if(upgrade == 'B') {
			board[tRow][tColumn]->value = 30;
			board[tRow][tColumn]->piece = 'B';
		}
		if(upgrade == 'R') {
			board[tRow][tColumn]->value = 50;
			board[tRow][tColumn]->piece = 'R';
		}
		if(upgrade == 'Q') {
			board[tRow][tColumn]->value = 90;
			board[tRow][tColumn]->piece = 'Q';
		}	
	}
}

int enPassantTracker(PIECE *board[8][8], int sRow, int sColumn, int tRow, int tColumn) {

	//Checks if piece moved is a pawn and if it moved 2 spaces
	int pmove;
	int target = tColumn;
	pmove = sRow - tRow;
	if(board[tRow][tColumn]->piece == 'P' && (pmove == 2 || pmove == -2)) {
		return target;
	}
	else {
		return -1;
	}
}

int checkCheckMate(PIECE *board[8][8], char color, int CCMPlayerorAI) {
	int notCheckmate;
        for(int i=0;i<8;i++) {
                for(int j=0;j<8;j++) {
                        if(board[i][j]!=NULL && board[i][j]->color==color) {
                                for(int k=0;k<8;k++) {
                                        for(int m=0;m<8;m++) {
						notCheckmate = checkValid(board,i,j,k,m,color,0);
						if (notCheckmate==1){
							return 0;
						}
					}
				}
			}
		}
	}
	if (notCheckmate == 1){
		return 0;
	}
	else{
		return 1;
	}
}

void stalemate (PIECE *board[8][8], char color, int CCMPlayerorAI) {
	int checkmate;
	int check;
	int stalematecounter;
	int i, j, varB, varW;
	check = checkCheck(board, color);
	checkmate = checkCheckMate(board, color, CCMPlayerorAI);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j] -> color == 'B') {
				varB++;
			}
			if (board[i][j] -> color == 'W') {
				varW++;
			}
			if (varB < 2 && varW < 2) {
				stalematecounter++;
			}
		}
	}
	if (stalematecounter == 50) {
		printf("You have reached a stalemate! Game Over.\n");
		exit(10);
	}	
	if (check == 0 && checkmate == 1) {
		printf("You have reached a stalemate! Game Over.\n");
		exit(10);
	}
				
	
}