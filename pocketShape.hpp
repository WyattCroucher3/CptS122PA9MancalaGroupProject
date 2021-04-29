// extend rectangle shape
class PocketShape final : public sf::RectangleShape {
	public:
		std::string getID(void) const;
		void setID(const std::string& newID);
		std::list<sf::Sprite> marbles; 
	private:
		std::string _id;
};

std::string PocketShape::getID(void) const {
	return this->_id;
}

void PocketShape::setID(const std::string& newID) {
	this->_id = newID;
}
