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
#include<vector>
using namespace std;


namespace utils{
    template<class T>
    ostream& operator<< (ostream& str, const vector<T>& vec);

    template<class T>
    bool is_unique(const vector<T>& vec);

}



#endif
