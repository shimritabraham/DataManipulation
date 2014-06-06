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
    vector<T> ReadNextCSVLine();
    bool IsEOF();
    

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


template<class T>
vector<T> FileInputManager<T>::
ReadNextCSVLine(){
    //Note: We don't know if EOF is reached until we have read it. If EOF is reached, return an empty vector.

    //checks
    ValidateObject();
    if(IsEOF()){
        throw FileIOError("EOF reached. ", itsFileName, __FILE__, __LINE__);
    }

    // read line with commas, possibly reached EOF
    string line;
    getline(itsStream, line, '\r');

    // If EOF is reached, return empty vector
    vector<T> data;
    if (IsEOF())
        return data;

    // change commas to spaces so we can make a vector easily
    replace(line.begin(), line.end(), ',', ' ');
    stringstream in(line);
    data = vector<T>(istream_iterator<T>(in), istream_iterator<T>());

    // check that something was read at all
    if(data.size() == 0 && !IsEOF()){
        throw FileIOError("Unable to create the required vector (inconsistent data types?) ", itsFileName, __FILE__, __LINE__);
    }

    return data;

}



#endif /* defined(__DataManipulation__FileInputManager__) */
