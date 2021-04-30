#include "RunApplication.hpp"
#include <time.h>
	
sf::Texture runApplication::boardTexture;
sf::Texture runApplication::buttonsTexture;
sf::Texture runApplication::marbleTexture1;
sf::Texture runApplication::marbleTexture0;
sf::Font runApplication::pocketFont;
sf::Font runApplication::statusFont;

runApplication::runApplication()
{
	pockets::setupMap(this->gameBoard);
	srand((unsigned int)time(NULL));
#if defined(WINDOWS)
	runApplication::boardTexture.loadFromFile("Images\\gameAssets\\mancalaBoard.png");
	runApplication::buttonsTexture.loadFromFile("Images\\gameAssets\\buttons.png");
	runApplication::marbleTexture0.loadFromFile("Images\\gameAssets\\marble0.png");
	runApplication::marbleTexture1.loadFromFile("Images\\gameAssets\\marble1.png");
	runApplication::pocketFont.loadFromFile("Fonts\\game_over.ttf");
	runApplication::statusFont.loadFromFile("Fonts\\bubbly.ttf");
#else
    runApplication::boardTexture.loadFromFile("Images/gameAssets/mancalaBoard.png");
    runApplication::buttonsTexture.loadFromFile("Images/gameAssets/buttons.png");
    runApplication::marbleTexture0.loadFromFile("Images/gameAssets/marble0.png");
    runApplication::marbleTexture1.loadFromFile("Images/gameAssets/marble1.png");
    runApplication::pocketFont.loadFromFile("Fonts/game_over.ttf");
    runApplication::statusFont.loadFromFile("Fonts/bubbly.ttf");
#endif
}

void runApplication::runApp() {

	// Initialize Window, Textures, and Sprites
	sf::RenderWindow window(sf::VideoMode(800, 350), "Mancala Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(5);
	

	// Who goes first
	whoGoesFirst();
	// create sprites
	sf::Sprite boardSprite;
	sf::Sprite buttonSprite;

	// set Textures 
	boardSprite.setTexture(runApplication::boardTexture);
	buttonSprite.setTexture(runApplication::buttonsTexture);

	// initialize board with marbles
	int offset = 13;
	float pocketOffset = 30;
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
				pocketPositions.insert(std::make_pair(kb.first, std::vector<float>({ (float)pocketOffset, (float)(80 - pocketOffset), (float)pocketOffset, (float)(300 - pocketOffset) })));
			}
			else {
				pocketPositions.insert(std::make_pair(kb.first, std::vector<float>({ (float)(700 + pocketOffset), (float)(780 - pocketOffset), (float)pocketOffset, (float)(300 - pocketOffset) })));
			}

		}
	}

	sf::Event ev;
	while (window.isOpen())
	{
        bool showingRules = false;
        sf::RectangleShape rulesShape;
        sf::Text rulesText;
		//Event polling
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				break;
            case sf::Event::KeyReleased:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    showingRules = false;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    auto position = sf::Mouse::getPosition(window);
                    
                    if (position.x >= 750 && position.y >= 300) {
                        if (showingRules) { break; }
                        this->displayRules(rulesShape, rulesText);
                        showingRules = true;
                        break;
                    } else if (position.y > 300) { break; }
                    
                    for (auto kb : gameBoard) {
                        if (kb.first != "P1" && kb.first != "P2") {
                            std::string temp = kb.first;
                            float minX = atoi(&temp[1]) * 100;
                            float maxX = minX + 100;
                            float minY = temp[0] == 'B' ? 0 : 150;
                            float maxY = minY + 150;
                            if (position.x > minX && position.x < maxX && position.y > minY && position.y < maxY && pockets::ownsPocket(temp, this->playerNumber) && gameBoard[temp]->getMarble().size() > 0) {
                                if (!disperseBeads(temp)) {
                                    switchTurns();
                                }
                                bool sideOneEmpty = false,
                                sideTwoEmpty = false;
                                int marbleCountA = 0,
                                marbleCountB = 0;
                                for (auto pocketName : gameBoard) {
                                    if (pocketName.first.at(0) == 'A') {
                                        for (auto marble : pocketName.second->getMarble()) {
                                            ++marbleCountA;
                                        }

                                    }
                                    if (pocketName.first.at(0) == 'B') {
                                        for (auto marble : pocketName.second->getMarble()) {
                                            ++marbleCountB;
                                        }
                                    }
                                }
                                if (marbleCountA == 0) {
                                    sideOneEmpty = true;
                                }
                                else if (marbleCountB == 0) {
                                    sideTwoEmpty = true;
                                }
                                if (sideOneEmpty || sideTwoEmpty) {
                                    endOfGame(sideOneEmpty ? "B" : "A", window);
                                }
                            }
                        }
                    }
                }
            default: break;
            }
		}
		// Update


		// Render
		window.clear(sf::Color(0, 0, 0, 255)); // Clear old frame
        
        // show rules and stop if needed.
        if (showingRules) {
            window.draw(rulesShape);
            window.draw(rulesText);
            window.display();
            system("read -r");
            continue;
        }

		// Draw sprite and pocket counts
		window.draw(boardSprite);
		buttonSprite.setPosition(0, 300);
		window.draw(buttonSprite);
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
		sf::Text currentPlayerText("Player Number: " + std::to_string(this->playerNumber), this->statusFont, 15);
		currentPlayerText.setPosition(60, 317);
        
        sf::Text rulesIcon("?", this->statusFont, 15);
        rulesIcon.setPosition(766,317);
        
        sf::Text statusBar("Play Again", this->statusFont, 15);
        statusBar.setPosition(500, 317);
        
		window.draw(currentPlayerText);
        window.draw(rulesIcon);
        window.draw(statusBar);
        
		window.display(); // Tell app that window is done drawing
	}
}

