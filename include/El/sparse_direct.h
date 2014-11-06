/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef EL_SPARSEDIRECT_C_H
#define EL_SPARSEDIRECT_C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Symmetric/Hermitian solves
   ========================== */
EL_EXPORT ElError ElSymmetricSolveDistSparse_s
( ElConstDistSparseMatrix_s A, ElDistMultiVec_s X );
EL_EXPORT ElError ElSymmetricSolveDistSparse_d
( ElConstDistSparseMatrix_d A, ElDistMultiVec_d X );
EL_EXPORT ElError ElSymmetricSolveDistSparse_c
( ElConstDistSparseMatrix_c A, ElDistMultiVec_c X );
EL_EXPORT ElError ElSymmetricSolveDistSparse_z
( ElConstDistSparseMatrix_z A, ElDistMultiVec_z X );

EL_EXPORT ElError ElHermitianSolveDistSparse_c
( ElConstDistSparseMatrix_c A, ElDistMultiVec_c X );
EL_EXPORT ElError ElHermitianSolveDistSparse_z
( ElConstDistSparseMatrix_z A, ElDistMultiVec_z X );

/* Least squares
   ============= */
EL_EXPORT ElError ElLeastSquaresDistSparse_s
( ElOrientation orientation,
  ElConstDistSparseMatrix_s A, ElConstDistMultiVec_s Y, ElDistMultiVec_s X );
EL_EXPORT ElError ElLeastSquaresDistSparse_d
( ElOrientation orientation,
  ElConstDistSparseMatrix_d A, ElConstDistMultiVec_d Y, ElDistMultiVec_d X );
EL_EXPORT ElError ElLeastSquaresDistSparse_c
( ElOrientation orientation,
  ElConstDistSparseMatrix_c A, ElConstDistMultiVec_c Y, ElDistMultiVec_c X );
EL_EXPORT ElError ElLeastSquaresDistSparse_z
( ElOrientation orientation,
  ElConstDistSparseMatrix_z A, ElConstDistMultiVec_z Y, ElDistMultiVec_z X );

/* Ridge regression
   ================ */
EL_EXPORT ElError ElRidgeDistSparse_s
( ElConstDistSparseMatrix_s A, ElConstDistMultiVec_s Y, 
  float alpha, ElDistMultiVec_s X );
EL_EXPORT ElError ElRidgeDistSparse_d
( ElConstDistSparseMatrix_d A, ElConstDistMultiVec_d Y, 
  double alpha, ElDistMultiVec_d X );
EL_EXPORT ElError ElRidgeDistSparse_c
( ElConstDistSparseMatrix_c A, ElConstDistMultiVec_c Y, 
  float alpha, ElDistMultiVec_c X );
EL_EXPORT ElError ElRidgeDistSparse_z
( ElConstDistSparseMatrix_z A, ElConstDistMultiVec_z Y, 
  double alpha, ElDistMultiVec_z X );

/* Tikhonov regularization
   ======================= */
EL_EXPORT ElError ElTikhonovDistSparse_s
( ElConstDistSparseMatrix_s A, ElConstDistMultiVec_s Y, 
  ElConstDistSparseMatrix_s Gamma, ElDistMultiVec_s X );
EL_EXPORT ElError ElTikhonovDistSparse_d
( ElConstDistSparseMatrix_d A, ElConstDistMultiVec_d Y, 
  ElConstDistSparseMatrix_d Gamma, ElDistMultiVec_d X );
EL_EXPORT ElError ElTikhonovDistSparse_c
( ElConstDistSparseMatrix_c A, ElConstDistMultiVec_c Y, 
  ElConstDistSparseMatrix_c Gamma, ElDistMultiVec_c X );
EL_EXPORT ElError ElTikhonovDistSparse_z
( ElConstDistSparseMatrix_z A, ElConstDistMultiVec_z Y, 
  ElConstDistSparseMatrix_z Gamma, ElDistMultiVec_z X );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ifndef EL_SPARSEDIRECT_C_H */
