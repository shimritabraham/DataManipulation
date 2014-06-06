//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include<vector>
#include "Matrix.h"
#include "FileInputManager.h"
using namespace std;

typedef vector<double> tdDoubleVec;


int main(int argc, const char * argv[])
{

    //assuming the file has no colnames and no rownames!

    //params:
    string fileName = "/Users/shimritabraham/Documents/work/data.csv";

    Matrix<double> a(fileName);
    const int i=0;
    const int j=0;
    const double k = a(i, j);

  //  const Matrix<double>& klaas(a);

    //klaas(i,j);


    cout<<k<<endl;



    return 0;
}

