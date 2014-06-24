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
#include "boost/shared_ptr.hpp"
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
//    boost::shared_ptr<TS> ts = TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, ptime>("/Users/shimritabraham/Documents/work/GSPC.csv", "%Y-%m-%d", true);
//    cout<<*ts<<endl;


    vector<ptime> a({ptime(date(2012, 3, 1)), ptime(date(2009, 1, 1)), ptime(date(2001, 1, 1))});
    DateTimeLabels sa(a);
    vector<ptime> b({ptime(date(2014, 5, 1)), ptime(date(2005, 5, 1)), ptime(date(2009, 1, 1))});
    DateTimeLabels sb(b);

    DateTimeLabels tmp;
    tmp = sa.intersect(sb);
    cout<<tmp<<endl;


//    vector<string> a{"zz", "aa"};
//    StringLabels sa(a);
//
//    vector<string> b{"bb", "aa"};
//    StringLabels sb(b);
//
//    StringLabels sc = sa.intersect(sb);
//
//    cout<<sc<<endl;

    return 0;
    //return igloo::TestRunner::RunAllTests();
}

