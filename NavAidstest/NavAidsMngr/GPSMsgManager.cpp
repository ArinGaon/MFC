#include "pch.h"
#include "GPSMsgManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CGPSMsgManager::CGPSMsgManager()
	{
		m_bStarted = FALSE;

		m_pGpsDateTime = NULL;
		m_pGpsPosition = NULL;
		m_pGpsShipInfo = NULL;

		m_pSerialMsgGPS = NULL;
		m_pMsgParserGPS = NULL;

		m_pGPSMsgProcThread = NULL;
		m_hGPSMsgProcExitEvent = CreateEvent(NULL, FALSE, FALSE, _T("GPS MSG MNGR EXIT EVENT"));
	}

	CGPSMsgManager::~CGPSMsgManager()
	{
		Finalize();

		CloseHandle(m_hGPSMsgProcExitEvent);
	}

	void CGPSMsgManager::Initialize()
	{
		// 구조체 메모리 할당
		if (m_pGpsDateTime == NULL)
		{
			m_pGpsDateTime = new T_GPS_DATETIME;
			static_cast<void>(ZeroMemory(m_pGpsDateTime, sizeof(T_GPS_DATETIME)));
		}

		if (m_pGpsPosition == NULL)
		{
			m_pGpsPosition = new T_GPS_POSITION;
			static_cast<void>(ZeroMemory(m_pGpsPosition, sizeof(T_GPS_POSITION)));
		}

		if (m_pGpsShipInfo == NULL)
		{
			m_pGpsShipInfo = new T_GPS_SHIP_INFO;
			static_cast<void>(ZeroMemory(m_pGpsShipInfo, sizeof(T_GPS_SHIP_INFO)));
		}

		if (m_pSerialMsgGPS == NULL)
		{
			m_pSerialMsgGPS = new CSerialMsgMngr();
		}

		if (m_pMsgParserGPS == NULL)
		{
			m_pMsgParserGPS = new CNMEAParser();
		}
	}

	void CGPSMsgManager::Finalize()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();

		if (m_pSerialMsgGPS != NULL)
		{
			delete m_pSerialMsgGPS;
			m_pSerialMsgGPS = NULL;
		}

		if (m_pMsgParserGPS != NULL)
		{
			delete m_pMsgParserGPS;
			m_pMsgParserGPS = NULL;
		}

		// 구조체 메모리 해제
		if (m_pGpsDateTime != NULL)
		{
			delete m_pGpsDateTime;
			m_pGpsDateTime = NULL;
		}

		if (m_pGpsPosition != NULL)
		{
			delete m_pGpsPosition;
			m_pGpsPosition = NULL;
		}

		if (m_pGpsShipInfo != NULL)
		{
			delete m_pGpsShipInfo;
			m_pGpsShipInfo = NULL;
		}
	}

	void CGPSMsgManager::Start()
	{
		CreateMsgProcThread();

		m_bStarted = TRUE;
	}

	void CGPSMsgManager::Stop()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();
	}

	void CGPSMsgManager::ClearMsg()
	{
		if (m_pSerialMsgGPS != NULL)
		{
			m_pSerialMsgGPS->Clear();
		}
	}

	BOOL CGPSMsgManager::IsStarted()
	{
		return m_bStarted;
	}

	CSerialMsgMngr* CGPSMsgManager::GetSerialMsgMngr()
	{
		return m_pSerialMsgGPS;
	}

	void CGPSMsgManager::UpdateGPSInfo(const E_PARSING_RESULT eParsingResult)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();
		if (pNaviInfo != NULL)
		{
			switch (eParsingResult)
			{
			case E_PARSING_RESULT::ePARSING_DONE_NMEA_GGA:
			{
				CopyGPSInfo(m_pMsgParserGPS->GetNMEA_GGA());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_NMEA_GLL:
			{
				CopyGPSInfo(m_pMsgParserGPS->GetNMEA_GLL());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_NMEA_RMC:
			{
				CopyGPSInfo(m_pMsgParserGPS->GetNMEA_RMC());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_NMEA_HDT:
			{
				CopyGPSInfo(m_pMsgParserGPS->GetNMEA_HDT());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_NMEA_VTG:
			{
				CopyGPSInfo(m_pMsgParserGPS->GetNMEA_VTG());
				break;
			}
			default:
			{
				break;
			}
			}  // switch
		}
	}

	void CGPSMsgManager::CopyGPSInfo(const T_NMEA_GGA* const pGGA)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((pNaviInfo != NULL) && (pGGA != NULL))
		{
			// 시간 정보 갱신
			if (m_pGpsDateTime != NULL)
			{
				m_pGpsDateTime->m_ucHour = static_cast<UCHAR>(pGGA->m_wHour);
				m_pGpsDateTime->m_ucMinute = static_cast<UCHAR>(pGGA->m_wMinute);
				m_pGpsDateTime->m_dSecond = pGGA->m_dSecond;

				pNaviInfo->UpdateTime(m_pGpsDateTime);
			}
			// 위치 정보 갱신
			if (m_pGpsPosition != NULL)
			{
				m_pGpsPosition->m_dLat = pGGA->m_sLatDegree + pGGA->m_dLatMinute / 60.0;
				m_pGpsPosition->m_dLon = pGGA->m_sLonDegree + pGGA->m_dLonMinute / 60.0;
				m_pGpsPosition->m_dAlt = pGGA->m_dAltitude;

				pNaviInfo->UpdatePosition(m_pGpsPosition);
			}
		}
	}

	void CGPSMsgManager::CopyGPSInfo(const T_NMEA_GLL* const pGLL)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((pNaviInfo != NULL) && (pGLL != NULL))
		{
			// 시간 정보 갱신
			if (m_pGpsDateTime != NULL)
			{
				m_pGpsDateTime->m_ucHour = static_cast<UCHAR>(pGLL->m_wHour);
				m_pGpsDateTime->m_ucMinute = static_cast<UCHAR>(pGLL->m_wMinute);
				m_pGpsDateTime->m_dSecond = pGLL->m_dSecond;

				pNaviInfo->UpdateTime(m_pGpsDateTime);
			}
			// 위치 정보 갱신
			if (m_pGpsPosition != NULL)
			{
				m_pGpsPosition->m_dLat = pGLL->m_sLatDegree + pGLL->m_dLatMinute / 60.0;
				m_pGpsPosition->m_dLon = pGLL->m_sLonDegree + pGLL->m_dLonMinute / 60.0;

				pNaviInfo->UpdatePosition(m_pGpsPosition);
			}
		}
	}

	void CGPSMsgManager::CopyGPSInfo(const T_NMEA_RMC* const pRMC)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((pNaviInfo != NULL) && (pRMC != NULL))
		{
			// 날짜 정보 갱신
			if (m_pGpsDateTime != NULL)
			{
				m_pGpsDateTime->m_usYear = static_cast<USHORT>(pRMC->m_wYear);
				m_pGpsDateTime->m_ucMonth = static_cast<UCHAR>(pRMC->m_wMonth);
				m_pGpsDateTime->m_ucDay = static_cast<UCHAR>(pRMC->m_wDay);

				pNaviInfo->UpdateDate(m_pGpsDateTime);
			}
			// 시간 정보 갱신
			if (m_pGpsDateTime != NULL)
			{
				m_pGpsDateTime->m_ucHour = static_cast<UCHAR>(pRMC->m_wHour);
				m_pGpsDateTime->m_ucMinute = static_cast<UCHAR>(pRMC->m_wMinute);
				m_pGpsDateTime->m_dSecond = pRMC->m_dSecond;

				pNaviInfo->UpdateTime(m_pGpsDateTime);
			}
			// 위치 정보 갱신
			if (m_pGpsPosition != NULL)
			{
				m_pGpsPosition->m_dLat = pRMC->m_sLatDegree + pRMC->m_dLatMinute / 60.0;
				m_pGpsPosition->m_dLon = pRMC->m_sLonDegree + pRMC->m_dLonMinute / 60.0;

				pNaviInfo->UpdatePosition(m_pGpsPosition);
			}
			// 속력, Course 갱신
			if (m_pGpsShipInfo != NULL)
			{
				m_pGpsShipInfo->m_dSpeedKts = pRMC->m_dSpeed;
				m_pGpsShipInfo->m_bValidSpeed = TRUE;
				m_pGpsShipInfo->m_dCourseTrue = pRMC->m_dTrackTrue;
				m_pGpsShipInfo->m_bValidCourse = TRUE;

				pNaviInfo->UpdateShipInfo(m_pGpsShipInfo);
			}
		}
	}

	void CGPSMsgManager::CopyGPSInfo(const T_NMEA_HDT* const pHDT)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((pNaviInfo != NULL) && (pHDT != NULL))
		{
			// 기동 정보 갱신
			if (m_pGpsShipInfo != NULL)
			{
				m_pGpsShipInfo->m_dHeadingTrue = pHDT->fHeading;
				m_pGpsShipInfo->m_bValidHeading = TRUE;
				
				pNaviInfo->UpdateShipInfo(m_pGpsShipInfo);
			}
		}
	}

	void CGPSMsgManager::CopyGPSInfo(const T_NMEA_VTG* const pVTG)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((pNaviInfo != NULL) && (pVTG != NULL))
		{
			// 기동 정보 갱신
			if (m_pGpsShipInfo != NULL)
			{
				m_pGpsShipInfo->m_dCourseTrue = pVTG->m_dCourseTrue;
				//m_pGpsShipInfo->m_dCourseMag = pVTG->m_dCourseMag;
				m_pGpsShipInfo->m_bValidCourse = TRUE;
				m_pGpsShipInfo->m_dSpeedKts = pVTG->m_dSpeedKnots;
				//m_pGpsShipInfo->m_dSpeedMph = pVTG->m_dSpeedKmPerH;
				m_pGpsShipInfo->m_bValidSpeed = TRUE;

				pNaviInfo->UpdateShipInfo(m_pGpsShipInfo);
			}
		}
	}

	void CGPSMsgManager::CreateMsgProcThread()
	{
		m_pGPSMsgProcThread = AfxBeginThread(static_cast<AFX_THREADPROC>(GPSMsgProcThread), static_cast<LPVOID>(this), THREAD_PRIORITY_ABOVE_NORMAL, 0U, static_cast<DWORD>(CREATE_SUSPENDED));
		if (m_pGPSMsgProcThread != NULL)
		{
			m_pGPSMsgProcThread->m_bAutoDelete = TRUE;
			static_cast<void>(m_pGPSMsgProcThread->ResumeThread());
		}
	}

	void CGPSMsgManager::ExitMsgProcThread()
	{
		if (m_pGPSMsgProcThread != NULL)
		{
			static_cast<void>(SetEvent(m_hGPSMsgProcExitEvent));

			static_cast<void>(WaitForSingleObject(m_pGPSMsgProcThread->m_hThread, static_cast<DWORD>(1000U)));

			m_pGPSMsgProcThread = NULL;
		}
	}

	void CGPSMsgManager::GPSMsgProcThread()
	{
		if (m_pSerialMsgGPS != NULL)
		{
			BYTE* pDataPtr = NULL;
			// 수신된 메시지를 한번에 세개까지 처리한다.
			for (INT nCnt = 0; nCnt < 3; nCnt++)
			{
				pDataPtr = m_pSerialMsgGPS->Pop();
				// 데이터가 존재하지 않으면 종료한다.
				if (pDataPtr == NULL)
				{
					break;
				}
				// 메시지 처리 시작이 아니면 큐에 있는 메시지를 버린다.
				if (m_bStarted == TRUE)
				{
					CString strMsg = reinterpret_cast<TCHAR*>(pDataPtr);
					if (m_pMsgParserGPS != NULL)
					{
						E_PARSING_RESULT eParsingResult = m_pMsgParserGPS->Parsing(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
						UpdateGPSInfo(eParsingResult);
					}
				}
			}
		}
	}

	UINT CGPSMsgManager::GPSMsgProcThread(LPVOID const lpParam)
	{
		CGPSMsgManager* const pMsgMngr = static_cast<CGPSMsgManager*>(lpParam);

		if (pMsgMngr != NULL)
		{
			INT nQuit = 0;

			DWORD dwEvent;

			while (nQuit < 1)
			{
				dwEvent = WaitForSingleObject(pMsgMngr->m_hGPSMsgProcExitEvent, 50U); // 50 ms 마다 동작
				switch (dwEvent)
				{
				case static_cast<DWORD>(WAIT_OBJECT_0 + 0U): // Exit Event
				{
					nQuit++;
					break;
				}
				case static_cast<DWORD>(WAIT_TIMEOUT):		// Time out
				{
					pMsgMngr->GPSMsgProcThread();
					break;
				}	
				default:
				{
					break;
				}
				}
			}
		}

		return 0U;
	}

} // NS_SALUS_MS_APP