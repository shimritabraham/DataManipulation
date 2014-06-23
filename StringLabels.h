//
//  StringLabels.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 17/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Labels_h
#define DataManipulation_Labels_h
#include <vector>
#include <string>
#include "LabelContainer.h"

using namespace std;


class StringLabels:public LabelContainer<string>{
public:

    // Con/De-structors
    StringLabels(vector<string> data):LabelContainer<string>(data){}
    StringLabels():LabelContainer<string>(){}
    StringLabels(const StringLabels& otherObj):LabelContainer<string>(otherObj.itsData){};
    virtual ~StringLabels(){};

    // General Utils
    virtual vector<string> to_string() const {return itsData;}
    virtual size_t find(const string& str) const ;
    virtual void SetDefaultLabels(const string& str, const size_t& len);
    virtual void swap(StringLabels& rhs);
    virtual StringLabels& operator= (const StringLabels& otherObj);


private:
    string itsInputFormat;

};



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
SetDefaultLabels(const string& str, const size_t& len){
    vector<string> result(len);
    for(size_t i =0; i<len; i++){
        result[i] = str+std::to_string(i);
    }
    SetData(result);
}

void StringLabels::
swap(StringLabels& rhs){
    LabelContainer::swap(rhs);
}


StringLabels& StringLabels::
operator= (const StringLabels& rhs){
    StringLabels tmp(rhs);
    swap(tmp);
    return *this;
}




#endif
