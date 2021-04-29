// extend rectangle shape
class PocketShape final : public sf::RectangleShape {
	public:
		inline PocketShape();
		inline std::string getID(void) const;
		inline void setID(const std::string& newID);
		std::list<sf::Sprite*> marbles; 
	private:
		std::string _id;
};

inline PocketShape::PocketShape() : RectangleShape() {

	//for (int index = 0; index < 4; ++index) {
	//	// Load  Textures
	//	sf::Texture marbleTexture0;
	//	marbleTexture0.loadFromFile("Images\\gameAssets\\marble0.png");

	//	sf::Texture marbleTexture1;
	//	marbleTexture1.loadFromFile("Images\\gameAssets\\marble1.png");
	//	// play sound when placing a marble on the screen
	//	//sf::Thread thread(&MusicPlayer::placeMarble, 1);
	//	//thread.launch();
	//	sf::Sprite* marble = new sf::Sprite;
	//	if (index % 2) {
	//		marble->setTexture(marbleTexture1);
	//	}
	//	else {
	//		marble->setTexture(marbleTexture0);
	//	}
	//	int maxWidth = this->getGlobalBounds().width - 30,
	//		x = rand() % maxWidth;
	//	int maxHeight = this->getGlobalBounds().height - 30,
	//		y = rand() % maxHeight;
	//	marble->setPosition(sf::Vector2f(x, y));
	//	marbles.push_back(marble);
	//}
	
}

inline std::string PocketShape::getID(void) const {
	return this->_id;
}

inline void PocketShape::setID(const std::string& newID) {
	this->_id = newID;
}
