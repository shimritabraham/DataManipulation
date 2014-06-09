//
//  RawMatrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 08/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_RawMatrix_h
#define DataManipulation_RawMatrix_h

#include<type_traits>
#include<string>
#include <boost/shared_ptr.hpp>
#include "FileInputManager.h"

template<class T>
class RawMatrix{
    // This should not be used directly by the user.
    // Instead, please create a Matrix object using the available MatrixFactory functions


    // FIXME: Initially, this class uses a vector of vectors to store matrix data. This can be expanded to gain more speed later.

public:
    // Con/Destructors
    RawMatrix(const string& fileName);
    RawMatrix(istream& ifstream);
    RawMatrix(boost::shared_ptr<vector<vector<T>>> pData);
    RawMatrix();
    ~RawMatrix(){};


    // accessors
    size_t GetNrCols() const {return ((*itsPRawMatrixData)[0]).size();};
    size_t GetNrRows() const {return (*itsPRawMatrixData).size();};

    const std::vector<T>& row(const int& idx) const;
          std::vector<T>& row(const int& idx);


    // operators -- read/write
    const T& operator() (const int& rowIdx, const int& colIdx)const;
    T& operator() (const int& rowIdx, const int& colIdx);


    // Utils functions
    template<class S>
    friend ostream& operator<< (ostream& str,  RawMatrix<S>& mat);
    void ValidateObject() const;
    void SwapRows(const int& r1, const int& r2);
    void SwapCols(const int& c1, const int& c2);

private:
    boost::shared_ptr<vector<vector<T>>> itsPRawMatrixData;


};


namespace{
    // Helper functions which are not meant to be called directly


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
            throw string("Inconsistent data types found in file ");

        // process string to make it easily convertible to a vector
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); //get rid of white space
        replace(line.begin(), line.end(), ',', ' ');
        stringstream in(line);

        // add row of data to result
        (*result).push_back(vector<T>(istream_iterator<T>(in), istream_iterator<T>()));
        
    }

    
}

template<class T>
const vector<T>& RawMatrix<T>::
row(const int& idx) const{
    return (*itsPRawMatrixData)[idx];
}


template<class T>
vector<T>& RawMatrix<T>::
row(const int& idx){
    return (*itsPRawMatrixData)[idx];
}

template<class T>
void RawMatrix<T>::
SwapRows(const int& r1, const int& r2){
    try{
        size_t nRows = GetNrRows();
        if(r1>=nRows || r2>=nRows){
            throw (string("Bounds error: Cannot swap rows ")+to_string(r1)+string(" and ") + to_string(r2));
        }

        vector<T> tmp = (*itsPRawMatrixData)[r2];
        (*itsPRawMatrixData)[r2] = (*itsPRawMatrixData)[r1];
        (*itsPRawMatrixData)[r1] = tmp;

        ValidateObject();
    }
    catch(string& err){
        cout<<err<<endl;
        exit(1);
    }
    catch(...){
        cout<<"Unknown Error occured in "<<__FILE__<<"; Row "<<__LINE__<<endl;
    }
}





template<class T>
void RawMatrix<T>::
ValidateObject() const{

    // check that there is at least one row
    size_t nRows = (*itsPRawMatrixData).size();
    if(nRows == 0)
        throw string("RawMatrix has zero rows");

    // check that there is at least one column
    size_t nCols = (*itsPRawMatrixData)[0].size();
    if(nCols == 0)
        throw string("RawMatrix has zero columns");

    // check that all columns are of equal size
    for(size_t i = 0; i<nCols; i++){
        if((*itsPRawMatrixData)[i].size() != nCols)
            throw string("Columns are not of equal size");
    }
}



template<class T>
T& RawMatrix<T>::
operator() (const int& rowIdx, const int& colIdx){
    return (*itsPRawMatrixData)[rowIdx][colIdx];
}

template<class T>
const T& RawMatrix<T>::
operator() (const int& rowIdx, const int& colIdx) const {
    return (*itsPRawMatrixData)[rowIdx][colIdx];
}


template<class T>
RawMatrix<T>::
RawMatrix(){
    // FIXME: Would be good to do validation but it will fail. Problem: I need this constructor elsewhere (do I?)
}

template<class T>
RawMatrix<T>::
RawMatrix(const string& fileName){

    try{
        // Read the file line by line and store the data in a vector of vectors where each row is a vector
        FileInputManager<T> fmgr(fileName);
        fmgr.ValidateObject();
        string line;
        boost::shared_ptr<vector<vector<T>>> pData(new vector<vector<T>>);

        while(getline(fmgr.GetStream(), line, '\r')){
            //keep incrementing the data container
            ProcessLine(pData, line);
        }

        itsPRawMatrixData=pData;

        // Check the integrity of the object
        ValidateObject();


    }catch (string&   str){
        cout<<str<<endl;
        exit(1);
    }
    catch(...){
        cout<<"Exception occured"<<endl;
        exit(1);
    }
}

template<class T>
RawMatrix<T>::
RawMatrix(istream& ifstream){

    try{
        // Read the file line by line and store the data in a vector of vectors where each row is a vector
        string line;
        boost::shared_ptr<vector<vector<T>>> pData(new vector<vector<T>>);

        while(getline(ifstream, line, '\r')){
            ProcessLine(pData, line);
        }

        itsPRawMatrixData=pData;

        // Check the integrity of the object
        ValidateObject();


    }catch (string&   str){
        cout<<str<<endl;
        exit(1);
    }
    catch(...){
        cout<<"Exception occured"<<endl;
        exit(1);
    }
}


template<class T>
RawMatrix<T>::
RawMatrix(boost::shared_ptr<vector<vector<T>>> pData){
    try{
        itsPRawMatrixData = pData;
        ValidateObject();
    }catch(string& str){
        cout <<str<<endl;
        exit(1);
    }
    catch(...){
        cout<<"Exception occured"<<endl;
        exit(1);
    }
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

#endif
