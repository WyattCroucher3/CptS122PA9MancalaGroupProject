#include "RunApplication.hpp"
#include <time.h>


runApplication::runApplication()
{
	pockets::setupMap(this->gameBoard);
	srand((unsigned int)time(NULL));
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

	// Initialize Window, Textures, and Sprites
	sf::RenderWindow window(sf::VideoMode(800, 300), "Mancala Game", sf::Style::Titlebar | sf::Style::Close);

	// Textures
	sf::Texture boardTexture;
	boardTexture.loadFromFile("Images\\gameAssets\\mancalaBoard.png");
	sf::Texture marbleTexture0;
	marbleTexture0.loadFromFile("Images\\gameAssets\\marble0.png");
	sf::Texture marbleTexture1;
	marbleTexture1.loadFromFile("Images\\gameAssets\\marble1.png");

	// create board sprite
	sf::Sprite boardSprite;

	// set Textures for board
	boardSprite.setTexture(boardTexture);

	for (auto kb : gameBoard) {
		if (kb.first != "P1" && kb.first != "P2") {
			kb.second.
		}
	}

	sf::Event ev;
	while (window.isOpen())
	{
		//Event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		// Update


		// Render
		window.clear(sf::Color(255, 255, 255, 255)); // Clear old frame

		// Draw sprite
		window.draw(boardSprite);
		PocketShape newShape;
		newShape.setSize(sf::Vector2f(100, 50));
		for (auto marble : newShape.marbles) {
			window.draw(*marble);
		}
		system("pause");
		window.display(); // Tell app that window is done drawing
	}
}

int runApplication::mainMenu()
{
	return 0;
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
	return true;
}

bool runApplication::determineCapture() // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
{
	return true;
}

void runApplication::captureAndScore() // Performs the capture action
{
	
}

bool runApplication::endOfGame() // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.
{
	return true;
}

void runApplication::determineWinner() // Counts totals in the
{

}
