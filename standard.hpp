//
//  standard.hpp
//  PA4
//
//  Created by Kyle Parker on 3/7/21.
//

#ifndef standard_hpp
#define standard_hpp

#if defined(_WIN32) || defined(_WIN64)
// import Windows-specific libraries as needed
#define WINDOWS
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // disable secure warnings
#endif
#define CLEAR_SCREEN "cls"
#define RETURN_KEY_UPPER "ENTER"
#define RETURN_KEY_LOWER "enter"
#endif

// include SFML Libs
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// include system libs for ALL platforms. Platform-specific libraries should be imported above.
#include <iostream> // std::cout, std::cin, std::endl, std::pair, std::make_pair, std::function
#include <string> // std::string, std::aoti, std::stoi
#include <list> // std::list
#include <fstream> // std::fstream
#include <unordered_map> // std::unordered_map
#include <chrono> // std::chrono
#include <thread>
#include <mutex>


/// declare using statements
using std::string;
using std::unordered_map;

// define standard types
typedef unsigned int UInt;

#endif /* standard_hpp */
