#include "RunApplication.hpp"
#include <time.h>
	
sf::Texture runApplication::boardTexture;
sf::Texture runApplication::marbleTexture1;
sf::Texture runApplication::marbleTexture0;
sf::Font runApplication::pocketFont;
sf::Font runApplication::statusFont;

runApplication::runApplication()
{
	pockets::setupMap(this->gameBoard);
	srand((unsigned int)time(NULL));
	runApplication::boardTexture.loadFromFile("Images\\gameAssets\\mancalaBoard.png");
	runApplication::marbleTexture0.loadFromFile("Images\\gameAssets\\marble0.png");
	runApplication::marbleTexture1.loadFromFile("Images\\gameAssets\\marble1.png");
	runApplication::pocketFont.loadFromFile("game_over.ttf");
	runApplication::statusFont.loadFromFile("bubbly.ttf");
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
	sf::RenderWindow window(sf::VideoMode(800, 350), "Mancala Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(5);
	

	// Who goes first
	whoGoesFirst();
	// create board sprite
	sf::Sprite boardSprite;

	// set Textures for board
	boardSprite.setTexture(runApplication::boardTexture);

	// initialize board with marbles
	int offset = 13;
	for (auto kb : gameBoard) {


		if (kb.first != "P1" && kb.first != "P2") {
			std::string temp = kb.first;
			float minX = atoi(&temp[1]) * 100 + offset;
			float maxX = minX + 60 - offset;
			float minY = temp[0] == 'B' ? offset : 150 + offset;
			float maxY = minY + 90 - offset;
			pocketPositions.insert(std::make_pair(kb.first, std::vector<float>({ minX, maxX, minY, maxY })));

			for (int index = 0; index < 4; ++index) {
				float x = rand() % (int)(maxX - minX) + minX;
				float y = rand() % (int)(maxY - minY) + minY;
				if (index % 2) {
					kb.second->addMarble(runApplication::marbleTexture1, sf::Vector2f(x, y));
				}
				else {
					kb.second->addMarble(runApplication::marbleTexture0, sf::Vector2f(x, y));
				}
			}
		}
		else {
			if (kb.first == "P1") {
				pocketPositions.insert(std::make_pair(kb.first, std::vector<float>({ (float)offset, (float)(100 - offset), (float)offset, (float)(300 - offset) })));
			}
			else {
				pocketPositions.insert(std::make_pair(kb.first, std::vector<float>({ (float)(700 + offset), (float)(800 - offset), (float)offset, (float)(300 - offset) })));
			}

		}
	}

	bool changePlayers = true;
	sf::Event ev;
	while (window.isOpen())
	{
		//Event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "click occurred" << std::endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					std::cout << "left mouse button press occurred" << std::endl;
					auto position = sf::Mouse::getPosition(window);
					for (auto kb : gameBoard) {
						if (kb.first != "P1" && kb.first != "P2") {
							std::string temp = kb.first;
							float minX = atoi(&temp[1]) * 100;
							float maxX = minX + 100;
							float minY = temp[0] == 'B' ? 0 : 150;
							float maxY = minY + 150;
							if (position.x > minX && position.x < maxX && position.y > minY && position.y < maxY) {
								std::pair<bool, std::pair<std::string,bool>> result = disperseBeads(temp);
								if (result.first) {
									changePlayers = false;
									//if (result.second.second) {
										//std::string pocket = pockets::getOppositeFromKey(result.second.first);
									//}
								}
								break;
							}
						}
					}
				}
			}
		}
		// Update


		// Render
		window.clear(sf::Color(0, 0, 0, 255)); // Clear old frame

		// Draw sprite and pocket counts
		window.draw(boardSprite);
		for (auto kb : gameBoard) {
			auto marbles = kb.second->getMarble();
			for (auto marble : marbles) {
				window.draw(*marble);
			}
			
			sf::Text temporaryText(std::to_string(marbles.size()), runApplication::pocketFont, 60);
			temporaryText.setPosition(this->pocketFontLocations.at(kb.first).first, this->pocketFontLocations.at(kb.first).second);
			window.draw(temporaryText);
		}

		// Draw fonts
		
		//Player indicator
		sf::Text currentPlayerText("Player Number: " + std::to_string(this->playerNumber), this->statusFont, 20);
		currentPlayerText.setPosition(0, 300);
		window.draw(currentPlayerText);
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

inline void runApplication::whoGoesFirst() // Function return a random integer (1 or 2) to determine which player goes first
{
	playerNumber = rand() % 2 + 1;
}

void runApplication::switchTurns(void) // Function rotates between players after each turn
{
	if (playerNumber == 1)
	{
		playerNumber = 2;
	}
	else if (playerNumber == 2)
	{
		playerNumber = 1;
	}

	return;
}

void runApplication::selectPocket() // User selects a pocket to begin their turn; function validates the choice as a valid option
{

}

std::pair<bool, std::pair<std::string, bool>> runApplication::disperseBeads(const std::string pocketName) // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again 
{
	std::cout << "Player Number: " << this->playerNumber << std::endl;
	std::string temp = pocketName;
	std::cout << "PocketName: " << pocketName << std::endl;
	std::cout << "Size: " << gameBoard[pocketName]->getMarble().size() << std::endl;
	for (auto target : gameBoard[pocketName]->getMarble()) {
		// sound
		pockets::nextPosition(temp, playerNumber);
		std::cout << "Next Position: " << temp << std::endl;
		float x = determineValidLocation(pocketPositions[temp].at(0), pocketPositions[temp].at(1));
		float y = determineValidLocation(pocketPositions[temp].at(2), pocketPositions[temp].at(3));
		float deltaX = x - target->getPosition().x;
		float deltaY = y - target->getPosition().y;
		target->move(sf::Vector2f(deltaX, deltaY));
		gameBoard[temp]->addMarble(target);
		//gameBoard[pocketName]->getMarble().remove(target);
	}
	gameBoard[pocketName]->getMarble().clear();
	//if (determineCapture()) {
	//	std::string opposite = pockets::getOppositeFromKey(temp);
	//	for (auto marble : gameBoard[opposite]->getMarble()) {
	//		float x = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(0), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(1));
	//		float y = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(2), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(3));
	//		float deltaX = x - marble->getPosition().x;
	//		float deltaY = y - marble->getPosition().y;
	//		marble->move(sf::Vector2f(deltaX, deltaY));
	//		gameBoard[playerNumber == 1 ? "P1" : "P2"]->addMarble(marble);
	//		gameBoard[opposite]->getMarble().pop_front();
	//	}
	//}
	return std::make_pair(false, std::make_pair("", false));
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


inline float runApplication::determineValidLocation(float min, float max) {
	return rand() % (int)(max - min) + min;
}