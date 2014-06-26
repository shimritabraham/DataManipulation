//
//  LMatrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 05/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_LMatrix_h
#define DataManipulation_LMatrix_h

// ASK: How do I check whether I really need all these includes? Eclipse used to mark this very nicely in Python code. Not sure how to do this in Xcode. Can VS do this?
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include "FileInputManager.h"
#include "RawMatrix.h"
#include "boost/shared_ptr.hpp"
using namespace std;


// forward-declare the Labelled Matrix class (to enable creation of aliases)
template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
class LMatrix;

template<class x, class y, class z>
using pLMatrix = boost::shared_ptr<LMatrix<x, y, z>>;

template<class x, class y, class z>
using v_pLMatrix = vector<pLMatrix<x, y, z>>;

typedef vector<string> strVec;




template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
class LMatrix{

    // Please use the available LMatrixFactory functions to create instances of this class

public:

    typedef LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> LM;
    typedef boost::shared_ptr<LM> pLM;
    typedef boost::shared_ptr<RawMatrix<dataType>> pRM;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Note: LMatrix objects should be created via Factory functions, not via the constructor
    LMatrix(const RawMatrix<dataType>& rawData, const rowLabelCollectionType& rowNames, const strVec& colNames);
    LMatrix(const boost::shared_ptr<LM> mat);
    LMatrix();
    virtual ~LMatrix(){};



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
    ostream& head(ostream& stream, const size_t =5)const;
    ostream& tail(ostream& stream, const size_t =5)const;
    pLM cbind(const pLM rhs) const;


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

    // cout parameter settings, used to print and align the data nicely
    // ASK: Ideally, these parameters should live in some config file. How do I do this?
    const int fieldWidth = 20;
    const size_t maxCols = 4;
    const size_t maxRows = 10;
    const int precision = 8;

};





// Non-member functions
template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
pLMatrix<dataType, rowLabelCollectionType, rowLabelElementType>
join(v_pLMatrix< dataType, rowLabelCollectionType, rowLabelElementType>  vecOfMatrixPtrs);






// ------------------------------------------------------------
// Function definitions
// ------------------------------------------------------------


namespace{
    // Helper functions that can only be called from this file

    // Function Declarations
    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintSmallLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth);

    template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth, const size_t& maxRows, const size_t& maxCols, const bool printHead = true, const bool printTail = true);


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
    void PrintLargeLMatrix(ostream& str, LMatrix<dataType, rowLabelCollectionType, rowLabelElementType> mat, const int& fieldWidth, const size_t& maxRows, const size_t& maxCols, const bool printHead, const bool printTail){

        size_t nRows = mat.GetNrRows();
        size_t nCols = mat.GetNrCols();
        size_t startEndColIdx = std::max<size_t>(nCols-maxCols/2-1, maxCols/2); // needed for when there are not many columns

        // print colnames
        strVec colnames = mat.GetColLabels();
        cout<<setw(fieldWidth)<<right<<"";
        for (size_t i=0; i<maxCols/2; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        if(nCols>maxCols)
            cout<<setw(fieldWidth)<<"...";
        for (size_t i=startEndColIdx; i<nCols; i++){
            cout<<setw(fieldWidth)<<right<<colnames[i];
        }
        cout<<endl;

        size_t printRows;
        if(printHead && printTail){
             printRows = maxRows/2;
        }else{
            printRows = maxRows;
        }

        strVec rownames = mat.GetRowLabels().to_string();
        // print the head of the matrix
        if(printHead){
            for (size_t i=0; i<printRows; i++){
                cout<<setw(fieldWidth)<<right<<rownames[i];
                for (size_t j=0; j<maxCols/2; j++){
                    str<<setw(fieldWidth)<<right<<mat(i, j);
                }
                if(nCols>maxCols)
                    cout<<setw(fieldWidth)<<"...";
                for (size_t j=startEndColIdx; j<nCols; j++){
                    str<<setw(fieldWidth)<<right<<mat(i, j);
                }

                str<<endl;
            }
        }

        if(nRows>maxRows){
            cout<<"."<<endl;
            cout<<"."<<endl;
            cout<<"."<<endl;
        }

        if(printTail){
            // print the tail of the matrix
            for (size_t i=nRows-printRows-1; i<nRows; i++){
                cout<<setw(fieldWidth)<<right<<rownames[i];
                for (size_t j=0; j<maxCols/2; j++){
                    str<<setw(fieldWidth)<<right<<mat(i, j);
                }
                if(nCols>maxCols)
                    cout<<setw(fieldWidth)<<"...";
                for (size_t j=startEndColIdx; j<nCols; j++){
                    str<<setw(fieldWidth)<<right<<mat(i, j);
                }
                str<<endl;
            }
        }

    }
}



