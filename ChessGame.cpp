/*
*  FILE	         : ChessGame.cpp
*  PROJECT       : ChessGame
*  PROGRAMMER    : Sean Potts
*  FIRST VERSION : 2023-06-12
*  DESCRIPTION   :
*	This file contains the Classes and main for running the a chess game. 
*/
#include <vector>
#include <iostream>
#include <string.h>
#include <map>
#include <conio.h>
#include <random>

// Constants
using namespace std;
const int BOARD_SIZE = 8;

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


/*
 *  NAME    : ChessPeice
 *  PURPOSE : The purpose of this class is to hold properites and methods of a chess piece. This is includes
 *			  the peices color, type, and if it can perform a special move such as a pawned being able to jump two places at the start of the game. 
 *			  It also has a method for getting getting a peices possible move set. 
 *
 */
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

	
	/*
	 * FUNCTION      : getPossibleMoves
	 *
	 * DESCRIPTION   : This function returns a vector of possible moves for a chess piece.
	 *
	 * RETURNS       :
	 *   vector<pair<int, int>>   : A vector containing pairs of integers representing possible moves.
	 *
	 */	
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
				if (color == black) {
					PossibleMoves.push_back(std::make_pair(0, 1));
					PossibleMoves.push_back(std::make_pair(1, 1));
					PossibleMoves.push_back(std::make_pair(-1, 1));
				}
				else {
					PossibleMoves.push_back(std::make_pair(0, -1));
					PossibleMoves.push_back(std::make_pair(1, -1));
					PossibleMoves.push_back(std::make_pair(-1, -1));
				}
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
		case bishop:
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

		default:
			break;
			
		}
		return PossibleMoves;
	
	}
	
	// how it should move

private:	

	//bool canMove;

};



