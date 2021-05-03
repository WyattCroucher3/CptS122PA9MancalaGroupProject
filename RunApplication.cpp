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

runApplication::~runApplication() {
    for (auto kv : this->gameBoard) {
        if (kv.second != nullptr) {
            delete kv.second;
        }
    }
}

void runApplication::runApp() {
	// Initialize Window, Textures, and Sprites
	sf::RenderWindow window(sf::VideoMode(800, 350), "Mancala Game", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(240);

	//Variables
	std::string statusText;
	int winner = -1;

	// Rules initialization
	bool showingRules = false;
	sf::RectangleShape rulesShape;
	sf::Text rulesText;

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
	for (auto kv : gameBoard) {


		if (kv.first != "P1" && kv.first != "P2") {
			std::string temp = kv.first;
			float minX = atoi(&temp[1]) * 100 + offset;
			float maxX = minX + 60 - offset;
			float minY = temp[0] == 'B' ? offset : 150 + offset;
			float maxY = minY + 90 - offset;
			pocketPositions.insert(std::make_pair(kv.first, std::vector<float>({ minX, maxX, minY, maxY })));

			for (int index = 0; index < 4; ++index) {
#if defined(WINDOWS)
                float x = (float)(rand() % (int)(maxX - minX)) + minX;
                float y = (float)(rand() % (int)(maxY - minY)) + minY;
#else
                float x = (float)(arc4random() % (uint32_t)(maxX - minX)) + minX;
                float y = (float)(arc4random() % (uint32_t)(maxY - minY)) + minY;
#endif
				if (index % 2) {
					kv.second->addMarble(runApplication::marbleTexture1, sf::Vector2f(x, y));
				}
				else {
					kv.second->addMarble(runApplication::marbleTexture0, sf::Vector2f(x, y));
				}
			}
		}
		else {
			if (kv.first == "P1") {
                pocketPositions.insert(std::make_pair(kv.first, std::vector<float>({ (float)pocketOffset, (float)(80 - pocketOffset), (float)pocketOffset, (float)(275 - pocketOffset) })));
			}
			else {
                pocketPositions.insert(std::make_pair(kv.first, std::vector<float>({ (float)(700 + pocketOffset), (float)(780 - pocketOffset), (float)pocketOffset, (float)(275 - pocketOffset) })));
			}

		}
	}

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
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && showingRules == true) {
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
					}
					else if (position.y > 300) { break; }

					for (auto kv : gameBoard) {
						if (kv.first != "P1" && kv.first != "P2") {
							std::string temp = kv.first;
							float minX = atoi(&temp[1]) * 100;
							float maxX = minX + 100;
							float minY = temp[0] == 'B' ? 0 : 150;
							float maxY = minY + 150;
							if (position.x > minX && position.x < maxX && position.y > minY && position.y < maxY && pockets::ownsPocket(temp, this->playerNumber) && gameBoard[temp]->getMarble().size() > 0) {
								std::pair<bool, bool> result = disperseBeads(temp, REDRAW_PARAMS);
								if (!result.first) {
									switchTurns();
									statusText = "";
								}
								
								else {
									statusText = "Play again!";
								}

							    if (result.second) {
									if (this->playerNumber == 1) {
										statusText = "Player 2 Capture!";
									}
									else {
										statusText = "Player 1 Capture!";
									}
								}

								bool sideOneEmpty = false,
									sideTwoEmpty = false;
								int marbleCountA = 0,
									marbleCountB = 0;
								for (auto pocketName : gameBoard) {
									if (pocketName.first.at(0) == 'A') {
                                        
                                        marbleCountA += pocketName.second->count();
									}
									if (pocketName.first.at(0) == 'B') {
                                        
                                        marbleCountB += pocketName.second->count();
									}
								}
								if (marbleCountA == 0) {
									sideOneEmpty = true;
								}
								else if (marbleCountB == 0) {
									sideTwoEmpty = true;
								}
								if (sideOneEmpty || sideTwoEmpty) {
									winner = endOfGame(sideOneEmpty ? "B" : "A", REDRAW_PARAMS);
								}
							}
						}
					}
				}
			default: break;
			}
		}
		// Update

		// show rules and stop if needed.
		if (showingRules) {
#ifndef __APPLE__
            window.setTitle("Mancala Game - Help Menu");
#endif
			window.clear(sf::Color(0, 0, 0, 255)); // Clear old frame
			window.draw(rulesShape);
			window.draw(rulesText);
			window.display();
		}
		else if (winner >= 0) {
			// clear window
			window.clear(sf::Color(0, 0, 0, 255)); // Clear old frame
			// Draw sprite and pocket counts
			window.draw(boardSprite);
			buttonSprite.setPosition(0, 300);
			window.draw(buttonSprite);
			for (auto kv : gameBoard) {
				auto marbles = kv.second->getMarble();
				for (auto marble : marbles) {
					window.draw(*marble);
				}

				sf::Text temporaryText(std::to_string(marbles.size()), runApplication::pocketFont, 60);
				temporaryText.setPosition(this->pocketFontLocations.at(kv.first).first, this->pocketFontLocations.at(kv.first).second);
				window.draw(temporaryText);
			}

			// Draw fonts

			//Player indicator
			sf::Text currentPlayerText("Player Number: " + std::to_string(this->playerNumber), this->statusFont, 15);
            
			currentPlayerText.setPosition(60, 317);

			sf::Text rulesIcon("?", this->statusFont, 15);
			rulesIcon.setPosition(766, 317);
			sf::Text statusBar(statusText, this->statusFont, 15);
			statusBar.setPosition(430, 317);

			window.draw(currentPlayerText);
			window.draw(rulesIcon);
			window.draw(statusBar);

			switch (winner) {
				case 1: {
#ifndef __APPLE__
                    window.setTitle("Mancala Game - Player 1 Wins!");
#endif
					sf::Text winnerText("Player 1 wins!", this->statusFont, 40);
					winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((140 - winnerText.getGlobalBounds().height) / 2));
					window.draw(winnerText);
					window.display(); // Tell app that window is done drawing
					break;
				}
				case 2: {
#ifndef __APPLE__
                    window.setTitle("Mancala Game - Player 2 Wins!");
#endif
					sf::Text winnerText("Player 2 wins!", this->statusFont, 40);
					winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((430 - winnerText.getGlobalBounds().height) / 2));
					window.draw(winnerText);
					window.display(); // Tell app that window is done drawing
					break;
				}
				case 0: {
#ifndef __APPLE__
                    window.setTitle("Mancala Game - Tie!");
#endif
                    
                    
					sf::Text winnerText("It's a tie!!", this->statusFont, 40);
					winnerText.setPosition(((800 - winnerText.getGlobalBounds().width) / 2), ((320 - winnerText.getGlobalBounds().height) / 2));
					window.draw(winnerText);
					window.display(); // Tell app that window is done drawing
					break;
				}
			}
		}
		else {
#ifndef __APPLE__
            window.setTitle("Mancala Game");
#endif
            buttonSprite.setPosition(0, 300);
            this->redraw(REDRAW_PARAMS);
		}
	}
}
void runApplication::redraw(REDRAW_PARAMS_PROTO) {
    
    std::lock_guard<std::mutex> lockguard(mutex);
    
    // clear window
    window.clear(sf::Color(0, 0, 0, 255)); // Clear old frame
    // Draw sprite and pocket counts
    window.draw(boardSprite);
    window.draw(buttonSprite);
    for (auto kv : this->gameBoard) {
        auto marbles = kv.second->getMarble();
        for (auto marble : marbles) {
            window.draw(*marble);
        }
        
        sf::Text temporaryText(std::to_string(marbles.size()), runApplication::pocketFont, 60);
        temporaryText.setPosition(this->pocketFontLocations.at(kv.first).first, this->pocketFontLocations.at(kv.first).second);
        window.draw(temporaryText);
    }
    
    // Draw fonts
    
    //Player indicator
    sf::Text currentPlayerText("Player Number: " + std::to_string(this->playerNumber), this->statusFont, 15);
    currentPlayerText.setPosition(60, 317);
#ifndef __APPLE__
    std::string p1Score = std::to_string(gameBoard["P1"]->count()), p2Score = std::to_string(gameBoard["P2"]->count());

    std:: string newTitle = "Mancala Game - Player Number: " + std::to_string(this->playerNumber) + " (" + (this->playerNumber == 1 ? p1Score : p2Score) + " vs " + (this->playerNumber == 1 ? p2Score : p1Score) +  ")";
    
    window.setTitle(newTitle);
#endif
    
    sf::Text rulesIcon("?", this->statusFont, 15);
    rulesIcon.setPosition(766, 317);
    
    sf::Text statusBar(statusText, this->statusFont, 15);
    statusBar.setPosition(430, 317);
    
    window.draw(currentPlayerText);
    window.draw(rulesIcon);
    window.draw(statusBar);
    
    window.display(); // Tell app that window is done drawing
    
}

