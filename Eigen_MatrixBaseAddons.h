//
//  Eigen_MatrixBaseAddons.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 27/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Eigen_MatrixBaseAddons_h
#define DataManipulation_Eigen_MatrixBaseAddons_h

typedef Eigen::MatrixBase<Derived> EMatB;
typedef shared_ptr<EMatB> pEMatB;
typedef vector<pEMatB> v_pEMatB;


inline Scalar at(uint i, uint j) const { return this->operator()(i,j); }


Index myRows(){return this->rows();}

// Equally weighted past observations
pEMatB equallyWeighted(const int lookback = -1) const; // negative lookback means 'use all data'
v_pEMatB equallyWeightedRolling(const uint lookback) const;

// EWMA-weighted past observations
pEMatB ewmaWeighted(const double lambda) const;
v_pEMatB ewmaWeightedRolling(const double lambda) const;

#endif
