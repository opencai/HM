/* ====================================================================================================================

	The copyright in this software is being made available under the License included below.
	This software may be subject to other third party and 	contributor rights, including patent rights, and no such
	rights are granted under this license.

	Copyright (c) 2010, SAMSUNG ELECTRONICS CO., LTD. and BRITISH BROADCASTING CORPORATION
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are permitted only for
	the purpose of developing standards within the Joint Collaborative Team on Video Coding and for testing and
	promoting such standards. The following conditions are required to be met:

		* Redistributions of source code must retain the above copyright notice, this list of conditions and
		  the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
		  the following disclaimer in the documentation and/or other materials provided with the distribution.
		* Neither the name of SAMSUNG ELECTRONICS CO., LTD. nor the name of the BRITISH BROADCASTING CORPORATION
		  may be used to endorse or promote products derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 * ====================================================================================================================
*/

/** \file			TComPrediction.h
    \brief		prediction class (header)
*/

#ifndef __TCOMPREDICTION__
#define __TCOMPREDICTION__


// Include files
#include "TComPic.h"
#include "TComMotionInfo.h"
#include "TComPattern.h"
#include "TComTrQuant.h"
#include "TComPredFilter.h"

// ====================================================================================================================
// Class definition
// ====================================================================================================================

/// prediction class
class TComPrediction : public TComPredFilter
{
protected:
  Int*			m_piYuvExt;
  Int       m_iYuvExtStride;
  Int       m_iYuvExtHeight;
  Int 			m_iDIFHalfTap;

  TComYuv   m_acYuvPred[2];
  TComYuv   m_cYuvPredTemp;
  TComYuv   m_cYuvExt;

  // ADI functions
	Void xPredIntraAngleAdi				( Int* pSrc, Int iSrcStride, Pel*& tpDst, Int iDstStride, UInt iWidth, UInt iHeight, UInt uiDirMode );
  Void xPredIntraVertAdi				( Int* pSrc, Int iSrcStride, Pel*& tpDst, Int iDstStride, UInt iWidth, UInt iHeight );
  Void xPredIntraHorAdi					( Int* pSrc, Int iSrcStride, Pel*& tpDst, Int iDstStride, UInt iWidth, UInt iHeight );
  Void xPredIntraDCAdi					( Int* pSrc, Int iSrcStride, Pel*& tpDst, Int iDstStride, UInt iWidth, UInt iHeight, Bool bAboveAvail, Bool bLeftAvail );
  Void xPredIntraPlaneAdi				( Int* pSrc, Int iSrcStride, Pel*& tpDst, Int iDstStride, UInt iWidth, UInt iHeight );
  Void xPredIntraBiAdi					( Int* pSrc, Int iSrcStride, Pel*& rpDst, Int iDstStride, UInt iWidth, UInt iHeight );
  __inline Int xGetContextPixel	( UInt uiDirMode, UInt uiXYflag, Int iTempD, Bool& bCenter );

  // motion compensation functions
  Void xPredInterUni            ( TComDataCU* pcCU,                          UInt uiPartAddr,               Int iWidth, Int iHeight, RefPicList eRefPicList, TComYuv*& rpcYuvPred, Int iPartIdx					 );
  Void xPredInterBi             ( TComDataCU* pcCU,                          UInt uiPartAddr,               Int iWidth, Int iHeight,                         TComYuv*& rpcYuvPred, Int iPartIdx					 );
  Void xPredInterLumaBlk        ( TComDataCU* pcCU, TComPicYuv* pcPicYuvRef, UInt uiPartAddr, TComMv* pcMv, Int iWidth, Int iHeight,                         TComYuv*& rpcYuv );
  Void xPredInterChromaBlk      ( TComDataCU* pcCU, TComPicYuv* pcPicYuvRef, UInt uiPartAddr, TComMv* pcMv, Int iWidth, Int iHeight,												 TComYuv*& rpcYuv                            );
  Void xWeightedAverage					( TComDataCU* pcCU, TComYuv* pcYuvSrc0, TComYuv* pcYuvSrc1, Int iRefIdx0, Int iRefIdx1, UInt uiPartAddr, Int iWidth, Int iHeight, TComYuv*& rpcYuvDst );

public:
  TComPrediction();
  virtual ~TComPrediction();

  Void		initTempBuff();

	// inter
  Void motionCompensation					( TComDataCU*  pcCU, TComYuv* pcYuvPred, RefPicList eRefPicList = REF_PIC_LIST_X, Int iPartIdx = -1 );

	// motion vector prediction
  Void getMvPredAMVP							( TComDataCU* pcCU, UInt uiPartIdx, UInt uiPartAddr, RefPicList eRefPicList, Int iRefIdx, TComMv& rcMvPred );

  // ADI
  Void predIntraLumaAdi						( TComPattern* pcTComPattern,             UInt uiDirMode, Pel* piPred, UInt uiStride, Int iWidth, Int iHeight,  TComDataCU* pcCU, Bool bAbove, Bool bLeft );
  Void predIntraChromaAdi					( TComPattern* pcTComPattern, Int* piSrc, UInt uiDirMode, Pel* piPred, UInt uiStride, Int iWidth, Int iHeight,  TComDataCU* pcCU, Bool bAbove, Bool bLeft );

	// CIP
	Void recIntraLumaCIP						( TComPattern* pcTComPattern, Pel* pPred, Pel* pResi, Pel* pReco, UInt uiStride, Int iWidth, Int iHeight, TComDataCU* pcCU, Bool bAboveAvail, Bool bLeftAvail );

  Int* getPredicBuf()							{ return m_piYuvExt;			}
  Int  getPredicBufWidth()				{ return m_iYuvExtStride; }
  Int  getPredicBufHeight()				{ return m_iYuvExtHeight; }
};


#endif // __TCOMPREDICTION__
