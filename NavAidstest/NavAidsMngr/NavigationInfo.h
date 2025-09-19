#pragma once

#include <afxmt.h>

namespace NS_SALUS_MS_APP
{
#pragma pack(push, 1)

	struct T_GPS_DATETIME
	{
		USHORT m_usYear;
		UCHAR m_ucMonth;
		UCHAR m_ucDay;
		UCHAR m_ucHour;
		UCHAR m_ucMinute;
		DOUBLE m_dSecond;

		BOOL m_bValidDate;	// FALSE = invalid, TRUE = valid
		BOOL m_bValidTime;	// FALSE = invalid, TRUE = valid;
	};

	struct T_GPS_POSITION
	{
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		DOUBLE m_dAlt;
		BOOL m_bValid; // FALSE = invalid, TRUE = valid
	};

	struct T_GPS_SHIP_INFO
	{
		DOUBLE m_dHeadingTrue;
		BOOL m_bValidHeading;
		DOUBLE m_dCourseTrue;
		//DOUBLE m_dCourseMag;
		BOOL m_bValidCourse;
		DOUBLE m_dSpeedKts;
		BOOL m_bValidSpeed;
	};

	struct T_EHS_INFO
	{
		DOUBLE m_dHeading;		// degree
		DOUBLE m_dDeviation;	// degree
		DOUBLE m_dVariation;	// degree
		USHORT m_usHeadingRef;	// 0 = true, 1 = magnetic, 2 = error, 3 = null;
		DOUBLE m_dTurnRate;		// degree/s
		DOUBLE m_dYaw;			// attitude yaw, degree
		DOUBLE m_dPitch;		// attitude pitch, degree
		DOUBLE m_dRoll;			// atittude roll, degree
		DOUBLE m_dHeave;		// m
	};

#pragma pack(pop)

	class AFX_EXT_CLASS CNavigationInfo
	{
	public:
		CNavigationInfo();
		~CNavigationInfo();

	public:
		static CNavigationInfo* GetInstance();
		static void DeleteInstance();

		void Initialize();
		void Finalize();

		// Set
		void UpdateDate(const T_GPS_DATETIME* const pDateTime);
		void UpdateTime(const T_GPS_DATETIME* const pDateTime);
		void UpdatePosition(const T_GPS_POSITION* const pPosition);
		void UpdateShipInfo(const T_GPS_SHIP_INFO* const pShipInfo);
		void UpdateHeading(const T_EHS_INFO* const pEhsInfo);
		void UpdateTurnRate(const T_EHS_INFO* const pEhsInfo);
		void UpdateHeave(const T_EHS_INFO* const pEhsInfo);
		void UpdateAttitude(const T_EHS_INFO* const pEhsInfo);

		void UpdateSimulGpsData(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dSOG, const DOUBLE dCOG, const DOUBLE dHDG);

		// Get
		void GetGpsDateTime(T_GPS_DATETIME* const pDateTime);
		void GetGpsPosition(T_GPS_POSITION* const pPosition);
		void GetGpsShipInfo(T_GPS_SHIP_INFO* const pShipInfo);
		void GetEhsInfo(T_EHS_INFO* const pEhsInfo);

		void Clear();

	private:
		void LockGPS();
		void UnlockGPS();

		void LockEHS();
		void UnlockEHS();

	private:
		static CNavigationInfo* m_pInstance;

		T_GPS_DATETIME* m_pGPSDateTime;
		T_GPS_POSITION* m_pGPSPosition;
		T_GPS_SHIP_INFO* m_pGPSShipInfo;

		T_EHS_INFO* m_pEHSInfo;

		CCriticalSection* m_pGPSInfoCS;
		CCriticalSection* m_pEHSInfoCS;
	};
} // NS_SALUS_MS_APP