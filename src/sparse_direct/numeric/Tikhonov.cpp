/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.
 
   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"
using namespace El;

namespace El {

template<typename F>
void Tikhonov
( const DistSparseMatrix<F>& A, const DistMultiVec<F>& Y, 
  const DistSparseMatrix<F>& Gamma, DistMultiVec<F>& X, const BisectCtrl& ctrl )
{
    DEBUG_ONLY(
        CallStackEntry cse("Tikhonov");
        if( A.Height() != Y.Height() )
            LogicError("Heights of A and Y must match");
    )
    const Int n = A.Width();
    DistSparseMatrix<F> C(A.Comm());
    Herk( LOWER, ADJOINT, Base<F>(1), A, C );
    Herk( LOWER, ADJOINT, Base<F>(1), Gamma, Base<F>(1), C );
    MakeHermitian( LOWER, C );
    X.SetComm( Y.Comm() );
    Zeros( X, n, Y.Width() );
    Multiply( ADJOINT, F(1), A, Y, F(0), X ); 
    HermitianSolve( C, X, ctrl );
}

#define PROTO(F) \
  template void Tikhonov \
  ( const DistSparseMatrix<F>& A, const DistMultiVec<F>& Y, \
    const DistSparseMatrix<F>& Gamma, DistMultiVec<F>& X, \
    const BisectCtrl& ctrl );
 
#define EL_NO_INT_PROTO
#include "El/macros/Instantiate.h"

} // namespace El
