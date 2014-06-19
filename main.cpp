//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include <iostream>
#include "boost/date_time/local_time/local_time.hpp"
#include "TimeSeriesFactory.h"
#include "LMatrix.h"
#include "TimeSeries.h"
#include "DateTimeLabels.h"
#include "StringLabels.h"
#include <string>

using namespace boost::posix_time;
using namespace std;

// Tests
//#include <igloo/igloo.h>
//#include "Tests_Matrix.h"


int main(int argc, const char * argv[])
{


    //TimeSeries
    TimeSeries<double, DateTimeLabels, ptime> ts = TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, ptime>("/Users/shimritabraham/Documents/work/smallfile.csv", "%Y-%m-%dT%H:%M:%S%F%Q", true);
    cout<<ts<<endl;

    //LMatrix
    LMatrix<double, StringLabels, string>  mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<double, StringLabels, string>("/Users/shimritabraham/Documents/work/smallfile.csv", true, true, "%Y-%m-%dT%H:%M:%S%F%Q");
    cout<<mat<<endl;

    return 0;
    //return igloo::TestRunner::RunAllTests();
}

