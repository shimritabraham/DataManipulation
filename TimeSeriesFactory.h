//
//  TimeSeriesFactory.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 16/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_TimeSeriesFactory_h
#define DataManipulation_TimeSeriesFactory_h

#include "TimeSeries.h"
#include "LMatrixFactory.h"
#include "StringLabels.h"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/shared_ptr.hpp"


namespace TimeSeriesFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class dataType, class dtContainerType, class dtElementType>
    pTS<dataType, dtContainerType, dtElementType>
    CreateTimeSeriesFromCsv(const string& fileName, const MatrixType mType, const string& dateTimeFormat, const bool hasColLabels = false);
}






namespace{

    template<class dataType, class dtContainerType, class dtElementType>
    boost::shared_ptr<TimeSeries<dataType, dtContainerType, dtElementType>>
    CreateSimpleTimeSeriesFromCsv(const string& fileName, const string& dateTimeFormat, const bool hasColLabels){

        // This is a simple TimeSeries implementation that is not optimised for speed.
        // The code is able to cope with and without the colnames being provided in the file

        typedef LMatrix<dataType, dtContainerType, dtElementType> LM;
        typedef TimeSeries<dataType, dtContainerType, dtElementType> TS;

        // Read and process the file, create an object of the base class
        boost::shared_ptr<LM> mat = LMatrixFactory::CreateLMatrixFromCsv<dataType, dtContainerType, dtElementType>(fileName, SIMPLE, hasColLabels, true, dateTimeFormat);


        // Create a TimeSeries object using the LMatric base object
        return boost::shared_ptr<TS>(new TS(mat));

    }

}



template<class dataType, class dtContainerType, class dtElementType>
pTS<dataType, dtContainerType, dtElementType> TimeSeriesFactory::
CreateTimeSeriesFromCsv(const string& fileName, const MatrixType mType, const string& dateTimeFormat, const bool hasColLabels){

    switch(mType){
        case(SIMPLE):
            return CreateSimpleTimeSeriesFromCsv<dataType, dtContainerType, dtElementType>(fileName, dateTimeFormat, hasColLabels);
            break;

        default:
            throw string("ERROR:\t This type of timeseries has not been implemented (yet)")+
            string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
            
            
    }
}


#endif
