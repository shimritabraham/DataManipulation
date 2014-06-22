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


namespace TimeSeriesFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class dataType, class dtContainerType, class dtElementType>
    TimeSeries<dataType, dtContainerType, dtElementType> CreateSimpleTimeSeriesFromCsv(const string& fileName, const string& dateTimeFormat, const bool hasColLabels = false);



}

template<class dataType, class dtContainerType, class dtElementType>
TimeSeries<dataType, dtContainerType, dtElementType> TimeSeriesFactory::
CreateSimpleTimeSeriesFromCsv(const string& fileName, const string& dateTimeFormat, const bool hasColLabels){

    // This is a simple TimeSeries implementation that is not optimised for speed.
    // The code is able to cope with and without the colnames being provided in the file

    typedef LMatrix<dataType, dtContainerType, dtElementType> LM;
    typedef TimeSeries<dataType, dtContainerType, dtElementType> TS;

    // Read and process the file, create an object of the base class
    LM mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<dataType, dtContainerType, dtElementType>(fileName, hasColLabels, true, dateTimeFormat);


    // Create a TimeSeries object using the LMatric base object
    TS ts(mat);

    return ts;

}



#endif
