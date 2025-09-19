#include "pch.h"
#include "NavigationInfo.h"

#include "MathBaseDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CNavigationInfo* CNavigationInfo::m_pInstance = NULL;

	CNavigationInfo::CNavigationInfo()
	{
		m_pGPSDateTime = NULL;
		m_pGPSPosition = NULL;
		m_pGPSShipInfo = NULL;
		m_pEHSInfo = NULL;

		m_pGPSInfoCS = new CCriticalSection();
		m_pEHSInfoCS = new CCriticalSection();
	}

	CNavigationInfo::~CNavigationInfo()
	{
		Finalize();

		if (m_pGPSInfoCS != NULL)
		{
			delete m_pGPSInfoCS;
			m_pGPSInfoCS = NULL;
		}

		if (m_pEHSInfoCS != NULL)
		{
			delete m_pEHSInfoCS;
			m_pEHSInfoCS = NULL;
		}
	}

	CNavigationInfo* CNavigationInfo::GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CNavigationInfo();
		}

		return m_pInstance;
	}

	void CNavigationInfo::DeleteInstance()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	void CNavigationInfo::Initialize()
	{
		if (m_pGPSDateTime == NULL)
		{
			m_pGPSDateTime = new T_GPS_DATETIME;
			static_cast<void>(ZeroMemory(m_pGPSDateTime, sizeof(T_GPS_DATETIME)));
		}

		if (m_pGPSPosition == NULL)
		{
			m_pGPSPosition = new T_GPS_POSITION;
			static_cast<void>(ZeroMemory(m_pGPSPosition, sizeof(T_GPS_POSITION)));
		}

		if (m_pGPSShipInfo == NULL)
		{
			m_pGPSShipInfo = new T_GPS_SHIP_INFO;
			static_cast<void>(ZeroMemory(m_pGPSShipInfo, sizeof(T_GPS_SHIP_INFO)));
		}

		if (m_pEHSInfo == NULL)
		{
			m_pEHSInfo = new T_EHS_INFO;
			static_cast<void>(ZeroMemory(m_pEHSInfo, sizeof(T_EHS_INFO)));
		}
	}

	void CNavigationInfo::Finalize()
	{
		if (m_pGPSDateTime != NULL)
		{
			delete m_pGPSDateTime;
			m_pGPSDateTime = NULL;
		}

		if (m_pGPSPosition != NULL)
		{
			delete m_pGPSPosition;
			m_pGPSPosition = NULL;
		}

		if (m_pGPSShipInfo != NULL)
		{
			delete m_pGPSShipInfo;
			m_pGPSShipInfo = NULL;
		}

		if (m_pEHSInfo != NULL)
		{
			delete m_pEHSInfo;
			m_pEHSInfo = NULL;
		}
	}

	void CNavigationInfo::UpdateDate(const T_GPS_DATETIME* const pDateTime)
	{
		if ((pDateTime != NULL) && (m_pGPSDateTime != NULL))
		{
			LockGPS();

			m_pGPSDateTime->m_usYear = pDateTime->m_usYear;
			m_pGPSDateTime->m_ucMonth = pDateTime->m_ucMonth;
			m_pGPSDateTime->m_ucDay = pDateTime->m_ucDay;
			m_pGPSDateTime->m_bValidDate = TRUE;

			UnlockGPS();
		}
	}

	void CNavigationInfo::UpdateTime(const T_GPS_DATETIME* const pDateTime)
	{
		if ((pDateTime != NULL) && (m_pGPSDateTime != NULL))
		{
			LockGPS();

			m_pGPSDateTime->m_ucHour = pDateTime->m_ucHour;
			m_pGPSDateTime->m_ucMinute = pDateTime->m_ucMinute;
			m_pGPSDateTime->m_dSecond = pDateTime->m_dSecond;
			m_pGPSDateTime->m_bValidTime = TRUE;

			UnlockGPS();
		}
	}

	void CNavigationInfo::UpdatePosition(const T_GPS_POSITION* const pPosition)
	{
		if ((pPosition != NULL) && (m_pGPSPosition != NULL))
		{
			LockGPS();

			m_pGPSPosition->m_dLat = pPosition->m_dLat;
			m_pGPSPosition->m_dLon = pPosition->m_dLon;
			m_pGPSPosition->m_dAlt = pPosition->m_dAlt;
			m_pGPSPosition->m_bValid = TRUE;

			UnlockGPS();
		}
	}

	void CNavigationInfo::UpdateShipInfo(const T_GPS_SHIP_INFO* const pShipInfo)
	{
		if ((pShipInfo != NULL) && (m_pGPSShipInfo != NULL))
		{
			LockGPS();

			static_cast<void>(CopyMemory(m_pGPSShipInfo, pShipInfo, sizeof(T_GPS_SHIP_INFO)));

			UnlockGPS();
		}
	}

	void CNavigationInfo::UpdateHeading(const T_EHS_INFO* const pEhsInfo)
	{
		if ((pEhsInfo != NULL) && (m_pEHSInfo != NULL))
		{
			LockEHS();

			m_pEHSInfo->m_dHeading = pEhsInfo->m_dHeading;
			m_pEHSInfo->m_dDeviation = pEhsInfo->m_dDeviation;
			m_pEHSInfo->m_dVariation = pEhsInfo->m_dVariation;
			m_pEHSInfo->m_usHeadingRef = pEhsInfo->m_usHeadingRef;

			UnlockEHS();
		}
	}

	void CNavigationInfo::UpdateTurnRate(const T_EHS_INFO* const pEhsInfo)
	{
		if ((pEhsInfo != NULL) && (m_pEHSInfo != NULL))
		{
			LockEHS();

			m_pEHSInfo->m_dTurnRate = pEhsInfo->m_dTurnRate;

			UnlockEHS();
		}
	}

	void CNavigationInfo::UpdateHeave(const T_EHS_INFO* const pEhsInfo)
	{
		if ((pEhsInfo != NULL) && (m_pEHSInfo != NULL))
		{
			LockEHS();

			m_pEHSInfo->m_dHeave = pEhsInfo->m_dHeave;

			UnlockEHS();
		}
	}

	void CNavigationInfo::UpdateAttitude(const T_EHS_INFO* const pEhsInfo)
	{
		if ((pEhsInfo != NULL) && (m_pEHSInfo != NULL))
		{
			LockEHS();

			m_pEHSInfo->m_dYaw = pEhsInfo->m_dYaw;
			m_pEHSInfo->m_dPitch = pEhsInfo->m_dPitch;
			m_pEHSInfo->m_dRoll = pEhsInfo->m_dRoll;

			UnlockEHS();
		}
	}

	void CNavigationInfo::UpdateSimulGpsData(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dSOG, const DOUBLE dCOG, const DOUBLE dHDG)
	{
		if (m_pGPSPosition != NULL)
		{
			LockGPS();

			m_pGPSPosition->m_dLat = dLat;
			m_pGPSPosition->m_dLon = dLon;
			m_pGPSPosition->m_dAlt = 0.0;
			m_pGPSPosition->m_bValid = TRUE;

			UnlockGPS();
		}

		if (m_pGPSShipInfo != NULL)
		{
			LockGPS();

			m_pGPSShipInfo->m_dCourseTrue = dCOG;
			m_pGPSShipInfo->m_bValidCourse = TRUE;
			m_pGPSShipInfo->m_dHeadingTrue = dHDG;
			m_pGPSShipInfo->m_bValidHeading = TRUE;
			m_pGPSShipInfo->m_dSpeedKts = dSOG * g_dMPS2KTS;
			m_pGPSShipInfo->m_bValidSpeed = TRUE;

			UnlockGPS();
		}
	}

	void CNavigationInfo::GetGpsDateTime(T_GPS_DATETIME* const pDateTime)
	{
		if ((pDateTime != NULL) && (m_pGPSDateTime != NULL))
		{
			LockGPS();

			static_cast<void>(CopyMemory(pDateTime, m_pGPSDateTime, sizeof(T_GPS_DATETIME)));

			UnlockGPS();
		}
	}

	void CNavigationInfo::GetGpsPosition(T_GPS_POSITION* const pPosition)
	{
		if ((pPosition != NULL) && (m_pGPSPosition != NULL))
		{
			LockGPS();

			static_cast<void>(CopyMemory(pPosition, m_pGPSPosition, sizeof(T_GPS_POSITION)));

			UnlockGPS();
		}
	}

	void CNavigationInfo::GetGpsShipInfo(T_GPS_SHIP_INFO* const pShipInfo)
	{
		if ((pShipInfo != NULL) && (m_pGPSShipInfo != NULL))
		{
			LockGPS();

			static_cast<void>(CopyMemory(pShipInfo, m_pGPSShipInfo, sizeof(T_GPS_SHIP_INFO)));

			UnlockGPS();
		}
	}

	void CNavigationInfo::GetEhsInfo(T_EHS_INFO* const pEhsInfo)
	{
		if ((pEhsInfo != NULL) && (m_pEHSInfo != NULL))
		{
			LockEHS();

			static_cast<void>(CopyMemory(pEhsInfo, m_pEHSInfo, sizeof(T_EHS_INFO)));

			UnlockEHS();
		}
	}

	void CNavigationInfo::Clear()
	{
		LockGPS();

		if (m_pGPSDateTime != NULL)
		{
			static_cast<void>(ZeroMemory(m_pGPSDateTime, sizeof(T_GPS_DATETIME)));
		}

		if (m_pGPSPosition != NULL)
		{
			static_cast<void>(ZeroMemory(m_pGPSPosition, sizeof(T_GPS_POSITION)));
		}

		if (m_pGPSShipInfo != NULL)
		{
			static_cast<void>(ZeroMemory(m_pGPSShipInfo, sizeof(T_GPS_SHIP_INFO)));
		}

		UnlockGPS();

		LockEHS();

		if (m_pEHSInfo != NULL)
		{
			static_cast<void>(ZeroMemory(m_pEHSInfo, sizeof(T_EHS_INFO)));
		}

		UnlockEHS();
	}

	void CNavigationInfo::LockGPS()
	{
		if (m_pGPSInfoCS != NULL)
		{
			static_cast<void>(m_pGPSInfoCS->Lock());
		}
	}

	void CNavigationInfo::UnlockGPS()
	{
		if (m_pGPSInfoCS != NULL)
		{
			static_cast<void>(m_pGPSInfoCS->Unlock());
		}
	}

	void CNavigationInfo::LockEHS()
	{
		if (m_pEHSInfoCS != NULL)
		{
			static_cast<void>(m_pEHSInfoCS->Lock());
		}
	}

	void CNavigationInfo::UnlockEHS()
	{
		if (m_pEHSInfoCS != NULL)
		{
			static_cast<void>(m_pEHSInfoCS->Unlock());
		}
	}

} // NS_SALUS_MS_APP