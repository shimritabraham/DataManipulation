//
//  Utils.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 10/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Utils_h
#define DataManipulation_Utils_h

template<class T>
ostream& operator<< (ostream& str, const vector<T>& vec){
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
