//
//  FileInputManager.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef __DataManipulation__FileInputManager__
#define __DataManipulation__FileInputManager__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "FileIOError.h"

using namespace std;

class FileInputManager{
public:
    // Con/Destructors
    FileInputManager(const string& fileName);
    ~FileInputManager();

    // Member Functions
    void ValidateObject() const;
    bool IsEOF();
    ifstream& GetStream(){return itsStream;}

private:
    // Data Members
    string itsFileName;
    ifstream itsStream;

};



#endif /* defined(__DataManipulation__FileInputManager__) */