void runApplication::displayRules(sf::RectangleShape & rect, sf::Text & text)
{
    sf::RectangleShape view(sf::Vector2f(800,350));
    view.setFillColor(sf::Color::Black);
    
    
    sf::Text _text(wrapText("Welcome to the ancient strategy game of Mancala!\n\nThe rules of this game are simple: players will take turns selecting pockets from their side of the board, and after a choice is made, the marbles from that pocket are dropped in pockets rotating counterclockwise around the board. Players score points by dropping marbles in their scoring pocket (the larger pocket to the right of the players board pockets) as they move around the board. Players only drop marbles in their own scoring pocket, and skip their opponents scoring pocket if they make it around the entire board.\n\nThere are just a few other rules to keep in mind: if you pick a pocket that has the perfect number of marbles to land in your scoring pocket, you get to go again! Also, if you select a pocket in which your last marble lands in an empty pocket on your side of the board, and the opposing pocket on your opponent's side has one or more marbles in it, then you get to \"capture\" your opponent's marbles (and your single marble) and add them to your scoring pocket!\n\nThe game ends once one player clears all the marbles on their side of the board. All remaining marbles on the opponent's side of the board are then added to the opponent's scoring pocket. The player with the most marbles in their scoring pocket at the end of the game wins!\n\n[Press return to continue...]", 800, this->statusFont, 12), this->statusFont, 12);
    
    _text.setPosition(0, 0);
    _text.setFillColor(sf::Color::White);
    
    rect = view;
    text = _text;
}

