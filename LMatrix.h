//
//  LMatrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_LMatrix_h
#define DataManipulation_LMatrix_h

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

template< class dataType>
class LMatrix{

    // Please use the available LMatrixFactly functions to create instances of this class

public:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Note: LMatrix objects should be created via Factory functions, not via the constructor
    LMatrix(RawMatrix<dataType>& rawData, strVec& rowNames, strVec& colNames);
    ~LMatrix(){}


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Member Functions ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // accessors
    RawMatrix<dataType> GetRawData(){  return itsRawData;}
    size_t GetNrCols()   const {return itsRawData.GetNrCols();}
    size_t GetNrRows()   const {return itsRawData.GetNrRows();}
    strVec GetColNames() const{return itsColNames;}
    strVec GetRowNames() const{return itsRowNames;}

    // printing
    std::ostream& operator<< (std::ostream& out);

    // operators -- read/write
    const dataType& operator() (const size_t& rowIdx, const size_t& colIdx)const {return itsRawData(rowIdx, colIdx);};
          dataType& operator() (const size_t& rowIdx, const size_t& colIdx)      {return itsRawData(rowIdx, colIdx);};
    const dataType& operator() (const std::string& rowName, const std::string& colName)const ;
          dataType& operator() (const std::string& rowName, const std::string& colName);

    const std::vector<dataType>& row(const size_t& idx) const  {return itsRawData.row(idx);}
          std::vector<dataType>& row(const size_t& idx)        {return itsRawData.row(idx);}
    const std::vector<dataType>& row(const std::string& name) const;
          std::vector<dataType>& row(const std::string& name);

    //ASK: return type is ref in row() and non-ref in col(). Can this be avoided?
    const std::vector<dataType> col(const size_t& idx) const   {return itsRawData.col(idx);}
          std::vector<dataType> col(const size_t& idx)         {return itsRawData.col(idx);}
    const std::vector<dataType> col(const std::string& name) const;
          std::vector<dataType> col(const std::string& name);

    // Utils
    void ValidateObject() const;
    void SwapRows(const size_t& r1, const size_t& r2);
    void SwapRows(const string& str1, const string& str2);
    void SwapCols(const size_t& c1, const size_t& c2);
    void SwapCols(const string& str1, const string& str2);

    // Friends
    template<class S>
    friend ostream& operator<< (ostream& str,  LMatrix<S>& mat);


private:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Data Members ~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    RawMatrix<dataType> itsRawData;  // this can potentially be templetized later
    strVec itsRowNames;
    strVec itsColNames;
};





namespace{
    // Helper functions that can only be called from this file

