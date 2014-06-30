//
//  Eigen_MatrixBaseAddons.h
//  DataManipulation
//
//  Created by Shimrit Abraham on 27/06/2014.
//  Copyright (c) 2014 sabraham. All rights reserved.
//

#ifndef DataManipulation_Eigen_MatrixBaseAddons_h
#define DataManipulation_Eigen_MatrixBaseAddons_h

#include <stdlib.h>
#include <iostream>

typedef Eigen::MatrixBase<Derived> EMatB;
typedef std::shared_ptr<EMatB> pEMatB;
typedef std::vector<pEMatB> v_pEMatB;


// ASK: I have not been able to separate the declaration from the definition of new methods here. Is this possible?


Index myRows(){
    return this->rows();
}


// ------------------------------------------
// Data Processing
// ------------------------------------------





template <typename OtherDerived>
void
diff(MatrixBase<OtherDerived> const & result_, const int lag = 0){
    Index nRows  = this->rows();

    // recommmended hack: get rid of constness in result
    MatrixBase<OtherDerived>& result = const_cast< MatrixBase<OtherDerived>& >(result_);
    result.derived().resize(nRows-abs(lag), this->cols());

    if (lag<0)
        result = this->bottomRows(nRows-abs(lag)) - this->topRows(nRows-abs(lag));
    if (lag == 0)
        throw std::string("ERROR:\t Lag parameter of zero is meaningless.")+
        std::string("\nFILE:\t")+std::string(__FILE__)+std::string("\nROW:\t")+std::to_string(__LINE__);
    if (lag>0)
        result = this->topRows(nRows-abs(lag)) - this->bottomRows(nRows-abs(lag));
}



template <typename OtherDerived>
void
lnRet(MatrixBase<OtherDerived> const & result_, const int lag = -1) {
    // lag<0: mat_t - mat_{t-|lag|}
    // lag>0: mat_t - mat_{t+|lag|}
    // lag = 0 is not allowed

    Index nRows  = this->rows();
    MatrixBase<OtherDerived>& result = const_cast< MatrixBase<OtherDerived>& >(result_);
    result.derived().resize(nRows-abs(lag), this->cols());

    if (lag<0)
        result = this->bottomRows(nRows-abs(lag)).cwiseQuotient(this->topRows(nRows-abs(lag))) ;
    if (lag == 0)
        throw std::string("ERROR:\t Lag parameter of zero is meaningless.")+
        std::string("\nFILE:\t")+std::string(__FILE__)+std::string("\nROW:\t")+std::to_string(__LINE__);
    if(lag>0)
        result = this->topRows(nRows-abs(lag)).cwiseQuotient(this->bottomRows(nRows-abs(lag))) ;


    result = result.array().log();


}



// ------------------------------------------
// Covariance Matrix: Equally weighted past observations
// ------------------------------------------


template <typename OtherDerived>
void cov(const MatrixBase<Derived>& x, const MatrixBase<Derived>& y, MatrixBase<OtherDerived> const & C)
{
    typedef typename Derived::Scalar Scalar;
    typedef typename internal::plain_row_type<Derived>::type RowVectorType;
    const Scalar num_observations = static_cast<Scalar>(x.rows());

    const RowVectorType x_mean = x.colwise().sum() / num_observations;
    const RowVectorType y_mean = y.colwise().sum() / num_observations;

    const_cast< MatrixBase<OtherDerived>& >(C) =
        (x.rowwise() - x_mean).transpose() * (y.rowwise() - y_mean) / (num_observations-1);
}

//
//template <typename OtherDerived>
//void
//Cov_equallyWeightedAllData(MatrixBase<OtherDerived> const & result_)const{
//    // recommmended hack: get rid of constness in result
//    MatrixBase<OtherDerived>& result = const_cast< MatrixBase<OtherDerived>& >(result_);
//    result.derived().resize(this->cols(), this->cols());
//
//    const MatrixBase<Derived>> x_mean = this->colwise().sum();
////    return pEMatB(new EMatB ((centered.transpose() * centered)/double(this->rows()))  );
//}

//
//pEMatB
//Cov_equallyWeighted(const int lookback = -1) {
//    // lookback<0 means 'use all data'
//
//    Index N = this->rows();
//
//    if (lookback<0){
//        // use all data to compute covariance matrix
//        return this->Cov_EquallyWeightedAllData();
//
//    }else{
//
//        // compute rolling covariance matrix
//        if(N<lookback+2)
//            throw std::string("ERROR:\t Lookback parameter too large compared to nr of rows in Matrix")+
//            std::string("\nFILE:\t")+std::string(__FILE__)+std::string("\nROW:\t")+std::to_string(__LINE__);
//        return this->bottomRows(lookback)->Cov_EquallyWeighted();
//    }
//
//}



v_pEMatB Cov_equallyWeightedRolling(const uint lookback) const;






// ------------------------------------------
// Covariance Matrix: EWMA-weighted past observations
// ------------------------------------------
pEMatB Cov_ewmaWeighted(const double lambda) const;
v_pEMatB Cov_ewmaWeightedRolling(const double lambda) const;






#endif