/*
 *  NAME    : ChessBoard
 *  PURPOSE : This class represents a chessboard which is constructed with the standard peices at the start of a chessgame. The ChessBoard class
 *			  allows players to move peices of their color.
 *
 */
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


	/*
	 * FUNCTION      : removeElements
	 *
	 * DESCRIPTION   : This function removes a chess piece from one position on the board and places it at another position.
	 *                 It also checks if a king is captured and determines the winner based on the captured king's color.
	 *
	 * PARAMETERS    :
	 *   col1        : The column index of the piece to be removed.
	 *   row1        : The row index of the piece to be removed.
	 *   col2        : The column index where the piece will be placed.
	 *   row2        : The row index where the piece will be placed.
	 *
	 * RETURNS       :
	 *   int         : 0 if no king is captured,
	 *                 1 if black king is captured and the winner is white,
	 *                 2 if white king is captured and the winner is black.
	 *
	 */
	int removeElements(int col1, int row1, int col2, int row2) 
	{

		int returnVal = 0;
		if (this->board[col2][row2] != NULL) {
			if (this->board[col2][row2]->curPiece == king) {
				Colors color = board[col2][row2]->color;
				if (color == black) {
					// winner is white
					returnVal = 1;
				}
				else
				{
					// winner is black
					returnVal = 2;
				}
			}
		}
		if(this->board[col1][row1] != NULL)
			this->board[col1][row1]->specialMove = false;

		this->board[col2][row2] = this->board[col1][row1];
		this->board[col1][row1] = NULL;
		return returnVal;

	}
	
	/*
	 * FUNCTION      : SelectPiece
	 *
	 * DESCRIPTION   : This function allows a player to select a piece on the chessboard.
	 *
	 * PARAMETERS    :
	 *   col         : Pointer to an integer to store the selected column index.
	 *   row         : Pointer to an integer to store the selected row index.
	 *   playername  : The name of the player.
	 *
	 * RETURNS       :
	 *   None
	 *
	 */
	void SelectPiece(int* col, int* row, string playername) {

		int selectedRow = 0;
		int selectedCol = 0;
		int keyPressed = 0;

		while (keyPressed != 13) // 13 is the ASCII value for Enter key
		{
			system("cls");
			Display(selectedRow, selectedCol, playername);

			// Handle user input
			keyPressed = _getch(); // Use getch() to get a character without waiting for the Enter key

			if (keyPressed == 224) // 224 is the extended key code
			{
				// Arrow key was pressed
				keyPressed = _getch(); // Read the actual key code

				if (keyPressed == 72) // 72 is the key code for up arrow
				{
					// Up arrow key was pressed
					if (selectedRow > 0)
						selectedRow--;
				}
				else if (keyPressed == 80) // 80 is the key code for down arrow
				{
					// Down arrow key was pressed
					if (selectedRow < BOARD_SIZE - 1)
						selectedRow++;
				}
				else if (keyPressed == 75) // 75 is the key code for left arrow
				{
					// Left arrow key was pressed
					if (selectedCol > 0)
						selectedCol--;
				}
				else if (keyPressed == 77) // 77 is the key code for right arrow
				{
					// Right arrow key was pressed
					if (selectedCol < BOARD_SIZE - 1)
						selectedCol++;
				}
			}
			
		}
		*row = selectedRow;
		*col = selectedCol;
		return;
	 }


	/*
	 * METHOD        : CheckKing
	 *
	 * DESCRIPTION   : This method checks for possible moves that put the king in check.
	 *
	 * PARAMETERS    :
	 *   kingsMoves  : A vector of pairs representing the possible moves for the king.
	 *   colKing     : The column index of the king.
	 *   rowKing     : The row index of the king.
	 *
	 * RETURNS       :
	 *   None
	 *
	 */
	vector<pair <int, int>> CheckKing(vector <pair <int, int>> kingsMoves, int colKing, int rowKing) {

		std::vector<pair<int, int> > PossibleMoves;

		// Gets a full cover of possible moves around king!
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
		PossibleMoves.push_back(std::make_pair(2, 1));
		PossibleMoves.push_back(std::make_pair(2, -1));
		PossibleMoves.push_back(std::make_pair(-2, 1));
		PossibleMoves.push_back(std::make_pair(-2, -1));
		PossibleMoves.push_back(std::make_pair(1, 2));
		PossibleMoves.push_back(std::make_pair(-1, 2));
		PossibleMoves.push_back(std::make_pair(1, -2));
		PossibleMoves.push_back(std::make_pair(-1, -2));

		for (auto it = begin(kingsMoves); it != end(kingsMoves); it++) {


			//get the x and y movement for each move
			int dx = it->first;
			int dy = it->second;

			// get the x and y location
			int x = colKing + dx;
			int y = rowKing + dy;

			for (auto iter = begin(PossibleMoves); iter != end(PossibleMoves); iter++) {

				int newX = x + it->first;
				int newY = y + it->second;

				// checks inside board
				if (newX >= 0 && newX <= 7 && newY >= 0 && newY <= 7) {
					if (board[newX][newY] != NULL && board[newX][newY]->color != board[colKing][rowKing]->color) {
						
					}

				}

			}

		}

	}

	/*
	 * METHOD        : validMoves
	 *
	 * DESCRIPTION   : This method calculates and returns the valid moves for a given piece on the chessboard.
	 *
	 * PARAMETERS    :
	 *   colPiece    : The column index of the piece.
	 *   rowPiece    : The row index of the piece.
	 *
	 * RETURNS       :
	 *   ValidMoves  : A vector of pairs representing the valid moves for the piece.
	 *
	 */
	 vector<pair<int, int> > validMoves(int colPiece, int rowPiece) {


		cout << "Piece selected: " << pieceNames[board[colPiece][rowPiece]->curPiece] << endl;
		// assign location
		selectedPieceLocation[0]= colPiece, selectedPieceLocation[1] = rowPiece;

		std::vector<pair<int, int> > PossibleMoves = this->board[colPiece][rowPiece]->getPossibleMoves();
		std::vector<pair<int, int> > ValidMoves; 
		
		for (auto it = begin(PossibleMoves); it != end(PossibleMoves); it++) {
			//get the x and y movement for each move
			int dx = it->first;
			int dy = it->second;

			// get the x and y location
			int x = colPiece + dx;
			int y = rowPiece + dy;

			// if pawn
			if (this->board[colPiece][rowPiece]->curPiece == pawn) {
				// Check if the move is within the board bounds
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					if (board[x][y] != NULL && board[x][y]->color == board[colPiece][rowPiece]->color) {
						// remove both pos move for pawn			
						if (dx == 0 && dy < 0) {
							// check for end first
							while (it != end(PossibleMoves) && it->first == 0 && it->second < 0)
							{
								it++;
							}
							it--;

						}
						// neg ver
						else if (dx == 0 && dy > 0) {
							while (it != end(PossibleMoves) && it->first == 0 && it->second > 0)
							{
								it++;
							}
							it--;

						}
					}
					else if (board[x][y] != NULL && board[x][y]->color != board[colPiece][rowPiece]->color && dx != 0) {
						// Add the move to valid moves
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
						cout << "Valid move: " << dx << ", " << dy << endl;

					}
					else if (board[x][y] == NULL && dx == 0) {
						// Add the move to valid moves
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
						cout << "Valid move: " << dx << ", " << dy << endl;
						
					}
				}
			}		
			else if (this->board[colPiece][rowPiece]->curPiece == knight) {
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					if (board[x][y] != NULL && board[x][y]->color != board[colPiece][rowPiece]->color) {
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
					}
					else if (board[x][y] == NULL) {
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
					}
				}
			}

			else if (this->board[colPiece][rowPiece]->curPiece == king) {
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					if (board[x][y] != NULL && board[x][y]->color != board[colPiece][rowPiece]->color) {
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
					}
					else if (board[x][y] == NULL) {
						
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
					}
				}
			}

			// logic check soon
			else {
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					if (board[x][y] != NULL && board[x][y]->color == board[colPiece][rowPiece]->color) {

						// we have our own piece infront  we need to figure out which way we are going and remove all possible movements such as hor/ver/diag
						if (dx > 0 && dy > 0) {
							while (it != end(PossibleMoves) && it->first > 0 && it->second > 0)
							{
								it++;
							}
							it--;
						}
						else if (dx > 0 && dy < 0) {
							while (it != end(PossibleMoves) && it->first > 0 && it->second < 0)
							{
								it++;
							}
							it--;
						}
						// pos x neg y ver 
						else if (dx < 0 && dy > 0) {
							while (it != end(PossibleMoves) && it->first < 0 && it->second > 0)
							{
								it++;
							}
							it--;
						}
						// neg x pos y ver 
						else if (dx < 0 && dy < 0) {
							while (it != end(PossibleMoves) && it->first < 0 && it->second < 0)
							{
								it++;
							}
							it--;
						}
						// neg x neg y ver

						else if (dx > 0 && dy == 0) {
							while (it != end(PossibleMoves) && it->first > 0 && it->second == 0)
							{
								it++;
							}
							it--;
						}
						// horizontal x pos
						else if (dx < 0 && dy == 0) {
							while (it != end(PossibleMoves) && it->first < 0 && it->second == 0)
							{
								it++;
							}
							it--;
						}
						// hor x neg
						else if (dx == 0 && dy < 0) {
							// check for end first
							while (it != end(PossibleMoves) && it->first == 0 && it->second < 0)
							{
								it++;
							}
							it--;

						}
						// neg ver
						else if (dx == 0 && dy > 0) {
							while (it != end(PossibleMoves) && it->first == 0 && it->second > 0)
							{
								it++;
							}
							it--;

						}
						// pos ver
					}
					else if (board[x][y] == NULL || board[x][y]->color != board[colPiece][rowPiece]->color) {
						// Add the move to valid moves
						ValidMoves.emplace_back(colPiece + dx, rowPiece + dy);
						cout << "Valid move: " << dx << ", " << dy << endl;
					}
				}
			}
		}
		
		return ValidMoves;

	 }

	~ChessBoard()
	{
	}
	
	/*
	 * METHOD        : Display
	 *
	 * DESCRIPTION   : This method displays the chessboard, highlighting the selected row and column, and prompts the player for the piece they want to move.
	 *
	 * PARAMETERS    :
	 *   selectedRow : The selected row index.
	 *   selectedCol : The selected column index.
	 *   playername  : The name of the player.
	 *
	 * RETURNS       : None
	 *
	 */
	void Display(int selectedRow, int selectedCol, string playername)
	{
		 // Clear the console (Windows)

		std::cout << "What piece do you want to move " << playername << "?" << std::endl;

		// Prints ChessBoard for Playing/Testing
		for (int j = 0; j < BOARD_SIZE; ++j) {
			for (int i = 0; i < BOARD_SIZE; ++i) {
				if (i == selectedCol && j == selectedRow) {
					std::cout << "->";
				}

				if (board[i][j] == NULL) {
					std::cout << "EMP ";
				}
				else {
					std::cout << colorNames[board[i][j]->color] << pieceNames[board[i][j]->curPiece] << " ";
				}
			}

			std::cout << j << std::endl;
		}

		for (int i = 0; i < BOARD_SIZE; i++) {
			std::cout << " " << i << "  ";
		}
	}

	

