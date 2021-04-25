#include "RunApplication.hpp"


runApplication::runApplication()
{
	pockets::setupMap(this->gameBoard);
}

void runApplication::runApp() // This is where all the functions will be called for runApplication
{
	








}

void runApplication::mainMenu()
{

}

void runApplication::displayRules()
{

}

int runApplication::whoGoesFirst() // Function return a random integer (1 or 2) to determine which player goes first
{

}

void runApplication::selectPocket() // User selects a pocket to begin their turn; function validates the choice as a valid option
{

}

bool runApplication::disperseBeads() // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again 
{

}

bool runApplication::determineCapture() // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
{

}

bool runApplication::endOfGame() // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.
{

}

void runApplication::determineWinner() // Counts totals in the
{

}