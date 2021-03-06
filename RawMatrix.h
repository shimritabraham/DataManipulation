//
//  RawMatrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 08/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_RawMatrix_h
#define DataManipulation_RawMatrix_h

#include <type_traits>
#include <string>
#include <boost/shared_ptr.hpp>
#include "FileInputManager.h"
#include "Utils.h"
#include <Eigen/Dense>


template<class T>
class RawMatrix{
    // This should not be used directly by the user.
    // Instead, please create a Matrix object using the available MatrixFactory functions



public:
    typedef boost::shared_ptr<RawMatrix<T>> pRM;
    typedef RawMatrix<T> RM;
    typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> eigenMatrix;

    // Con/Destructors
    RawMatrix(const string& fileName);
    RawMatrix(istream& ifstream);
    RawMatrix(const boost::shared_ptr <vector<vector<T>>>& pData);
    RawMatrix();
    RawMatrix(const size_t& nRows);
    ~RawMatrix(){};

    // Accessors
    size_t GetNrCols() const {return ((*itsPRawMatrixData)[0]).size();};
    size_t GetNrRows() const {return (*itsPRawMatrixData).size();};
    pRM GetSubsetOfRows(const vector<size_t> rowIndices) const;

    //ASK: return type is ref in row() and non-ref in col(). Can this be avoided?
    const vector<T>& row(const size_t& idx) const {return (*itsPRawMatrixData)[idx];}
          vector<T>& row(const size_t& idx)       {return (*itsPRawMatrixData)[idx];}
    const vector<T> col(const size_t& idx) const;
          vector<T> col(const size_t& idx);

    // Operators -- read/write
    const T& operator() (const size_t& rowIdx, const size_t& colIdx)const;
    T& operator() (const size_t& rowIdx, const size_t& colIdx);

    // Util functions
    void ValidateObject() const;
    void SwapRows(const size_t& r1, const size_t& r2);
    void SwapCols(const size_t& c1, const size_t& c2);
    void AppendToRow(const vector<T> vec, size_t idx);
    pRM cbind(const pRM rhs) const;
    eigenMatrix asEigenMatrix() const;

    // Friend Functions
    template<class S>
    friend ostream& operator<< (ostream& str,  RawMatrix<S>& mat);


private:
    boost::shared_ptr<vector<vector<T>>> itsPRawMatrixData;


};


namespace{
    // Helper functions which are not meant to be called directly

    // Function declarations:

    template<class T>
    void ProcessLine(boost::shared_ptr<vector<vector<T>>> result, string& line);
    bool OnlyNumbers(const string& str);


    // Function definitions

    bool OnlyNumbers(const string& str){
        // Are all characters either numeric, a space or a dot?
        // Helper function to read data and assert type consistency

        int sumNums = 0;
        for(size_t i = 0; i< str.size(); i++){
            if ((isnumber(str[i]) || isspace(str[i]) || str[i] == '.' || str[i] == ','))
                sumNums++;
        }
        return (sumNums == str.size());
    }


    template<class T>
    void ProcessLine(boost::shared_ptr<vector<vector<T>>> result, string& line){
        // check type consistency of this line: either everything is numeric, or not and T is string
        if(!OnlyNumbers(line) && !std::is_same<T, string>::value)
            throw string("ERROR:\tInconsistent data types found in file ")+
            string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);

        // process string to make it easily convertible to a vector
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); //get rid of white space
        replace(line.begin(), line.end(), ',', ' ');
        stringstream in(line);

        // add row of data to result
        (*result).push_back(vector<T>(istream_iterator<T>(in), istream_iterator<T>()));
    }
}



template<class T>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> RawMatrix<T>::
asEigenMatrix() const{

    typedef Eigen::Matrix<T, Eigen::Dynamic, 1> VectorX;

    size_t nRows = GetNrRows();
    size_t nCols = GetNrCols();

    eigenMatrix result(nRows, nCols);
    for (size_t i=0; i<nRows; i++){
        result.row(i) = VectorX::Map(&(*itsPRawMatrixData)[i][0],(*itsPRawMatrixData)[i].size());
    }

    return result;


}



template<class T>
boost::shared_ptr<RawMatrix<T>> RawMatrix<T>::
GetSubsetOfRows(const vector<size_t> rowIndices) const{

    pRM result(new RawMatrix<T>(rowIndices.size()));
    for(size_t i=0; i<rowIndices.size(); i++){
        result->row(i) = this->row(rowIndices[i]);
    }
    result->ValidateObject();
    return result;
}


template<class T>
void RawMatrix<T>::
AppendToRow(const vector<T> vec, size_t idx){
    typename vector<T>::const_iterator it = row(idx).end();
    row(idx).insert(it, vec.begin(), vec.end());
}



