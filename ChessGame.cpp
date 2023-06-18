// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Later other files will be added for cleaner code. Currently development of classes will all be done in ChassGame.cpp before being seperated into different files. 
#include <vector>
#include <iostream>
#include <string.h>
#include <map>

using namespace std;



enum Pieces {pawn = 3, knight, bishop, castle, queen, king};
enum Colors {white = 1, black};




std::map<Colors, std::string> colorNames = {
	{white, "W-"},
	{black, "B-"}
};

std::map<Pieces, std::string> pieceNames = {
	{pawn, "P"},
	{knight, "K"},
	{castle, "C"},
	{queen, "Q"},
	{bishop, "B"},
	{king, "K"}
};

class ChessPeice
{
public:
	Pieces curPiece;
	Colors color;
	bool specialMove = true;

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

	// diag move is  1 horizontal + 1 vertical 


	std::vector<std::pair<int, int>> getPossibleMoves() {

		std::vector<pair<int, int> > PossibleMoves;

		switch (curPiece)
		{
		case pawn:
			if (specialMove == true)
			{
				PossibleMoves.push_back(std::make_pair(2, 0));
				PossibleMoves.push_back(std::make_pair(1, 0));
				PossibleMoves.push_back(std::make_pair(1, 1));
				specialMove = false;
			}
			else
			{
				PossibleMoves.push_back(std::make_pair(1, 0));
				PossibleMoves.push_back(std::make_pair(1, 1));
			}
			break;

		case knight:
			PossibleMoves.push_back(std::make_pair(2, 1));
			PossibleMoves.push_back(std::make_pair(2, -1));
			PossibleMoves.push_back(std::make_pair(-2, 1));
			PossibleMoves.push_back(std::make_pair(-2, -1));
			PossibleMoves.push_back(std::make_pair(1, 2));
			PossibleMoves.push_back(std::make_pair(-1, 2));
			PossibleMoves.push_back(std::make_pair(1, -2));
			PossibleMoves.push_back(std::make_pair(-1, -2));
			break;
		case queen:
			// Horizontal movements (positive)
			for (int i = 1; i < 8; ++i) {
				PossibleMoves.emplace_back(i, 0);
			}

			// Horizontal movements (negative)
			for (int i = -1; i > -8; --i) {
				PossibleMoves.emplace_back(i, 0);
			}

			// Vertical movements (positive)
			for (int i = 1; i < 8; ++i) {
				PossibleMoves.emplace_back(0, i);
			}

			// Vertical movements (negative)
			for (int i = -1; i > -8; --i) {
				PossibleMoves.emplace_back(0, i);
			}

			// Diagonal movements (positive)
			for (int i = 1, j = 1; i < 8; ++i, ++j) {
				PossibleMoves.emplace_back(i, j);
			}

			for (int i = -1, j = -1; i > -8; --i, --j) {
				PossibleMoves.emplace_back(i, j);
			}

			for (int i = -1, j = 1; i > -8; --i, ++j) {
				PossibleMoves.emplace_back(i, j);
			}

			for (int i = 1, j = -1; i < 8; ++i, --j) {
				PossibleMoves.emplace_back(i, j);
			}

			break;

		case castle:
			// Horizontal movements (positive)
			for (int i = 1; i < 8; ++i) {
				PossibleMoves.emplace_back(i, 0);
			}

			// Horizontal movements (negative)
			for (int i = -1; i > -8; --i) {
				PossibleMoves.emplace_back(i, 0);
			}

			// Vertical movements (positive)
			for (int i = 1; i < 8; ++i) {
				PossibleMoves.emplace_back(0, i);
			}

			// Vertical movements (negative)
			for (int i = -1; i > -8; --i) {
				PossibleMoves.emplace_back(0, i);
			}

		case king:
			PossibleMoves.emplace_back(-1, -1);
			PossibleMoves.emplace_back(-1, 1);
			PossibleMoves.emplace_back(1, -1);
			PossibleMoves.emplace_back(1, 1);

			PossibleMoves.emplace_back(0, -1);
			PossibleMoves.emplace_back(0, 1);
			PossibleMoves.emplace_back(1, 0);
			PossibleMoves.emplace_back(-1, 0);
			break;

		default:
			break;
			
		}
		return PossibleMoves;
	
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

	void swapElements(int row1, int col1, int row2, int col2) {

		std::swap(this->board[row1][col1], this->board[row2][col2]);

	}

	~ChessBoard()
	{
	}
	void MovePiece(Colors pieceColor) 
	{
		cout << "What piece do you want to move?" << endl;

		// Prints ChessBoard for Playing/Testing
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (board[i][j] == NULL) {
					cout << "EMP ";
				}
				else {
					cout << colorNames[board[i][j]->color] << pieceNames[board[i][j]->curPiece] << " ";
				}
				
			}
			cout << i;
			cout << std::endl;
		}
		for (int i = 0; i < 8; i++) {
			cout <<  i << "   ";
		}

		cout << endl;
		cout << "Select a piece using Column/Row formate" << endl;
	
		string piece;
		cin >> piece;

		cout << "Select a spot to move using Column/Row formate" << endl;
		string location;
		cin >> location;

		cout << piece << location; 

		int rowPiece = piece[0] - '0';
		int colPiece = piece[1] - '0';
		int rowMove = location[0] - '0';
		int colMove = location[1] - '0';

	
		swapElements(rowPiece, colPiece, rowMove, colMove);
		// Prints ChessBoard for Playing/Testing
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (board[i][j] == NULL) {
					cout << "EMP ";
				}
				else {
					cout << colorNames[board[i][j]->color] << pieceNames[board[i][j]->curPiece] << " ";
				}

			}
			cout << i;
			cout << std::endl;
		}
		for (int i = 0; i < 8; i++) {
			cout << i << "   ";
		}

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
		if (player1Color == white) {
			whosTurn = 1;
		}
		else {
			whosTurn = 2;	
		}
		cout << "New Game Created!" << endl;
	}

	Player player1;
	Player player2;
	ChessBoard chessGame;
	string stateOfGame;
	int whosTurn; // 1 or 2;

	~Game()
	{
	}

	void MakeTurn() 
	{
		if (whosTurn == 1) 
		{
			chessGame.MovePiece(player1.playerColor);
		}
		else
		{
			chessGame.MovePiece(player2.playerColor);
		}
		
	}

private:

};





// pawn moves one space forward/2 at the start.. condition to check spaces to the left+up & right+up for takening a peice 

// castle can move left/right/up/down any number of spaces need to check each space infront to see if something occupies it.

// bishop can move diagnol.. left/up||down right/up||down

// king can move 1 space diag or ver/hor

// knight can move in an L 2 ver/hor one left/right

// logic for each peice needs to be stored in the peice class! 
// methods like move, need to check what piece is being moved, and check if a piece is in the way, 



int main()
{
	ChessBoard chessboard;

	chessboard.MovePiece(white);


	
}

