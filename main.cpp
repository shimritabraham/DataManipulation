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
#include <Eigen/Dense>


using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;

// Tests
//#include <igloo/igloo.h>
//#include "Tests_Matrix.h"


typedef TimeSeries<double, DateTimeLabels, ptime> TSd;
typedef boost::shared_ptr<TimeSeries<double, DateTimeLabels, ptime>> pTSd;
typedef boost::shared_ptr<LMatrix<double, DateTimeLabels, ptime>> pLM;





int main(int argc, const char * argv[])
{
    // settings
    string path = "/Users/shimritabraham/Documents/work/";
    string extension = ".csv";
    vector<string> symbols = {"GSPC", "GDAXI", "FTSE", "IXIC", "N225"};
    string dateTimeFormat = "%Y-%m-%d";
    vector<pTSd> to_join;
    string colNameExtension = ".Close";

    // Read and process data for each symbol
    for (string s:symbols){
        string fullPath = path+s+extension;
        pTSd ts = TimeSeriesFactory::CreateTimeSeriesFromCsv<double, DateTimeLabels, ptime>(fullPath, SIMPLE, dateTimeFormat, true);
        pTSd colToJoin(new TSd (ts->col(s+colNameExtension)) );
        to_join.push_back(colToJoin);
    }

    // Join the columns
    pTSd joined_cols = join(to_join);
    cout<<(*joined_cols)<<endl;

    // Turn TimeSeries into Eigen::Matrix object
    Eigen::MatrixXd eigenMat = joined_cols->asEigenMatrix();
    cout<<eigenMat<<endl;


    return 0;
    //return igloo::TestRunner::RunAllTests();
}

