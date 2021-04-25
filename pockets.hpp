//
//  pockets.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/24/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef pockets_hpp
#define pockets_hpp

namespace pockets {

class Pocket {
protected:
    string ID;
    unsigned int _count;
    sf::Image image;
    
    Pocket(string & setID, const unsigned int & setCount) {
        this->ID = setID;
        this->_count = setCount;
    }
public:
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
    virtual void updateCount(const int & newCount) = 0;
    
    unsigned int count() const {
        return this->_count;
    }
};

class MancalaPocket final : public Pocket {
    unsigned int owner;
public:
    MancalaPocket(string & setID,
                  unsigned int & player,
                  const unsigned int & setCount = 4) : Pocket(setID, setCount) {
        this->owner = player;
        this->updateCount((int)setCount);
    }
    
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
    void updateCount(const int & newCount) override {
        sf::Thread thread(&MusicPlayer::placeMarble, newCount < 7 ? newCount : 7);
        thread.launch(); // will run asynchronously
        
        this->_count = (unsigned int)newCount;
        // update label here
        // this method is virtial because this needs a larger pocket than its sister class `BoardPocket`
    }
    
    /// get wether or not the pocket is owned by this player by passing in a key.
    ///
    /// - Postcondition: boolean indicating owernship is returned
    /// - Parameter key:  the key to test against.
    /// - Returns:  a boolean that determines if the hole passed via key is owned by this player
    /// - Version: 1.0
    inline bool ownsPocket(unsigned int & key) const { return owner == 1 ? key < 10 : key > 10; }
};

typedef map<string, Pocket*> pocketMap;

class BoardPocket final : public Pocket {
public:
    BoardPocket(string & setID, const unsigned int & setCount = 4) : Pocket (setID, setCount) {
        this->updateCount((int)setCount);
    }
    
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
    void updateCount(const int & newCount) override {
        sf::Thread thread(&MusicPlayer::placeMarble, newCount < 7 ? newCount : 7);
        thread.launch(); // will run asynchronously
        
        this->_count = (unsigned int)newCount;
        // update label here
        // this method is virtial because this needs a smaller pocket than its sister class `MancalaPocket`
    }
};

/// Sets up the pockets, adding 6 BoardPockets on each side with 2 MancalaPockets on player sides.
/// Note: bottom row should be 0x, top row should be 1x, player one should be 21 and player 2 should be 22.
///
/// - Precondition: map is empty
/// - Postcondition: map is setup
/// - Parameter target:  the empty map to set values to
/// - Version: 1.0
void setupMap(map<string, Pocket*> & target) {
    for (unsigned int first = 0; first < 30; first += 10) {
        if (first == 20) { // MancalaPockets.
            for (unsigned int second = 1; second <= 2; second += 1) {
                string key = "P";
                key += std::to_string(second);
                
                MancalaPocket * p = new MancalaPocket(key, second);
                Pocket * pocket = dynamic_cast<Pocket*>(p);
                
                target.insert(std::make_pair(key, pocket));
            }
        } else { // BoardPockets.
            for (int second = 1; second <= 6; second += 1) {
                string key = first == 10 ? "B" : "A";
                
                key += std::to_string(second);
                
                BoardPocket * p = new BoardPocket(key);
                Pocket * pocket = dynamic_cast<Pocket*>(p);
                
                target.insert(std::make_pair(key, pocket));
            }
        }
    }
}

/// get a key corrsponding to the opposite corner
///
/// - Precondition: user placed marble in empty pocket on their side
/// - Postcondition: key is returned
/// - Parameter key:  the key to reverse
/// - Returns: the new key
/// - Version: 1.0
inline unsigned int getOppositeFromKey(unsigned int & key) {
    return (key < 10 ? 11 : 1) + 6 - (key % 10);
}

}

#endif /* pockets_hpp */
