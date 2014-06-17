//
//  TimeSeries.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 16/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_TimeSeries_h
#define DataManipulation_TimeSeries_h

#include "LMatrix.h"
typedef vector<string> strVec;

template<class dataType, class dtContainerType, class dtElementType>
class TimeSeries: public LMatrix<dataType, dtContainerType, dtElementType>{
    // a TimeSeries object is a special kind of Labelled Matrix where the rownames represent timestamps

public:
    TimeSeries(RawMatrix<dataType>& rawData, dtContainerType& rowNames, strVec& colNames);
    TimeSeries():LMatrix<dataType, dtContainerType, dtElementType>(){};
    ~TimeSeries(){};


    // Util functions:
    void ValidateObject();
    bool IsSorted();
    bool IsUnique();
    void Sort();

    //FIXME: check if cout works


};

// Non-Member Functions:
TimeSeries<class dataType, class dtContainerType, class dtElementType>
LeftJoin(const TimeSeries<dataType, dtContainerType, dtElementType>& LHS_ts, const TimeSeries<dataType, dtContainerType, dtElementType>& RHS_ts);

TimeSeries<class dataType, class dtContainerType, class dtElementType>
Intersect(const TimeSeries<dataType, dtContainerType, dtElementType>& ts1, const TimeSeries<dataType, dtContainerType, dtElementType>& ts2);

TimeSeries<class dataType, class dtContainerType, class dtElementType>
Union(const TimeSeries<dataType, dtContainerType, dtElementType>& ts1, const TimeSeries<dataType, dtContainerType, dtElementType>& ts2);











#endif