    // Function Declarations
    template<class dataType>
    void PrintSmallLMatrix(ostream& str, LMatrix<dataType> mat, const int& fieldWidth);
    template<class dataType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType> mat, const int& fieldWidth, const int& maxRows, const int& maxCols);


    // Function Definitions
    template<class dataType>
    void PrintSmallLMatrix(ostream& str, LMatrix<dataType> mat, const int& fieldWidth){
        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();

        // print colnames
        strVec colnames = mat.GetColNames();
        cout<<setw(fieldWidth)<<right<<"";
        for (size_t i=0; i<nCols; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<endl;

        // print rownames and data row by row
        strVec rownames = mat.GetRowNames();
        for (size_t i=0; i<nRows; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            str<<endl;
        }
        
    }


    template<class dataType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType> mat, const int& fieldWidth, const int& maxRows, const int& maxCols){

        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();

        // print colnames
        strVec colnames = mat.GetColNames();
        cout<<setw(fieldWidth)<<right<<"";
        for (size_t i=0; i<maxCols/2; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<setw(fieldWidth)<<"...";
        for (size_t i=nCols-maxCols/2-1; i<nCols; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<endl;


        // print the head of the matrix
        strVec rownames = mat.GetRowNames();
        for (size_t i=0; i<maxRows/2; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<maxCols/2; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            cout<<setw(fieldWidth)<<"...";
            for (size_t j=nCols-maxCols/2-1; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }

            str<<endl;
        }

        cout<<"."<<endl;
        cout<<"."<<endl;
        cout<<"."<<endl;

        // print the tail of the matrix
        for (size_t i=nRows-maxRows/2-1; i<nRows; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<maxCols/2; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            cout<<setw(fieldWidth)<<"...";
            for (size_t j=nCols-maxCols/2-1; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            str<<endl;
        }

    }
}


template<class dataType>
void LMatrix<dataType>::
ValidateObject() const{

    // check the underlying raw data
    itsRawData.ValidateObject();

    // check that the column labels have the right size
    if(itsRawData.GetNrCols() != itsColNames.size())
        throw string("ERROR:\tLength of column labels does not match number of data columns")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);

    // check that the row labels have the right size
    if(itsRawData.GetNrRows() != itsRowNames.size())
        throw string("ERROR:\tLength of row labels does not match number of rows in data")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
}


template<class dataType>
void LMatrix<dataType>::
SwapRows(const size_t& r1, const size_t& r2){

    // swap raw data
    itsRawData.SwapRows(r1, r2);

    // swap row labels
    string tmp = itsRowNames[r2];
    itsRowNames[r2] = itsRowNames[r1];
    itsRowNames[r1] = tmp;

    ValidateObject();
}


template<class dataType>
void LMatrix<dataType>::
SwapRows(const string& str1, const string& str2){
    vector<string>::iterator rowIter1 = find(itsRowNames.begin(), itsRowNames.end(), str1);
    vector<string>::iterator rowIter2 = find(itsRowNames.begin(), itsRowNames.end(), str2);

    if(rowIter1 == itsRowNames.end() || rowIter2 == itsRowNames.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + str1 +string(" and/or ")+ str2 +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t r1 = distance(itsRowNames.begin(), rowIter1);
    size_t r2 = distance(itsRowNames.begin(), rowIter2);

    return SwapRows(r1, r2);
}


template<class dataType>
void LMatrix<dataType>::
SwapCols(const string& str1, const string& str2){
    vector<string>::iterator colIter1 = find(itsColNames.begin(), itsColNames.end(), str1);
    vector<string>::iterator colIter2 = find(itsColNames.begin(), itsColNames.end(), str2);

    if(colIter1 == itsColNames.end() || colIter2 == itsColNames.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + str1 +string(" and/or ")+ str2 +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t c1 = distance(itsColNames.begin(), colIter1);
    size_t c2 = distance(itsColNames.begin(), colIter2);

    return SwapCols(c1, c2);
}


template<class dataType>
void LMatrix<dataType>::
SwapCols(const size_t &c1, const size_t &c2){

    // swap raw data
    itsRawData.SwapCols(c1, c2);

    // swap col labels
    string tmp = itsColNames[c2];
    itsColNames[c2] = itsColNames[c1];
    itsColNames[c1] = tmp;

    ValidateObject();
}


template<class dataType>
LMatrix<dataType>::
LMatrix(RawMatrix<dataType>& rawData, strVec& rowNames, strVec& colNames):
    itsRawData(rawData), itsRowNames(rowNames), itsColNames(colNames)
{
    ValidateObject();

}


template<class dataType>
const dataType& LMatrix<dataType>::
operator() (const std::string& rowName, const std::string& colName)const{

    // find mapping between string indices to location in the matrix
    vector<string>::iterator rowIter = find(itsRowNames.begin(), itsRowNames.end(), rowName);
    vector<string>::iterator colIter = find(itsColNames.begin(), itsColNames.end(), colName);

    if(rowIter == itsRowNames.end() || colIter == itsColNames.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + rowName +string(" and/or ")+colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t i = distance(itsRowNames.begin(), rowIter);
    size_t j = distance(itsColNames.begin(), colIter);
    return itsRawData(i, j);
}


template<class dataType>
dataType& LMatrix<dataType>::
operator() (const std::string& rowName, const std::string& colName){

    // find mapping between string indices to location in the matrix
    vector<string>::iterator rowIter = find(itsRowNames.begin(), itsRowNames.end(), rowName);
    vector<string>::iterator colIter = find(itsColNames.begin(), itsColNames.end(), colName);

    if(rowIter == itsRowNames.end() || colIter == itsColNames.end()){
        throw string("ERROR:\tElement ") + rowName +string(" and/or ")+colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t i = distance(itsRowNames.begin(), rowIter);
    size_t j = distance(itsColNames.begin(), colIter);
    return itsRawData(i, j);
}



template<class dataType>
ostream& operator<< (ostream& str,  LMatrix<dataType>& mat){

    // ASK: Ideally, these parameters should live in some config file. How do I do this?
    const int& fieldWidth = 20;
    const int& maxCols = 4;
    const int& maxRows = 10;
    const int& precision = 8;

    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Raw Data "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;

    str<<setprecision(precision);
    if(nRows<=maxRows && nCols<=maxCols){
        PrintSmallLMatrix(str, mat, fieldWidth);
    }else{
        PrintLargeLMatrix(str, mat, fieldWidth, maxRows, maxCols);
    }

    return str;
}


template<class dataType>
const std::vector<dataType>& LMatrix<dataType>::
row(const std::string& name) const{

    // check input
    strVec::iterator iElement = find(itsRowNames.begin(), itsRowNames.end(), name);
    if(iElement == itsRowNames.end()){
        throw string("ERROR:\tUnable to find rowname ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsRowNames.begin(), iElement);
    return row(idx);
}


template<class dataType>
std::vector<dataType>& LMatrix<dataType>::
row(const std::string& name){

    // check input
    strVec::iterator iElement = find(itsRowNames.begin(), itsRowNames.end(), name);
    if(iElement == itsRowNames.end()){
        throw string("ERROR:\tUnable to find rowname ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsRowNames.begin(), iElement);
    return row(idx);
}


template<class dataType>
vector<dataType> LMatrix<dataType>::
col(const std::string& name){

    // check input
    strVec::iterator iElement = find(itsColNames.begin(), itsColNames.end(), name);
    if(iElement == itsColNames.end()){
        throw string("ERROR:\tUnable to find a column named ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsColNames.begin(), iElement);
    return itsRawData.col(idx);
}



template<class dataType>
const std::vector<dataType> LMatrix<dataType>::
col(const std::string& name)const{

    // check input
    strVec::iterator iElement = find(itsColNames.begin(), itsColNames.end(), name);
    if(iElement == itsColNames.end()){
        throw string("ERROR:\tUnable to find a column named ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }
    size_t idx = distance(itsColNames.begin(), iElement);
    return itsRawData.col(idx);
}



#endif


