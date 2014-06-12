//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include <iostream>
#include "MatrixFactory.h"
#include <ctype.h>
#include "Utils.h"
#include <algorithm>
using namespace std;


int main(int argc, const char * argv[])
{

    try{

        //Data file source:
        string fileName;
        cout<<"Please provide a file name"<<endl;
        getline(cin, fileName);
//        fileName = "/Users/shimritabraham/Documents/work/USDRates_Mids.csv";


        // Load csv into a Matrix object using a factory method
        Matrix<double> mat = MatrixFactory::CreateSimpleMatrixFromCsv<double>(fileName, true, true);
        cout<<mat<<endl;



    }catch(string& err){
        cout<<err<<endl;
    }catch(FileIOError& err){
        err.PrintMessage();
    }
    catch(...){
        cout<<"Unexpected error occured"<<endl;
    }

    return 0;
}

