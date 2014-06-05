//
//  FileIO.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include "FileIOError.h"
#include <string>
#include <iostream>
using namespace std;


FileIOError::FileIOError(const string&msg, const string& fileName, const string& thrownInFile, const int& thrownInRow):
            itsMessage(msg), itsFileName(fileName), itsThrownInFile(thrownInFile), itsThrownInRow(thrownInRow){

}

void FileIOError::PrintMessage() const {
    cout<<itsMessage<<endl;
    cout<<"File Name: \'"<<itsFileName<<endl;
    cout<<"Exception was thrown in: \n"<<itsThrownInFile<<"; Row: "<<itsThrownInRow<<endl;
}



