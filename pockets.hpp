//
//  pockets.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/24/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#pragma once

#define ABORT_IF_KEY_NOT_2 if (key.size() > 2) { cout << "FATAL ERROR: KEY SIZE IS TOO SMALL!!!" << endl << "FUNC CALL: " << __FUNCTION__ << endl; std::abort(); }
#define END_A (key == "A6")

namespace pockets {

class Pocket {
protected:
    PocketShape shapeSprite;
    
    Pocket(string & setID) {
        shapeSprite.setID(setID);
    }
public:
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
//    virtual void updateCount(const int & newCount) = 0;
    
    void addMarble(void) {
        shapeSprite.addMarble();
    }
    
    virtual unsigned int count() const = 0;
};

class MancalaPocket final : public Pocket {
    unsigned int owner;
public:
    MancalaPocket(string & setID,
                  unsigned int & player) : Pocket(setID) {
        this->owner = player;
//        this->updateCount((int)setCount);
    }
    
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
//    void updateCount(const int & newCount) override {
//        sf::Thread thread(&MusicPlayer::placeMarble, newCount < 7 ? newCount : 7);
//        thread.launch(); // will run asynchronously
//
//        this->_count = (unsigned int)newCount;
//    }
    
    /// get wether or not the pocket is owned by this player by passing in a key.
    ///
    /// - Postcondition: boolean indicating owernship is returned
    /// - Parameter key:  the key to test against.
    /// - Returns:  a boolean that determines if the hole passed via key is owned by this player
    /// - Version: 1.0
    inline bool ownsPocket(const string & key) const {
        cout << "Use of " << __FUNCTION__ << " is deprecated!" << endl;
        ABORT_IF_KEY_NOT_2
        return (owner == 1 && key[1]== '1') || (owner == 2 && key[1] == '2');
    }
    
    unsigned int count() const {
        return (unsigned int)this->shapeSprite.marbles.size();
    }
};

typedef unordered_map<string, Pocket*> pocketMap;

class BoardPocket final : public Pocket {
public:
    BoardPocket(string & setID) : Pocket (setID) {
//        this->updateCount((int)setCount);
    }
    
    unsigned int count() const {
        return (unsigned int)this->shapeSprite.marbles.size();
    }
    
    /// Update the count and image reflecting the new value.
    ///
    /// - Precondition: marble was dropped or hole was picked up
    /// - Postcondition: the value is updated along with image. audio is played at this point.
    /// - Parameter newCount:  the new count to handle
    /// - Version: 1.0
//    void updateCount(const int & newCount) override {
//        sf::Thread thread(&MusicPlayer::placeMarble, newCount < 7 ? newCount : 7);
//        thread.launch(); // will run asynchronously
//
//        this->_count = (unsigned int)newCount;
//    }
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
    
    int keyi = atoi(&key[1]);
    
    if (key[0] == 'B') {
        keyi += 10;
    } else if (key[0] == 'A');/* VERIFY KEY IS VALID */
      else {
        return "";
    }
    
    keyi = (keyi < 10 ? 11 : 1) + 6 - (keyi % 10);
    
    string rtnKey = "";
    
    rtnKey += keyi < 10 ? 'A' : 'B';
    
    rtnKey += keyi % 10;
    
    return rtnKey;
}

}

