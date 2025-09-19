#pragma once

#include "DataTypeDef.h"
#include "MathBaseDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsMath
	{
	public:
		CSmsMath();

	public:
		static FLOAT ToRadianF(FLOAT fDegree);
		static FLOAT ToDegreeF(FLOAT fRadian);
		static DOUBLE ToRadian(DOUBLE dDegree);
		static DOUBLE ToDegree(DOUBLE dRadian);

		// Returns random float in [0, 1).
		static FLOAT RandF();
		// Returns random float in [Min, Max).
		static FLOAT RandF(FLOAT fMin, FLOAT fMax);
		static INT Rand(INT nMin, INT nMax);

		template<typename T>
		static T Min(const T& a, const T& b)
		{
			return a < b ? a : b;
		}
		template<typename T>
		static T Max(const T& a, const T& b)
		{
			return a > b ? a : b;
		}

		template<typename T>
		static T Lerp(const T& a, const T& b, float t)
		{
			return a + (b - a) * t;
		}

		template<typename T>
		static T Clamp(const T& x, const T& low, const T& high)
		{
			return ((x < low) ? low : ((x > high) ? high : x));
		}

		static DOUBLE NormalizeDegree(const DOUBLE& dDegree);
		static DOUBLE NormalizeDegree(const DOUBLE& dDegree, const DOUBLE dLow, const DOUBLE dHigh);
		static DOUBLE NormalizeRadian(const DOUBLE dRadian);

		// Returns the polar angle of the point (x,y) in [0, 2*PI).
		static FLOAT XYToAngle(FLOAT fX, FLOAT fY);
		static DOUBLE XYToAngle(DOUBLE dX, DOUBLE dY);

		static void GetColor(const COLORREF clrRef, FLOAT& fRed, FLOAT& fGreen, FLOAT& fBlue);
	};

} // NS_SALUS_MS_APP