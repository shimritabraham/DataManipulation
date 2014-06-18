//
//  DateTimeLabels.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 17/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include "DateTimeLabels.h"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <vector>
using namespace boost::posix_time;
typedef boost::posix_time::ptime pt;

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
SetDefaultLabels(string& str, const size_t& len){
    //ignore the str variable in this case

    vector<pt> result;
    pt NaNDateTime = pt(boost::posix_time::not_a_date_time);
    for (size_t i=0; i<len; i++){
        result.push_back(NaNDateTime);
    }
    itsData = result;
}