int runApplication::mainMenu()
{
	return 0;
}

void runApplication::displayRules(sf::RectangleShape & rect, sf::Text & text)
{
    sf::RectangleShape view(sf::Vector2f(800,350));
    view.setFillColor(sf::Color::Black);
    // "Welcome to the ancient strategy game of Mancala!\n\nThe rules of this game are simple: players will take turns selecting pockets from their\nside of the board, and after a choice\nis made, the marbles from that pocket are dropped in pockets rotating counterclockwise\naround the board. Players score points\nby dropping marbles in their scoring pocket (the larger pocket to the right of the players board pockets) as they move around the board. Players only\ndrop marbles in their own scoring pocket, and skip their opponents scoring pocket if they make it around the entire board.\n\nThere are just a few other rules to keep in mind: if you pick a pocket that has the perfect number of marbles to land in your scoring pocket, you get to\ngo again! Also, if you select a pocket in which your last marble lands in an empty pocket on your side of the board, and the opposing pocket on your\nopponent’s side has one or more marbles in it, then you get to “capture” your opponent’s marbles (and your single marble) and add them to your scoring\npocket!\n\nThe game ends once one player clears all the marbles on their side of the board. All remaining marbles on the opponent’s side of the board\nare then added to the opponents scoring pocket. The player with the most marbles in their scoring pocket at the end of the game wins!"
    
    
    sf::Text _text(wrapText("Welcome to the ancient strategy game of Mancala!\n\nThe rules of this game are simple: players will take turns selecting pockets from their side of the board, and after a choice is made, the marbles from that pocket are dropped in pockets rotating counterclockwise around the board. Players score points by dropping marbles in their scoring pocket (the larger pocket to the right of the players board pockets) as they move around the board. Players only drop marbles in their own scoring pocket, and skip their opponents scoring pocket if they make it around the entire board.\n\nThere are just a few other rules to keep in mind: if you pick a pocket that has the perfect number of marbles to land in your scoring pocket, you get to go again! Also, if you select a pocket in which your last marble lands in an empty pocket on your side of the board, and the opposing pocket on your opponent’s side has one or more marbles in it, then you get to “capture” your opponent’s marbles (and your single marble) and add them to your scoring pocket!\n\nThe game ends once one player clears all the marbles on their side of the board. All remaining marbles on the opponent’s side of the board are then added to the opponents scoring pocket. The player with the most marbles in their scoring pocket at the end of the game wins!\n\n[Press return to continue...]", 800, this->statusFont, 12), this->statusFont, 12);
    
    _text.setPosition(0, 0);
    _text.setFillColor(sf::Color::White);
    
    rect = view;
    text = _text;
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

bool runApplication::disperseBeads(const std::string pocketName) // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again 
{
	std::string temp = pocketName;
	for (auto target : gameBoard[pocketName]->getMarble()) {
		// sound
		pockets::nextPosition(temp, playerNumber);
		float x = determineValidLocation(pocketPositions[temp].at(0), pocketPositions[temp].at(1));
		float y = determineValidLocation(pocketPositions[temp].at(2), pocketPositions[temp].at(3));
		float deltaX = x - target->getPosition().x;
		float deltaY = y - target->getPosition().y;
		target->move(sf::Vector2f(deltaX, deltaY));
		gameBoard[temp]->addMarble(target);
	}
	gameBoard[pocketName]->getMarble().clear();
	if (determineCapture(temp)) {
		std::string opposite = pockets::getOppositeFromKey(temp);
		for (auto marble : gameBoard[opposite]->getMarble()) {
			float x = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(0), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(1));
			float y = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(2), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(3));
			float deltaX = x - marble->getPosition().x;
			float deltaY = y - marble->getPosition().y;
			marble->move(sf::Vector2f(deltaX, deltaY));
			gameBoard[playerNumber == 1 ? "P1" : "P2"]->addMarble(marble);
		}
		for (auto marble : gameBoard[temp]->getMarble()) {
			float x = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(0), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(1));
			float y = determineValidLocation(pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(2), pocketPositions[playerNumber == 1 ? "P1" : "P2"].at(3));
			float deltaX = x - marble->getPosition().x;
			float deltaY = y - marble->getPosition().y;
			marble->move(sf::Vector2f(deltaX, deltaY));
			gameBoard[playerNumber == 1 ? "P1" : "P2"]->addMarble(marble);
		}
		gameBoard[temp]->getMarble().clear();
		gameBoard[opposite]->getMarble().clear();
	}
	return temp == (playerNumber == 1 ? "P1" : (playerNumber == 2 ? "P2" : "")); // if playerNumber == 1, then P1, else check if playerNumber == 2, then P2 else return false
}

