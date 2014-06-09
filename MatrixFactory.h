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
    template<class T>
    Matrix<T> CreateSimpleMatrixFromVectors(const vector< vector<T> >& vecvec);


}

namespace {
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
Matrix<T> MatrixFactory::CreateSimpleMatrixFromCsv(const string& fileName, const bool& hasColLabels, const bool& hasRowLabels){

    strVec colNames;
    strVec rowNames;
    RawMatrix<T> rawData;

    // simplest case: no labels present in file
    if(!hasColLabels && !hasRowLabels){
        RawMatrix<T> rawData(fileName);
        rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());

        // Call constructor (Validation is done inside constructor)
        return Matrix<T>(rawData, rowNames, colNames);

    }

    // Assuming there are row and/or col labels, we need a file handler
    FileInputManager<T> fmgr(fileName);
    fmgr.ValidateObject();
    istream& fin = fmgr.GetStream();

    if(hasColLabels){
        // first read the col labels
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

    // We can only now create default column labels, if needed
    if(!hasColLabels)
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());


    // Finally, call the Matrix constructor (Validation is done inside constructor)
    return Matrix<T>(rawData, rowNames, colNames);


    //FIXME: How do I avoid returning by value in this function?

}





#endif