inline void runApplication::whoGoesFirst() // Function return a random integer (1 or 2) to determine which player goes first
{
#if defined(WINDOWS)
	playerNumber = rand() % 2 + 1;
#else
    playerNumber = arc4random() % 2 + 1;
#endif
}

void runApplication::switchTurns() // Function rotates between players after each turn
{
    std::lock_guard<std::mutex> lockguard(mutex);
	if (playerNumber == 1)
	{
		playerNumber = 2;
	}
	else if (playerNumber == 2)
	{
		playerNumber = 1;
	}

}

void runApplication::animateBeads(runApplication::AnimationData * dataPointer) {
    runApplication::AnimationData data = *dataPointer;
    // make sure both are even or odd
    if (fmod(data.endX, 2) != fmod(data.startX,2)) { data.endX += 1; }
    
    // make sure both are even or odd
    if (fmod(data.endY, 2) != fmod(data.startY,2)) { data.endY += 1; }
    
    float curX = data.startX, curY = data.startY;
    
    while ((data.endX != curX) || (data.endY != curY)) {
        
        float moveY = data.endY != curY ? 1 : 0;
        if (data.negativeY) { moveY *= -1; }
        float moveX = data.endX != curX ? 1 : 0;
        
        if (std::abs(curX - data.endX) > 500) {
            moveX = 4;
        } else if (std::abs(curX - data.endX) > 200) {
            moveX = 2;
        }
        
        if (data.fast) {
            moveX *= 2;
            moveY *= 2;
        }
        
        if (data.negativeX) { moveX *= -1; }
        
        data.target->move(moveX, moveY);
        curX = data.target->getPosition().x;
        curY = data.target->getPosition().y;
        
        data.runner->redraw(*data.window, data.statusText, *data.boardSprite, *data.buttonSprite);
    }
}

inline void runApplication::loopForAnimation(const std::string &oldPocket, sf::Sprite *&target, const std::string &targetKey, REDRAW_PARAMS_PROTO, bool fast, bool isEndOfGame) {
    if (target == NULL) { return; }
    std::thread animateThread, musicThread;
    runApplication::AnimationData* data;
    
    auto & targetHole = gameBoard[targetKey];
    
    auto startPos = target->getPosition();
    float x = determineValidLocation(pocketPositions[targetKey].at(0), pocketPositions[targetKey].at(1));
    float y = determineValidLocation(pocketPositions[targetKey].at(2), pocketPositions[targetKey].at(3));
    
    bool negY = y - startPos.y < 0;
    bool negX = x - startPos.x < 0;
    
    data = new runApplication::AnimationData(this, target, startPos.x, x, startPos.y, y, negY, negX, REDRAW_PARAMS, fast);
    
    animateThread = std::thread(&runApplication::animateBeads, data);
    
    animateThread.join();
    
    if (isEndOfGame) {
        musicThread = std::thread(&MusicPlayer::collectSide);
    } else {
        try {
            musicThread = std::thread(&MusicPlayer::placeMarble, targetHole->count() + 1);
        } catch (Error &e) {
            std::cout << e;
        }
    }
    
    gameBoard[oldPocket]->getMarble().pop_front();
    targetHole->addMarble(target);
    
    musicThread.join();
    
    delete data;
    
}

