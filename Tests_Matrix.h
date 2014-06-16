//
//  Tests_Matrix.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 16/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Tests_Matrix_h
#define DataManipulation_Tests_Matrix_h

#include <igloo/igloo.h>


using namespace igloo;

Context(SomeTest){
    Spec(FirstTest){
        int a = 3;
        Assert::That(a, Equals(3));
    }
};


#endif
