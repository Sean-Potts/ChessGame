// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Later other files will be added for cleaner code. Currently development of classes will all be done in ChassGame.cpp before being seperated into different files. 
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;



enum Pieces {pawn, knight, bishop, castle, queen, king};
enum Colors {white, black};

class ChessPeice
{
public:
	Pieces curPiece;
	Colors color;

	ChessPeice(Pieces piece, Colors color)
	{
		this->curPiece = piece;
		this->color = color;
	}

	ChessPeice()
	{

	}
	~ChessPeice() {

	}
	
	
	// how it should move

private:

	//bool canMove;

};




class ChessBoard
{
public:

	// store refereences to objects as pointers
	// if chessBoard is NULL there is an empty space to move to. 
	ChessPeice* board[8][8] = { NULL };

	//tell peice if it can move

	ChessBoard()
	{
		Colors colorOfPiece = white;
		// sets up chess board
	
		for (int j = 0; j < 8; j+=7) {
			board[j][0] = new ChessPeice(castle, colorOfPiece);
			board[j][1] = new ChessPeice(knight, colorOfPiece);
			board[j][2] = new ChessPeice(bishop, colorOfPiece);
			board[j][4] = new ChessPeice(queen, colorOfPiece);
			board[j][3] = new ChessPeice(king, colorOfPiece);
			board[j][5] = new ChessPeice(bishop, colorOfPiece);
			board[j][6] = new ChessPeice(knight, colorOfPiece);
			board[j][7] = new ChessPeice(castle, colorOfPiece);
			colorOfPiece = black;
		}
		for (int i = 0; i < 8; i++) {
			board[1][i] = new ChessPeice(pawn, white);
		}
		for (int i = 0; i < 8; i++) {
			board[6][i] = new ChessPeice(pawn, black);
		}

	}

	~ChessBoard()
	{
	}

private:

};

class Player
{

public:

	string stateOfGame;
	string name;
	Colors playerColor;
	int numberTurns = 0;

	Player()
	{
	}
	Player(string name, Colors color)
	{
		this->name = name;
		this->playerColor = color;

	}
	~Player()
	{
	}

private:

};


class Game
{
public:

	


	Game(string player1, string player2, Colors player1Color, Colors player2Color) :player1(player1, player1Color), player2(player2, player2Color), chessGame()
	{
		cout << "New Game Created!" << endl;
	}

	Player player1;
	Player player2;
	ChessBoard chessGame;

	~Game()
	{
	}

private:

};










int main()
{
	ChessBoard chessboard;


	
}

