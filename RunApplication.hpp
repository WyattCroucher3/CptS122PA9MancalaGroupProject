#pragma once

#include "Gameboard.hpp"
#include "pockets.hpp"

class runApplication
{
public:
	void runApp();

	void mainMenu();
	void displayRules();
	int whoGoesFirst(); // Function return a random integer (1 or 2) to determine which player goes first

	void selectPocket(); // User selects a pocket to begin their turn; function validates the choice as a valid option
	bool disperseBeads(); // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again 

	bool determineCapture(); // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
	bool endOfGame(); // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.

	void determineWinner(); // Counts totals in the 

private:
	GameBoard gameBoard[14];
};