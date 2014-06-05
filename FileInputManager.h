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
#include<fstream>
#include <string>
using namespace std;

class FileInputManager{
public:
    FileInputManager(const string& fileName);
    ~FileInputManager();

private:
    string itsFileName;
    ifstream itsStream;

};





#endif /* defined(__DataManipulation__FileInputManager__) */
