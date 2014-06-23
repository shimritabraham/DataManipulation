//
//  LMatrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_LMatrix_h
#define DataManipulation_LMatrix_h

// FIXME: Check whether you really need all these includes
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <iomanip>
#include <iterator>
#include "FileInputManager.h"
#include "RawMatrix.h"
#include "boost/shared_ptr.hpp"
using namespace std;

typedef vector<string> strVec;

template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
class LMatrix{

    // Please use the available LMatrixFactly functions to create instances of this class

public:

    typedef LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LM;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Note: LMatrix objects should be created via Factory functions, not via the constructor
    LMatrix(RawMatrix<dataType>& rawData, rowLabelCollectionType& rowNames, strVec& colNames);
    LMatrix(const LM& mat);
    LMatrix();
    ~LMatrix(){};



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

    // operators -- read/write matrix elements, rows or columns
    const dataType& operator() (const size_t& rowIdx, const size_t& colIdx)const {return itsRawData(rowIdx, colIdx);};
          dataType& operator() (const size_t& rowIdx, const size_t& colIdx)      {return itsRawData(rowIdx, colIdx);};
    const dataType& operator() (const rowLabelElementType& rowName, const std::string& colName)const ;
          dataType& operator() (const rowLabelElementType& rowName, const std::string& colName);


    const std::vector<dataType>& raw_row(const size_t& idx) const  {return itsRawData.row(idx);}
          std::vector<dataType>& raw_row(const size_t& idx)        {return itsRawData.row(idx);}
    const std::vector<dataType>& raw_row(const rowLabelElementType& name) const;
          std::vector<dataType>& raw_row(const rowLabelElementType& name);
    const LM row(const rowLabelElementType& name) const;
          LM row(const rowLabelElementType& name);
    const LM row(const size_t& idx) const;
          LM row(const size_t& idx);


    //ASK: return type is ref in raw_row() and non-ref in raw_col(). Can this be avoided?
    const std::vector<dataType> raw_col(const size_t& idx) const   {return itsRawData.col(idx);}
          std::vector<dataType> raw_col(const size_t& idx)         {return itsRawData.col(idx);}
    const std::vector<dataType> raw_col(const std::string& name) const;
          std::vector<dataType> raw_col(const std::string& name);
    const LM col(const string& name) const;
          LM col(const string& name);
    const LM col(const size_t& idx) const;
          LM col(const size_t& idx);


    // Utils
    void ValidateObject() const;
    void SwapRows(const size_t& r1, const size_t& r2);
    void SwapRows(const rowLabelElementType& str1, const rowLabelElementType& str2);
    void SwapCols(const size_t& c1, const size_t& c2);
    void SwapCols(const string& str1, const string& str2);

