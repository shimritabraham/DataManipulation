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
using namespace std;

typedef vector<double> tdDoubleVec;



void foo(vector<int>* p){
    (*p).push_back(3);
}



int main(int argc, const char * argv[])
{

    try{

        //params:
        string fileName = "/Users/shimritabraham/Documents/work/data.csv";
        Matrix<double> a = MatrixFactory::CreateSimpleMatrixFromCsv<double>(fileName, true, true);
        cout<<a<<endl;
        auto r =a.col("secondCol");
        cout<<r<<endl;

    }catch(string& err){
        cout<<err<<endl;
    }catch(...){
        cout<<"Unexpected error occured"<<endl;
    }

    return 0;
}

