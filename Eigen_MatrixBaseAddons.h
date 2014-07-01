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
#include <vector>


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



// --------------------------------------------------------------
// Covariance Matrix: Equally weighted past observations
// --------------------------------------------------------------



template <typename OtherDerived>
void
Cov_equallyWeightedAllData(MatrixBase<OtherDerived> const & result) const
{
    typedef typename Derived::Scalar Scalar;
    typedef typename internal::plain_row_type<Derived>::type RowVectorType;
    const Scalar num_observations = static_cast<Scalar>(this->rows());

    const RowVectorType colMeans = this->colwise().sum() / num_observations;

    const_cast< MatrixBase<OtherDerived>& >(result) =
    (this->rowwise() - colMeans).transpose() * (this->rowwise() - colMeans) / (num_observations-1);

}


template <typename OtherDerived>
void
Cov_equallyWeighted(MatrixBase<OtherDerived> const & result_, const Index lookback) {

    // hack recommended by documentation
    MatrixBase<OtherDerived>& result = const_cast< MatrixBase<OtherDerived>& >(result_);
    result.derived().resize(this->cols(), this->cols());

    // call cov function that uses all data on bottomrows section of the matrix
    this->bottomRows(lookback).Cov_equallyWeightedAllData(result);
}


template <typename OtherDerived>
std::vector<  OtherDerived  >
Cov_equallyWeightedRolling(MatrixBase<OtherDerived>  const & matHolder_, const Index lookback) {

    // validate input
    if(lookback>=this->rows()){
        throw std::string("ERROR:\t Lookback parameter is too large compared to matrix rows.")+
        std::string("\nFILE:\t")+std::string(__FILE__)+std::string("\nROW:\t")+std::to_string(__LINE__);
    }

    // hack recommended by documentation
    MatrixBase<OtherDerived>& matHolder = const_cast< MatrixBase<OtherDerived>& >(matHolder_);
    matHolder.derived().resize(this->cols(), this->cols());


    typedef typename internal::plain_matrix_type<OtherDerived>::type plain_mat;
    std::vector<plain_mat> result;

    // compute rolling cov matrix
    for(Index i=lookback; i<this->rows(); i++){
        this->topRows(i).Cov_equallyWeighted(matHolder, lookback);
        result.push_back(matHolder);
    }

    return result;
}





// --------------------------------------------------------------
// Covariance Matrix: EWMA-weighted past observations
// --------------------------------------------------------------
pEMatB Cov_ewmaWeighted(const double lambda) const;
v_pEMatB Cov_ewmaWeightedRolling(const double lambda) const;






#endif
