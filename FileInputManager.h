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
#include<sstream>
#include <string>
#include<vector>
#include "FileIOError.h"

using namespace std;

template<class T>
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

template<class T>
FileInputManager<T>::
FileInputManager(const string& fileName): itsFileName(fileName), itsStream(fileName){
    ValidateObject();
}


template<class T>
FileInputManager<T>::
~FileInputManager(){
    if(itsStream.is_open()){
        itsStream.close();
    }
}


template<class T>
void FileInputManager<T>::
ValidateObject() const{
    try{
        if(!itsStream){
            throw FileIOError("Unable to open file. ", itsFileName, __FILE__, __LINE__);
        }

    }catch(FileIOError& err){
        err.PrintMessage();
        exit(1);
    }
}


template<class T>
bool FileInputManager<T>::
IsEOF(){
    return itsStream.eof();
}





#endif /* defined(__DataManipulation__FileInputManager__) */
