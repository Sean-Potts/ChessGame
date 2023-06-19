// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Later other files will be added for cleaner code. Currently development of classes will all be done in ChassGame.cpp before being seperated into different files. 
#include <vector>
#include <iostream>
#include <string.h>
#include <map>
#include <conio.h>

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
				if (color == black) {
														 //i=x  j=y
					PossibleMoves.push_back(std::make_pair(0, 2));
					PossibleMoves.push_back(std::make_pair(0, 1));
					PossibleMoves.push_back(std::make_pair(1, 1));
					PossibleMoves.push_back(std::make_pair(-1, 1));
					specialMove = false;
				}
				else {
					PossibleMoves.push_back(std::make_pair(0, -2));
					PossibleMoves.push_back(std::make_pair(0, -1));
					PossibleMoves.push_back(std::make_pair(1, -1));
					PossibleMoves.push_back(std::make_pair(-1, -1));
					specialMove = false;
				}
			}
			else
			{
				PossibleMoves.push_back(std::make_pair(0, 1));
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
			break;

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
	
	// properties
	ChessPeice* board[8][8] = { NULL };

	int selectedPieceLocation[2];
	//tell peice if it can move

	ChessBoard()
	{
		Colors colorOfPiece = black;
		// sets up chess board
	
		for (int j = 0; j < 8; j+=7) {
			board[0][j] = new ChessPeice(castle, colorOfPiece);
			board[1][j] = new ChessPeice(knight, colorOfPiece);
			board[2][j] = new ChessPeice(bishop, colorOfPiece);
			board[3][j] = new ChessPeice(queen, colorOfPiece);
			board[4][j] = new ChessPeice(king, colorOfPiece);
			board[5][j] = new ChessPeice(bishop, colorOfPiece);
			board[6][j] = new ChessPeice(knight, colorOfPiece);
			board[7][j] = new ChessPeice(castle, colorOfPiece);
			colorOfPiece = white;
		}
		for (int i = 0; i < 8; i++) {
			board[i][1] = new ChessPeice(pawn, black);
		}
		for (int i = 0; i < 8; i++) {
			board[i][6] = new ChessPeice(pawn, white);
		}

	}

	void swapElements(int row1, int col1, int row2, int col2) 
	{
		std::swap(this->board[row1][col1], this->board[row2][col2]);
	}


	void removeElements(int col1, int row1, int col2, int row2) 
	{

		this->board[col2][row2] = this->board[col1][row1];
		this->board[col1][row1] = NULL;

	}
	

	 vector<pair<int, int> > validMoves() {


		cout << "select Piece col(X)/row(Y)" << endl;
		string piece;
		cin >> piece;
		int colPiece = piece[0] - '0';
		int rowPiece = piece[1] - '0';

		cout << "Piece selected: " << pieceNames[board[colPiece][rowPiece]->curPiece] << endl;
		// assign location
		selectedPieceLocation[0]= colPiece, selectedPieceLocation[1] = rowPiece;

		std::vector<pair<int, int> > PossibleMoves = this->board[colPiece][rowPiece]->getPossibleMoves();
		std::vector<pair<int, int> > ValidMoves; 

		// vector of pairs somewhat working now its type to validate the movement of the piece 
		// if anything is in the way example to the left, all negative -x values dont work with a y value of 0 dont work cause thats a linear movement
		for (auto it = begin(PossibleMoves); it != end(PossibleMoves); it++) {
		
			if ((colPiece + it->first) >= 0 && (colPiece + it->first) <= 7 && (rowPiece + it->second) >= 0 && (rowPiece + it->second) <= 7) {

				if (board[colPiece + it->first][rowPiece + it->second] != NULL) {
					
						if (board[colPiece + it->first][rowPiece + it->second]->color == board[colPiece][rowPiece]->color)
						{							
							while (it->first >= 0 && it != end(PossibleMoves) && it->second == 0) 
							{
								it++;
							}
						}
						else 
						{
							
							cout << "valid move take piece" << endl;
							ValidMoves.emplace_back(it->first+colPiece, it->second+rowPiece);
							cout << it->first << ", " << it->second << endl;
						}
				}
				else {
					if (board[colPiece][rowPiece]->curPiece == pawn && it->first == 0 ) {
						cout << "valid move empty spot" << endl;
						ValidMoves.emplace_back(it->first + colPiece, it->second + rowPiece);
						cout << it->first << ", " << it->second << endl;
					}
					else {
						cout << "not valid because no piece is there" << endl;
					}
				}
			}
			else {
				cout << "invalid move" << it->first << ", " << it->second << endl;
			}
		
		}

		cout << "\nValid moves are as follows" << endl;
		for (auto it = begin(ValidMoves); it != end(ValidMoves); it++) 
		{
			cout << it->first << ", " << it->second << endl;
		}
		return ValidMoves;

	 }



	

	~ChessBoard()
	{
	}

	void MovePiece(Colors pieceColor) 
	{
		cout << "What piece do you want to move?" << endl;

		// Prints ChessBoard for Playing/Testing
		for (int j = 0; j < 8; ++j) {
			for (int i = 0; i < 8; ++i) {
				if (board[i][j] == NULL) {
					cout << "EMP ";
				}
				else {
					cout << colorNames[board[i][j]->color] << pieceNames[board[i][j]->curPiece] << " ";
				}
				
			}
			cout << j;
			cout << std::endl;
		}
		for (int i = 0; i < 8; i++) {
			cout <<  i << "   ";
		}

		/* cout << endl;
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
		} */

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

void displayOptions(const std::vector<std::pair<int, int>>& ValidMoves, int selectedOption)
{
	std::cout << "Valid moves are as follows:" << std::endl;

	for (int i = 0; i < ValidMoves.size(); i++)
	{
		if (i == selectedOption)
			std::cout << "-> ";
		else
			std::cout << "   ";

		std::cout << ValidMoves[i].first << ", " << ValidMoves[i].second << std::endl;
	}
}

int main()
{
	ChessBoard chessboard;

	chessboard.MovePiece(white);
	
	std::vector<std::pair<int, int>> ValidMoves = chessboard.validMoves();
	// Populate the ValidMoves vector

	int selectedOption = 0;
	int keyPressed = 0;

	while (keyPressed != 13) // 13 is the ASCII value for Enter key
	{
		system("cls"); // Clear the console (Windows)

		displayOptions(ValidMoves, selectedOption);

		// Handle user input
		keyPressed = _getch(); // Use getch() to get a character without waiting for the Enter key

		if (keyPressed == 224) // 224 is the extended key code
		{
			// Arrow key was pressed
			keyPressed = _getch(); // Read the actual key code

			if (keyPressed == 72) // 72 is the key code for up arrow
			{
				// Up arrow key was pressed
				if (selectedOption > 0)
					selectedOption--;
			}
			else if (keyPressed == 80) // 80 is the key code for down arrow
			{
				// Down arrow key was pressed
				if (selectedOption < ValidMoves.size() - 1)
					selectedOption++;
			}
		}
	}

	// Print the selected option
	std::cout << "Selected option: " << ValidMoves[selectedOption].first << ", "
		<< ValidMoves[selectedOption].second << std::endl;

	
	chessboard.removeElements(chessboard.selectedPieceLocation[0], chessboard.selectedPieceLocation[1], ValidMoves[selectedOption].first, ValidMoves[selectedOption].second);
	chessboard.MovePiece(white);

	return 0;


	
}

