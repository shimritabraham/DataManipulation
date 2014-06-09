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





int main(int argc, const char * argv[])
{

    //assuming the file has no colnames and no rownames!

    //params:
    string fileName = "/Users/shimritabraham/Documents/work/data.csv";

    Matrix<double> a = MatrixFactory::CreateSimpleMatrixFromCsv<double>(fileName, true);
    cout<<a.GetColNames()[1]<<endl;


    return 0;
}

