//
//  run_application_unit_tests.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/30/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#include "RunApplication.hpp"

#ifndef run_application_unit_tests_hpp
#define run_application_unit_tests_hpp

class run_application_unit_tests final {
    void runTestOnInit(void) {
        auto startTime = time(0);
        
        long success = 0, fail = 0;
        
        std::cout << "Beginning test on runApplication's constructor at " << startTime << std::endl;
        
        runApplication app;
        
        if (app.gameBoard.size() == 14) {
            success += 1;
        } else {
            fail += 1;
        }
        
        
        if (runApplication::boardTexture.getSize().x > 0 && runApplication::boardTexture.getSize().y > 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        if (runApplication::buttonsTexture.getSize().x > 0 && runApplication::buttonsTexture.getSize().y > 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        if (runApplication::marbleTexture0.getSize().x > 0 && runApplication::marbleTexture0.getSize().y > 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        if (runApplication::marbleTexture1.getSize().x > 0 && runApplication::marbleTexture1.getSize().y > 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        if (!runApplication::pocketFont.getInfo().family.empty()) {
            success += 1;
        } else {
            fail += 1;
        }
        
        if (!runApplication::statusFont.getInfo().family.empty()) {
            success += 1;
        } else {
            fail += 1;
        }
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
    void runTestOnGameWinner(void) {
        auto startTime = time(0);
        
        long success = 0, fail = 0;
        
        std::cout << "Beginning test on runApplication::endOfGame(std::string) at " << startTime << std::endl;
        
        runApplication app;
        
        int winner = -1;
        
        winner = app.endOfGame("A");
        
        if (winner == 2) {
            success += 1;
        } else {
            fail += 1;
        }
        
        winner = -1; // reset winner
        
        winner = app.endOfGame("B");
        
        if (winner == 1) {
            success += 1;
        } else {
            fail += 1;
        }
        
        winner = -1; // reset winner
        
        winner = app.endOfGame("A");
        winner = app.endOfGame("B");
        
        if (winner == 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        winner = -1; // reset winner
        
        winner = app.endOfGame("B");
        winner = app.endOfGame("A");
        
        if (winner == 0) {
            success += 1;
        } else {
            fail += 1;
        }
        
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
    void runTestOnSwitchTurns(void) {
        auto startTime = time(0);
        
        long success = 0, fail = 0;
        
        std::cout << "Beginning test on runApplication::endOfGame(std::string) at " << startTime << std::endl;
        
        runApplication app;
        
        app.playerNumber = 1;
        
        app.switchTurns();
        
        if (app.playerNumber == 2) {
            success += 1;
        } else {
            fail += 1;
        }
        
        app.switchTurns();
        
        if (app.playerNumber == 1) {
            success += 1;
        } else {
            fail += 1;
        }
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
public:
    run_application_unit_tests(void) {
        time_t startTime = time(0);
        std::cout << "Beginning tests at " << startTime << "." << std::endl;
        std::cout << "Run `runTestOnInit`... (" << startTime << ")." << std::endl;
        this->runTestOnInit();
        std::cout << "Test `runTestOnInit` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Run `runTestOnGameWinner`... (" << startTime << ")." << std::endl;
        this->runTestOnGameWinner();
        std::cout << "Test `runTestOnGameWinner` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Run `runTestOnSwitchTurns`... (" << startTime << ")." << std::endl;
        this->runTestOnSwitchTurns();
        std::cout << "Test `runTestOnSwitchTurns` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
//        std::cout << "Run `runTestOnCreatePocketMap`... (" << startTime << ")." << std::endl;
//        this->runTestOnCreatePocketMap();
//        std::cout << "Test `runTestOnCreatePocketMap` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Tests finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
    }
};

#endif /* run_application_unit_tests_hpp */
