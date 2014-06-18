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
    TimeSeries<dataType, dtContainerType, dtElementType>
    CreateSimpleTimeSeriesFromCsv(const string& fileName, const string& dateTimeFormat, const bool hasColLabels = false);



}


namespace{
    // Hidden functions, can only be used in this file

    template<class dtElementType>
    dtElementType StringToDateTimes(const string& strDate, const string& dateTimeFormat ){
        // ASK: This seems very convoluted but I haven't found a cleaner way to do this. Any idea?

        boost::posix_time::ptime dt(boost::posix_time::not_a_date_time);
        std::stringstream ss;
        boost::local_time::local_time_input_facet* myFacet(new boost::local_time::local_time_input_facet(dateTimeFormat));
        ss.imbue(std::locale(std::locale::classic(), myFacet));
        ss.str(strDate);
        ss >> dt;
        return dt;
    }


    template<class dtContainerType, class dtElementType>
    dtContainerType StringVectorToDateTimes(const vector<string> strVec, const string& dateTimeFormat){

        // Validate the dateTimeFormat and strVec input parameters
        if(strVec.size() == 0 || dateTimeFormat.size() == 0){
            throw string("ERROR:\tInput parameters strVec and/or dateTimeFormat are of length zero")+
            string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+to_string(__LINE__);
        }

        // Convert the string dates to dtElementType's
        dtContainerType result;
        for(size_t i=0; i<strVec.size(); i++){
            result.push_back(StringToDateTimes<dtElementType>(strVec[i], dateTimeFormat));
        }
        
        return result;
    }

}



template<class dataType, class dtContainerType, class dtElementType>
TimeSeries<dataType, dtContainerType, dtElementType> TimeSeriesFactory::
CreateSimpleTimeSeriesFromCsv(const string& fileName, const string& dateTimeFormat, const bool hasColLabels){
    // This is a simple TimeSeries implementation that is not optimised for speed.
    // The code is able to cope with and without the colnames being provided in the file

    TimeSeries<dataType, dtContainerType, dtElementType> result;

    // Read and process the file, create an object of the base class with strings as row labels
    LMatrix<dataType, StringLabels, string> mat = LMatrixFactory::CreateSimpleLMatrixFromCsv<dataType, StringLabels, string>(fileName, hasColLabels, true);


//    // Change the row labels from strings into dtElementType's
//    StringLabels orgRowLabels = mat.GetRowLabels();
//    dtContainerType dts = StringVectorToDateTimes<dtContainerType, dtElementType>(orgRowLabels, dateTimeFormat);

//    // Create a TimeSeries object

 
    // Create a TimeSeries object


    return result;

}



#endif
