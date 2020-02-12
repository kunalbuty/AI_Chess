# Makefile for hw4, EECS22L Winter 2019 
# Author: Marvin Neil Sabas
# Modification: Team 6 
# Date:   1/16/2019

CC     = gcc
DEBUG  = -g
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -Wall -std=c99

#
GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`
OPTS = -g
INC	= $(GTKINC)
LIBS	= $(GTKLIBS)
#incorperating GTK Libraries

OBJS = chess.o Moves.o Pieces.o Possibilities.o AI.o  
DEPS =  Moves.h Pieces.h Possibilities.h AI.h chessgtk.h
#added in gtk header

all: chess

test: chess
	./chess
tar: 
	tar -czvf Chess_Alpha_src.tar.gz /users/ugrad/2018/fall/chowdha1/Team06 --exclude=/users/ugrad/2018/fall/chowdha1/Team06/.git

chess:  chess.o Moves.o Pieces.o Possibilities.o AI.o
	gcc  $(LFLAGS) $(LIBS) chess.o Moves.o Pieces.o Possibilities.o AI.o -o chess

chess.o: chess.c $(DEPS)
	$(CC) $(CFLAGS) $(INC) chess.c -o chess.o
#added the gtk Lib
Moves.o: Moves.c Moves.h Pieces.h 
	$(CC) $(CFLAGS) Moves.c -o Moves.o
	
Pieces.o: Pieces.c Pieces.h 
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o
	
Possibilities.o: Possibilities.c Possibilities.h 
	$(CC) $(CFLAGS) Possibilities.c -o Possibilities.o
	
AI.o: AI.c AI.h Pieces.h Possibilities.h Moves.h 
	$(CC) $(CFLAGS) AI.c -o AI.o

clean:
	rm -f *.o $(DESIGN)
	rm chess
	rm Log.txt
	rm Chess_Alpha_src.tar.gz
	rm Chess_Alpha.tar.gz

