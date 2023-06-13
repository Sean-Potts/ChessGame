// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Later other files will be added for cleaner code. Currently development of classes will all be done in ChassGame.cpp before being seperated into different files. 
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;


enum Pieces{pawn, knight, bishop, castle, queen, king};
class ChessPeice
{
public:
	Pieces curPiece;

	ChessPeice(Pieces piece)

	{
		curPiece = piece;
		//this->color = color;
		//this->canMove = move;

	}

	ChessPeice()
	{

	}
	~ChessPeice() {

	}
	
	string getColor() {
		return color;
	}

	void setColor(string setColor) {
		color = setColor;
	}

private:

	string color; 
	bool canMove;

};




class ChessBoard
{
public:

	// store refereences to objects as pointers
	ChessPeice* board[8][8]; 


	ChessBoard()
	{
		// sets up chess board
		board[0][0] = new ChessPeice(castle);
		for (int j = 0; j < 8; j+=7) {
			board[j][0] = new ChessPeice(castle);
			board[j][1] = new ChessPeice(knight);
			board[j][2] = new ChessPeice(bishop);
			board[j][4] = new ChessPeice(queen);
			board[j][3] = new ChessPeice(king);
			board[j][5] = new ChessPeice(bishop);
			board[j][6] = new ChessPeice(knight);
			board[j][7] = new ChessPeice(castle);
		}
		for (int i = 0; i < 8; i++) {
			board[1][i] = new ChessPeice(pawn);
		}
		for (int i = 0; i < 8; i++) {
			board[6][i] = new ChessPeice(pawn);
		}

	}

	~ChessBoard()
	{
	}

private:

};



class Game
{
public:

	//Player playersInGame;
	//essBoard chessGame;
	

	Game()
	{

	}

	~Game()
	{
	}

private:

};




class Player
{
	
public:

	string stateOfGame;
	string name; 
	int numberTurns;

	Player()
	{
	}

	~Player()
	{
	}

private:

};






int main()
{
    std::cout << "Hello World!\n";
}

