//
//  FileInputManager.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 10/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include "FileInputManager.h"


FileInputManager::
FileInputManager(const string& fileName): itsFileName(fileName), itsStream(fileName){
    ValidateObject();
}


FileInputManager::
~FileInputManager(){
    if(itsStream.is_open()){
        itsStream.close();
    }
}


void FileInputManager::
ValidateObject() const{

    if(!itsStream){
        throw FileIOError("Unable to open file. ", itsFileName, __FILE__, __LINE__);
    }
}


bool FileInputManager::
IsEOF(){
    return itsStream.eof();
}

