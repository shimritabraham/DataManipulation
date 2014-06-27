//
//  Covariance.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 27/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Covariance_h
#define DataManipulation_Covariance_h

#include <memory>
#include <Eigen/Dense>

using namespace std;

template<class dataType, class dataContainerClass>
class Covariance{
    // dataContainerClass can be e.g. Eigen::Matrix, or LMatrix, or TimeSeries etc.
    // dataType can be int, double, float etc


public:
    typedef Eigen::Matrix<dataType, Eigen::Dynamic, Eigen::Dynamic> EMat;
    typedef shared_ptr<EMat> pEMat;
    typedef vector<pEMat> v_pEMat;

    // Equally weighted past observations
    pEMat equallyWeighted(const int lookback = -1) const; // negative lookback means 'use all data'
    v_pEMat equallyWeightedRolling(const uint lookback) const;

    // EWMA-weighted past observations
    pEMat ewmaWeighted(const double lambda) const;
    v_pEMat ewmaWeightedRolling(const double lambda) const;


private:
    shared_ptr<dataContainerClass> pRetData; // can be log returns, pct rets etc.
};

#endif
