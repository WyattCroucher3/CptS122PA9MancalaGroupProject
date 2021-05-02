#pragma once

#include "Headers.hpp"

#define REDRAW_PARAMS_PROTO sf::RenderWindow & window, std::string & statusText, sf::Sprite & boardSprite, sf::Sprite & buttonSprite
#define REDRAW_PARAMS window, statusText, boardSprite, buttonSprite

class run_application_unit_tests;

class runApplication
{
    class AnimationData;
public:
	runApplication(void);
    
    ~runApplication(void);

	void runApp(void);
	void displayRules(sf::RectangleShape & rect, sf::Text & text);
	inline void whoGoesFirst(void); // Function return a random integer (1 or 2) to determine which player goes first
	void switchTurns(void);
    void redraw(REDRAW_PARAMS_PROTO);
    
    static void animateBeads(runApplication::AnimationData * data);

    inline void loopForAnimation(const std::string &oldPocket, sf::Sprite *&target, const std::string &targetKey, REDRAW_PARAMS_PROTO, bool fast = false, bool isEndGame = false);
    
    std::pair<bool,bool> disperseBeads(const std::string & pocketName, REDRAW_PARAMS_PROTO); // Beads from chosen pocket are dispersed counterclockwise; function returns 'true' if it lands in a mancala pocket so the player can go again
    
	bool determineCapture(const std::string& pocketName); // Checks to see if the bead landed on the players side, if the pocket was empty, and if there's any beads in the opposing pocket
    
    void runAnimationForEndOfGame(std::pair<const std::basic_string<char>, pockets::Pocket *> &kv);
    
    int endOfGame(const std::string & emptyThisSide, REDRAW_PARAMS_PROTO); // accepts a string with a side to empty when the game is over

	inline float determineValidLocation(float min, float max);
    
    friend run_application_unit_tests;

private:
    std::mutex mutex;
	unsigned int playerNumber;
	static sf::Texture boardTexture;
	static sf::Texture buttonsTexture;
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
    
    
    class AnimationData final {
    public:
        AnimationData(void) {}
        AnimationData(runApplication * nrunner, sf::Sprite * ntarget, const float & nstartX, float & nendX, const float & nstartY, float & nendY, const bool & nnegativeY, const bool & nnegativeX, REDRAW_PARAMS_PROTO, bool nfast = false) {
            this->runner = nrunner;
            this->target = ntarget;
            this->startX = nstartX;
            this->endX = nendX;
            this->startY = nstartY;
            this->endY = nendY;
            this->negativeY = nnegativeY;
            this->negativeX = nnegativeX;
            this->window = &window;
            this->statusText = statusText;
            this->boardSprite = &boardSprite;
            this->buttonSprite = &buttonSprite;
            this->fast = nfast;
        }
        ~AnimationData(void) {};
        runApplication * runner;
        sf::Sprite * target;
        sf::Sprite * boardSprite;
        sf::Sprite * buttonSprite;
        float startX, endX, startY, endY;
        bool negativeY, negativeX, fast;
        sf::RenderWindow * window;
        std::string statusText;
    };
};



