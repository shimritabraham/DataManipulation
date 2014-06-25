//
//  TimeSeries.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 16/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_TimeSeries_h
#define DataManipulation_TimeSeries_h

#include <memory>
#include "LMatrix.h"
#include "boost/shared_ptr.hpp"
typedef vector<string> strVec;

template<class dataType, class dtContainerType, class dtElementType>
class TimeSeries: public LMatrix<dataType, dtContainerType, dtElementType>{
    // a TimeSeries object is a special kind of Labelled Matrix where the rownames represent timestamps


public:

    // Typedefs
    typedef LMatrix<dataType, dtContainerType, dtElementType> LM;
    typedef TimeSeries <dataType, dtContainerType, dtElementType> TS;
    typedef boost::shared_ptr<TS> pTS;
    typedef boost::shared_ptr<LM> pLM;


    // Con/Destructors
    TimeSeries(const RawMatrix<dataType>& rawData, const dtContainerType& rowNames, const strVec& colNames);
    TimeSeries(boost::shared_ptr<LM> mat);
    TimeSeries(const LM& mat):LM(mat){ValidateObject();}
    TimeSeries():LM(){};
    ~TimeSeries(){};

    // Accessor functions
    const TS row(const dtElementType& name) const {return TimeSeries(LM::row(name));}
          TS row(const dtElementType& name)       {return TimeSeries(LM::row(name));}
    const TS row(const size_t& idx)         const {return TimeSeries(LM::row(idx));}
          TS row(const size_t& idx)               {return TimeSeries(LM::row(idx));}

    const TS col(const string& name)const   {return TimeSeries(LM::col(name));}
          TS col(const string& name)        {return TimeSeries(LM::col(name));}
    const TS col(const size_t& idx) const   {return TimeSeries(LM::col(idx));}
          TS col(const size_t& idx)         {return TimeSeries(LM::col(idx));}

    // Util functions:
    void ValidateObject() const;
    bool is_sorted()      const{return LM::is_sorted();}
    bool is_unique()      const{return LM::is_unique();}
    pTS cbind(const pTS rhs) const;

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
boost::shared_ptr<TimeSeries<dateType, dtContainerType, dtElementType>> TimeSeries<dateType, dtContainerType, dtElementType>::
cbind(const pTS rhs) const{
    pLM LM_result(LM::cbind(rhs));

    // downcast the pointer
    pTS TS_result(new TS(*LM_result));
    return TS_result;
}


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
TimeSeries(const RawMatrix<dataType>& rawData, const dtContainerType& rowNames, const strVec& colNames):
        LMatrix<dataType, dtContainerType, dtElementType>(rawData, rowNames, colNames){

    ValidateObject();
}


template <class dataType, class dtContainerType, class dtElementType>
TimeSeries<dataType, dtContainerType, dtElementType>::
TimeSeries(boost::shared_ptr<LMatrix<dataType, dtContainerType, dtElementType>> mat): LMatrix<dataType, dtContainerType, dtElementType>(mat){

    ValidateObject();
}











#endif