std::pair<bool,bool> runApplication::disperseBeads(const std::string & pocketName, REDRAW_PARAMS_PROTO) // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again
{
	std::string temp = pocketName;
	bool capture = false;
    
    auto marbles = gameBoard[pocketName]->getMarble();
	for (auto target : marbles) {
        
		pockets::nextPosition(temp, playerNumber);
        loopForAnimation(pocketName, target, temp, REDRAW_PARAMS);
	}
        
	if (determineCapture(temp)) {
        
		capture = true;
		std::string opposite = pockets::getOppositeFromKey(temp);
        
        auto oppMarbles = gameBoard[opposite]->getMarble();
        auto tmpMarbles = gameBoard[temp]->getMarble();
        
		for (auto marble : oppMarbles) {
            loopForAnimation(opposite, marble, playerNumber == 1 ? "P1" : "P2", REDRAW_PARAMS, true);
		}
        
		for (auto marble : tmpMarbles) {
            loopForAnimation(temp, marble, playerNumber == 1 ? "P1" : "P2", REDRAW_PARAMS, true);
		}
	}
    
//    if (thread.joinable()) {
//        thread.join();
//    }

	return std::make_pair(temp == (playerNumber == 1 ? "P1" : (playerNumber == 2 ? "P2" : "")), capture); // if playerNumber == 1, then P1, else check if playerNumber == 2, then P2 else return false
}

bool runApplication::determineCapture(const std::string &pocketName) // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
{
	if (pockets::ownsPocket(pocketName, this->playerNumber)) {
		if (gameBoard[pocketName]->getMarble().size() == 1) {
			if (gameBoard[pockets::getOppositeFromKey(pocketName)]->getMarble().size() > 0) {
				return true;
			}
		}
	}
	return false;
}

int runApplication::endOfGame(const std::string & emptyThisSide, REDRAW_PARAMS_PROTO) // returns true if the game is over (i.e.one player doesnt have any beads on their side of the board.
{
	int marbleCountSideA = 0,
		marbleCountSideB = 0;
    
	if (emptyThisSide == "A") {
		// empty side A
		for (auto kv : gameBoard) {
			if (kv.first.at(0) == 'A') {
                auto marbles = kv.second->getMarble();
				for (auto marble : marbles) {
                    
                    this->loopForAnimation(kv.first, marble, "P2", REDRAW_PARAMS, true, true);
                    
//					float x = determineValidLocation(pocketPositions["P2"].at(0), pocketPositions["P2"].at(1));
//					float y = determineValidLocation(pocketPositions["P2"].at(2), pocketPositions["P2"].at(3));
//					float deltaX = x - marble->getPosition().x;
//					float deltaY = y - marble->getPosition().y;
//					marble->move(sf::Vector2f(deltaX, deltaY));
//					gameBoard["P2"]->addMarble(marble);
				}
			}
		}
        
        marbleCountSideA = (int)gameBoard["P1"]->count();
        marbleCountSideB = (int)gameBoard["P2"]->count();
		}
	else {
		// empty side B
		for (auto kv : gameBoard) {
			if (kv.first.at(0) == 'B') {
                auto marbles = kv.second->getMarble();
				for (auto marble : marbles) {
                    
                    this->loopForAnimation(kv.first, marble, "P1", REDRAW_PARAMS, true, true);
                    
//					float x = determineValidLocation(pocketPositions["P1"].at(0), pocketPositions["P1"].at(1));
//					float y = determineValidLocation(pocketPositions["P1"].at(2), pocketPositions["P1"].at(3));
//					float deltaX = x - marble->getPosition().x;
//					float deltaY = y - marble->getPosition().y;
//					marble->move(sf::Vector2f(deltaX, deltaY));
//					gameBoard["P1"]->addMarble(marble);
				}
			}
		}

        marbleCountSideA = (int)gameBoard["P1"]->count();
        marbleCountSideB = (int)gameBoard["P2"]->count();
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
	
	//Who won?
	return winner;
}

inline float runApplication::determineValidLocation(float min, float max) {
#if defined(WINDOWS)
	return rand() % (int)(max - min) + min;
#else
    return (float)fmod(arc4random(), (max - min)) + min;
#endif
}