bool runApplication::determineCapture(const std::string &pocketName) // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
{
	if (pockets::ownsPocket(pocketName, this->playerNumber)) {
		std::cout << pockets::getOppositeFromKey(pocketName) << std::endl;
		if (gameBoard[pocketName]->getMarble().size() == 1) {
			if (gameBoard[pockets::getOppositeFromKey(pocketName)]->getMarble().size() > 0) {
				return true;
			}
		}
	}
	return false;
}

void runApplication::endOfGame(std::string emptyThisSide, sf::RenderWindow& mainWindow) // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.
{
	int marbleCountSideA = 0,
		marbleCountSideB = 0;
	if (emptyThisSide == "A") {
		// empty side A
		for (auto kb : gameBoard) {
			if (kb.first.at(0) == 'A') {
				for (auto marble : kb.second->getMarble()) {
					float x = determineValidLocation(pocketPositions["P2"].at(0), pocketPositions["P2"].at(1));
					float y = determineValidLocation(pocketPositions["P2"].at(2), pocketPositions["P2"].at(3));
					float deltaX = x - marble->getPosition().x;
					float deltaY = y - marble->getPosition().y;
					marble->move(sf::Vector2f(deltaX, deltaY));
					gameBoard["P2"]->addMarble(marble);
				}
			}
		}

			for (auto marble : gameBoard["P1"]->getMarble()) {
				++marbleCountSideA;
			}
			for (auto marble : gameBoard["P2"]->getMarble()) {
				++marbleCountSideB;
			}
		}
	else {
		// empty side B
		for (auto kb : gameBoard) {
			if (kb.first.at(0) == 'B') {
				for (auto marble : kb.second->getMarble()) {
					float x = determineValidLocation(pocketPositions["P1"].at(0), pocketPositions["P1"].at(1));
					float y = determineValidLocation(pocketPositions["P1"].at(2), pocketPositions["P1"].at(3));
					float deltaX = x - marble->getPosition().x;
					float deltaY = y - marble->getPosition().y;
					marble->move(sf::Vector2f(deltaX, deltaY));
					gameBoard["P1"]->addMarble(marble);
				}
			}
		}

		for (auto marble : gameBoard["P1"]->getMarble()) {
			++marbleCountSideA;
		}
		for (auto marble : gameBoard["P2"]->getMarble()) {
			++marbleCountSideB;
		}
	}

	int winner = -1;
	if (marbleCountSideA > marbleCountSideB) {
		// Player 1 wins
		winner = 1;
	}
	else if (marbleCountSideA < marbleCountSideB) {
		// Player 2 wins
		winner = 2;
	}
	else {
		//tie
		winner = 0;
	}

	// Render
	mainWindow.clear(sf::Color(0, 0, 0, 255)); // Clear old frame
	
	//Who won?
	switch (winner) {
		case 1: {
			sf::Text winnerText("Player 1 wins!", this->statusFont, 20);
			winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((350 - winnerText.getGlobalBounds().height) / 2));
			mainWindow.draw(winnerText);
			mainWindow.display(); // Tell app that window is done drawing
			system("pause");
			break;
		}
		case 2: {
			sf::Text winnerText("Player 2 wins!", this->statusFont, 20);
			winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((350 - winnerText.getGlobalBounds().height) / 2));
			mainWindow.draw(winnerText);
			mainWindow.display(); // Tell app that window is done drawing
			system("pause");
			break;
		}
		case 0: {
			sf::Text winnerText("It's a tie!!", this->statusFont, 20);
			winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((350 - winnerText.getGlobalBounds().height) / 2));
			mainWindow.draw(winnerText);
			mainWindow.display(); // Tell app that window is done drawing
			system("pause");
			break;
		}
	}
}

void runApplication::determineWinner() // Counts totals in the
{

}


inline float runApplication::determineValidLocation(float min, float max) {
	return rand() % (int)(max - min) + min;
}
