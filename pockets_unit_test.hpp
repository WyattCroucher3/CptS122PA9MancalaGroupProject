//
//  pockets_unit_test.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/27/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef pockets_unit_test_hpp
#define pockets_unit_test_hpp

class pockets_unit_test final {
    const std::list<string> keys = {"A1", "A2", "A3", "A4", "A5", "A6", "P2", "B6", "B5", "B4", "B3", "B2", "B1", "P1"};
    
    // tests pockets::nextPosition method againist know pattern, keys.
    void runTestOnNextPosition(void) {
        
        string key = "A1";
        
        auto startTime = time(0);
        
        cout << "Beginning test on pockets::nextPosition(std::string,UInt) at " << startTime << endl;
        
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
        cout << success << " succeeded, " << fail << " failed." << endl;
        cout << "Operation completed after " << (time(0) - startTime) << " seconds." << endl;
    }
    
    // test ownership of pockets.
    void runTetstOnOwnership(void) {
        
        auto startTime = time(0);
        
        cout << "Beginning test on pockets::nextPosition(std::string,UInt) at " << startTime << endl;
        
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
        
        cout << success << " succeeded, " << fail << " failed." << endl;
        cout << "Operation completed after " << (time(0) - startTime) << " seconds." << endl;
    }
    
    void runTestOnOppositeKey(void) {
        auto startTime = time(0);
        
        cout << "Beginning test on pockets::getOppositeFromKey(std::string) at " << startTime << endl;
        
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
        
        cout << success << " succeeded, " << fail << " failed." << endl;
        cout << "Operation completed after " << (time(0) - startTime) << " seconds." << endl;
    }
    
    void runTestOnCreatePocketMap(void) {
        auto startTime = time(0);
        
        cout << "Beginning test on pockets::setupMap(unordered_map<string, Pocket*>) at " << startTime << endl;
        
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
        
        cout << success << " succeeded, " << fail << " failed." << endl;
        cout << "Operation completed after " << (time(0) - startTime) << " seconds." << endl;
    }
    
public:
    pockets_unit_test(void) {
        time_t startTime = time(0);
        cout << "Beginning tests at " << startTime << "." << endl;
        cout << "Run `runTestOnNextPosition`... (" << startTime << ")." << endl;
        this->runTestOnNextPosition();
        out << "Test `runTestOnNextPosition` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << endl;
        cout << "Run `runTestOnOwnership`... (" << startTime << ")." << endl;
        this->runTestOnOwnership();
        out << "Test `runTestOnOwnership` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << endl;
        cout << "Run `runTestOnOppositeKey`... (" << startTime << ")." << endl;
        this->runTestOnOppositeKey();
        out << "Test `runTestOnOppositeKey` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << endl;
        cout << "Run `runTestOnCreatePocketMap`... (" << startTime << ")." << endl;
        this->runTestOnCreatePocketMap();
        out << "Test `runTestOnCreatePocketMap` finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << endl;
        out << "Tests finished after " << (time(0) - startTime) <<  " seconds." << startTime << "." << endl;
    }
};

#endif /* pockets_unit_test_hpp */
