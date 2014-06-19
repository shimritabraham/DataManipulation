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

typedef boost::posix_time::ptime pt;
using namespace std;

class DateTimeLabels{
public:

    // Con/De-structors
    DateTimeLabels(vector<pt> data, const string inputFormat):itsData(data), itsInputFormat(inputFormat){}
    DateTimeLabels(const string inputFormat):itsInputFormat(inputFormat){}
    DateTimeLabels(){}
    DateTimeLabels(const DateTimeLabels& otherObj){itsData = otherObj.itsData;};
    ~DateTimeLabels(){}


    // Operators
    const pt& operator[](const size_t idx) const {return itsData[idx];}
          pt& operator[](const size_t idx)       {return itsData[idx];}

    // General Utils
    void push_back(pt dt){itsData.push_back(dt);}
    void push_back(string str);
    vector<string> to_string() const;
    size_t size() const {return itsData.size();}
    size_t find(const pt td) const ;
    void SetDefaultLabels(string& str, const size_t& len);
    void Swap(const DateTimeLabels& rhs);
    DateTimeLabels& operator=(const DateTimeLabels& rhs);
    bool is_sorted();

private:
    vector<pt> itsData;
    string itsInputFormat;
};

#endif