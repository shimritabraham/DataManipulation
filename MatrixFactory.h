//
//  MatrixFactory.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 06/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_MatrixFactory_h
#define DataManipulation_MatrixFactory_h

#include <algorithm>
#include <cctype>
#include "Matrix.h"
#include "RawMatrix.h"
#include "FileInputManager.h"

using namespace std;

namespace MatrixFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class T>
    Matrix<T> CreateSimpleMatrixFromCsv(const string& fileName, const bool& hasColLabels = false, const bool& hasRowLabels =false);
    template<class T>
    Matrix<T> CreateSimpleMatrixFromVectors(const vector< vector<T> >& vecvec);


}

namespace {
    vector<string> CreateDefaultLabels(const string& str, const size_t& len);

    vector<string> CreateDefaultLabels(const string& str, const size_t& len){
        vector<string> result(len);
        for(size_t i =0; i<len; i++){
            result[i] = str+to_string(i);
        }
        return result;
    }
}


template<class T>
Matrix<T> MatrixFactory::CreateSimpleMatrixFromCsv(const string& fileName, const bool& hasColLabels, const bool& hasRowLabels){

    if(!hasColLabels && !hasRowLabels){
        RawMatrix<T> rawData(fileName);
        strVec rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
        strVec colNames = CreateDefaultLabels("col_", rawData.GetNrCols());

        return Matrix<T>(rawData, rowNames, colNames);

    }else if(hasColLabels && !hasRowLabels){
        // read column labels
        FileInputManager<T> fmgr(fileName);
        fmgr.ValidateObject();
        string line;
        getline(fmgr.GetStream(), line, '\r');

        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); //get rid of white space
        replace(line.begin(), line.end(), ',', ' '); // turn commas into spaces for easy conversion into vector
        stringstream in(line);
        strVec colNames = strVec(istream_iterator<string>(in), istream_iterator<string>());

        RawMatrix<T> rawData(fmgr.GetStream());
        strVec rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());

        return Matrix<T>(rawData, rowNames, colNames);

    }else{
        throw string("Not implemented");
    }



}





#endif
