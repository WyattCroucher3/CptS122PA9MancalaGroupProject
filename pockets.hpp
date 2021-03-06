//
//  pockets.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/24/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#pragma once

#define ABORT_IF_KEY_NOT_2 if (key.size() > 2) { std::cout << "FATAL ERROR: KEY SIZE IS TOO SMALL!!!" << std::endl << "FUNC CALL: " << __FUNCTION__ << std::endl; std::abort(); }

namespace pockets {

class Pocket {
protected:
    PocketShape shapeSprite;
public:
    
    virtual ~Pocket(void) {}
    
    sf::Sprite& addMarble(sf::Texture& newTexture, const sf::Vector2f& newVector) {
        return shapeSprite.addMarble(newTexture, newVector);
    }
    void addMarble(sf::Sprite*& sprite) {
        return shapeSprite.addMarble(sprite);
    }
    std::list<sf::Sprite*> &getMarble(void) {
        return this->shapeSprite.marbles;
    }
    virtual unsigned long count() const = 0;
};

class MancalaPocket final : public Pocket {
    unsigned int owner;
public:
    MancalaPocket(unsigned int & player) {
        this->owner = player;
    }
    
    unsigned long count() const {
        return this->shapeSprite.marbles.size();
    }
};

class BoardPocket final : public Pocket {
public:
    BoardPocket(void){}
    
    unsigned long count() const {
        return this->shapeSprite.marbles.size();
    }
};

/// Sets up the pockets, adding 6 BoardPockets on each side with 2 MancalaPockets on player sides.
/// Note: bottom row should be 0x, top row should be 1x, player one should be 21 and player 2 should be 22.
///
/// - Precondition: map is empty
/// - Postcondition: map is setup
/// - Parameter target:  the empty map to set values to
/// - Version: 1.0
inline void setupMap(unordered_map<string, Pocket*> & target) noexcept {
    for (unsigned int first = 0; first < 30; first += 10) {
        if (first == 20) { // MancalaPockets.
            for (unsigned int second = 1; second <= 2; second += 1) {
                string key = "P";
                key += std::to_string(second);
                
                MancalaPocket * p = new MancalaPocket(/*key, */second);
                Pocket * pocket = dynamic_cast<Pocket*>(p);
                
                target.insert(std::make_pair(key, pocket));
            }
        } else { // BoardPockets.
            for (int second = 1; second <= 6; second += 1) {
                string key = first == 10 ? "B" : "A";
                
                key += std::to_string(second);
                
                BoardPocket * p = new BoardPocket(/*key*/);
                Pocket * pocket = dynamic_cast<Pocket*>(p);
                
                target.insert(std::make_pair(key, pocket));
            }
        }
    }
}

inline void nextPosition(string & key, const unsigned int & playerID) noexcept {
    ABORT_IF_KEY_NOT_2
    
    if (key[0] != 'P' && !(key == "A6" || key == "B1")) {
        if (key[0] == 'A') {
            key = {key[0], static_cast<char>(key[1]+1)};
        } else { // 'B'
            key = {key[0], static_cast<char>(key[1]-1)};
        }
    } else if (key[0] != 'P') {
        if (key[0] == 'B') {
            key = playerID == 1 ? "P1" : "A1";
        } else { // goto P2 or B6
            key = playerID == 2 ? "P2" : "B6";
        }
    } else {
        key = playerID == 1 ? "A1" : "B6";
    }
}

/// get a key corrsponding to the opposite corner
///
/// - Precondition: user placed marble in empty pocket on their side
/// - Postcondition: key is returned
/// - Parameter key:  the key to reverse
/// - Returns: the new key
/// - Version: 1.0
inline string getOppositeFromKey(const string & key) noexcept {
    ABORT_IF_KEY_NOT_2
    
    if (key == "P1" || key == "P2") { return key; }
    
    string key1 = {'B',key[1]}, key2 = {'A',key[1]};
    
    return key[0] == 'A' ? key1 : key2;
    
}

/// get wether or not the pocket is owned by this player by passing in a key.
///
/// - Postcondition: boolean indicating owernship is returned
/// - Parameter key:  the key to test against.
/// - Returns:  a boolean that determines if the hole passed via key is owned by this player
/// - Version: 1.0
inline bool ownsPocket(const string & key, unsigned int & owner) {
    ABORT_IF_KEY_NOT_2
    return (owner == 1 && key[0]== 'B') || (owner == 2 && key[0] == 'A');
}

// define types for pockets
typedef unordered_map<string, Pocket*> pocketMap;

}
