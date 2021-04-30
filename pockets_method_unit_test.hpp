//
//  pockets_methods_unit_test.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/27/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef pockets_methods_unit_test_hpp
#define pockets_methods_unit_test_hpp

class pockets_methods_unit_test final {
    const std::list<string> keys = {"A1", "A2", "A3", "A4", "A5", "A6", "P2", "B6", "B5", "B4", "B3", "B2", "B1", "P1"};
    
    // tests pockets::nextPosition method againist know pattern, keys.
    void runTestOnNextPosition(void) {
        
        string key = "A1";
        
        auto startTime = time(0);
        
        std::cout << "Beginning test on pockets::nextPosition(std::string,UInt) at " << startTime << std::endl;
        
        long x = 1, success = 0, fail = 0;
        
        for (; x <= 10000; x += 1) {
            
            for (int i = 0; i < 10000; i += 1) {
                if (key == "P2") { pockets::nextPosition(key, 1); } // we can skip because P2 should never be a value for player 1.
                
                string oldK = key;
                unsigned long pos = 0, newPos = 0;
                for (auto data : keys) { pos += 1; if (data == key) { break; } }
                pockets::nextPosition(key, 1);
                for (auto data : keys) { newPos += 1; if (data == key) { break; } }
                if (std::abs((int)newPos-(int)pos) != 1) {
                    if (!(newPos == 1 && pos == keys.size()) && (!(newPos == 8 && pos == 6))) {
                        fail += 1;
                    } else {
                        success += 1;
                    }
                }
            }
            
            if (key == "P1") { pockets::nextPosition(key, 2); } // we can skip because P1 should never be a value for player 2.
            
            for (int i = 0; i < 10000; i += 1) {
                string oldK = key;
                unsigned long pos = 0, newPos = 0;
                for (auto data : keys) { pos += 1; if (data == key) { break; } }
                pockets::nextPosition(key, 2);
                for (auto data : keys) { newPos += 1; if (data == key) { break; } }
                if (std::abs((int)newPos-(int)pos) != 1 && (!(newPos == 1 && pos == keys.size() - 1))) {
                    fail += 1;
                } else {
                    success += 1;
                }
            }
        }
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
    // test ownership of pockets.
    void runTetstOnOwnership(void) {
        
        auto startTime = time(0);
        
        std::cout << "Beginning test on pockets::nextPosition(std::string,UInt) at " << startTime << std::endl;
        
        long success = 0, fail = 0;
        
        for (unsigned int owner = 1; owner <= 2; owner += 1) {
            for (auto key : keys) {
                if (key.at(0) == 'B' && owner == 1 && pockets::ownsPocket(key, owner)) { // test owner 1 and B
                    success += 1;
                } else {
                    fail += 1;
                }
                
                if (key.at(0) == 'A' && owner == 1 && !pockets::ownsPocket(key, owner)) { // test owner 1 and A
                    success += 1;
                } else {
                    fail += 1;
                }
                
                if (key.at(0) == 'A' && owner == 2 && pockets::ownsPocket(key, owner)) { // test owner 2 and A
                    success += 1;
                } else {
                    fail += 1;
                }
                
                if (key.at(0) == 'B' && owner == 2 && !pockets::ownsPocket(key, owner)) { // test owner 2 and B
                    success += 1;
                } else {
                    fail += 1;
                }
            }
        }
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
    void runTestOnOppositeKey(void) {
        auto startTime = time(0);
        
        std::cout << "Beginning test on pockets::getOppositeFromKey(std::string) at " << startTime << std::endl;
        
        long success = 0, fail = 0;
        
        for (auto key : keys) {
            if (key == "P1" || key == "P2") {
                if (key == pockets::getOppositeFromKey(key)) {
                    success += 1;
                } else {
                    fail += 1;
                }
                continue; // unique case so skip code below
            }
            
            if (key.at(0) == 'A' && pockets::getOppositeFromKey(key) == 'B' && key.at(1) == pockets::getOppositeFromKey(key).at(1)) {
                success += 1;
            } else {
                fail += 1;
            }
            
            if (key.at(0) == 'B' && pockets::getOppositeFromKey(key) == 'A' && key.at(1) == pockets::getOppositeFromKey(key).at(1)) {
                success += 1;
            } else {
                fail += 1;
            }
        }
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
    void runTestOnCreatePocketMap(void) {
        auto startTime = time(0);
        
        std::cout << "Beginning test on pockets::setupMap(unordered_map<string, Pocket*>) at " << startTime << std::endl;
        
        long success = 0, fail = 0;
        
        unordered_map<string, Pocket*> testMap;
        
        pockets::setupMap(testMap);
        
        if (testMap.size() == 14) {
            success += 1;
        } else {
            fail += 1;
        }
        
        for (auto kv : testMap) {
            if (testMap.second != nullptr) {
                success += 1;
            } else {
                fail += 1;
            }
            
            bool a2b = std::is_convertible<A*, B*>::value;
            
            if ((kv.first == "P1" || kv.first == "P2") && (std::is_convertible<kv.second, pockets::MancalaPocket*>::value)) {
                success += 1;
            } else {
                fail += 1;
            }
            
            if (!(kv.first == "P1" || kv.first == "P2") && (std::is_convertible<kv.second, pockets::BoardPocket*>::value)) {
                success += 1;
            } else {
                fail += 1;
            }
        }
        
        std::cout << success << " succeeded, " << fail << " failed." << std::endl;
        std::cout << "Operation completed after " << (time(0) - startTime) << " seconds." << std::endl;
    }
    
public:
    pockets_unit_test(void) {
        time_t startTime = time(0);
        std::cout << "Beginning tests at " << startTime << "." << std::endl;
        std::cout << "Run `runTestOnNextPosition`... (" << startTime << ")." << std::endl;
        this->runTestOnNextPosition();
        out << "Test `runTestOnNextPosition` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Run `runTestOnOwnership`... (" << startTime << ")." << std::endl;
        this->runTestOnOwnership();
        out << "Test `runTestOnOwnership` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Run `runTestOnOppositeKey`... (" << startTime << ")." << std::endl;
        this->runTestOnOppositeKey();
        out << "Test `runTestOnOppositeKey` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        std::cout << "Run `runTestOnCreatePocketMap`... (" << startTime << ")." << std::endl;
        this->runTestOnCreatePocketMap();
        out << "Test `runTestOnCreatePocketMap` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
        out << "Tests finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << std::endl;
    }
};

#endif /* pockets_methods_unit_test_hpp */
