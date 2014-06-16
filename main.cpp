//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include <iostream>
#include "boost/date_time/local_time/local_time.hpp"
#include "LMatrixFactory.h"

// Tests
#include <igloo/igloo.h>
#include "Tests_Matrix.h"


int main(int argc, const char * argv[])
{

    LMatrix<double, vector<string>, string> mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<double, vector<string>, string>("/Users/shimritabraham/Documents/work/smallfile.csv", true, true);
    //vector<string>rNames = mat.GetRowLabels();
    cout<<mat<<endl;


//    boost::posix_time::ptime dt(boost::posix_time::not_a_date_time);
//    std::stringstream ss;
//    ss.exceptions(std::ios_base::failbit);
//    boost::local_time::local_time_input_facet* lif1(new boost::local_time::local_time_input_facet("%Y-%m-%dT%H:%M:%S%F%Q"));
//    ss.imbue(std::locale(std::locale::classic(), lif1));
//    ss.str("2014-03-25T06:22:00.000");
//    ss >> dt;
//    std::cout << dt << std::endl;

//    return igloo::TestRunner::RunAllTests();
}

