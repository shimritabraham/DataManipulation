//
//  MatrixFactory.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 06/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_MatrixFactory_h
#define DataManipulation_MatrixFactory_h

#include "Matrix.h"
#include "RawMatrix.h"
#include "FileInputManager.h"

namespace MatrixFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class T>
    Matrix<T> CreateSimpleMatrixFromCsv(const string& fileName);
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
Matrix<T> MatrixFactory::CreateSimpleMatrixFromCsv(const string& fileName){

    RawMatrix<T> rawData(fileName);
    strVec rowNames = CreateDefaultLabels("row_", rawData.GetNrRows());
    strVec colNames = CreateDefaultLabels("col_", rawData.GetNrCols());

    return Matrix<T>(rawData, rowNames, colNames);
}





#endif
