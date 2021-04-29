#pragma once

#include "Headers.hpp"

class runApplication
{
public:
	runApplication();

	void runApp();

	int mainMenu();
	void displayRules();
	inline void whoGoesFirst(); // Function return a random integer (1 or 2) to determine which player goes first
	void switchTurns(void);

	void selectPocket(); // User selects a pocket to begin their turn; function validates the choice as a valid option
	std::pair<bool, std::pair<std::string, bool>> disperseBeads(const std::string pocketName); // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again 
	bool determineCapture(); // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
	void captureAndScore(); // Performs the capture action
	bool endOfGame(); // returns true if the game is over; false otherwise (i.e.one player doesnt have any beads on their side of the board.

	void determineWinner(); // Counts totals in the 
	inline float determineValidLocation(float min, float max);

private:
	int playerNumber;
	static sf::Texture boardTexture;
	static sf::Texture marbleTexture1;
	static sf::Texture marbleTexture0;
	pockets::pocketMap gameBoard;
	std::unordered_map<std::string, std::vector<float>> pocketPositions;
};



