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

    typedef LMatrix<dataType, dtContainerType, dtElementType> LM;

public:
    TimeSeries(RawMatrix<dataType>& rawData, dtContainerType& rowNames, strVec& colNames);
    TimeSeries(LM mat);
    TimeSeries():LM(){};
    ~TimeSeries(){};


    // Util functions:
    void ValidateObject() const;
    bool is_sorted()      const{return LM::is_sorted();}
    bool is_unique()      const{return LM::is_unique();}

};

// Non-Member Functions:
TimeSeries<class dataType, class dtContainerType, class dtElementType>
LeftJoin(const TimeSeries<dataType, dtContainerType, dtElementType>& LHS_ts, const TimeSeries<dataType, dtContainerType, dtElementType>& RHS_ts);

TimeSeries<class dataType, class dtContainerType, class dtElementType>
Intersect(const TimeSeries<dataType, dtContainerType, dtElementType>& ts1, const TimeSeries<dataType, dtContainerType, dtElementType>& ts2);

TimeSeries<class dataType, class dtContainerType, class dtElementType>
Union(const TimeSeries<dataType, dtContainerType, dtElementType>& ts1, const TimeSeries<dataType, dtContainerType, dtElementType>& ts2);






//--------------------------------------------------------------------------------------------------
// --------------------------- Function Definitions ------------------------------------------------
//--------------------------------------------------------------------------------------------------

template<class dateType, class dtContainerType, class dtElementType>
void TimeSeries<dateType, dtContainerType, dtElementType>::
ValidateObject() const {

    //ASK: How do I check that dtElementType is some sort of date/time object here?

    // Validate the data
    LMatrix<dateType, dtContainerType, dtElementType>::ValidateObject();

    // Check that the labels are sorted and unique
    if(!is_sorted()){
        throw string("ERROR:\tTimeSeries labels are not sorted")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+std::to_string(__LINE__);
    }
    if(!is_unique()){
        throw string("ERROR:\tTimeSeries labels are not unique")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+std::to_string(__LINE__);
    }

}



template <class dataType, class dtContainerType, class dtElementType>
TimeSeries<dataType, dtContainerType, dtElementType>::
TimeSeries(RawMatrix<dataType>& rawData, dtContainerType& rowNames, strVec& colNames):
        LMatrix<dataType, dtContainerType, dtElementType>(rawData, rowNames, colNames){

    ValidateObject();
}


template <class dataType, class dtContainerType, class dtElementType>
TimeSeries<dataType, dtContainerType, dtElementType>::
TimeSeries(LMatrix<dataType, dtContainerType, dtElementType> mat): LMatrix<dataType, dtContainerType, dtElementType>(mat){

    ValidateObject();
}











#endif
