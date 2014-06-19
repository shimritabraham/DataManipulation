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

using namespace std;

class StringLabels{
public:

    // Con/De-structors
    StringLabels(vector<string> data, const string inputFormat):itsData(data), itsInputFormat(inputFormat){}
    StringLabels(const string inputFormat):itsInputFormat(inputFormat){}
    StringLabels(const StringLabels& otherObj){itsData = otherObj.itsData;};
    StringLabels(){}
    ~StringLabels(){};

    // Operators
    const string& operator[](const size_t idx) const {return itsData[idx];}
          string& operator[](const size_t idx)       {return itsData[idx];}

    // General Utils
    void push_back(string str){itsData.push_back(str);}
    vector<string> to_string() const {return itsData;}
    size_t size() const {return itsData.size();}
    size_t find(const string& str) const ;
    void SetDefaultLabels(string& str, const size_t& len);
    StringLabels& operator= (const StringLabels& otherObj);
    bool is_sorted();


private:
    vector<string> itsData;
    string itsInputFormat;

    void swap(StringLabels& rhs);
};

#endif
