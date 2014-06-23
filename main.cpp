//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include <iostream>
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

#include "TimeSeriesFactory.h"
#include "LMatrix.h"
#include "TimeSeries.h"
#include "DateTimeLabels.h"
#include "StringLabels.h"
#include <string>
#include <vector>
#include "Utils.h"

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;

// Tests
//#include <igloo/igloo.h>
//#include "Tests_Matrix.h"


typedef TimeSeries<double, DateTimeLabels, ptime> TS;

int main(int argc, const char * argv[])
{

    //TimeSeries
    TS ts = TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, ptime>("/Users/shimritabraham/Documents/work/GSPC.csv", "%Y-%m-%d", true);
    cout<<ts<<endl;

    ptime t(date(2014, 6, 5));
    cout<<t<<endl;
    TS tmp = ts.row(t);
    cout<<tmp<<endl;

    const size_t idx = 1;
    TS tmp2 = ts.row(idx);
    cout<<tmp2<<endl;

    TS tmp3 = ts.col(string("GSPC.High"));
    cout<<tmp3<<endl;

    TS tmp4 = ts.col(idx);
    cout<<tmp4<<endl;

    return 0;
    //return igloo::TestRunner::RunAllTests();
}

