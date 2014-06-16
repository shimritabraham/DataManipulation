//
//  LMatrixFactory.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 06/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_LMatrixFactory_h
#define DataManipulation_LMatrixFactory_h

#include <algorithm>
#include <cctype>
#include "LMatrix.h"
#include "RawMatrix.h"
#include "FileInputManager.h"
#include <boost/shared_ptr.hpp>
#include "Utils.h"
using namespace std;



namespace LMatrixFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class dataType>
    LMatrix<dataType> CreateSimpleLMatrixFromCsv(const string& fileName, const bool& hasColLabels = false, const bool& hasRowLabels =false);

    // FIXME: Could add more 'create-functions' e.g. CreateSimpleLMatrixFromVectors(), CreateSpeedyLMatrix(), CreateSparseLMatrix() etc. These would have different RawMatrix<T> implementations depending on the requirements.
}


namespace {
    // These functions are hidden, only used in this file


    // Function declarations
    template<class dataType>
    void ReadFileWithRowNames(boost::shared_ptr<vector<vector<dataType>>> pData, strVec& rowLabels, istream& fin);
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
        getline(fin, line, '\n');

        //get rid of white space and quotes
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        line.erase(remove( line.begin(), line.end(), '\"' ), line.end());

        // turn commas into spaces for easy conversion into vector
        replace(line.begin(), line.end(), ',', ' ');

        // convert to vector
        stringstream in(line);
        strVec colNames = strVec(istream_iterator<string>(in), istream_iterator<string>());

        return colNames;
    }


    template<class dataType>
    void ReadFileWithRowNames(boost::shared_ptr<vector<vector<dataType>>> pData, strVec& rowLabels, istream& fin){

        string line;
        string rowName;
        while(getline(fin, line, '\n')){
            // process string to make it easily convertible to a vector

            //get rid of white space and quotes
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            line.erase(remove( line.begin(), line.end(), '\"' ), line.end());

            replace(line.begin(), line.end(), ',', ' ');
            stringstream in(line);

            // read and save row name first
            in>>rowName;
            rowLabels.push_back(rowName);

            // then add the rest of the data to result
            (*pData).push_back(vector<dataType>(istream_iterator<dataType>(in), istream_iterator<dataType>()));
        }
    }

}


template<class dataType>
LMatrix<dataType> LMatrixFactory::
CreateSimpleLMatrixFromCsv(const string& fileName, const bool& hasColLabels, const bool& hasRowLabels){
    // This is a simple labelled matrix implementation that is not optimised for speed.

    // Several cases are possible:
    // 1. No row labels, no column labels are provided in the csv
    // 2. Row labels and/or column labels are provided in the csv

    // ASK: I would like to split this into smaller bits but without adding extra copies-by-value. Discuss issues.

    strVec colNames;
    strVec rowNames;
    RawMatrix<dataType> rawData;

    // simplest case: no labels present in file
    if(!hasColLabels && !hasRowLabels){
        rawData = RawMatrix<dataType>(fileName);
        rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());

        // Call constructor (Validation is done inside constructor)
        return LMatrix<dataType>(rawData, rowNames, colNames);

    }

    // Assuming there are row and/or col labels, we need a file handler
    FileInputManager fmgr(fileName);
    fmgr.ValidateObject();
    istream& fin = fmgr.GetStream();

    // first read the col labels -- get it out of the way
    if(hasColLabels){
        colNames = ReadColLabels(fin);
    }

    if(hasRowLabels){
        // read data and row labels from file
        boost::shared_ptr<vector<vector<dataType>>> pData(new(vector<vector<dataType>>));
        ReadFileWithRowNames(pData, rowNames, fin);
        rawData = RawMatrix<dataType>(pData);
    }else{
        // read only the data from file, activate default row labels
        rawData = RawMatrix<dataType>(fin);
        rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
    }

    // Now that we know the dimensions of the data, we can create default column labels, if needed
    if(!hasColLabels)
        colNames = CreateDefaultLabels("col_", rawData.GetNrCols());


    // Finally, call the LMatrix constructor (Validation is done inside constructor)
    return LMatrix<dataType>(rawData, rowNames, colNames);


    //ASK: Can I avoid returning by value in this function?

}





#endif