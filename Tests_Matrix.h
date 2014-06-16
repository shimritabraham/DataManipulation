//
//  Tests_Matrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 16/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Tests_Matrix_h
#define DataManipulation_Tests_Matrix_h

#include <iostream>
#include "LMatrixFactory.h"

#include <igloo/igloo.h>


using namespace igloo;

Context(CreateMatrix){

    // ASK: Unable to find out how to provide a relative path, so using abs path instead
    LMatrix<double, vector<string>, string> mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<double, vector<string>, string>("/Users/shimritabraham/Documents/work/smallfile.csv", true, true);

    // FIXME:
    // - Check that you can load a LMatrix from a file with/without row/column labels
    // - Test cout
    // etc... 



};


#endif
