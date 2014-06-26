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


// forward-declare the LMatrix class (to enable creation of alias)
template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
class TimeSeries;

template<class x, class y, class z>
using TS = TimeSeries<x, y, z>;

template<class x, class y, class z>
using pTS = boost::shared_ptr<TimeSeries<x, y, z>>;

template<class x, class y, class z>
using v_pTS = vector<pTS<x, y, z>>;

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
template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
pTS<dataType, rowLabelCollectionType, rowLabelElementType>
join(v_pTS< dataType, rowLabelCollectionType, rowLabelElementType>  vecOfMatrixPtrs);



//--------------------------------------------------------------------------------------------------
// --------------------------- Function Definitions ------------------------------------------------
//--------------------------------------------------------------------------------------------------


template<class dataType, class rowLabelCollectionType, class rowLabelElementType>
pTS<dataType, rowLabelCollectionType, rowLabelElementType>
join(v_pTS< dataType, rowLabelCollectionType, rowLabelElementType>  vecOfTimeSeriesPtrs){

    typedef pLMatrix<dataType, rowLabelCollectionType, rowLabelElementType>     pLM_hier;
    typedef v_pLMatrix<dataType, rowLabelCollectionType, rowLabelElementType>   v_pLM_hier;
    typedef pTS<dataType, rowLabelCollectionType, rowLabelElementType>          pTS_hier;
    typedef TS<dataType, rowLabelCollectionType, rowLabelElementType>       	TS_hier;

    v_pLM_hier vecOfLMPtrs(vecOfTimeSeriesPtrs.begin(), vecOfTimeSeriesPtrs.end());    pLM_hier pLM_result(join(vecOfLMPtrs));

    // downcast the pointer
    pTS_hier TS_result(new TS_hier(*pLM_result));
    return TS_result;

}



template<class dateType, class dtContainerType, class dtElementType>
boost::shared_ptr<TimeSeries<dateType, dtContainerType, dtElementType>> TimeSeries<dateType, dtContainerType, dtElementType>::
cbind(const pTS rhs) const{
    pLM pLM_result(LM::cbind(rhs));

    // ASK: downcasting the pointer here. Is this ok or is there a better way to make cbind() return a TimeSeries pointer?
    pTS TS_result(new TS(*pLM_result));
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
