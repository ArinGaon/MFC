#pragma once

#include "CoordBaseDef.h"

namespace NS_SALUS_MS_APP
{
	// *****************************************************************************
	//  WGS-84 Datum and Unit Conversion Parameter Definition
	// *****************************************************************************

	class AFX_EXT_CLASS CGeoCoord
	{
	public:
		CGeoCoord();

	public:
		// *****************************************************************************
		//  Coordinate Conversion Function Definition
		// *****************************************************************************
		static void ENU2LLA(T_GEO_POS3D* const pRefLLA, T_CART_POS3D* const pENU, T_GEO_POS3D* const pLLA);
		static void ENU2ECEF(T_GEO_POS3D* const pLLA, T_CART_POS3D* const pENU, T_CART_POS3D* const pECEF);
		static void ECEF2LLA(T_CART_POS3D* const pECEF, T_GEO_POS3D* const pLLA);
		static void LLA2ENU(T_GEO_POS3D* const pLLA, T_GEO_POS3D* const pRefLLA, T_CART_POS3D* const pENU);
		static void ECEF2ENU(T_CART_POS3D* const pECEF, T_GEO_POS3D* const pLLA, T_CART_POS3D* const pENU);
		static void LLA2ECEF(T_GEO_POS3D* const pLLA, T_CART_POS3D* const pECEF);
		static void Geodetic2Geocentric(T_GEO_POS3D* const pGdLLA, T_GEO_POS3D* const pGcLLA);
		static void Geocentric2Geodetic(T_GEO_POS3D* const pGcLLA, T_GEO_POS3D* const pGdLLA);

		static DOUBLE CalcDistance(const DOUBLE dLat1, const DOUBLE dLon1, const DOUBLE dLat2, const DOUBLE dLon2);
		static DOUBLE GetRefLongitudeWithDistance(const DOUBLE dX, const DOUBLE dY, const DOUBLE dR);
		static DOUBLE GetRefLatitudeWithDistance(const DOUBLE dY, const DOUBLE dR, const BOOL bUpper);

		static void InverseVincenty(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dDstLat, const DOUBLE dDstLon, DOUBLE* const pRange, DOUBLE* const pBearing);
		static void DirectVincenty(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dRange, const DOUBLE dBearing, DOUBLE* const pDstLat, DOUBLE* const pDstLon);
		static void LL2EN(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dTgtLat, const DOUBLE dTgtLon, DOUBLE* const pX, DOUBLE* const pY);
		static void EN2LL(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dX, const DOUBLE dY, DOUBLE* const pTgtLat, DOUBLE* const pTgtLon);

		static void Geo2XY(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dDstLat, const DOUBLE dDstLon, DOUBLE& dX, DOUBLE& dY);
		static void XY2Geo(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dX, const DOUBLE dY, DOUBLE& dDstLat, DOUBLE& dDstLon);
		static void Geo2RT(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dDstLat, const DOUBLE dDstLon, DOUBLE& dR, DOUBLE& dT);
		static void RT2Geo(const DOUBLE dRefLat, const DOUBLE dRefLon, const DOUBLE dR, const DOUBLE dT, DOUBLE& dDstLat, DOUBLE& dDstLon);
		static void XY2RT(const DOUBLE dX, const DOUBLE dY, DOUBLE& dR, DOUBLE& dT);
		static void RT2XY(const DOUBLE dR, const DOUBLE dT, DOUBLE& dX, DOUBLE& dY);
	};
} // NS_SALUS_MS_APP