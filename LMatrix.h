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

template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
class LMatrix{

    // Please use the available LMatrixFactly functions to create instances of this class

public:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Note: LMatrix objects should be created via Factory functions, not via the constructor
    LMatrix(RawMatrix<dataType>& rawData, rowLabelCollectionType& rowNames, strVec& colNames);
    ~LMatrix(){}


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Member Functions ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // accessors
    RawMatrix<dataType> GetRawData(){  return itsRawData;}
    size_t GetNrCols()                    const {return itsRawData.GetNrCols();}
    size_t GetNrRows()                    const {return itsRawData.GetNrRows();}
    strVec GetColLabels()                 const{return itsColLabels;}
    rowLabelCollectionType GetRowLabels() const{return itsRowLabels;}

    // printing
    std::ostream& operator<< (std::ostream& out);

    // operators -- read/write
    const dataType& operator() (const size_t& rowIdx, const size_t& colIdx)const {return itsRawData(rowIdx, colIdx);};
          dataType& operator() (const size_t& rowIdx, const size_t& colIdx)      {return itsRawData(rowIdx, colIdx);};
    const dataType& operator() (const rowLabelElementType& rowName, const std::string& colName)const ;
          dataType& operator() (const rowLabelElementType& rowName, const std::string& colName);

    const std::vector<dataType>& row(const size_t& idx) const  {return itsRawData.row(idx);}
          std::vector<dataType>& row(const size_t& idx)        {return itsRawData.row(idx);}
    const std::vector<dataType>& row(const rowLabelElementType& name) const;
          std::vector<dataType>& row(const rowLabelElementType& name);

    //ASK: return type is ref in row() and non-ref in col(). Can this be avoided?
    const std::vector<dataType> col(const size_t& idx) const   {return itsRawData.col(idx);}
          std::vector<dataType> col(const size_t& idx)         {return itsRawData.col(idx);}
    const std::vector<dataType> col(const std::string& name) const;
          std::vector<dataType> col(const std::string& name);

    // Utils
    void ValidateObject() const;
    void SwapRows(const size_t& r1, const size_t& r2);
    void SwapRows(const rowLabelElementType& str1, const rowLabelElementType& str2);
    void SwapCols(const size_t& c1, const size_t& c2);
    void SwapCols(const string& str1, const string& str2);

    // Friends
    template<class dt, class rlct, class rlet>
    friend ostream& operator<< (ostream& str,  LMatrix<dt, rlct, rlet>& mat);


private:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Data Members ~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    RawMatrix<dataType> itsRawData;  // this can potentially be templetized later
    rowLabelCollectionType itsRowLabels;
    strVec itsColLabels;
};





namespace{
    // Helper functions that can only be called from this file

