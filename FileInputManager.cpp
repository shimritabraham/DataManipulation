//
//  FileInputManager.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include "FileInputManager.h"
#include "FileIOError.h"

FileInputManager::FileInputManager(const string& fileName):
itsFileName(fileName), itsStream(fileName){
    try{
        if(!itsStream){
            throw FileIOError("Unable to open file. ", fileName, __FILE__, __LINE__);
        }

    }catch(FileIOError& err){
        err.PrintMessage();
        exit(1);
    }

}


FileInputManager::~FileInputManager(){
    if(itsStream.is_open()){
        itsStream.close();
    }
}