private:

};



/*
 *  NAME    : Player
 *  PURPOSE : Purpose is to store player data, such as the name, color of the player, and their number of turns
 *
 */
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


/*
 *  NAME    : Game
 *  PURPOSE : This holds a game which contains two players, and a chess board. The game determines whos turn it is based on starting color, after
 *			  which players take turns until one player gets their king taken and loses.
 *
 */
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
		stateOfGame = true;
		cout << "New Game Created!" << endl;
	}

	Player player1;
	Player player2;
	ChessBoard chessGame;
	bool stateOfGame;
	int whosTurn; // 1 or 2;
	string winner;

	~Game()
	{
	}
	
	/*
	 * METHOD        : MakeTurn
	 *
	 * DESCRIPTION   : This method represents a player's turn in the chess game. It handles the selection of a piece, displays valid moves, and allows the player to make a move.
	 *
	 * PARAMETERS    : None
	 *
	 * RETURNS       : None
	 *
	 */
	void MakeTurn() 
	{
		int selectedRow = 0;
		int selectedCol = 0;
		int keyPressed = 0;
		int selectedOption = 0;
		string playerName; 
		Colors currentPlayerCol;
		std::vector<std::pair<int, int>> ValidMoves;

		if (whosTurn == 1) 
		{
			playerName = player1.name;
			currentPlayerCol = player1.playerColor;
			whosTurn = 2;
		}
		else
		{
			playerName = player2.name;
			currentPlayerCol = player2.playerColor;
			whosTurn = 1;
		}
		while (1)
		{
			chessGame.SelectPiece(&selectedCol, &selectedRow, playerName);
			if (chessGame.board[selectedCol][selectedRow] != NULL && chessGame.board[selectedCol][selectedRow]->color == currentPlayerCol)
			{
				ValidMoves = chessGame.validMoves(selectedCol, selectedRow);
				if (ValidMoves.size() != 0) {
					break; 
				}
			}
			else {
				cout << "Can't Move Oppenents Piece \n" << endl;
			}
			cout << selectedCol << "and" << selectedRow << endl;

		}
		selectedOption = 0;
		keyPressed = 0;

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
		int gameState = chessGame.removeElements(chessGame.selectedPieceLocation[0], chessGame.selectedPieceLocation[1], ValidMoves[selectedOption].first, ValidMoves[selectedOption].second);
		
		
		if (gameState == 1) {
			stateOfGame = false;
			winner = player1.name;
		}
		else if (gameState == 2) {
			stateOfGame = false;
			winner = player2.name;
		}
		return;
	}


	/*
	 * METHOD        : displayOptions
	 *
	 * DESCRIPTION   : This method displays the valid moves along with the selected option.
	 *
	 * PARAMETERS    :
	 *   ValidMoves  : A vector of pairs representing the valid moves.
	 *   selectedOption : An integer representing the index of the selected option.
	 *
	 * RETURNS       : None
	 *
	 */
	void displayOptions(const std::vector<std::pair<int, int>>& ValidMoves, int selectedOption)
	{
		std::cout << "Valid moves are as follows:" << std::endl;
		if (ValidMoves.size() == 0) {
			cout << "No moves avaliable" << endl;

		}
		for (int i = 0; i < ValidMoves.size(); i++)
		{
			if (i == selectedOption)
				std::cout << "-> ";
			else
				std::cout << "   ";

			std::cout << ValidMoves[i].first << ", " << ValidMoves[i].second << std::endl;
		}
	}


private:

};

std::string coinToss()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	int result = dis(gen);

	if (result == 0)
		return "Heads";
	else
		return "Tails";
}




int main()
{
	string player1;
	string player2;
	Colors player1Col;
	Colors player2Col;


	cout << "Enter Player 1's Name: ";
	cin >> player1;

	cout << "Enter Player 2's Name: ";
	cin >> player2;

	ChessBoard chessboard;

	if (coinToss() == "Heads")
	{
		player1Col = white;
		player2Col = black;
	}
	else
	{
		player1Col = black;
		player2Col = white;
	}

	Game newGame(player1, player2, player1Col, player2Col);

	while (newGame.stateOfGame == true) {
		newGame.MakeTurn();
		if (newGame.stateOfGame == false)
			break;
	}
	cout << "Congrats " << newGame.winner <<  "You have won the game" << endl;


	return 0;


	
}

