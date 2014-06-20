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
    StringLabels(vector<string> data, const string inputFormat):LabelContainer<string>(data){}
    StringLabels(const string inputFormat):LabelContainer<string>(){}
    StringLabels(const StringLabels& otherObj):LabelContainer<string>(otherObj.itsData){};
    StringLabels():LabelContainer<string>(){}
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

#endif
