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

using namespace std;

typedef vector<double> tdDoubleVec;



void foo(vector<int>* p){
    (*p).push_back(3);
}



int main(int argc, const char * argv[])
{

    //params:
    string fileName = "/Users/shimritabraham/Documents/work/data.csv";

    Matrix<double> a = MatrixFactory::CreateSimpleMatrixFromCsv<double>(fileName, true, true);
    cout<<a<<endl;

    vector<int>* m = new vector<int>;
    foo(m);
    foo(m);
    


    return 0;
}

