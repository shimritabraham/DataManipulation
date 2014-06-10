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
    str<<"[";
    for(size_t i=0; i<vec.size(); i++){
        str<<vec[i];
        if(i<vec.size()-1)
            str<<", ";
    }
    str<<"]";
    return str;
}



#endif
