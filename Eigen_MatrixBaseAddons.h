//
//  Eigen_MatrixBaseAddons.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 27/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Eigen_MatrixBaseAddons_h
#define DataManipulation_Eigen_MatrixBaseAddons_h

inline Scalar at(uint i, uint j) const { return this->operator()(i,j); }

#endif
