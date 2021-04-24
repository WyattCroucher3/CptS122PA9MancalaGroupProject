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

#include "MancalaPocket.h"
#include "BoardPocket.h"

class GameBoard : public MancalaPocket, public BoardPocket
{
public:
	GameBoard();

	~GameBoard();

private:
	GameBoard* gameBoard[14];
};