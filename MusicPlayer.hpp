//
//  MusicPlayer.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/23/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef MusicPlayer_hpp
#define MusicPlayer_hpp

/// Contains functions that handle sounds throughout game.
namespace MusicPlayer {

static std::mutex musicMutex;
/// Play music at the path for a certian rep.
/// Cannot be called using pf::Thread
///
/// - Precondition: setup is dropping marbles
/// - Postcondition: audio played
/// - Parameter: data - a vector that contains exactly two values;
/// - Warning: Will throw error on failure.
/// - Version: 1.0
inline void playMusic(const std::string & path, const int & count = 1) {
    std::lock_guard<std::mutex> lockguard(MusicPlayer::musicMutex);
    
    sf::Music music;
    
    int x = 0;
    while (count < 0 || x < count) {
        if (!music.openFromFile(path)) {
            throw Error("Could not locate file");
        }
        music.play();
        while (music.getStatus() == sf::SoundSource::Status::Playing) {}
        if (count >= 0) { x += 1; }
    }
}

/// Play music at the path for a certian repition.
///
/// Async:
/// ```
/// sf::Thread (MusicPlayer::playMusicWithV, <#VECTOR#>)
/// ```
///
/// - Precondition: setup is dropping marbles
/// - Postcondition: audio played
/// - Parameter: data - a vector that contains exactly two values;
/// - Warning: Will throw error on failure.
/// - Version: 1.0
inline void playMusicWithV(const std::vector<std::string> & data) {
    if (data.size() == 2) {
        playMusic(data.at(0), stoi(data.at(1)));
    } else {
        throw Error({{"reason","Unexpectedly found more or less than 2 elements!"}, {"code","0x00000000"}, {"count", std::to_string(data.size())}});
    }
}
/// Play music at the path for one rep.
///
/// Async: `sf::Thread (MusicPlayer::playMusicAtPath, <#PATH#>)`
///
/// - Precondition: setup is dropping marbles
/// - Postcondition: audio played
/// - Parameter: path - the path to the file.
/// - Warning: Will throw error on failure.
/// - Version: 1.0
inline void playMusicAtPath(const std::string & path) {
    try {
        playMusic(path);
    } catch (Error &e) {
        std::cout << e;
    }
}

/// plays the collect side sound once.
///
/// - Precondition: game about to end and side needs to be collected.
/// - Postcondition: sound played.
/// - Version: 1.0
inline void collectSide(void) {
    try {
        playMusic("Audio/Collect Side.wav");
    } catch (Error &e) {
        std::cout << e;
    }
}

/// sound when a certian amount of marbles will be present.
///
/// NOTE: Pass the new value in. passing in the current value may result in incorrect sound playing.
///
/// - Precondition: marble was dropped.
/// - Postcondition: sound played.
/// - Parameter count:  the number of marbles that are now in the hole, including the recently added one.
/// - Version: 1.0
inline void placeMarble(const unsigned long & count) {
    if (count < 0) { throw Error("Out of range. Value cannot be negative."); }
    
    std::string path = "Audio/Place ";
    switch (count) {
    case 0:
        path += "Marbles.wav";
        break;
    case 1: case 2: case 3: case 4: case 5: case 6:
        path += std::to_string(count);
        path += " Marble.wav";
        break;
    default: // >= 7
        path += "7 Marble.wav";
        break;
    }
    
    try {
        playMusic(path);
    } catch (Error &e) {
        std::cout << e;
    }
    
}

/// play the reset sound.
///
/// - Precondition: User clicked reset
/// - Postcondition: Sound Played
/// - Version: 1.0
inline void resetSound(void) {
    try {
        playMusic("Audio/Reset.wav");
    } catch (Error &e) {
        std::cout << e;
    }
}

/// Play the sound when setting up the game
///
/// - Precondition: game resetting
/// - Postcondition: sound played.
/// - Version: 1.0
inline void setupSound(void) {
    try {
        playMusic("Audio/Setup Marble.wav");
    } catch (Error &e) {
        std::cout << e;
    }
}

}

#endif /* MusicPlayer_hpp */