    // Function Declarations
    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintSmallLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth);
    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth, const int& maxRows, const int& maxCols);


    // Function Definitions
    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintSmallLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth){
        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();

        // print colnames
        strVec colnames = mat.GetColLabels();
        cout<<setw(fieldWidth)<<right<<"";
        for (size_t i=0; i<nCols; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<endl;

        // print rownames and data row by row
        strVec rownames = mat.GetRowLabels();
        for (size_t i=0; i<nRows; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            str<<endl;
        }
        
    }


    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth, const int& maxRows, const int& maxCols){

        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();

        // print colnames
        strVec colnames = mat.GetColLabels();
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
        strVec rownames = mat.GetRowLabels();
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


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
void LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
ValidateObject() const{

    // check the underlying raw data
    itsRawData.ValidateObject();

    // check that the column labels have the right size
    if(itsRawData.GetNrCols() != itsColLabels.size())
        throw string("ERROR:\tLength of column labels does not match number of data columns")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);

    // check that the row labels have the right size
    if(itsRawData.GetNrRows() != itsRowLabels.size())
        throw string("ERROR:\tLength of row labels does not match number of rows in data")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
void LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
SwapRows(const size_t& r1, const size_t& r2){

    // swap raw data
    itsRawData.SwapRows(r1, r2);

    // swap row labels
    string tmp = itsRowLabels[r2];
    itsRowLabels[r2] = itsRowLabels[r1];
    itsRowLabels[r1] = tmp;

    ValidateObject();
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
void LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
SwapRows(const rowLabelElementType& str1, const rowLabelElementType& str2){
    typename rowLabelCollectionType::iterator rowIter1 = find(itsRowLabels.begin(), itsRowLabels.end(), str1);
    typename rowLabelCollectionType::iterator rowIter2 = find(itsRowLabels.begin(), itsRowLabels.end(), str2);

    if(rowIter1 == itsRowLabels.end() || rowIter2 == itsRowLabels.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + str1 +string(" and/or ")+ str2 +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t r1 = distance(itsRowLabels.begin(), rowIter1);
    size_t r2 = distance(itsRowLabels.begin(), rowIter2);

    return SwapRows(r1, r2);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
void LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
SwapCols(const string& str1, const string& str2){
    vector<string>::iterator colIter1 = find(itsColLabels.begin(), itsColLabels.end(), str1);
    vector<string>::iterator colIter2 = find(itsColLabels.begin(), itsColLabels.end(), str2);

    if(colIter1 == itsColLabels.end() || colIter2 == itsColLabels.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + str1 +string(" and/or ")+ str2 +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t c1 = distance(itsColLabels.begin(), colIter1);
    size_t c2 = distance(itsColLabels.begin(), colIter2);

    return SwapCols(c1, c2);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
void LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
SwapCols(const size_t &c1, const size_t &c2){

    // swap raw data
    itsRawData.SwapCols(c1, c2);

    // swap col labels
    string tmp = itsColLabels[c2];
    itsColLabels[c2] = itsColLabels[c1];
    itsColLabels[c1] = tmp;

    ValidateObject();
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
LMatrix(RawMatrix<dataType>& rawData, rowLabelCollectionType& rowNames, strVec& colNames):
    itsRawData(rawData), itsRowLabels(rowNames), itsColLabels(colNames)
{
    ValidateObject();

}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const dataType& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
operator() (const rowLabelElementType& rowName, const std::string& colName)const{

    // find mapping between string indices to location in the matrix
    typename rowLabelCollectionType::iterator rowIter = find(itsRowLabels.begin(), itsRowLabels.end(), rowName);
    vector<string>::iterator colIter = find(itsColLabels.begin(), itsColLabels.end(), colName);

    if(rowIter == itsRowLabels.end() || colIter == itsColLabels.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + rowName +string(" and/or ")+colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t i = distance(itsRowLabels.begin(), rowIter);
    size_t j = distance(itsColLabels.begin(), colIter);
    return itsRawData(i, j);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
dataType& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
operator() (const rowLabelElementType& rowName, const std::string& colName){

    // find mapping between string indices to location in the matrix
    typename rowLabelCollectionType::iterator rowIter = find(itsRowLabels.begin(), itsRowLabels.end(), rowName);
    vector<string>::iterator colIter = find(itsColLabels.begin(), itsColLabels.end(), colName);

    if(rowIter == itsRowLabels.end() || colIter == itsColLabels.end()){
        throw string("ERROR:\tElement ") + rowName +string(" and/or ")+colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t i = distance(itsRowLabels.begin(), rowIter);
    size_t j = distance(itsColLabels.begin(), colIter);
    return itsRawData(i, j);
}



template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
ostream& operator<< (ostream& str,  LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>& mat){

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


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const vector<dataType>& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const rowLabelElementType& name) const{

    // check input
    typename rowLabelCollectionType::iterator iElement = find(itsRowLabels.begin(), itsRowLabels.end(), name);
    if(iElement == itsRowLabels.end()){
        throw string("ERROR:\tUnable to find rowname ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsRowLabels.begin(), iElement);
    return row(idx);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
vector<dataType>& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const rowLabelElementType& name){

    // check input
    typename rowLabelCollectionType::iterator iElement = find(itsRowLabels.begin(), itsRowLabels.end(), name);
    if(iElement == itsRowLabels.end()){
        throw string("ERROR:\tUnable to find rowname ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsRowLabels.begin(), iElement);
    return row(idx);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
vector<dataType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const std::string& name){

    // check input
    strVec::iterator iElement = find(itsColLabels.begin(), itsColLabels.end(), name);
    if(iElement == itsColLabels.end()){
        throw string("ERROR:\tUnable to find a column named ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    size_t idx = distance(itsColLabels.begin(), iElement);
    return itsRawData.col(idx);
}



template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const std::vector<dataType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const std::string& name)const{

    // check input
    strVec::iterator iElement = find(itsColLabels.begin(), itsColLabels.end(), name);
    if(iElement == itsColLabels.end()){
        throw string("ERROR:\tUnable to find a column named ")+name+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }
    size_t idx = distance(itsColLabels.begin(), iElement);
    return itsRawData.col(idx);
}



#endif