    // Friends
    template<class dt, class rlct, class rlet>
    friend ostream& operator<< (ostream& str,  LMatrix<dt, rlct, rlet>& mat);


protected:
    bool is_sorted() const {return itsRowLabels.is_sorted();}
    bool is_unique() const {return itsRowLabels.is_unique();}



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
        strVec rownames = mat.GetRowLabels().to_string();
        for (size_t i=0; i<nRows; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            str<<endl;
        }
        
    }


    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth, const size_t& maxRows, const size_t& maxCols){

        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();

        // print colnames
        strVec colnames = mat.GetColLabels();
        cout<<setw(fieldWidth)<<right<<"";
        for (size_t i=0; i<maxCols/2; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        if(nCols>maxCols)
            cout<<setw(fieldWidth)<<"...";
        for (size_t i=nCols-maxCols/2-1; i<nCols; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<endl;


        // print the head of the matrix
        strVec rownames = mat.GetRowLabels().to_string();
        for (size_t i=0; i<maxRows/2; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<maxCols/2; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            if(nCols>maxCols)
                cout<<setw(fieldWidth)<<"...";
            for (size_t j=nCols-maxCols/2-1; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }

            str<<endl;
        }


        if(nRows>maxRows){
            cout<<"."<<endl;
            cout<<"."<<endl;
            cout<<"."<<endl;
        }

        // print the tail of the matrix
        for (size_t i=nRows-maxRows/2-1; i<nRows; i++){
            cout<<setw(fieldWidth)<<right<<rownames[i];
            for (size_t j=0; j<maxCols/2; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            if(nCols>maxCols)
                cout<<setw(fieldWidth)<<"...";
            for (size_t j=nCols-maxCols/2-1; j<nCols; j++){
                str<<setw(fieldWidth)<<right<<mat(i, j);
            }
            str<<endl;
        }

    }
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
LMatrix(){
    // FIXME: Would be good to do validation but it will fail.
    // Problem: I need this constructor elsewhere (do I really?)
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
LMatrix(const LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>& mat){
    itsRawData = mat.itsRawData;
    itsColLabels = mat.itsColLabels;
    itsRowLabels =mat.itsRowLabels;
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

    size_t r1 = itsRowLabels.find(str1);
    size_t r2 = itsRowLabels.find(str2);

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
    vector<string>::iterator colIter = find(itsColLabels.begin(), itsColLabels.end(), colName);
    if(colIter == itsColLabels.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t j = distance(itsColLabels.begin(), colIter);
    size_t i = itsRowLabels.find(rowName);

    return itsRawData(i, j);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
dataType& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
operator() (const rowLabelElementType& rowName, const std::string& colName){


    // find mapping between string indices to location in the matrix
    vector<string>::iterator colIter = find(itsColLabels.begin(), itsColLabels.end(), colName);
    if(colIter == itsColLabels.end()){
        throw string("ERROR:\tBoundary exceeded. \nElement ") + colName +string(" cannot be found")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // find the element in the underlying raw data
    size_t j = distance(itsColLabels.begin(), colIter);
    size_t i = itsRowLabels.find(rowName);

    return itsRawData(i, j);

}



template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
ostream& operator<< (ostream& str,  LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>& mat){



    // ASK: Ideally, these parameters should live in some config file. How do I do this?
    const int& fieldWidth = 20;
    const size_t& maxCols = 4;
    const size_t& maxRows = 10;
    const int& precision = 8;


    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Raw Data "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;

    str<<setprecision(precision);
    if(nRows<=maxRows && nCols<=maxCols){
        PrintSmallLMatrix(str, mat, fieldWidth);
    }else{
        size_t adjMaxRows = std::min<size_t>(maxRows, nRows);
        size_t adjMaxCols = std::min<size_t>(maxCols, nCols);
        PrintLargeLMatrix(str, mat, fieldWidth, adjMaxRows, adjMaxCols);
    }

    return str;
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const vector<dataType>& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
raw_row(const rowLabelElementType& name) const{
    size_t idx = itsRowLabels.find(name);
    return raw_row(idx);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
vector<dataType>& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
raw_row(const rowLabelElementType& name){

    size_t idx = itsRowLabels.find(name);
    return raw_row(idx);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
vector<dataType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
raw_col(const std::string& name){

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
raw_col(const std::string& name)const{

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
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const rowLabelElementType& name){

    // extract the raw row data
    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    pRawData->push_back(raw_row(name));
    RawMatrix<dataType> RM(pRawData);

    // create row label object
    vector<rowLabelElementType> rowNameVec = {name};
    rowLabelCollectionType rowNameContainer(rowNameVec);

    return LMatrix(RM, rowNameContainer, itsColLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const rowLabelElementType& name) const{

    // extract the raw row data
    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    pRawData->push_back(raw_row(name));
    RawMatrix<dataType> RM(pRawData);

    // create row label object
    vector<rowLabelElementType> rowNameVec = {name};
    rowLabelCollectionType rowNameContainer(rowNameVec);

    return LMatrix(RM, rowNameContainer, itsColLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const size_t& idx){

    // extract the raw row data
    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    pRawData->push_back(raw_row(idx));
    RawMatrix<dataType> RM(pRawData);

    // create row label object
    vector<rowLabelElementType> rowNameVec = {itsRowLabels[idx]};
    rowLabelCollectionType rowNameContainer(rowNameVec);

    return LMatrix(RM, rowNameContainer, itsColLabels);
}



template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
row(const size_t& idx) const{

    // extract the raw row data
    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    pRawData->push_back(raw_row(idx));
    RawMatrix<dataType> RM(pRawData);

    // create row label object
    vector<rowLabelElementType> rowNameVec = {itsRowLabels[idx]};
    rowLabelCollectionType rowNameContainer(rowNameVec);

    return LMatrix(RM, rowNameContainer, itsColLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const string& name){
    vector<dataType> raw_data = raw_col(name);

    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    for (size_t i=0; i<raw_data.size(); i++){
        vector<dataType> x = {raw_data[i]};
        pRawData->push_back(x);
    }
    RawMatrix<dataType> RM(pRawData);
    vector<string> colLabels = {name};

    return LMatrix(RM, itsRowLabels, colLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const string& name) const {
    vector<dataType> raw_data = raw_col(name);

    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    for (size_t i=0; i<raw_data.size(); i++){
        vector<dataType> x = {raw_data[i]};
        pRawData->push_back(x);
    }
    RawMatrix<dataType> RM(pRawData);
    vector<string> colLabels = {name};

    return LMatrix(RM, itsRowLabels, colLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const size_t& idx){
    vector<dataType> raw_data = raw_col(idx);

    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    for (size_t i=0; i<raw_data.size(); i++){
        vector<dataType> x = {raw_data[i]};
        pRawData->push_back(x);
    }
    RawMatrix<dataType> RM(pRawData);
    vector<string> colLabels = {itsColLabels[idx]};

    return LMatrix(RM, itsRowLabels, colLabels);
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
const LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
col(const size_t& idx) const {
    vector<dataType> raw_data = raw_col(idx);

    boost::shared_ptr <vector<vector<dataType>>> pRawData(new vector<vector<dataType>>);
    for (size_t i=0; i<raw_data.size(); i++){
        vector<dataType> x = {raw_data[i]};
        pRawData->push_back(x);
    }
    RawMatrix<dataType> RM(pRawData);
    vector<string> colLabels = {itsColLabels[idx]};

    return LMatrix(RM, itsRowLabels, colLabels);
}
#endif


