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

typedef boost::posix_time::ptime pt;
using namespace std;

class DateTimeLabels:public LabelContainer<pt>{
public:

    // Con/De-structors
    DateTimeLabels(vector<pt> data, const string inputFormat):LabelContainer<pt>(data){}
    DateTimeLabels(const string inputFormat):LabelContainer<pt>(){}
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

    friend ostream& operator<< (ostream& stream, DateTimeLabels& rhs) ;
};

#endif