template<class T>
boost::shared_ptr<RawMatrix<T>>  RawMatrix<T>::
cbind(const pRM rhs) const{
    // ASK: How do I check that the matrices to be joined have similar elements (same type)? or is that already guaranteed?

    size_t nRows = GetNrRows();

    // check that both matrices have the same nr of rows
    if(nRows != rhs->GetNrRows()){
        throw string("ERROR:\tUnable to join two raw matrices with unequal nr of rows")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // make sure there is at least one row to join
    if(nRows == 0){
        throw string("ERROR:\tZero rows to join. Not implemented yet")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    RM lhs = *this;

    // join each row
    pRM result(new RM(nRows));
    for(size_t i=0; i<nRows; i++){
        result->row(i) = row(i);
        result->AppendToRow(rhs->row(i), i);
    }

    // Sanity check
    result->ValidateObject();

    return result;
}



template<class T>
void RawMatrix<T>::
SwapRows(const size_t& r1, const size_t& r2){
    size_t nRows = GetNrRows();

    // check input
    if(r1>=nRows || r2>=nRows){
        throw (string("ERROR:\tCannot swap rows ")+to_string(r1)+string(" and ") + to_string(r2))+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // swap rows
    vector<T> tmp = (*itsPRawMatrixData)[r2];
    (*itsPRawMatrixData)[r2] = (*itsPRawMatrixData)[r1];
    (*itsPRawMatrixData)[r1] = tmp;

    ValidateObject();
}


template<class T>
void RawMatrix<T>::
SwapCols(const size_t &c1, const size_t &c2){

    // check input
    size_t nCols = GetNrCols();
    if(c1>=nCols || c2>=nCols){
        throw (string("ERROR:\tCannot swap cols ")+to_string(c1)+string(" and ") + to_string(c2))+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }

    // swap columns
    vector<T> orgCol1 = col(c1);
    size_t nRows = GetNrRows();
    for (size_t i=0; i<nRows; i++){
        (*itsPRawMatrixData)[i].at(c1) =(*itsPRawMatrixData)[i][c2];
        (*itsPRawMatrixData)[i].at(c2) = orgCol1[i];
    }

    ValidateObject();
}


template<class T>
void RawMatrix<T>::
ValidateObject() const{

    // check that there is at least one row
    size_t nRows = (*itsPRawMatrixData).size();
    if(nRows == 0)
        throw string("ERROR:\tRawMatrix has zero rows")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);

    // check that there is at least one column
    size_t nCols = (*itsPRawMatrixData)[0].size();
    if(nCols == 0)
        throw string("ERROR:\tRawMatrix has zero columns")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);

    // check that all rows are of equal size
    for(size_t i = 0; i<nRows; i++){
        if((*itsPRawMatrixData)[i].size() != nCols)
            throw string("ERROR:\tColumns are not of equal size")+
            string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
    }
}


template<class T>
T& RawMatrix<T>::
operator() (const size_t& rowIdx, const size_t& colIdx){
    return (*itsPRawMatrixData)[rowIdx][colIdx];
}


template<class T>
const T& RawMatrix<T>::
operator() (const size_t& rowIdx, const size_t& colIdx) const {
    return (*itsPRawMatrixData)[rowIdx][colIdx];
}


template<class T>
RawMatrix<T>::
RawMatrix(){
    // ASK: Would be good to do validation but it will fail because it isn't a proper matrix yet.
    // Problem: I need this constructor elsewhere (do I really?)
}

//<##>
template<class T>
RawMatrix<T>::
RawMatrix(const size_t& nRows){
    itsPRawMatrixData = boost::shared_ptr<vector<vector<T>>>(new vector<vector<T>>);
    itsPRawMatrixData->resize(nRows);
}

template<class T>
RawMatrix<T>::
RawMatrix(const string& fileName){

    // Read the file line by line and store the data in a vector of vectors where each row is a vector

    FileInputManager fmgr(fileName);
    fmgr.ValidateObject();
    string line;
    boost::shared_ptr<vector<vector<T>>> pData(new vector<vector<T>>);

    while(getline(fmgr.GetStream(), line, '\n')){
        //keep incrementing the data container
        ProcessLine(pData, line);
    }

    itsPRawMatrixData=pData;

    // Check the integrity of the object
    ValidateObject();

}


template<class T>
RawMatrix<T>::
RawMatrix(istream& ifstream){

    // Read the file line by line and store the data in a vector of vectors where each row is a vector
    string line;
    boost::shared_ptr<vector<vector<T>>> pData(new vector<vector<T>>);

    while(getline(ifstream, line, '\n')){
        ProcessLine(pData, line);
    }

    itsPRawMatrixData=pData;

    // Check the integrity of the object
    ValidateObject();
}


template<class T>
RawMatrix<T>::
RawMatrix(const boost::shared_ptr<vector<vector<T>>>& pData){
    itsPRawMatrixData = pData;
    ValidateObject();
}


template<class S>
ostream& operator<< (ostream& str,  RawMatrix<S>& mat){
    size_t nRows = mat.GetNrRows();
    size_t nCols = mat.GetNrCols();
    str<<"Raw Data "<<"("<<nRows<<"x"<<nCols<<"):"<<endl;
    for (int i=0; i<nRows; i++){
        for (int j=0; j<nCols; j++){
            str<<'\t'<<mat(i, j);
            // only print a comma if there's another number to print
            if (j < nCols-1)
                cout<<", ";
        }
        str<<endl;
    }
    return str;
}


template<class T>
vector<T> RawMatrix<T>::
col(const size_t& idx){
    size_t nRows = GetNrRows();
    vector<T> result;

    for (size_t i=0; i<nRows; i++){
        result.push_back((*itsPRawMatrixData)[i][idx]);
    }
    return result;
}


template<class T>
const vector<T> RawMatrix<T>::
col(const size_t& idx) const{
    size_t nRows = GetNrRows();
    vector<T> result;

    for (size_t i=0; i<nRows; i++){
        result.push_back((*itsPRawMatrixData)[i][idx]);
    }
    return result;
}


#endif
