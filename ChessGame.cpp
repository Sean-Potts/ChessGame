// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Later other files will be added for cleaner code. Currently development of classes will all be done in ChassGame.cpp before being seperated into different files. 
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;



class ChessPeice
{
public:
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

class Pawn:ChessPeice
{
public:

	Pawn()
	{
	}

	~Pawn()
	{
	}

private:

};


class ChessBoard
{
public:

	ChessBoard()
	{
	}

	~ChessBoard()
	{
	}

private:

};



class Game
{
public:

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
