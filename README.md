# Chess AI
## Introduction
The objective of this project is to create a chess AI engine that one can play against. To do this, I created a tree of all possible moves. Next I use the min max algorithm to figure out the ideal move to make. As of now, the AI can think 2 moves ahead, but I am looking to expand this when I have the time.

## Installation
1) Clone the Git Repository onto your machine. This program works best in a Linux environment
2) Be sure to have C installed on your machine.
3) Run the following commands to install the packages required for this program:
		`sudo apt-get install gtk+2.0`
		`sudo apt-get install -y pkg-config`
		`sudo apt install build-essential`
4) Navigate into to the *src* folder
5) Compile the code by typing in `make chess`
6) Run the code by typing in `./chess`

## Modes

**Easy Mode**: the computer simply makes random moves. 
**Hard Mode**: the computer thinks 2 moves ahead.

## Bugs and Limitations
This was group project assigned in class, and so there were deadlines that prevented us from making this project perfect. Castling occasionally fails, but I am currently looking into this to figure out why. Also, due to inexperience at the time of creation, our code was far too convoluted to be efficient. This means that the Chess Engine can only think a maximum of 2 moves ahead. While this may prove slightly challenging for beginners to the game, anyone who has played chess more than a handful of times will be able to beat this program quite easily. 
