//
//  StringLabels.cpp
//  DataManipulation
//
//  Created by Shimrit Abraham on 17/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#include "StringLabels.h"
#include <string>


size_t StringLabels::
find(const string& str) const{

    // do the search
    vector<string>::const_iterator iElement = std::find(itsData.begin(), itsData.end(), str);

    // check if found
    if(iElement == itsData.end()){
        throw string("ERROR\tUnable to find \'")+str+string("\'")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+std::to_string(__LINE__);
    }

    // return distance from start
    return std::distance(itsData.begin(), iElement);
}


void StringLabels::
SetDefaultLabels(string& str, const size_t& len){
    vector<string> result(len);
    for(size_t i =0; i<len; i++){
        result[i] = str+std::to_string(i);
    }
    itsData = result;
}



void StringLabels::
swap(StringLabels& rhs){
    itsData = rhs.itsData;
    itsInputFormat = rhs.itsInputFormat;
}


StringLabels& StringLabels::
operator= (const StringLabels& rhs){
    StringLabels tmp(rhs);
    swap(tmp);
    return *this;
}


bool StringLabels::
is_sorted(){
    return std::is_sorted(itsData.begin(), itsData.end());
}


