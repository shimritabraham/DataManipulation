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

namespace TimeSeriesFactory{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Factory function declarations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    template<class T>
    TimeSeries<T> CreateSimpleTimeSeriesFromCsv(const string& fileName, const bool& hasColLabels = false, const string dateTimeFormat);

}






#endif
