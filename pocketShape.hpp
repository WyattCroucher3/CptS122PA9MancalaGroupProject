// extend rectangle shape
class PocketShape final : public sf::RectangleShape {
	public:
		inline std::string getID(void) const;
		inline void setID(const std::string& newID);
		std::list<sf::Sprite*> marbles; 
		inline sf::Sprite& addMarble(sf::Texture& newTexture, const sf::Vector2f& newVector);
		inline void addMarble(sf::Sprite*& sprite);
	private:
		std::string _id;
};

inline std::string PocketShape::getID(void) const {
	return this->_id;
}

inline void PocketShape::setID(const std::string& newID) {
	this->_id = newID;
}

inline sf::Sprite& PocketShape::addMarble(sf::Texture& newTexture, const sf::Vector2f& newVector) {
	sf::Sprite* newSprite = new sf::Sprite(newTexture);
	newSprite->setPosition(newVector);
	this->marbles.push_back(newSprite);
	return *newSprite;
}

inline void PocketShape::addMarble(sf::Sprite*& sprite) {
	this->marbles.push_back(sprite);
}
