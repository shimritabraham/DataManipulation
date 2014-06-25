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
typedef boost::shared_ptr<TimeSeries<double, DateTimeLabels, ptime>> pTS;
typedef boost::shared_ptr<LMatrix<double, DateTimeLabels, ptime>> pLM;






int main(int argc, const char * argv[])
{

    //TimeSeries
    boost::shared_ptr<TS> ts1 = TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, ptime>("/Users/shimritabraham/Documents/work/GSPC.csv", "%Y-%m-%d", true);
    boost::shared_ptr<TS> ts2 = TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, ptime>("/Users/shimritabraham/Documents/work/GDAXI_dateChg.csv", "%Y-%m-%d", true);

    pTS pts1(new TS (ts1->col("GSPC.Close")));
    pTS pts2(new TS (ts2->col("GDAXI.Close")));

    pLM a = pts1->cbind(pts2);
    a->head(cout, 10);


    return 0;
    //return igloo::TestRunner::RunAllTests();
}

