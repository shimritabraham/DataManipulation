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
#include "DateTimeLabels.h"
#include <string>

using namespace boost::posix_time;
using namespace std;
// Tests
//#include <igloo/igloo.h>
//#include "Tests_Matrix.h"


int main(int argc, const char * argv[])
{

    TimeSeriesFactory::CreateSimpleTimeSeriesFromCsv<double, DateTimeLabels, boost::posix_time::ptime>("/Users/shimritabraham/Documents/work/smallfile.csv", "%Y-%m-%dT%H:%M:%S%F%Q", true);
    //vector<string>rNames = mat.GetRowLabels();

//    LMatrix<double, StringLabels, string> mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<double, StringLabels, string>("/Users/shimritabraham/Documents/work/smallfile.csv", true, true);
//
//    cout<<mat<<endl;


//    boost::posix_time::ptime dt(boost::posix_time::not_a_date_time);
//    std::stringstream ss;
//    ss.exceptions(std::ios_base::failbit);
//    boost::local_time::local_time_input_facet* lif1(new boost::local_time::local_time_input_facet("%Y-%m-%dT%H:%M:%S%F%Q"));
//    ss.imbue(std::locale(std::locale::classic(), lif1));
//    ss.str("2014-03-25T03:41:00.000");
//    ss >> dt;
//    std::cout << dt << std::endl;
//    string a = to_simple_string(dt);
//    cout<<a<<endl;


    return 0;
    //return igloo::TestRunner::RunAllTests();
}

