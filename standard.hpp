//
//  standard.hpp
//  PA4
//
//  Created by Kyle Parker on 3/7/21.
//

#ifndef standard_hpp
#define standard_hpp

// OS-Based libs
// following macros definitons were found at https://sourceforge.net/p/predef/wiki/OperatingSystems/
/* BEGIN MACROS */

#if defined(_WIN32) || defined(_WIN64)
    // import Windows-specific libraries as needed
    #define WINDOWS
    #define _CRT_SECURE_NO_WARNINGS // disable secure warnings

    #define CLEAR_SCREEN "cls"
    #define RETURN_KEY_UPPER "ENTER"
    #define RETURN_KEY_LOWER "enter"
    /* END WINDOWS */
#elif defined(__APPLE__) || defined(__MACH__)
    // import macOS-specific libraries as needed.
    #include <unistd.h> // sleep

    #define CLEAR_SCREEN "clear"
    #define RETURN_KEY_UPPER "RETURN"
    #define RETURN_KEY_LOWER "return"
    /* END MACOS */
#elif defined(__linux__) || defined(linux) || defined(__linux)
    // import Linux-specific libraries as needed.

    #include <unistd.h> // sleep

    #define CLEAR_SCREEN "clear"
    #define RETURN_KEY_UPPER "RETURN"
    #define RETURN_KEY_LOWER "return"
    /* END LINUX */
#else
    #define UNSUPPORTED_OS OTHER_OS // was not caught by one of the above cases.
#endif

/* END MACROS */

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
#include <chrono>
#include <thread>


//// declare using statements
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;
using std::unordered_map;

// define standard types
typedef unsigned int UInt;
typedef std::pair<std::string, std::string> stringPair;

std::ostream & operator <<(std::ostream & lhs, std::map<std::string, std::string> & rhs);

namespace kp {
// define protocol stubs
inline void checkOS(void);
inline void fatalError(std::string);

inline std::string strToLower(const std::string &str);
inline std::string strToUpper(const std::string &str);

inline bool isnumber(const std::string &str);
inline bool getYesNo(void);

inline void clearScreen(void);
inline void waitForReturn(bool shouldClear = false);

inline bool isYes(std::string str);
template <typename T> inline bool isYes(T value);


/// Simply print a warning if a macro is defined and warn user the OS is not supported
///
/// - Precondition: Program loaded into memory
/// - Postcondition: Warning was issued if requred
/// - seealso: functions.hpp
/// - version: 1.0
inline void checkOS() {
#if defined(UNSUPPORTED_OS)
    std::cout << "[WARN] Unsupported Operating System! (" << UNSUPPORTED_OS << ")" << std::endl;
#endif
}

/// throw a non-recoverable error for debugging. Should never be called when deploying software.
///
/// - Precondition: aruguments are all strings. all other values are not accepted.
/// - Postcondition: program stopped.
/// - Warning: Program will exit
/// - Parameter count: the number of arguments
/// - Parameter ... : the variable list to run through.
/// - seealso: [Microsoft Docs, "Functions with Variable Argument Lists (C++)"] (https://docs.microsoft.com/en-us/cpp/cpp/functions-with-variable-argument-lists-cpp?view=msvc-160)
/// - version: 1.1
inline void fatalError(std::string reason) {
    std::cout << "Fatal Error: " << reason << std::endl;
    abort();
}

/// Convert a string to all lowercase, rather than a single character.
///
/// - Postcondition: string is lowercased
/// - Warning: not localized, undefined behavior may occur with non-ascii characters
/// - Parameter str: the string ot lowercase
/// - version: 1.0
inline std::string strToLower(const std::string &str) {
    std::string newStr = "";
    
    for (char ch : str) {
        newStr += (char)tolower(ch);
    }
    
    return newStr;
}

/// Convert a string to all uppercsae, rather than a single character.
///
/// - Postcondition: string is uppercased
/// - Warning: not localized, undefined behavior may occur with non-ascii characters
/// - Parameter str: the string to uppercase
/// - version: 1.0
inline std::string strToUpper(const std::string &str) {
    std::string newStr = "";
    
    for (char ch : str) {
        newStr += (char)toupper(ch);
    }
    
    return newStr;
}

/// check a string to determine if whole string consists of numbers. should always be called before stoi.
///
/// - Precondition: str is non null.
/// - Postcondition: bool indicating if whole string are numbers.
/// - Parameter str:  the string to check for numbers
/// - Returns: bool indicating if the string is a number.
/// - Version: 1.0
inline bool isnumber(const std::string &str) {
    for (auto ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

/// get a yes/no response from user
///
/// - Precondition: user prompted for a yes/no question.
/// - Postcondition: bool is returned, true for yes, false for no
/// - Returns: boolean indicating success
/// - version: 1.0
inline bool getYesNo(void) {
    std::string str;
    std::cout << "(y)es/(n)o\n>";
    std::cin >> str;
    return isYes(str);
}

// define inline methods:

/// clears the screen using a macro defined per OS for cross platform compatability.
///
/// - Precondition: Screen needs to be cleared
/// - Postcondition: Screen is cleared
/// - Warning: Any information printed prior to this call may not be accessable.
/// - version: 1.0
inline void clearScreen(void) {
    system(CLEAR_SCREEN);
}

/// isYes, with string param
///
/// - Precondition: input should be indicating a true or false value
/// - Postcondition: if the input is acceptable, then it will return 1 for yes/true
/// - Warning: if the user does not respond correctly to the prompt, it may be treated as false.
/// - Parameter str:  string that holds the true/false data
/// - Returns: bool indicating yes/no
/// - version: 1.1
inline bool isYes(std::string str) {
    str = strToLower(str);
    return str == "yes" || str == "y" || str == "true" || str == "t" || str == "1";
}

/// isYes, with any param
///
/// - Precondition: input should be indicating a true or false value of any number
/// - Postcondition: if the input is acceptable, then it will return 1 for yes/true
/// - Warning: if the user does not respond with a string (caught with other overloaded method) or a number, the program could crash.
/// - Parameter value: any type, should be 1 or 0 of some type
/// - Returns: bool indicating 1/0
/// - version: 1.0
template <typename T>
inline bool isYes(T value) { return value == 1; }

/// wait for return, wait on user
///
/// - Precondition: prompt or end of activity
/// - Postcondition: user pressed return/return
/// - Parameter shouldClear: boolean indicating if getLine should be called before prompt, so it does not return without waiting. By default, false.
/// - version: 1.1
inline void waitForReturn(bool shouldClear) {
    std::string wait;
    if (shouldClear) { std::getline(std::cin, wait); }
    std::cout << std::endl << "[PRESS " << RETURN_KEY_UPPER << " TO CONTINUE]" << std::endl;
    std::getline(std::cin, wait);
}
}

/// Output a map of type string, string using insertion operator (Overloaded Func)
///
/// When the map is empty, {} will represent the data.
///
/// - Postcondition: map is printed onto screen.
/// - Parameter lhs:  the stream to insert into
/// - Parameter rhs:  the data to insert
/// - Returns: the stream, including data from the map.
/// - Version: 1.0
inline std::ostream & operator <<(std::ostream & lhs, std::map<std::string, std::string> & rhs) {
    std::ostream & rtnVal = lhs;
    rtnVal << "{";
    
    bool needsComma = false;
    for (auto data : rhs) {
        if (needsComma) {
            rtnVal << ", ";
        }
        rtnVal << "{ " << data.first << " : " << data.second << "}";
        needsComma = true;
    }
    
    rtnVal << "}";
    return rtnVal;
}
#endif /* standard_hpp */
