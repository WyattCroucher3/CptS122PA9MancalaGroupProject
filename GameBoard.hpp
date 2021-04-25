#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::fstream;
using std::string;
using std::vector;

#include "pockets.hpp"

class GameBoard
{
public:
	GameBoard();

	~GameBoard();

private:
	gameBoard[0] = new BoardPocket;
	gameBoard[1] = new BoardPocket;
	gameBoard[2] = new BoardPocket;
	gameBoard[3] = new BoardPocket;
	gameBoard[4] = new BoardPocket;
	gameBoard[5] = new BoardPocket;
	gameBoard[6] = new MancalaPocket;
	gameBoard[7] = new BoardPocket;
	gameBoard[8] = new BoardPocket;
	gameBoard[9] = new BoardPocket;
	gameBoard[10] = new BoardPocket;
	gameBoard[11] = new BoardPocket;
	gameBoard[12] = new BoardPocket;
	gameBoard[13] = new MancalaPocket;
};