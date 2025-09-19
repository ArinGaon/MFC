#pragma once

#include <afxwin.h>

#include "DataTypeDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_RANGE_UNIT : INT
	{
		eRANGE_NM = 0,		// nm, Nutical miles
		eRANGE_METER = 1,	// meter
	};

	enum class E_SPEED_UNIT : INT
	{
		eSPEED_KTS = 0,		// kn, kts, knots, 1 kts = 1852 m / h
		eSPEED_MPS = 1,		// meter per second
	};

	enum class E_ANGLE_UNIT : INT
	{
		eANGLE_DEGREE = 0,	// 0 ~ 359.9999
		eANGLE_RADIAN = 1,	// -PI ~ +PI
		eANGLE_BIDEGREE = 2,	// -180 ~ 180
	};

	// Geodetic unit
	enum class E_GEO_UNIT : INT
	{
		eGEO_DEGREE = 0,
		eGEO_DEG_MIN = 1,
	};

	// date time
	enum class E_TIME_UNIT : INT
	{
		eTIME_UTC = 0,
		eTIME_LOCAL = 1,
	};

	class AFX_EXT_CLASS CUnitsManager
	{
	public:
		CUnitsManager();
		~CUnitsManager();

	public:
		static CUnitsManager* GetInstance();
		static void DeleteInstance();

		void SetRangeUnit(const E_RANGE_UNIT eRangeUnit);
		void SetSpeedUnit(const E_SPEED_UNIT eSpeedUnit);
		void SetAngleUnit(const E_ANGLE_UNIT eAngleUnit);
		void SetGeodeticUnit(const E_GEO_UNIT eGeoUnit);
		void SetTimeUnit(const E_TIME_UNIT eTimeUnit);
		void SetDirUnit(CString LatDir, CString LonDir);

		E_RANGE_UNIT GetRangeUnit();
		E_SPEED_UNIT GetSpeedUnit();
		E_ANGLE_UNIT GetAngleUnit();
		E_GEO_UNIT GetGeoditicUnit();
		E_TIME_UNIT GetTimeUnit();
		// Latitude
		CString GetStrLatitude(const DOUBLE dLat);
		CString GetStrLatitudeUnit(const DOUBLE dLat);
		CString GetStrLatitudePos(const E_GEO_UNIT eGeoUnit, const DOUBLE dLat);
		CString GetStrLatitudeC(const DOUBLE dLat);
		CString GetStrLatitudeCU(const DOUBLE dLat);
		CString GetStrLatitudeCP(const DOUBLE dLat);
		CString GetStrLatitudeC(const E_GEO_UNIT eGeoUnit, const DOUBLE dLat);
		CString GetStrLatitudeCU(const E_GEO_UNIT eGeoUnit, const DOUBLE dLat);
		// Longitude
		CString GetStrLongitude(const DOUBLE dLon);
		CString GetStrLongitudeUnit(const DOUBLE dLon);
		CString GetStrLongitudePos(const E_GEO_UNIT eGeoUnit, const DOUBLE dLon);
		CString GetStrLongitudeC(const DOUBLE dLon);
		CString GetStrLongitudeCU(const DOUBLE dLon);
		CString GetStrLongitudeCP(const DOUBLE dLon);
		CString GetStrLongitudeC(const E_GEO_UNIT eGeoUnit, const DOUBLE dLon);
		CString GetStrLongitudeCU(const E_GEO_UNIT eGeoUnit, const DOUBLE dLon);
		// Speed
		CString GetStrSpeed(const DOUBLE dSpeed);
		CString GetStrSpeedU(const DOUBLE dSpeed);
		CString GetStrSpeedUnit();
		CString GetStrSpeed(const E_SPEED_UNIT eSpeedUnit, const DOUBLE dSpeed);
		CString GetStrSpeedU(const E_SPEED_UNIT eSpeedUnit, const DOUBLE dSpeed);
		// Range
		CString GetStrRange(const DOUBLE dRange);
		CString GetStrRangeU(const DOUBLE dRange);
		CString GetStrRangeUnit();
		CString GetStrRange(const E_RANGE_UNIT eRangeUnit, const DOUBLE dRange);
		CString GetStrRangeU(const E_RANGE_UNIT eRangeUnit, const DOUBLE dRange);
		// Angle
		CString GetStrAngle(const DOUBLE dAngle);
		CString GetStrAngleU(const DOUBLE dAngle);
		CString GetStrAngleUnit();
		CString GetStrAngle(const E_ANGLE_UNIT eAngleUnit, const DOUBLE dAngle);
		CString GetStrAngleU(const E_ANGLE_UNIT eAngleUnit, const DOUBLE dAngle);

		CString m_strLatDir;
		CString m_strLonDir;
	private:
		void GetGeoDegMin(const DOUBLE dDegree, INT& nDegree, DOUBLE& dMinute);
		void GetGeoDegMinSec(const DOUBLE dDegree, INT& nDegree, INT& nMinute, DOUBLE& dSecond);
		void GetDegMinGeo(const int degree, double dMinute, double& dDegree);
	private:
		static CUnitsManager* m_pInstance;

		E_RANGE_UNIT m_eRangeUnit;
		E_SPEED_UNIT m_eSpeedUnit;
		E_ANGLE_UNIT m_eAngleUnit;
		E_GEO_UNIT m_eGeoUnit;
		E_TIME_UNIT m_eTimeUnit;
	};

} // NS_SALUS_MS_APP

