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
	bool determineCapture(const std::string& pocketName); // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
	void captureAndScore(); // Performs the capture action
	bool endOfGame(); // returns true if the game is over; false otherwise (i.e.one player doesnt have any beads on their side of the board.

	void determineWinner(); // Counts totals in the 
	inline float determineValidLocation(float min, float max);

private:
	int playerNumber;
	static sf::Texture boardTexture;
	static sf::Texture marbleTexture1;
	static sf::Texture marbleTexture0;
	static sf::Font pocketFont;
	static sf::Font statusFont;
	pockets::pocketMap gameBoard;
	std::unordered_map<std::string, std::vector<float>> pocketPositions;
	const std::unordered_map<std::string, std::pair<float, float>> pocketFontLocations =
		{ {"P1", std::make_pair(45,240) },
		{"A1", std::make_pair(145,240) },
		{"A2", std::make_pair(245,240) },
		{"A3", std::make_pair(345,240) },
		{"A4", std::make_pair(445,240) },
		{"A5", std::make_pair(545,240) },
		{"A6", std::make_pair(645,240) },
		{"P2", std::make_pair(745,240) },
		{"B1", std::make_pair(145,90) },
		{"B2", std::make_pair(245,90) },
		{"B3", std::make_pair(345,90) },
		{"B4", std::make_pair(445,90) },
		{"B5", std::make_pair(545,90) },
		{"B6", std::make_pair(645,90) } };
};



