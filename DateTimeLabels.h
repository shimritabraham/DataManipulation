//
//  DateTimeLabels.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 17/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_DateTimeLabels_h
#define DataManipulation_DateTimeLabels_h

#include "boost/date_time/local_time/local_time.hpp"
#include <vector>
#include "LabelContainer.h"

using namespace boost::posix_time;
using namespace std;

typedef boost::posix_time::ptime pt;


class DateTimeLabels:public LabelContainer<pt>{
public:

    // Con/De-structors
    DateTimeLabels(vector<pt> data):LabelContainer<pt>(data){}
    DateTimeLabels():LabelContainer<pt>(){}
    DateTimeLabels(const DateTimeLabels& otherObj):LabelContainer<pt>(otherObj.itsData){};
    virtual ~DateTimeLabels(){}

    // General Utils
    virtual void push_back(const string& str, const string& inputFormat);
    virtual vector<string> to_string() const;
    virtual size_t find(const pt td) const ;
    virtual void SetDefaultLabels(const string& str, const size_t& len);
    virtual void swap(const DateTimeLabels& rhs);
    virtual DateTimeLabels& operator=(const DateTimeLabels& rhs);
    DateTimeLabels join(const DateTimeLabels& rhs) const;
    DateTimeLabels intersect(const DateTimeLabels& rhs) const;


    // Friends
    friend ostream& operator<< (ostream& stream, DateTimeLabels& rhs) ;
    friend DateTimeLabels join(const DateTimeLabels& LHS, const DateTimeLabels& RHS);
    friend DateTimeLabels intersect(const DateTimeLabels& LHS, const DateTimeLabels& RHS);

};





DateTimeLabels DateTimeLabels::
intersect(const DateTimeLabels& rhs) const{
    DateTimeLabels joinedData = this->join(rhs);
    vector<pt> rawData = joinedData.itsData;

    // sort the labels first, otherwise unique() won't work properly
    std::sort(rawData.begin(), rawData.end());

    vector<pt>::iterator it = unique(rawData.begin(), rawData.end());
    rawData.resize(distance(rawData.begin(), it));

    return(DateTimeLabels(rawData));
}

DateTimeLabels DateTimeLabels::
join(const DateTimeLabels& rhs) const{
    vector<pt> result(itsData);
    result.insert(result.end(), rhs.itsData.begin(), rhs.itsData.end());
    return DateTimeLabels(result);
}

ostream&
operator<< (ostream& stream, DateTimeLabels& rhs) {
    stream<<rhs.itsData;
    return stream;
}


vector<string> DateTimeLabels::
to_string() const{
    vector<string> result;
    for(size_t i=0; i<itsData.size(); i++){
        result.push_back(to_simple_string(itsData[i]));
    }
    return result;
}


size_t DateTimeLabels::
find(const pt td) const{

    // do the search
    vector<pt>::const_iterator iElement = std::find(itsData.begin(), itsData.end(), td);

    // check if found
    if(iElement == itsData.end()){
        throw string("ERROR\tUnable to find \'")+to_simple_string(td)+string("\'")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+std::to_string(__LINE__);
    }

    // return distance from the start
    return std::distance(itsData.begin(), iElement);
}


void DateTimeLabels::
SetDefaultLabels(const string& str, const size_t& len){
    //ignore the str variable in this case

    vector<pt> result;
    pt NaNDateTime = pt(boost::posix_time::not_a_date_time);
    for (size_t i=0; i<len; i++){
        result.push_back(NaNDateTime);
    }
    itsData = result;
}


void DateTimeLabels::
push_back(const string& str, const string& inputFormat){
    ptime dt(not_a_date_time);
    std::stringstream ss;
    boost::local_time::local_time_input_facet* myFacet(new boost::local_time::local_time_input_facet(inputFormat));
    ss.imbue(std::locale(std::locale::classic(), myFacet));
    ss.str(str);
    ss >> dt;
    LabelContainer::push_back(dt, inputFormat);
}


void DateTimeLabels::
swap(const DateTimeLabels& rhs){
    itsData = rhs.itsData;
}


DateTimeLabels& DateTimeLabels::
operator=(const DateTimeLabels& rhs){
    swap(rhs);
    return *this;
}



#endif
