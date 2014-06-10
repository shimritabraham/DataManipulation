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
#include <boost/shared_ptr.hpp>
using namespace std;



namespace MatrixFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class T>
    Matrix<T> CreateSimpleMatrixFromCsv(const string& fileName, const bool& hasColLabels = false, const bool& hasRowLabels =false);

    // FIXME: Could add more 'create-functions' e.g. CreateSimpleMatrixFromVectors(), CreateSpeedyMatrix(), CreateSparseMatrix() etc. These would have different RawMatrix<T> implementations depending on the requirements.
}


namespace {
    // These functions are hidden, only used in this file


    // Function declarations
    template<class T>
    void ReadFileWithRowNames(boost::shared_ptr<vector<vector<T>>> pData, strVec& rowLabels, istream& fin);
    vector<string> CreateDefaultLabels(const string& str, const size_t& len);
    strVec ReadColLabels(istream& fin);


    // Function definitions
    vector<string> CreateDefaultLabels(const string& str, const size_t& len){
        vector<string> result(len);
        for(size_t i =0; i<len; i++){
            result[i] = str+to_string(i);
        }
        return result;
    }


    strVec ReadColLabels(istream& fin){
        string line;
        getline(fin, line, '\r');

        //get rid of white space
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

        // turn commas into spaces for easy conversion into vector
        replace(line.begin(), line.end(), ',', ' ');

        // convert to vector
        stringstream in(line);
        strVec colNames = strVec(istream_iterator<string>(in), istream_iterator<string>());
        
        return colNames;
    }


    template<class T>
    void ReadFileWithRowNames(boost::shared_ptr<vector<vector<T>>> pData, strVec& rowLabels, istream& fin){

        string line;
        string rowName;
        while(getline(fin, line, '\r')){
            // process string to make it easily convertible to a vector
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); //get rid of white space
            replace(line.begin(), line.end(), ',', ' ');
            stringstream in(line);

            // read and save row name first
            in>>rowName;
            rowLabels.push_back(rowName);

            // then add the rest of the data to result
            (*pData).push_back(vector<T>(istream_iterator<T>(in), istream_iterator<T>()));
        }
    }

}


template<class T>
Matrix<T> MatrixFactory::
CreateSimpleMatrixFromCsv(const string& fileName, const bool& hasColLabels, const bool& hasRowLabels){
    // This is a simple matrix implementation that is not optimised for speed.

    // Several cases are possible:
    // 1. No row labels, no column labels are provided in the csv
    // 2. Row labels and/or column labels are provided in the csv

    // ASK: I would like to split this into smaller bits but without adding extra copies-by-value. Discuss issues.

    strVec colNames;
    strVec rowNames;
    RawMatrix<T> rawData;

    // simplest case: no labels present in file
    if(!hasColLabels && !hasRowLabels){
        rawData = RawMatrix<T>(fileName);
        rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());

        // Call constructor (Validation is done inside constructor)
        return Matrix<T>(rawData, rowNames, colNames);

    }

    // Assuming there are row and/or col labels, we need a file handler
    FileInputManager<T> fmgr(fileName);
    fmgr.ValidateObject();
    istream& fin = fmgr.GetStream();

    // first read the col labels -- get it out of the way
    if(hasColLabels){
        colNames = ReadColLabels(fin);
    }

    if(hasRowLabels){
        // read data and row labels from file
        boost::shared_ptr<vector<vector<T>>> pData(new(vector<vector<T>>));
        ReadFileWithRowNames(pData, rowNames, fin);
        rawData = RawMatrix<T>(pData);
    }else{
        // read only the data from file, activate default row labels
        rawData = RawMatrix<T>(fin);
        rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
    }

    // Now that we know the dimensions of the data, we can create default column labels, if needed
    if(!hasColLabels)
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());


    // Finally, call the Matrix constructor (Validation is done inside constructor)
    return Matrix<T>(rawData, rowNames, colNames);


    //ASK: Can I avoid returning by value in this function?

}





#endif
