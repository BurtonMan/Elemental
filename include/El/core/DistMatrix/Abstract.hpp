/*
   Copyright (c) 2009-2014, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef EL_DISTMATRIX_ABSTRACT_DECL_HPP
#define EL_DISTMATRIX_ABSTRACT_DECL_HPP

namespace El {

template<typename T> 
class AbstractDistMatrix
{
public:
    // Typedefs
    // ========
    typedef AbstractDistMatrix<T> type;

    // Constructors and destructors
    // ============================
    // Move constructor
    AbstractDistMatrix( type&& A ) EL_NOEXCEPT;

    virtual ~AbstractDistMatrix();

    virtual AbstractDistMatrix<T>* Construct
    ( const El::Grid& g, Int root ) const = 0;
    virtual AbstractDistMatrix<T>* ConstructTranspose
    ( const El::Grid& g, Int root ) const = 0;
    virtual AbstractDistMatrix<T>* ConstructDiagonal
    ( const El::Grid& g, Int root ) const = 0;
    // TODO: ConstructPartialCol and friends?

    // Assignment and reconfiguration
    // ==============================
    // Move assignment
    type& operator=( type&& A );

    void Empty();
    void EmptyData();
    void SetGrid( const El::Grid& grid );
    void Resize( Int height, Int width );
    void Resize( Int height, Int width, Int ldim );
    void MakeConsistent( bool includingViewers=false );
    void MakeSizeConsistent( bool includingViewers=false );

    // Realignment
    // -----------
    void Align( Int colAlign, Int rowAlign, bool constrain=true );
    void AlignCols( Int colAlign, bool constrain=true );
    void AlignRows( Int rowAlign, bool constrain=true );
    void FreeAlignments();
    void SetRoot( Int root, bool constrain=true );
    void AlignWith
    ( const El::DistData& data, bool constrain=true, bool allowMismatch=false );
    void AlignColsWith
    ( const El::DistData& data, bool constrain=true, bool allowMismatch=false );
    void AlignRowsWith
    ( const El::DistData& data, bool constrain=true, bool allowMismatch=false );
    void AlignAndResize
    ( Int colAlign, Int rowAlign, Int height, Int width, 
      bool force=false, bool constrain=true );
    void AlignColsAndResize
    ( Int colAlign, Int height, Int width, 
      bool force=false, bool constrain=true );
    void AlignRowsAndResize
    ( Int rowAlign, Int height, Int width, 
      bool force=false, bool constrain=true );

    // Buffer attachment
    // -----------------
    // (Immutable) view of a distributed matrix's buffer
    void Attach
    ( Int height, Int width, const El::Grid& grid, 
      Int colAlign, Int rowAlign, T* buffer, Int ldim, Int root=0 );
    void LockedAttach
    ( Int height, Int width, const El::Grid& grid,
      Int colAlign, Int rowAlign, const T* buffer, Int ldim, Int root=0 );
    void Attach
    ( Int height, Int width, const El::Grid& grid,
      Int colAlign, Int rowAlign, El::Matrix<T>& A, Int root=0 );
    void LockedAttach
    ( Int height, Int width, const El::Grid& grid,
      Int colAlign, Int rowAlign, const El::Matrix<T>& A, Int root=0 );

    // Basic queries
    // =============

    // Global matrix information
    // -------------------------
    Int  Height()                       const;
    Int  Width()                        const;
    Int  DiagonalLength( Int offset=0 ) const;
    bool Viewing()                      const;
    bool Locked()                       const;

    // Local matrix information
    // ------------------------
          Int            LocalHeight()                      const;
          Int            LocalWidth()                       const;
          Int            LDim()                             const;
          El::Matrix<T>& Matrix();
    const El::Matrix<T>& LockedMatrix()                     const;
          size_t         AllocatedMemory()                  const;
          T*             Buffer();
          T*             Buffer( Int iLoc, Int jLoc );
    const T*             LockedBuffer()                     const;
    const T*             LockedBuffer( Int iLoc, Int jLoc ) const;

    // Distribution information
    // ------------------------
            const El::Grid&    Grid()                  const;
                  Int          ColAlign()              const;
                  Int          RowAlign()              const;
                  Int          ColShift()              const;
                  Int          RowShift()              const;
                  bool         ColConstrained()        const;
                  bool         RowConstrained()        const;
                  bool         RootConstrained()       const;
                  bool         Participating()         const;
                  Int          RowOwner( Int i )       const;     
                  Int          ColOwner( Int j )       const;     
                  Int          Owner( Int i, Int j )   const; 
                  Int          LocalRow( Int i )       const;     
                  Int          LocalCol( Int j )       const; 
                  Int          LocalRowOffset( Int i ) const; 
                  Int          LocalColOffset( Int j ) const; 
                  Int          GlobalRow( Int iLoc )   const;
                  Int          GlobalCol( Int jLoc )   const;
                  bool         IsLocalRow( Int i )     const; 
                  bool         IsLocalCol( Int j )     const;
                  bool         IsLocal( Int i, Int j ) const;
    virtual       Dist         ColDist()               const = 0;
    virtual       Dist         RowDist()               const = 0;
    virtual       Dist         CollectedColDist()      const = 0;
    virtual       Dist         CollectedRowDist()      const = 0;
    virtual       Dist         PartialColDist()        const = 0;
    virtual       Dist         PartialRowDist()        const = 0;
    virtual       Dist         PartialUnionColDist()   const = 0;
    virtual       Dist         PartialUnionRowDist()   const = 0;
    virtual       mpi::Comm    ColComm()               const = 0;
    virtual       mpi::Comm    RowComm()               const = 0;
    virtual       mpi::Comm    PartialColComm()        const;
    virtual       mpi::Comm    PartialRowComm()        const;
    virtual       mpi::Comm    PartialUnionColComm()   const;
    virtual       mpi::Comm    PartialUnionRowComm()   const;
    virtual       mpi::Comm    DistComm()              const = 0;
    virtual       mpi::Comm    CrossComm()             const = 0;
    virtual       mpi::Comm    RedundantComm()         const = 0;
    virtual       Int          ColStride()             const = 0;
    virtual       Int          RowStride()             const = 0;
    virtual       Int          PartialColStride()      const;
    virtual       Int          PartialRowStride()      const;
    virtual       Int          PartialUnionColStride() const;
    virtual       Int          PartialUnionRowStride() const;
    virtual       Int          DistSize()              const = 0;
    virtual       Int          CrossSize()             const = 0;
    virtual       Int          RedundantSize()         const = 0;
                  Int          ColRank()               const;
                  Int          RowRank()               const;
                  Int          PartialColRank()        const;
                  Int          PartialRowRank()        const;
                  Int          PartialUnionColRank()   const;
                  Int          PartialUnionRowRank()   const; 
                  Int          DistRank()              const;
                  Int          CrossRank()             const;
                  Int          RedundantRank()         const;
                  Int          Root()                  const;
    virtual       El::DistData DistData()              const = 0;

    // Single-entry manipulation
    // =========================

    // Global entry manipulation 
    // -------------------------
    // NOTE: Local entry manipulation is often much faster and should be
    //       preferred in most circumstances where performance matters.
    T       Get( Int i, Int j )                            const;
    Base<T> GetRealPart( Int i, Int j )                    const;
    Base<T> GetImagPart( Int i, Int j )                    const;
    void    Set( Int i, Int j, T alpha );
    void    SetRealPart( Int i, Int j, Base<T> alpha );
    void    SetImagPart( Int i, Int j, Base<T> alpha );
    void    Update( Int i, Int j, T alpha );
    void    UpdateRealPart( Int i, Int j, Base<T> alpha );
    void    UpdateImagPart( Int i, Int j, Base<T> alpha );
    void    MakeReal( Int i, Int j );
    void    Conjugate( Int i, Int j );

    // Local entry manipulation
    // ------------------------
    // NOTE: Clearly each of the following routines could instead be performed
    //       via composing [Locked]Matrix() with the corresponding local
    //       routine, but a large amount of code might need to change if 
    //       these were removed.
    T       GetLocal( Int iLoc, Int jLoc )                            const;
    Base<T> GetLocalRealPart( Int iLoc, Int jLoc )                    const;
    Base<T> GetLocalImagPart( Int iLoc, Int jLoc )                    const;
    void    SetLocal( Int iLoc, Int jLoc, T alpha );
    void    SetLocalRealPart( Int iLoc, Int jLoc, Base<T> alpha );
    void    SetLocalImagPart( Int iLoc, Int jLoc, Base<T> alpha );
    void    UpdateLocal( Int iLoc, Int jLoc, T alpha );
    void    UpdateLocalRealPart( Int iLoc, Int jLoc, Base<T> alpha );
    void    UpdateLocalImagPart( Int iLoc, Int jLoc, Base<T> alpha );
    void    MakeLocalReal( Int iLoc, Int jLoc );
    void    ConjugateLocal( Int iLoc, Int jLoc );

    // Diagonal manipulation
    // =====================
    bool DiagonalAlignedWith( const El::DistData& d, Int offset=0 ) const;
    Int DiagonalRoot( Int offset=0 ) const;
    Int DiagonalAlign( Int offset=0 ) const;

    // Interact over a specified communicator
    // ======================================
    void BroadcastOver( mpi::Comm comm, Int rank=0 );
    void SumOver( mpi::Comm comm );

    // Assertions
    // ==========
    void ComplainIfReal() const;
    void AssertNotLocked() const;
    void AssertNotStoringData() const;
    void AssertValidEntry( Int i, Int j ) const;
    void AssertValidSubmatrix( Int i, Int j, Int height, Int width ) const;
    void AssertSameSize( Int height, Int width ) const;

protected:
    // Member variables
    // ================

    // Global and local matrix information 
    // -----------------------------------
    ViewType viewType_;
    Int height_, width_;
    El::Matrix<T> matrix_;
    
    // Process grid and distribution metadata
    // --------------------------------------
    bool colConstrained_, rowConstrained_, rootConstrained_;
    Int colAlign_, rowAlign_,
        colShift_, rowShift_;
    Int root_;
    const El::Grid* grid_;

    // Private constructors
    // ====================
    // Create a 0 x 0 distributed matrix
    AbstractDistMatrix( const El::Grid& g=DefaultGrid(), Int root=0 );

    // Exchange metadata with another matrix
    // =====================================
    virtual void ShallowSwap( type& A );

    // Modify the distribution metadata
    // ================================
    void SetShifts();
    void SetColShift();
    void SetRowShift();
    void SetGrid();

    // Friend declarations
    // ===================
    template<typename S,Dist J,Dist K> friend class GeneralDistMatrix;
    template<typename S,Dist J,Dist K> friend class DistMatrix;

    template<typename S,Dist J,Dist K> friend class GeneralBlockDistMatrix;
    template<typename S,Dist J,Dist K> friend class BlockDistMatrix;
};

template<typename T>
void AssertConforming1x2
( const AbstractDistMatrix<T>& AL, const AbstractDistMatrix<T>& AR );

template<typename T>
void AssertConforming2x1
( const AbstractDistMatrix<T>& AT, const AbstractDistMatrix<T>& AB );

template<typename T>
void AssertConforming2x2
( const AbstractDistMatrix<T>& ATL, const AbstractDistMatrix<T>& ATR,
  const AbstractDistMatrix<T>& ABL, const AbstractDistMatrix<T>& ABR );

} // namespace El

#endif // ifndef EL_DISTMATRIX_ABSTRACT_DECL_HPP
