//
//  run_application_unit_tests.hpp
//  Final Proj
//
//  Created by Kyle Parker on 4/30/21.
//  Copyright © 2021 Kyle Parker. All rights reserved.
//

#ifndef run_application_unit_tests_hpp
#define run_application_unit_tests_hpp

class run_application_unit_tests {
    
    
public:
    run_application_unit_tests(void) {
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

#endif /* run_application_unit_tests_hpp */
