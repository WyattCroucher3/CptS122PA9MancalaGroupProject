#include "RunApplication.hpp"
#include <time.h>


runApplication::runApplication()
{
	pockets::setupMap(this->gameBoard);
	srand((unsigned int)time(NULL));

	// Initialize Window, Textures, and Sprites
	sf::RenderWindow window(sf::VideoMode(800, 300), "Mancala Game", sf::Style::Titlebar | sf::Style::Close);

	// Textures
	sf::Texture boardTexture;
	boardTexture.loadFromFile("Images\\gameAssets\\mancalaBoard.png");

	sf::Texture marbleTexture0;
	marbleTexture0.loadFromFile("Images\\gameAssets\\marble0.png");

	sf::Texture marbleTexture1;
	marbleTexture0.loadFromFile("Images\\gameAssets\\marble1.png");

	// create sprites
	sf::Sprite boardSprite;
	sf::Sprite marbleSprite0[24];
	sf::Sprite marbleSprite1[24];

	// set Textures for sprites
	boardSprite.setTexture(boardTexture);

	for (int index = 0; index < 24; ++index) {
		marbleSprite0[index].setTexture(marbleTexture0);
		marbleSprite1[index].setTexture(marbleTexture1);
	}
}

//void runApplication::runApp() // This is where all the functions will be called for runApplication
//{
//	int mainOption = 0, turn = 0;
//
//
//	// Choice 1: Play game
//	// Choice 2: How to play
//	// Choice 3: Exit application
//
//	do { // loops till user wants to exit game
//
//		mainOption = mainMenu();
//
//		if (mainOption == 1) // User wants to play the game
//		{
//			bool gameOver = false, goAgain = false, capture = false;
//
//			turn = whoGoesFirst(); // Player who goes first is picked at random
//
//			do { // Loops until one player has no beads on their side
//
//				do {
//
//					selectPocket(); //pocket is selected by the user
//					goAgain = disperseBeads(); //beads are moved counterclockwise around the board
//
//				} while (goAgain == true); // will loop is a bead lands in the mancala pocket
//				
//				capture = determineCapture(); // determines if the player cets to "capture" the opponents beads
//
//				if (capture == true)
//				{
//					captureAndScore(); // Captures if determined to be true
//				}
//
//				gameOver = endOfGame(); // Checks to see if the game has ended
//
//                if (endOfGame() == false)
//				{
//					switchTurns(turn); // If the game isn't over, the players switch turns
//				}
//
//			} while (gameOver == false); // If the game is over, we break out of the loop
//
//			determineWinner(); // A winner is determined by the contents of their mancala pockets
//
//		}
//		if (mainOption == 2) // User selected the tutorial
//		{
//
//			displayRules();
//
//		}
//		else
//		{
//
//		}
//
//	} while (mainOption >= 1 && mainOption <= 2);
//
//	return;
//}

void runApplication::runApp() {
	while 
}

int runApplication::mainMenu()
{

}

void runApplication::displayRules()
{

}

int runApplication::whoGoesFirst() // Function return a random integer (1 or 2) to determine which player goes first
{
	int player = 0;
	player = rand() % 2 + 1;
	
	return player;
}

void runApplication::switchTurns(int& player) // Function rotates between players after each turn
{
	if (player == 1)
	{
		player = 2;
	}
	else if (player == 2)
	{
		player = 1;
	}

	return;
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

void runApplication::captureAndScore() // Performs the capture action
{

}

bool runApplication::endOfGame() // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.
{

}

void runApplication::determineWinner() // Counts totals in the
{

}
