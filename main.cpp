//
//  main.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

//#define EIGEN_MATRIXBASE_PLUGIN "Eigen_MatrixBaseAddons.h" // This HAS to be done first
//
//#include <iostream>
//#include "boost/date_time/local_time/local_time.hpp"
//#include "boost/date_time/posix_time/posix_time.hpp"
//#include "boost/date_time/gregorian/gregorian.hpp"
//#include "boost/shared_ptr.hpp"
//#include "TimeSeriesFactory.h"
//#include "LMatrix.h"
//#include "TimeSeries.h"
//#include "DateTimeLabels.h"
//#include "StringLabels.h"
//#include <string>
//#include <vector>
//#include "Utils.h"
//#include <Eigen/Dense>
//
//
//using namespace boost::posix_time;
//using namespace boost::gregorian;
//using namespace std;
//using namespace Eigen;
//// Tests
////#include <igloo/igloo.h>
////#include "Tests_Matrix.h"
//
//
//typedef TimeSeries<double, DateTimeLabels, ptime> TSd;
//typedef boost::shared_ptr<TimeSeries<double, DateTimeLabels, ptime>> pTSd;
//typedef boost::shared_ptr<LMatrix<double, DateTimeLabels, ptime>> pLM;
//


//int main(int argc, const char * argv[])
//{
//    // settings
//    string path = "/Users/shimritabraham/Documents/work/";
//    string extension = ".csv";
//    vector<string> symbols = {"GSPC", "GDAXI", "FTSE", "IXIC", "N225"};
//    string dateTimeFormat = "%Y-%m-%d";
//    vector<pTSd> to_join;
//    string colNameExtension = ".Close";
//
//    // Read and process data for each symbol
//    for (string s:symbols){
//        string fullPath = path+s+extension;
//        pTSd ts = TimeSeriesFactory::CreateTimeSeriesFromCsv<double, DateTimeLabels, ptime>(fullPath, SIMPLE, dateTimeFormat, true);
//        pTSd colToJoin(new TSd (ts->col(s+colNameExtension)) );
//        to_join.push_back(colToJoin);
//    }
//
//    // Join the columns
//    pTSd joined_cols = join(to_join);
//    cout<<(*joined_cols)<<endl;
//
//    // Turn TimeSeries into Eigen::Matrix object
//    Eigen::MatrixXd eigenMat = joined_cols->asEigenMatrix();
//    cout<<eigenMat<<endl;
//    cout<<eigenMat(1, 2)<<endl;
//    cout<<eigenMat.myRows()<<endl;
//    cout<<eigenMat.bottomRows(3).myRows()<<endl;



    

//    return 0;
//    //return igloo::TestRunner::RunAllTests();
//}


#include <iostream>
#include <vector>
#define EIGEN_MATRIXBASE_PLUGIN "Eigen_MatrixBaseAddons.h"
#include <Eigen/Dense>
using namespace std;


int main()
{
    Eigen::Matrix<double, 7, 3, Eigen::RowMajor> a;

    vector<double> r1{1, 2, 3};
    vector<double> r2{1, 5, 3};
    vector<double> r3{3, 3, 3};
    vector<double> r4{15, 2, 3};
    vector<double> r5{78, 12, 88};
    vector<double> r6{90, 5, 9};
    vector<double> r7{1, 22, 33};

    vector<vector<double>> allVec{r1, r2, r3, r4, r5, r6, r7};

    for (int i = 0; i < 7; i++)
        a.row(i) = Eigen::Matrix<double, 3, 1>::Map(&allVec[i][0],allVec[i].size());

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> res;
    cout<<a<<endl;
    cout<<endl;
    a.lnRet(res, 1);
    cout<<res<<endl;
//    a.Cov_equallyWeightedAllData(res);
    a.cov(a, a, res);
    cout<<res<<endl;

    
}

