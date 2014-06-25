//
//  LabelContainer.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 19/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_LabelContainer_h
#define DataManipulation_LabelContainer_h

#include <vector>
#include <algorithm>
#include <set>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;


template<class elementType>
class LabelContainer{
public:
    typedef boost::shared_ptr<LabelContainer<elementType>> pLC;

    //Con/De-structors
    LabelContainer(vector<elementType> data):itsData(data){};
    LabelContainer(const LabelContainer& rhs):itsData(rhs.itsData){}
    LabelContainer(){}
    virtual ~LabelContainer(){};

    // Accessors
    void SetData(const vector<elementType>& vec){itsData = vec;}

    // Operators
    const elementType& operator[](const size_t idx) const {return itsData[idx];}
    virtual LabelContainer<elementType>& operator= (const LabelContainer& otherObj);

    // Util Functions
    virtual void push_back(const elementType& x, const string& inputFormat){itsData.push_back(x);}
    size_t size() const {return itsData.size();}
    virtual size_t find(const elementType& x) const ;
    virtual void swap(const LabelContainer& rhs);
    bool is_sorted() const{return std::is_sorted(itsData.begin(), itsData.end());}
    bool is_unique() const;
    bool equal(const LabelContainer<elementType> rhs) const;

    // Pure virtual functions
    virtual vector<string> to_string() const = 0;
    virtual void SetDefaultLabels(const string& helper, const size_t& len) = 0;

    // Friend Functions
    friend ostream& operator<< (ostream& stream, vector<elementType>& rhs);

protected:
    vector<elementType> itsData;

};



//---------------------------------------------
// Non-member function declarations
//---------------------------------------------





//---------------------------------------------
// Function Definitions
//---------------------------------------------


template<class elementType>
bool LabelContainer<elementType>::
equal(const LabelContainer<elementType> rhs) const{

    // check sizes of vectors
    if(this->size() != rhs.size()){
        return false;
    }

    // compare elements of underlying data
    if(!std::equal(itsData.begin(), itsData.end(), rhs.itsData.begin())){
        return false;
    }

    return true;
}


template<class elementType>
size_t LabelContainer<elementType>::
find(const elementType& x) const{

    // do the search
    typename vector<elementType>::const_iterator iElement = std::find(itsData.begin(), itsData.end(), x);

    // check if found
    if(iElement == itsData.end()){
        throw string("ERROR\tUnable to find element in vector\'")+
        string("\nFILE:\t")+string(__FILE__)+string("\nROW:\t")+std::to_string(__LINE__);
    }

    // return distance from the start
    return std::distance(itsData.begin(), iElement);
}


template<class elementType>
void LabelContainer<elementType>::
swap(const LabelContainer& rhs){
    itsData = rhs.itsData;
}


template<class elementType>
LabelContainer<elementType>& LabelContainer<elementType>::
operator= (const LabelContainer& otherObj){
    swap(otherObj);
    return *this;
}


template<class elementType>
ostream& operator<< (ostream& stream, LabelContainer<elementType>& rhs) {
    stream<<rhs.itsData;
    return stream;
}


template<class elementType>
bool LabelContainer<elementType>::
is_unique() const{
    set <elementType> setEquivalent(itsData.begin(), itsData.end());
    return setEquivalent.size() == itsData.size();
}

#endif
