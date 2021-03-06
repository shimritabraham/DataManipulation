//
//  Utils.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 10/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Utils_h
#define DataManipulation_Utils_h

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
ostream& operator<< (ostream& str, const vector<T>& vec);


namespace utils{

    template<class T>
    bool is_unique(const vector<T>& vec);

    template<class T>
    vector<T> intersection(vector<T> v1, vector<T> v2);

}


template<class T>
vector<T> utils::
intersection(vector<T> v1, vector<T> v2){

    vector<T> v3;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}





template<class T>
ostream&
operator<< (ostream& str, const vector<T>& vec){
    size_t maxVecSize = 10;
    size_t vecSize =vec.size();
    str<<"[";


    if(vecSize<maxVecSize){
        // small matrix -> print all elements
        for(size_t i=0; i<vecSize; i++){
            str<<vec[i];
            if(i<vec.size()-1)
                str<<", ";
        }
    }else{
        // large matrix -> only print head and tale
        for(size_t i=0; i<maxVecSize/2; i++){
            str<<vec[i];
            if(i<vec.size()-1)
                str<<", ";
        }
        cout<<"..."<<endl;
        for(size_t i=vecSize-maxVecSize/2-1; i<vecSize; i++){
            str<<vec[i];
            if(i<vec.size()-1)
                str<<", ";
        }

    }
    str<<"]";
    return str;
}


#endif