template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
pLMatrix<dataType, rowLabelCollectionType, rowLabelElementType>
join(v_pLMatrix< dataType, rowLabelCollectionType, rowLabelElementType>  vecOfMatrixPtrs){

    pLMatrix<dataType, rowLabelCollectionType, rowLabelElementType> result = vecOfMatrixPtrs[0];

    for(size_t i=1; i<vecOfMatrixPtrs.size(); i++){
        result = result->cbind(vecOfMatrixPtrs[i]);
    }

    return result;
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
boost::shared_ptr<  LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>  >
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
cbind(const pLM rhs) const {

    vector<string> newColLabels(itsColLabels);
    newColLabels.insert(newColLabels.end(),rhs->itsColLabels.begin(), rhs->itsColLabels.end());


    // simple case: labels of both objects are identical
    if (itsRowLabels.equal(rhs->itsRowLabels)){

        //  join the raw data
        pRM pRhsData(new RawMatrix<dataType> (rhs->itsRawData));
        pRM pJoinedRawData = itsRawData.cbind(pRhsData);

        // return a ptr to a new LMatrix object
        LM tmp =LM(*pJoinedRawData, itsRowLabels, newColLabels);
        return pLM(new LM(*pJoinedRawData, itsRowLabels, newColLabels));
    }

    // Join and sort the rowlabels from both objects
    rowLabelCollectionType newRowLabels = itsRowLabels.intersect(rhs->itsRowLabels);


    // select the right rows from lhs and rhs objects
    vector<size_t> rLabelIndices_lhs;
    vector<size_t> rLabelIndices_rhs;
    for(size_t i=0; i<newRowLabels.size(); i++){
        rLabelIndices_lhs.push_back(itsRowLabels.find(newRowLabels[i]));
        rLabelIndices_rhs.push_back(rhs->itsRowLabels.find(newRowLabels[i]));
    }
    
    pRM pRawData_lhs = itsRawData.GetSubsetOfRows(rLabelIndices_lhs);
    pRM pRawData_rhs = rhs->itsRawData.GetSubsetOfRows(rLabelIndices_rhs);

    // join the data
    pRM pJoinedRawData = pRawData_lhs->cbind(pRawData_rhs);

    // return a ptr to a new LMatrix object
    return pLM(new LM(*pJoinedRawData, newRowLabels, newColLabels));


}




template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
LMatrix(){
    // ASK: Would be good to do validation but it will fail.
    // Problem: I need this constructor elsewhere (do I really?)
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
LMatrix(const boost::shared_ptr<LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>> mat){
    itsRawData = mat->itsRawData;
    itsColLabels = mat->itsColLabels;
    itsRowLabels =mat->itsRowLabels;
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
LMatrix(const RawMatrix<dataType>& rawData, const rowLabelCollectionType& rowNames, const strVec& colNames):
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

    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Matrix "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;

    str<<setprecision(mat.precision);
    if(nRows<=mat.maxRows && nCols<=mat.maxCols){
        PrintSmallLMatrix(str, mat, mat.fieldWidth);
    }else{
        size_t adjMaxRows = std::min<size_t>(mat.maxRows, nRows);
        size_t adjMaxCols = std::min<size_t>(mat.maxCols, nCols);
        PrintLargeLMatrix(str, mat, mat.fieldWidth, adjMaxRows, adjMaxCols);
    }

    return str;
}


//<##>
template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
ostream& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
head(ostream& stream, const size_t n)const{

    size_t nRows = this->GetNrRows();
    size_t nCols = this->GetNrCols();

    stream<<"Matrix "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;
    stream<<setprecision(precision);
    size_t adjMaxRows = std::min<size_t>(n, nRows);
    size_t adjMaxCols = std::min<size_t>(maxCols, nCols);

    PrintLargeLMatrix(stream, *this, fieldWidth, adjMaxRows, adjMaxCols, true, false);

    return stream;
}


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
ostream& LMatrix<dataType, rowLabelCollectionType, rowLabelElementType>::
tail(ostream& stream, const size_t n)const{
    size_t nRows = this->GetNrRows();
    size_t nCols = this->GetNrCols();

    stream<<"Matrix "<<"("<<nRows<<"x"<<nCols<<"):"<<endl<<endl;
    stream<<setprecision(precision);
    size_t adjMaxRows = std::min<size_t>(n, nRows);
    size_t adjMaxCols = std::min<size_t>(maxCols, nCols);

    PrintLargeLMatrix(stream, *this, fieldWidth, adjMaxRows, adjMaxCols, false, true);

    return stream;

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



//LMatrix<class dataType, class dtContainerType, class dtElementType>
//Intersect(const LMatrix<dataType, dtContainerType, dtElementType>& ts1, const LMatrix<dataType, dtContainerType, dtElementType>& ts2){
//
//}





#endif


