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
#include <iomanip>
#include <iterator>
#include "FileInputManager.h"
#include "RawMatrix.h"
using namespace std;

typedef vector<string> strVec;

template< class T>
class Matrix{
    // This should not be created directly by the user.
    // Instead, please use the available MatrixFactly functions

public:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Note: Matrix objects should be created via Factory functions, not via constructor
    Matrix(RawMatrix<T>& rawData, strVec& rowNames, strVec& colNames);
    ~Matrix(){}

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Member Functions ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // accessors
    RawMatrix<T> GetRawData(){return itsRawData;}
    size_t GetNrCols() const {return itsRawData.GetNrCols();}
    size_t GetNrRows() const {return itsRawData.GetNrRows();}
    strVec GetColNames() const{return itsColNames;}
    strVec GetRowNames() const{return itsRowNames;}

    // printing
    std::ostream& operator<< (std::ostream& out);

    // operators -- read/write
    const T& operator() (const int& rowIdx, const int& colIdx)const {return itsRawData(rowIdx, colIdx);};
          T& operator() (const int& rowIdx, const int& colIdx)      {return itsRawData(rowIdx, colIdx);};
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
    void ValidateObject() const;
    void SortByRowLabels(); // make 2 versions: in place and copy. Make  this into a normal function
    void SwapRows(const int& r1, const int& r2);
    void SwapCols(const int& c1, const int& c2);

    // Friends
    template<class S>
    friend ostream& operator<< (ostream& str,  Matrix<S>& mat);


private:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Data Members ~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    RawMatrix<T> itsRawData;  // this can potentially be templetized later
    strVec itsRowNames;
    strVec itsColNames;
};


template<class T>
void Matrix<T>::
ValidateObject() const{

    // check the underlying raw data
    itsRawData.ValidateObject();

    // check that the labels have the right size
    if(itsRawData.GetNrCols() != itsColNames.size())
        throw string("Length of column labels does not match number of data columns");
    if(itsRawData.GetNrRows() != itsRowNames.size())
        throw string("Length of row labels does not match number of rows in data");
}

template<class T>
void Matrix<T>::
SwapRows(const int& r1, const int& r2){

    // swap raw data
    itsRawData.SwapRows(r1, r2);

    // swap row labels
    string tmp = itsRowNames[r2];
    itsRowNames[r2] = itsRowNames[r1];
    itsRowNames[r1] = tmp;

    ValidateObject();

}

template<class T>
Matrix<T>
intersect(const Matrix<T>& mat, const strVec& labels);


template<class T>
Matrix<T>::
Matrix(RawMatrix<T>& rawData, strVec& rowNames, strVec& colNames):
    itsRawData(rawData), itsRowNames(rowNames), itsColNames(colNames)
{
    try{
        ValidateObject();
    }catch(string& str){
        cout<<str<<endl;
        exit(1);
    }
    catch(...){
        cout<<"Exception occured"<<endl;
        exit(1);
    }
}


template<class T>
const T& Matrix<T>::
operator() (const std::string& rowName, const std::string& colName)const{

    // find mapping between string indices to location in the matrix
    vector<string>::const_iterator rowIter = find(itsRowNames.begin(), itsRowNames.end(), rowName);
    vector<string>::const_iterator colIter = find(itsColNames.begin(), itsColNames.end(), colName);

    int i = distance(itsRowNames.begin(), rowIter);
    int j = distance(itsColNames.begin(), colIter);

    // find the element in the underlying raw data
    return itsRawData(i, j);
}

template<class T>
T& Matrix<T>::
operator() (const std::string& rowName, const std::string& colName){

    // find mapping between string indices to location in the matrix
    vector<string>::iterator rowIter = find(itsRowNames.begin(), itsRowNames.end(), rowName);
    vector<string>::iterator colIter = find(itsColNames.begin(), itsColNames.end(), colName);

    size_t i = distance(itsRowNames.begin(), rowIter);
    size_t j = distance(itsColNames.begin(), colIter);

    // find the element in the underlying raw data
    return itsRawData((int) i, (int) j);

}



template<class S>
ostream& operator<< (ostream& str,  Matrix<S>& mat){

    const int& fieldWidth = 15;

    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Raw Data "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;

    // print colnames
    strVec colnames = mat.GetColNames();
    cout<<setw(fieldWidth)<<" ";
    for (size_t i=0; i<nCols; i++){
        cout<<setw(fieldWidth)<<colnames[i];
    }
    cout<<endl;

    strVec rownames = mat.GetRowNames();
    for (int i=0; i<nRows; i++){
        cout<<setw(fieldWidth)<<rownames[i];
        for (int j=0; j<nCols; j++){
            str<<setw(fieldWidth)<<mat(i, j);
            // only print a comma if there's another number to print
            if (j < nCols-1)
                cout<<", ";
        }
        str<<endl;
    }
    return str;

}

template<class T>
const vector<T>& Matrix<T>::
row(const int& idx) const{
    return itsRawData.row(idx);
}

template<class T>
vector<T>& Matrix<T>::
row(const int& idx){
    return itsRawData.row(idx);
}

template<class T>
const std::vector<T>& Matrix<T>::
row(const std::string& name) const{
    strVec::iterator iElement = find(itsRowNames.begin(), itsRowNames.end(), name);
    size_t idx = distance(itsRowNames.begin(), iElement);
    return row(idx);
}


template<class T>
std::vector<T>& Matrix<T>::
row(const std::string& name){
    strVec::iterator iElement = find(itsRowNames.begin(), itsRowNames.end(), name);
    size_t idx = distance(itsRowNames.begin(), iElement);
    return row((int) idx);
}


#endif


