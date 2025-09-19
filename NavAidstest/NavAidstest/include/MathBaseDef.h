#pragma once

namespace NS_SALUS_MS_APP
{
	static const DOUBLE g_dWGS84PI = 3.1415926535897932384626433832795;		// Circular Constant
	static const DOUBLE g_dDEG2RAD = g_dWGS84PI / 180.0;						// Degree to Radian Conversion
	static const DOUBLE g_dRAD2DEG = 180.0 / g_dWGS84PI; 						// Radian to Degree Conversion
	static const DOUBLE g_dNM2M = 1852.0;									// Nautical Mile to Meter
	static const DOUBLE g_dM2NM = 1.0 / g_dNM2M;							// Meter to Nautical Mile
	static const DOUBLE g_dKTS2MPS = g_dNM2M / 3600.0;						// Knots to m/s	
	static const DOUBLE g_dMPS2KTS = 3600.0 / g_dNM2M;						// m/s to Knots	

} // NS_SALUS_MS_APP