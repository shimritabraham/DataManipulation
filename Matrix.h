//
//  Matrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Matrix_h
#define DataManipulation_Matrix_h

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include "FileInputManager.h"
using namespace std;


//namespace MatrixFactories
//{
//    template< class T>
//    Matrix<T> createSimpleMatrix();
//
//    Matrix createSimpleMatrix(const string& filename)
//    Matrix createSimpleMatrixZeros(int i, int j);
//
//    Matrix createSparseMatrix();
//}
//
//class SparseContainer;
//class FullContainer;
//
//Matrix<double, SparseContainer> sparseMatrix;
//

template< class T>
class Matrix{

    public:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Matrix(const std::string& filename);
    ~Matrix(){}

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Member Functions ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // accessors
    size_t GetNrCols() const {return (itsRawData[0]).size();};
    size_t GetNrRows() const {return itsRawData.size();};

    // printing
    std::ostream& operator<< (std::ostream& out);

    // operators -- read/write
    const T& operator() (const int& rowIdx, const int& colIdx)const;
       T& operator() (const int& rowIdx, const int& colIdx);
    const T& operator() (const std::string& rowName, const std::string& colName)const ;
          T& operator() (const std::string& rowName, const std::string& colName);

    const std::vector<T>& row(const int& idx) const;
          std::vector<T>& row(const int& idx);
    const std::vector<T>& row(const std::string& name) const;
          std::vector<T>& row(const std::string& name);

    const std::vector<T>& col(const int& idx) const;
          std::vector<T>& col(const int& idx);
    const std::vector<T>& col(const std::string& name) const;
          std::vector<T>& col(const std::string& name);

    // Utils
    void ValidateObject() const;//e.g.: make sure its square.
    void SortByRowLabels(); // make 2 versions: in place and copy. Make  this into a normal function

    // Friends
    template<class S>
    friend ostream& operator<< (ostream& str,  Matrix<S>& mat);

    private:
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Data Members ~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//    M itsRawDataNew;
    std::vector<std::vector<T>> itsRawData;       // Each row is a vector
    std::vector<std::string> itsRowNames;
    std::vector<std::string> itsColNames;
};

template<class T>
Matrix<T> intersect(const Matrix<T>& mat, const std::vector<std::string>& labels);


template<class T>
Matrix<T>::Matrix(const string& fileName){

    FileInputManager<T> fmgr(fileName);
    try{
        while(!fmgr.IsEOF()){

            vector<T> a = fmgr.ReadNextCSVLine();

            //Make sure we did not reach EOF before adding it to itsRawData
            if(!fmgr.IsEOF()){
                itsRawData.push_back(a);
            }
        }


    }catch(FileIOError err){
        err.PrintMessage();
    }
}

template<class T>
T& Matrix<T>::
operator() (const int& rowIdx, const int& colIdx){
    return itsRawData[rowIdx][colIdx];
}

template<class T>
const T& Matrix<T>::
operator() (const int& rowIdx, const int& colIdx) const {
    return itsRawData[rowIdx][colIdx];
}

template<class S>
ostream& operator<< (ostream& str,  Matrix<S>& mat){
    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Member \'itsRawData\'"<<"("<<nRows<<"x"<<nCols<<"):"<<endl;
    for (int i=0; i<nRows; i++){
        for (int j=0; j<nCols; j++){
            str<<mat(i, j);

        }
        str<<endl;
    }
    return str;
}


#endif


