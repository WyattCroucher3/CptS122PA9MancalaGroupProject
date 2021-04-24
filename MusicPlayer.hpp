//
//  MusicPlayer.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/23/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef MusicPlayer_hpp
#define MusicPlayer_hpp

namespace MusicPlayer {
    
/// Play music at the path for a certian rep.
/// Cannot be called using pf::Thread
///
/// - Precondition: setup is dropping marbles
/// - Postcondition: audio played
/// - Parameter: data - a vector that contains exactly two values;
/// - Warning: Will throw error on failure.
/// - Version: 1.0
void playMusic(const std::string & path, const int & count = 1) {
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
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer. 
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
void * playMusicWithV(const std::vector<std::string> & data) {
    if (data.size() == 2) {
        playMusic(data.at(0), stoi(data.at(1)));
    } else {
        throw Error({{"reason","Unexpectedly found more or less than 2 elements!"}, {"code","0x00000000"}, {"count", std::to_string(data.size())}});
    }
    return NULL;
}
/// Play music at the path for one rep.
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer.
///
/// Async: `sf::Thread (MusicPlayer::playMusicAtPath, <#PATH#>)`
///
/// - Precondition: setup is dropping marbles
/// - Postcondition: audio played
/// - Parameter: path - the path to the file.
/// - Warning: Will throw error on failure.
/// - Version: 1.0
void * playMusicAtPath(const std::string & path) {
    playMusic(path);
    return NULL;
}

/// plays the collect side sound once.
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer.
///
/// - Precondition: game about to end and side needs to be collected.
/// - Postcondition: sound played.
/// - Version: 1.0
void * collectSide(void) {
    playMusic("Audio/Collect Side.wav");
    return NULL;
}

/// sound when a certian amount of marbles will be present. Ex. 0 marbles are in hole, one was just placed.
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer.
///
/// - Precondition: marble was dropped.
/// - Postcondition: sound played.
/// - Parameter count:  the number of marbles that are now in the hole, including the recently added one.
/// - Version: 1.0
void * placeMarble(const short & count) {
    if (count >= 1 && count <= 7) {
        std::string path = "Audio/Place ";
        path += std::to_string(count);
        path += " Marble.wav";
        
        playMusic(path);
    } else {
        throw Error("Out of range.");
    }
    
    return NULL;
}

/// play the reset sound.
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer.
///
/// - Precondition: User clicked reset
/// - Postcondition: Sound Played
/// - Version: 1.0
void * resetSound(void) {
    playMusic("Audio/Reset.wav");
    return NULL;
}

/// Play the sound when setting up the game, sound be called 6 times.
/// NOTE: This can be called on a thread without pointer notation as the function is already a pointer.
///
/// - Precondition: game resetting
/// - Postcondition: sound played.
/// - Version: 1.0
void * setupSound(void) {
    playMusic("Audio/Setup Marble.wav");
    return NULL;
}

}

#endif /* MusicPlayer_hpp */
