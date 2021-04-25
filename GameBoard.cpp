#include "GameBoard.hpp"

GameBoard::GameBoard()
{
	gameBoard[0] = new BoardPocket;
	gameBoard[1] = new BoardPocket;
	gameBoard[2] = new BoardPocket;
	this->gameBoard[3] = new BoardPocket;
	this->gameBoard[4] = new BoardPocket;
	this->gameBoard[5] = new BoardPocket;
	this->gameBoard[6] = new MancalaPocket;
	this->gameBoard[7] = new BoardPocket;
	this->gameBoard[8] = new BoardPocket;
	this->gameBoard[9] = new BoardPocket;
	this->gameBoard[10] = new BoardPocket;
	this->gameBoard[11] = new BoardPocket;
	this->gameBoard[12] = new BoardPocket;
	this->gameBoard[13] = new MancalaPocket;
}