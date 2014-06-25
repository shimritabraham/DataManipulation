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
#include "boost/shared_ptr.hpp"
#include "Utils.h"

using namespace std;


class StringLabels:public LabelContainer<string>{
public:
    typedef LabelContainer<string> LC;
    typedef boost::shared_ptr<StringLabels> pSLabels;

    // Con/De-structors
    StringLabels():LC(){}
    StringLabels(const StringLabels& otherObj):LC(otherObj.itsData){}
    StringLabels(const vector<string> vec):LC(vec){}
    StringLabels(const LC otherObj):LC(otherObj){}
    StringLabels(const boost::shared_ptr<LC> otherObj):LC(*otherObj){}
    virtual ~StringLabels(){};

    // General Utils
    StringLabels& operator= (const StringLabels& otherObj);
    virtual vector<string> to_string() const {return itsData;}
    virtual size_t find(const string& str) const ;
    virtual void SetDefaultLabels(const string& str, const size_t& len);
    virtual void swap(StringLabels& rhs);
    StringLabels join(const StringLabels& rhs) const;
    StringLabels intersect(const StringLabels& rhs)const;


    // Friends
    friend ostream& operator<< (ostream& stream, StringLabels& rhs);

};



ostream&
operator<< (ostream& stream, StringLabels& rhs) {
    stream<<rhs.itsData;
    return stream;
}


StringLabels StringLabels::
join(const StringLabels& rhs) const{
    vector<string> allData(itsData);
    allData.insert(allData.end(), rhs.itsData.begin(), rhs.itsData.end());
    return StringLabels(allData);
}


StringLabels StringLabels::
intersect(const StringLabels& rhs) const{
    vector<string> vec_lhs(itsData);
    vector<string> vec_rhs(rhs.itsData);
    utils::intersection(vec_lhs, vec_rhs);
    return StringLabels(utils::intersection(vec_lhs, vec_rhs));
}

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
