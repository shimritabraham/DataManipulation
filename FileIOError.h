//
//  FileIO.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_FileIO_h
#define DataManipulation_FileIO_h
#include <string>

using namespace std;

class FileIOError{
public:
    // Con/De-structors
    FileIOError(const string&msg, const string& fileName, const string& thrownInFile, const int& thrownInRow);
    ~FileIOError(){}

    // Utils
    void PrintMessage() const;
private:
    string itsMessage;
    string itsFileName;
    string itsThrownInFile;
    int    itsThrownInRow;
};



#endif
