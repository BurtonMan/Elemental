/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"
#include "El.h"
using namespace El;

extern "C" {

ElError ElCopyGraph( ElConstGraph A, ElGraph B )
{ EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) }
ElError ElCopyDistGraph( ElConstDistGraph A, ElDistGraph B )
{ EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) }

ElError ElCopyGraphFromRoot( ElConstDistGraph GDist, ElGraph G )
{ EL_TRY( CopyFromRoot( *CReflect(GDist), *CReflect(G) ) ) }
ElError ElCopyGraphFromNonRoot( ElConstDistGraph GDist, ElInt root )
{ EL_TRY( CopyFromNonRoot( *CReflect(GDist), root ) ) }

#define C_PROTO_BASE(SIG,SIGBASE,T) \
  /* Y := alpha X + Y */ \
  ElError ElAxpy_ ## SIG \
  ( CREFLECT(T) alpha, ElConstMatrix_ ## SIG X, ElMatrix_ ## SIG Y ) \
  { EL_TRY( Axpy( CReflect(alpha), *CReflect(X), *CReflect(Y) ) ) } \
  ElError ElAxpyDist_ ## SIG \
  ( CREFLECT(T) alpha, ElConstDistMatrix_ ## SIG X, ElDistMatrix_ ## SIG Y ) \
  { EL_TRY( Axpy( CReflect(alpha), *CReflect(X), *CReflect(Y) ) ) } \
  ElError ElAxpySparse_ ## SIG \
  ( CREFLECT(T) alpha, \
    ElConstSparseMatrix_ ## SIG X, ElSparseMatrix_ ## SIG Y ) \
  { EL_TRY( Axpy( CReflect(alpha), *CReflect(X), *CReflect(Y) ) ) } \
  ElError ElAxpyDistSparse_ ## SIG \
  ( CREFLECT(T) alpha, \
    ElConstDistSparseMatrix_ ## SIG X, ElDistSparseMatrix_ ## SIG Y ) \
  { EL_TRY( Axpy( CReflect(alpha), *CReflect(X), *CReflect(Y) ) ) } \
  /* tri(Y) := tri(alpha X + Y) */ \
  ElError ElAxpyTrapezoid_ ## SIG \
  ( ElUpperOrLower uplo, CREFLECT(T) alpha, \
    ElConstMatrix_ ## SIG X, ElMatrix_ ## SIG Y, ElInt offset ) \
  { EL_TRY \
    ( AxpyTrapezoid \
      ( CReflect(uplo), CReflect(alpha), \
        *CReflect(X), *CReflect(Y), offset ) ) } \
  ElError ElAxpyTrapezoidDist_ ## SIG \
  ( ElUpperOrLower uplo, CREFLECT(T) alpha, \
    ElConstDistMatrix_ ## SIG X, ElDistMatrix_ ## SIG Y, ElInt offset ) \
  { EL_TRY \
    ( AxpyTrapezoid \
      ( CReflect(uplo), CReflect(alpha), \
        *CReflect(X), *CReflect(Y), offset ) ) } \
  ElError ElAxpyTrapezoidSparse_ ## SIG \
  ( ElUpperOrLower uplo, CREFLECT(T) alpha, \
    ElConstSparseMatrix_ ## SIG X, ElSparseMatrix_ ## SIG Y, ElInt offset ) \
  { EL_TRY \
    ( AxpyTrapezoid \
      ( CReflect(uplo), CReflect(alpha), \
        *CReflect(X), *CReflect(Y), offset ) ) } \
  ElError ElAxpyTrapezoidDistSparse_ ## SIG \
  ( ElUpperOrLower uplo, CREFLECT(T) alpha, \
    ElConstDistSparseMatrix_ ## SIG X, ElDistSparseMatrix_ ## SIG Y, \
    ElInt offset ) \
  { EL_TRY \
    ( AxpyTrapezoid \
      ( CReflect(uplo), CReflect(alpha), \
        *CReflect(X), *CReflect(Y), offset ) ) } \
  /* B = A */ \
  ElError ElCopy_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElMatrix_ ## SIG B ) \
  { EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopyDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElDistMatrix_ ## SIG B ) \
  { EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopySparse_ ## SIG \
  ( ElConstSparseMatrix_ ## SIG A, ElSparseMatrix_ ## SIG B ) \
  { EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopyDistSparse_ ## SIG \
  ( ElConstDistSparseMatrix_ ## SIG A, ElDistSparseMatrix_ ## SIG B ) \
  { EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopySparseMatrixFromRoot_ ## SIG \
  ( ElConstDistSparseMatrix_ ## SIG ADist, ElSparseMatrix_ ## SIG A ) \
  { EL_TRY( CopyFromRoot( *CReflect(ADist), *CReflect(A) ) ) } \
  ElError ElCopySparseMatrixFromNonRoot_ ## SIG \
  ( ElConstDistSparseMatrix_ ## SIG ADist, ElInt root ) \
  { EL_TRY( CopyFromNonRoot( *CReflect(ADist), root ) ) } \
  ElError ElCopyDistMultiVec_ ## SIG \
  ( ElConstDistMultiVec_ ## SIG A, ElDistMultiVec_ ## SIG B ) \
  { EL_TRY( Copy( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopyMultiVecFromRoot_ ## SIG \
  ( ElConstDistMultiVec_ ## SIG A, ElMatrix_ ## SIG B ) \
  { EL_TRY( CopyFromRoot( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElCopyMultiVecFromNonRoot_ ## SIG \
  ( ElConstDistMultiVec_ ## SIG A, ElInt root ) \
  { EL_TRY( CopyFromNonRoot( *CReflect(A), root ) ) } \
  /* Dot product (<A,B>=vec(A)^H vec(B)) */ \
  ElError ElDot_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElConstMatrix_ ## SIG B, CREFLECT(T)* prod ) \
  { EL_TRY( *prod = CReflect(Dot(*CReflect(A),*CReflect(B))) ) } \
  ElError ElDotDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElConstDistMatrix_ ## SIG B, \
    CREFLECT(T)* prod ) \
  { EL_TRY( *prod = CReflect(Dot(*CReflect(A),*CReflect(B))) ) } \
  /* EntrywiseFill */ \
  ElError ElEntrywiseFill_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) (*fill)() ) \
  { try { \
      auto newFill = [&]() { return CReflect(fill()); }; \
      EntrywiseFill( *CReflect(A), std::function<T(void)>(newFill) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElEntrywiseFillDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) (*fill)() ) \
  { try { \
      auto newFill = [&]() { return CReflect(fill()); }; \
      EntrywiseFill( *CReflect(A), std::function<T(void)>(newFill) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  /* EntrywiseMap */ \
  ElError ElEntrywiseMap_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) (*func)(CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( T alpha ) \
        { return CReflect(func(CReflect(alpha))); }; \
      EntrywiseMap( *CReflect(A), std::function<T(T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElEntrywiseMapDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) (*func)(CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( T alpha ) \
        { return CReflect(func(CReflect(alpha))); }; \
      EntrywiseMap( *CReflect(A), std::function<T(T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElEntrywiseMapSparse_ ## SIG \
  ( ElSparseMatrix_ ## SIG A, CREFLECT(T) (*func)(CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( T alpha ) \
        { return CReflect(func(CReflect(alpha))); }; \
      EntrywiseMap( *CReflect(A), std::function<T(T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElEntrywiseMapDistSparse_ ## SIG \
  ( ElDistSparseMatrix_ ## SIG A, CREFLECT(T) (*func)(CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( T alpha ) \
        { return CReflect(func(CReflect(alpha))); }; \
      EntrywiseMap( *CReflect(A), std::function<T(T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  /* Fill */ \
  ElError ElFill_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) alpha ) \
  { EL_TRY( Fill( *CReflect(A), CReflect(alpha) ) ) } \
  ElError ElFillDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) alpha ) \
  { EL_TRY( Fill( *CReflect(A), CReflect(alpha) ) ) } \
  /* Hadamard */ \
  ElError ElHadamard_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElConstMatrix_ ## SIG B, ElMatrix_ ## SIG C ) \
  { EL_TRY( Hadamard(*CReflect(A),*CReflect(B),*CReflect(C)) ) } \
  ElError ElHadamardDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElConstDistMatrix_ ## SIG B, \
    ElDistMatrix_ ## SIG C ) \
  { EL_TRY( Hadamard(*CReflect(A),*CReflect(B),*CReflect(C)) ) } \
  /* Hilbert-Schmidt inner product (same as Dot) */ \
  ElError ElHilbertSchmidt_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElConstMatrix_ ## SIG B, CREFLECT(T)* prod ) \
  { EL_TRY( *prod = \
      CReflect(HilbertSchmidt(*CReflect(A),*CReflect(B))) ) } \
  ElError ElHilbertSchmidtDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElConstDistMatrix_ ## SIG B, \
    CREFLECT(T)* prod ) \
  { EL_TRY( *prod = \
      CReflect(HilbertSchmidt(*CReflect(A),*CReflect(B))) ) } \
  /* Imaginary part */ \
  ElError ElImagPart_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElMatrix_ ## SIGBASE AImag ) \
  { EL_TRY( ImagPart( *CReflect(A), *CReflect(AImag) ) ) } \
  ElError ElImagPartDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElDistMatrix_ ## SIGBASE AImag ) \
  { EL_TRY( ImagPart( *CReflect(A), *CReflect(AImag) ) ) } \
  /* IndexDependentFill */ \
  ElError ElIndexDependentFill_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) (*fill)(ElInt,ElInt) ) \
  { try { \
      auto newFill = [&]( Int i, Int j ) { return CReflect(fill(i,j)); }; \
      IndexDependentFill \
      ( *CReflect(A), std::function<T(Int,Int)>(newFill) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElIndexDependentFillDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) (*fill)(ElInt,ElInt) ) \
  { try { \
      auto newFill = [&]( Int i, Int j ) { return CReflect(fill(i,j)); }; \
      IndexDependentFill \
      ( *CReflect(A), std::function<T(Int,Int)>(newFill) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  /* IndexDependentMap */ \
  ElError ElIndexDependentMap_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) (*func)(ElInt,ElInt,CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( Int i, Int j, T alpha ) \
        { return CReflect(func(i,j,CReflect(alpha))); }; \
      IndexDependentMap \
      ( *CReflect(A), std::function<T(Int,Int,T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  ElError ElIndexDependentMapDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) (*func)(ElInt,ElInt,CREFLECT(T)) ) \
  { try { \
      auto newMap = [&]( Int i, Int j, T alpha ) \
        { return CReflect(func(i,j,CReflect(alpha))); }; \
      IndexDependentMap \
      ( *CReflect(A), std::function<T(Int,Int,T)>(newMap) ); \
    } EL_CATCH; return EL_SUCCESS; } \
  /* MakeSymmetric */ \
  ElError ElMakeSymmetric_ ## SIG \
  ( ElUpperOrLower uplo, ElMatrix_ ## SIG A ) \
  { EL_TRY( MakeSymmetric( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeSymmetricDist_ ## SIG \
  ( ElUpperOrLower uplo, ElDistMatrix_ ## SIG A ) \
  { EL_TRY( MakeSymmetric( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeSymmetricSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElSparseMatrix_ ## SIG A ) \
  { EL_TRY( MakeSymmetric( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeSymmetricDistSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElDistSparseMatrix_ ## SIG A ) \
  { EL_TRY( MakeSymmetric( CReflect(uplo), *CReflect(A) ) ) } \
  /* MakeTrapezoidal */ \
  ElError ElMakeTrapezoidal_ ## SIG \
  ( ElUpperOrLower uplo, ElMatrix_ ## SIG A, ElInt offset ) \
  { EL_TRY( MakeTrapezoidal( CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElMakeTrapezoidalDist_ ## SIG \
  ( ElUpperOrLower uplo, ElDistMatrix_ ## SIG A, ElInt offset ) \
  { EL_TRY( MakeTrapezoidal( CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElMakeTrapezoidalSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElSparseMatrix_ ## SIG A, ElInt offset ) \
  { EL_TRY( MakeTrapezoidal( CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElMakeTrapezoidalDistSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElDistSparseMatrix_ ## SIG A, ElInt offset ) \
  { EL_TRY( MakeTrapezoidal( CReflect(uplo), *CReflect(A), offset ) ) } \
  /* MaxAbs */ \
  ElError ElMaxAbs_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(MaxAbs(*CReflect(A))) ) } \
  ElError ElMaxAbsDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(MaxAbs(*CReflect(A))) ) } \
  ElError ElSymmetricMaxAbs_ ## SIG \
  ( ElUpperOrLower uplo, ElConstMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMaxAbs(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElSymmetricMaxAbsDist_ ## SIG \
  ( ElUpperOrLower uplo, ElConstDistMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMaxAbs(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElVectorMaxAbs_ ## SIG \
  ( ElConstMatrix_ ## SIG x, ElValueInt_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(VectorMaxAbs(*CReflect(x))) ) } \
  ElError ElVectorMaxAbsDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG x, ElValueInt_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(VectorMaxAbs(*CReflect(x))) ) } \
  /* MinAbs */ \
  ElError ElMinAbs_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(MinAbs(*CReflect(A))) ) } \
  ElError ElMinAbsDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(MinAbs(*CReflect(A))) ) } \
  ElError ElSymmetricMinAbs_ ## SIG \
  ( ElUpperOrLower uplo, ElConstMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMinAbs(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElSymmetricMinAbsDist_ ## SIG \
  ( ElUpperOrLower uplo, ElConstDistMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMinAbs(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElVectorMinAbs_ ## SIG \
  ( ElConstMatrix_ ## SIG x, ElValueInt_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(VectorMinAbs(*CReflect(x))) ) } \
  ElError ElVectorMinAbsDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG x, ElValueInt_ ## SIGBASE *entry ) \
  { EL_TRY( *entry = CReflect(VectorMinAbs(*CReflect(x))) ) } \
  /* TODO: QuasiDiagonalScale */ \
  /* Scale */ \
  ElError ElScale_ ## SIG \
  ( CREFLECT(T) alpha, ElMatrix_ ## SIG A ) \
  { EL_TRY( Scale( CReflect(alpha), *CReflect(A) ) ) } \
  ElError ElScaleDist_ ## SIG \
  ( CREFLECT(T) alpha, ElDistMatrix_ ## SIG A ) \
  { EL_TRY( Scale( CReflect(alpha), *CReflect(A) ) ) } \
  ElError ElScaleSparse_ ## SIG \
  ( CREFLECT(T) alpha, ElSparseMatrix_ ## SIG A ) \
  { EL_TRY( Scale( CReflect(alpha), *CReflect(A) ) ) } \
  ElError ElScaleDistSparse_ ## SIG \
  ( CREFLECT(T) alpha, ElDistSparseMatrix_ ## SIG A ) \
  { EL_TRY( Scale( CReflect(alpha), *CReflect(A) ) ) } \
  ElError ElScaleDistMultiVec_ ## SIG \
  ( CREFLECT(T) alpha, ElDistMultiVec_ ## SIG A ) \
  { EL_TRY( Scale( CReflect(alpha), *CReflect(A) ) ) } \
  /* Real part */ \
  ElError ElRealPart_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElMatrix_ ## SIGBASE AReal ) \
  { EL_TRY( RealPart( *CReflect(A), *CReflect(AReal) ) ) } \
  ElError ElRealPartDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElDistMatrix_ ## SIGBASE AReal ) \
  { EL_TRY( RealPart( *CReflect(A), *CReflect(AReal) ) ) } \
  /* ScaleTrapezoid */ \
  ElError ElScaleTrapezoid_ ## SIG \
  ( CREFLECT(T) alpha, ElUpperOrLower uplo, ElMatrix_ ## SIG A, ElInt offset ) \
  { EL_TRY( ScaleTrapezoid \
      ( CReflect(alpha), CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElScaleTrapezoidDist_ ## SIG \
  ( CREFLECT(T) alpha, ElUpperOrLower uplo, ElDistMatrix_ ## SIG A, \
    ElInt offset ) \
  { EL_TRY( ScaleTrapezoid \
      ( CReflect(alpha), CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElScaleTrapezoidSparse_ ## SIG \
  ( CREFLECT(T) alpha, ElUpperOrLower uplo, ElSparseMatrix_ ## SIG A, \
    ElInt offset ) \
  { EL_TRY( ScaleTrapezoid \
      ( CReflect(alpha), CReflect(uplo), *CReflect(A), offset ) ) } \
  ElError ElScaleTrapezoidDistSparse_ ## SIG \
  ( CREFLECT(T) alpha, ElUpperOrLower uplo, ElDistSparseMatrix_ ## SIG A, \
    ElInt offset ) \
  { EL_TRY( ScaleTrapezoid \
      ( CReflect(alpha), CReflect(uplo), *CReflect(A), offset ) ) } \
  /* SetDiagonal */ \
  ElError ElSetDiagonal_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( SetDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  ElError ElSetDiagonalDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( SetDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  /* Swap */ \
  ElError ElSwap_ ## SIG \
  ( ElOrientation orientation, ElMatrix_ ## SIG X, ElMatrix_ ## SIG Y ) \
  { EL_TRY( \
      Swap( CReflect(orientation), *CReflect(X), *CReflect(Y) ) ) } \
  ElError ElSwapDist_ ## SIG \
  ( ElOrientation orientation, \
    ElDistMatrix_ ## SIG X, ElDistMatrix_ ## SIG Y ) \
  { EL_TRY( \
      Swap( CReflect(orientation), *CReflect(X), *CReflect(Y) ) ) } \
  ElError ElRowSwap_ ## SIG \
  ( ElMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( RowSwap( *CReflect(A), to, from ) ) } \
  ElError ElRowSwapDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( RowSwap( *CReflect(A), to, from ) ) } \
  ElError ElColSwap_ ## SIG \
  ( ElMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( ColSwap( *CReflect(A), to, from ) ) } \
  ElError ElColSwapDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( ColSwap( *CReflect(A), to, from ) ) } \
  ElError ElSymmetricSwap_ ## SIG \
  ( ElUpperOrLower uplo, ElMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( SymmetricSwap( CReflect(uplo), *CReflect(A), to, from ) ) } \
  ElError ElSymmetricSwapDist_ ## SIG \
  ( ElUpperOrLower uplo, ElDistMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( SymmetricSwap( CReflect(uplo), *CReflect(A), to, from ) ) } \
  /* TODO: Symmetric2x2Scale */ \
  /* B = A^T */ \
  ElError ElTranspose_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElMatrix_ ## SIG B ) \
  { EL_TRY( Transpose(*CReflect(A),*CReflect(B),false) ) } \
  ElError ElTransposeDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElDistMatrix_ ## SIG B ) \
  { EL_TRY( Transpose(*CReflect(A),*CReflect(B),false) ) } \
  ElError ElTransposeSparse_ ## SIG \
  ( ElConstSparseMatrix_ ## SIG A, ElSparseMatrix_ ## SIG B ) \
  { EL_TRY( Transpose(*CReflect(A),*CReflect(B),false) ) } \
  ElError ElTransposeDistSparse_ ## SIG \
  ( ElConstDistSparseMatrix_ ## SIG A, ElDistSparseMatrix_ ## SIG B ) \
  { EL_TRY( Transpose(*CReflect(A),*CReflect(B),false) ) } \
  /* UpdateDiagonal */ \
  ElError ElUpdateDiagonal_ ## SIG \
  ( ElMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( UpdateDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  ElError ElUpdateDiagonalDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( UpdateDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  ElError ElUpdateDiagonalSparse_ ## SIG \
  ( ElSparseMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( UpdateDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  ElError ElUpdateDiagonalDistSparse_ ## SIG \
  ( ElDistSparseMatrix_ ## SIG A, CREFLECT(T) alpha, ElInt offset ) \
  { EL_TRY( UpdateDiagonal( *CReflect(A), CReflect(alpha), offset ) ) } \
  /* Zero */ \
  ElError ElZero_ ## SIG ( ElMatrix_ ## SIG A ) \
  { EL_TRY( Zero( *CReflect(A) ) ) } \
  ElError ElZeroDist_ ## SIG ( ElDistMatrix_ ## SIG A ) \
  { EL_TRY( Zero( *CReflect(A) ) ) }

#define C_PROTO_REALONLY(SIG,Real) \
  /* DiagonalSolve */ \
  ElError ElDiagonalSolve_ ## SIG \
  ( ElLeftOrRight side, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalSolve \
      ( CReflect(side), NORMAL, \
        *CReflect(d), *CReflect(X) ) ) } \
  ElError ElDiagonalSolveDist_ ## SIG \
  ( ElLeftOrRight side, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalSolve \
      ( CReflect(side), NORMAL, \
        *CReflect(d), *CReflect(X) ) ) }

#define C_PROTO_NOCOMPLEX(SIG,T) \
  /* DiagonalScale */ \
  ElError ElDiagonalScale_ ## SIG \
  ( ElLeftOrRight side, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalScale( CReflect(side), NORMAL, *CReflect(d), *CReflect(X) ) ) } \
  ElError ElDiagonalScaleDist_ ## SIG \
  ( ElLeftOrRight side, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalScale( CReflect(side), NORMAL, *CReflect(d), *CReflect(X) ) ) } \
  /* DiagonalScaleTrapezoid */ \
  ElError ElDiagonalScaleTrapezoid_ ## SIG \
  ( ElLeftOrRight side, ElUpperOrLower uplo, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X, ElInt offset ) \
  { EL_TRY( \
      DiagonalScaleTrapezoid \
      ( CReflect(side), CReflect(uplo), NORMAL, \
        *CReflect(d), *CReflect(X), offset ) ) } \
  ElError ElDiagonalScaleTrapezoidDist_ ## SIG \
  ( ElLeftOrRight side, ElUpperOrLower uplo, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X, ElInt offset ) \
  { EL_TRY( \
      DiagonalScaleTrapezoid \
      ( CReflect(side), CReflect(uplo), NORMAL, \
        *CReflect(d), *CReflect(X), offset ) ) } \
  /* Unconjugated dot product, vec(A)^T vec(B) */ \
  ElError ElDotu_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElConstMatrix_ ## SIG B, CREFLECT(T)* prod ) \
  { EL_TRY( *prod = CReflect(Dotu(*CReflect(A),*CReflect(B))) ) } \
  ElError ElDotuDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElConstDistMatrix_ ## SIG B, \
    CREFLECT(T)* prod ) \
  { EL_TRY( *prod = CReflect(Dotu(*CReflect(A),*CReflect(B))) ) } \
  /* Max */ \
  ElError ElMax_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(Max(*CReflect(A))) ) } \
  ElError ElMaxDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(Max(*CReflect(A))) ) } \
  ElError ElSymmetricMax_ ## SIG \
  ( ElUpperOrLower uplo, ElConstMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMax(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElSymmetricMaxDist_ ## SIG \
  ( ElUpperOrLower uplo, ElConstDistMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMax(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElVectorMax_ ## SIG \
  ( ElConstMatrix_ ## SIG x, ElValueInt_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(VectorMax(*CReflect(x))) ) } \
  ElError ElVectorMaxDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG x, ElValueInt_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(VectorMax(*CReflect(x))) ) } \
  /* Min */ \
  ElError ElMin_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(Min(*CReflect(A))) ) } \
  ElError ElMinDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(Min(*CReflect(A))) ) } \
  ElError ElSymmetricMin_ ## SIG \
  ( ElUpperOrLower uplo, ElConstMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMin(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElSymmetricMinDist_ ## SIG \
  ( ElUpperOrLower uplo, ElConstDistMatrix_ ## SIG A, \
    ElValueIntPair_ ## SIG *entry ) \
  { EL_TRY( *entry = \
      CReflect(SymmetricMin(CReflect(uplo),*CReflect(A))) ) } \
  ElError ElVectorMin_ ## SIG \
  ( ElConstMatrix_ ## SIG x, ElValueInt_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(VectorMin(*CReflect(x))) ) } \
  ElError ElVectorMinDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG x, ElValueInt_ ## SIG *entry ) \
  { EL_TRY( *entry = CReflect(VectorMin(*CReflect(x))) ) }

#define C_PROTO_FIELD(SIG,SIGBASE,F) \
  /* Column norms */ \
  ElError ElColumnNormsDistMultiVec_ ## SIG \
  ( ElConstDistMultiVec_ ## SIG A, ElMatrix_ ## SIGBASE norms ) \
  { EL_TRY( ColumnNorms( *CReflect(A), *CReflect(norms) ) ) } \
  /* Nrm2 (same as FrobeniusNorm) */ \
  ElError ElNrm2_ ## SIG \
  ( ElConstMatrix_ ## SIG A, Base<F>* norm ) \
  { EL_TRY( *norm = Nrm2(*CReflect(A)) ) } \
  ElError ElNrm2Dist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, Base<F>* norm ) \
  { EL_TRY( *norm = Nrm2(*CReflect(A)) ) } \
  ElError ElNrm2DistMultiVec_ ## SIG \
  ( ElConstDistMultiVec_ ## SIG A, Base<F>* norm ) \
  { EL_TRY( *norm = Nrm2( *CReflect(A) ) ) } \
  /* TODO: QuasiDiagonalSolve */ \
  /* TODO: Symmetric2x2Inv */ \
  /* TODO: Symmetric2x2Solve */

#define C_PROTO_INT(SIG,T) \
  C_PROTO_BASE(SIG,SIG,T) \
  C_PROTO_NOCOMPLEX(SIG,T)

#define C_PROTO_REAL(SIG,Real) \
  C_PROTO_BASE(SIG,SIG,Real) \
  C_PROTO_NOCOMPLEX(SIG,Real) \
  C_PROTO_REALONLY(SIG,Real) \
  C_PROTO_FIELD(SIG,SIG,Real)

#define C_PROTO_COMPLEX(SIG,SIGBASE,T) \
  C_PROTO_BASE(SIG,SIGBASE,T) \
  C_PROTO_FIELD(SIG,SIGBASE,T) \
  /* B = A^H */ \
  ElError ElAdjoint_ ## SIG \
  ( ElConstMatrix_ ## SIG A, ElMatrix_ ## SIG B ) \
  { EL_TRY( Adjoint( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElAdjointDist_ ## SIG \
  ( ElConstDistMatrix_ ## SIG A, ElDistMatrix_ ## SIG B ) \
  { EL_TRY( Adjoint( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElAdjointSparse_ ## SIG \
  ( ElConstSparseMatrix_ ## SIG A, ElSparseMatrix_ ## SIG B ) \
  { EL_TRY( Adjoint( *CReflect(A), *CReflect(B) ) ) } \
  ElError ElAdjointDistSparse_ ## SIG \
  ( ElConstDistSparseMatrix_ ## SIG A, ElDistSparseMatrix_ ## SIG B ) \
  { EL_TRY( Adjoint( *CReflect(A), *CReflect(B) ) ) } \
  /* Conjugate */ \
  ElError ElConjugate_ ## SIG( ElMatrix_ ## SIG A ) \
  { EL_TRY( Conjugate( *CReflect(A) ) ) } \
  ElError ElConjugateDist_ ## SIG( ElDistMatrix_ ## SIG A ) \
  { EL_TRY( Conjugate( *CReflect(A) ) ) } \
  /* DiagonalScale */ \
  ElError ElDiagonalScale_ ## SIG \
  ( ElLeftOrRight side, ElOrientation orientation, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalScale \
      ( CReflect(side), CReflect(orientation), \
        *CReflect(d), *CReflect(X) ) ) } \
  ElError ElDiagonalScaleDist_ ## SIG \
  ( ElLeftOrRight side, ElOrientation orientation, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalScale \
      ( CReflect(side), CReflect(orientation), \
        *CReflect(d), *CReflect(X) ) ) } \
  /* DiagonalScaleTrapezoid */ \
  ElError ElDiagonalScaleTrapezoid_ ## SIG \
  ( ElLeftOrRight side, ElUpperOrLower uplo, ElOrientation orientation, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X, ElInt offset ) \
  { EL_TRY( \
      DiagonalScaleTrapezoid \
      ( CReflect(side), CReflect(uplo), CReflect(orientation), \
        *CReflect(d), *CReflect(X), offset ) ) } \
  ElError ElDiagonalScaleTrapezoidDist_ ## SIG \
  ( ElLeftOrRight side, ElUpperOrLower uplo, ElOrientation orientation, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X, ElInt offset ) \
  { EL_TRY( \
      DiagonalScaleTrapezoid \
      ( CReflect(side), CReflect(uplo), CReflect(orientation), \
        *CReflect(d), *CReflect(X), offset ) ) } \
  /* DiagonalSolve */ \
  ElError ElDiagonalSolve_ ## SIG \
  ( ElLeftOrRight side, ElOrientation orientation, \
    ElConstMatrix_ ## SIG d, ElMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalSolve \
      ( CReflect(side), CReflect(orientation), \
        *CReflect(d), *CReflect(X) ) ) } \
  ElError ElDiagonalSolveDist_ ## SIG \
  ( ElLeftOrRight side, ElOrientation orientation, \
    ElConstDistMatrix_ ## SIG d, ElDistMatrix_ ## SIG X ) \
  { EL_TRY( \
      DiagonalSolve \
      ( CReflect(side), CReflect(orientation), \
        *CReflect(d), *CReflect(X) ) ) } \
  /* HermitianSwap */ \
  ElError ElHermitianSwap_ ## SIG \
  ( ElUpperOrLower uplo, ElMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( HermitianSwap( CReflect(uplo), *CReflect(A), to, from ) ) } \
  ElError ElHermitianSwapDist_ ## SIG \
  ( ElUpperOrLower uplo, ElDistMatrix_ ## SIG A, ElInt to, ElInt from ) \
  { EL_TRY( HermitianSwap( CReflect(uplo), *CReflect(A), to, from ) ) } \
  /* MakeHermitian */ \
  ElError ElMakeHermitian_ ## SIG \
  ( ElUpperOrLower uplo, ElMatrix_ ## SIG A ) \
  { EL_TRY( MakeHermitian( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeHermitianDist_ ## SIG \
  ( ElUpperOrLower uplo, ElDistMatrix_ ## SIG A ) \
  { EL_TRY( MakeHermitian( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeHermitianSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElSparseMatrix_ ## SIG A ) \
  { EL_TRY( MakeHermitian( CReflect(uplo), *CReflect(A) ) ) } \
  ElError ElMakeHermitianDistSparse_ ## SIG \
  ( ElUpperOrLower uplo, ElDistSparseMatrix_ ## SIG A ) \
  { EL_TRY( MakeHermitian( CReflect(uplo), *CReflect(A) ) ) } \
  /* MakeReal */ \
  ElError ElMakeReal_ ## SIG \
  ( ElMatrix_ ## SIG A ) { EL_TRY( MakeReal( *CReflect(A) ) ) } \
  ElError ElMakeRealDist_ ## SIG \
  ( ElDistMatrix_ ## SIG A ) { EL_TRY( MakeReal( *CReflect(A) ) ) }

#include "El/macros/CInstantiate.h"

} // extern "C"
