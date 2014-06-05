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

namespace MatrixUtils {

    template<class T>
    class Matrix{

        public:

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~ Con/De structors ~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        Matrix(const std::string& filename, const T& type);
        Matrix(const std::ifstream, const T& type);
        ~Matrix(){}

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~ Member Functions ~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // accessors
        int GetNrCols() const;
        int GetNrRows() const;

        // printing
        std::ostream& operator<< (std::ostream& out);

        // operators -- read/write
        const std::vector<T>& operator() (const int& rowIdx, const int& colIdx)const;
              std::vector<T>& operator() (const int& rowIdx, const int& colIdx);
        const std::vector<T>& operator() (const std::string& rowName, const std::string& colName)const ;
              std::vector<T>& operator() (const std::string& rowName, const std::string& colName);

        const std::vector<T>& row(const int& idx) const;
              std::vector<T>& row(const int& idx);
        const std::vector<T>& row(const std::string& name) const;
              std::vector<T>& row(const std::string& name);

        const std::vector<T>& col(const int& idx) const;
              std::vector<T>& col(const int& idx);
        const std::vector<T>& col(const std::string& name) const;
              std::vector<T>& col(const std::string& name);

        // Utils
        void SortByRowLabels();

        private:
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~ Data Members ~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        std::vector<std::vector<T>> mRawData;       // Each column is a vector --> extendable to diff types per column
        std::vector<std::string> mRowNames;
        std::vector<std::string> mColNames;
    };

    template<class T>
    Matrix<T> intersect(const Matrix<T>& mat, const std::vector<std::string>& labels);



}
#endif
