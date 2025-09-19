#include "pch.h"
#include "EHSMsgManager.h"

#include "MathBaseDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CEHSMsgManager::CEHSMsgManager()
	{
		m_bStarted = FALSE;

		m_pEHSInfo = NULL;

		m_pSerialMsgEHS = NULL;
		m_pMsgParserEHS = NULL;

		m_pEHSMsgProcThread = NULL;
		m_hEHSMsgProcExitEvent = CreateEvent(NULL, FALSE, FALSE, _T("EHS MSG MNGR EXIT EVENT"));
	}

	CEHSMsgManager::~CEHSMsgManager()
	{
		Finalize();

		CloseHandle(m_hEHSMsgProcExitEvent);
	}

	void CEHSMsgManager::Initialize()
	{
		if (m_pEHSInfo == NULL)
		{
			m_pEHSInfo = new T_EHS_INFO;
			static_cast<void>(ZeroMemory(m_pEHSInfo, sizeof(T_EHS_INFO)));
		}

		if (m_pSerialMsgEHS == NULL)
		{
			m_pSerialMsgEHS = new CSerialMsgMngr();
		}

		if (m_pMsgParserEHS == NULL)
		{
			m_pMsgParserEHS = new CNMEAParser();
		}
	}

	void CEHSMsgManager::Finalize()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();

		if (m_pSerialMsgEHS != NULL)
		{
			delete m_pSerialMsgEHS;
			m_pSerialMsgEHS = NULL;
		}

		if (m_pMsgParserEHS != NULL)
		{
			delete m_pMsgParserEHS;
			m_pMsgParserEHS = NULL;
		}

		if (m_pEHSInfo != NULL)
		{
			delete m_pEHSInfo;
			m_pEHSInfo = NULL;
		}
	}

	void CEHSMsgManager::Start()
	{
		CreateMsgProcThread();

		m_bStarted = TRUE;
	}

	void CEHSMsgManager::Stop()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();
	}

	void CEHSMsgManager::ClearMsg()
	{
		if (m_pSerialMsgEHS != NULL)
		{
			m_pSerialMsgEHS->Clear();
		}
	}

	BOOL CEHSMsgManager::IsStarted()
	{
		return m_bStarted;
	}

	CSerialMsgMngr* CEHSMsgManager::GetSerialMsgMngr()
	{
		return m_pSerialMsgEHS;
	}

	void CEHSMsgManager::UpdateEHSInfo(const E_PARSING_RESULT eParsingResult)
	{
		if (m_pMsgParserEHS != NULL)
		{
			switch (eParsingResult)
			{
			case E_PARSING_RESULT::ePARSING_DONE_EHS_HEADING:
			{
				CopyEHSHeading(m_pMsgParserEHS->GetNMEA_CAN());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_EHS_TURNRATE:
			{
				CopyEHSTurnrate(m_pMsgParserEHS->GetNMEA_CAN());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_EHS_HEAVE:
			{
				CopyEHSHeave(m_pMsgParserEHS->GetNMEA_CAN());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_EHS_ATTITUDE:
			{
				CopyEHSAttitude(m_pMsgParserEHS->GetNMEA_CAN());
				break;
			}
			default:
			{
				break;
			}
			}  // switch
		}
	}

	void CEHSMsgManager::CopyEHSHeading(const T_NMEA_CAN* const pCAN)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((m_pEHSInfo != NULL) && (pCAN != NULL) && (pNaviInfo != NULL))
		{
			m_pEHSInfo->m_dHeading = pCAN->m_dHeading * g_dRAD2DEG;
			m_pEHSInfo->m_dDeviation = pCAN->m_dDeviation * g_dRAD2DEG;
			m_pEHSInfo->m_dVariation = pCAN->m_dVariation * g_dRAD2DEG;
			m_pEHSInfo->m_usHeadingRef = pCAN->m_wHeadingRef;

			pNaviInfo->UpdateHeading(m_pEHSInfo);
		}
	}

	void CEHSMsgManager::CopyEHSTurnrate(const T_NMEA_CAN* const pCAN)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((m_pEHSInfo != NULL) && (pCAN != NULL) && (pNaviInfo != NULL))
		{
			m_pEHSInfo->m_dTurnRate = pCAN->m_dTurnRate * g_dRAD2DEG;

			pNaviInfo->UpdateTurnRate(m_pEHSInfo);
		}
	}

	void CEHSMsgManager::CopyEHSHeave(const T_NMEA_CAN* const pCAN)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((m_pEHSInfo != NULL) && (pCAN != NULL) && (pNaviInfo != NULL))
		{
			m_pEHSInfo->m_dHeave = pCAN->m_dHeave;

			pNaviInfo->UpdateHeave(m_pEHSInfo);
		}
	}

	void CEHSMsgManager::CopyEHSAttitude(const T_NMEA_CAN* const pCAN)
	{
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();

		if ((m_pEHSInfo != NULL) && (pCAN != NULL) && (pNaviInfo != NULL))
		{
			m_pEHSInfo->m_dYaw = pCAN->m_dYaw * g_dRAD2DEG;
			m_pEHSInfo->m_dPitch = pCAN->m_dPitch * g_dRAD2DEG;
			m_pEHSInfo->m_dRoll = pCAN->m_dRoll * g_dRAD2DEG;

			pNaviInfo->UpdateAttitude(m_pEHSInfo);
		}
	}

	void CEHSMsgManager::CreateMsgProcThread()
	{
		m_pEHSMsgProcThread = AfxBeginThread(static_cast<AFX_THREADPROC>(EHSMsgProcThread), static_cast<LPVOID>(this), THREAD_PRIORITY_ABOVE_NORMAL, 0U, static_cast<DWORD>(CREATE_SUSPENDED));
		if (m_pEHSMsgProcThread != NULL)
		{
			m_pEHSMsgProcThread->m_bAutoDelete = TRUE;
			static_cast<void>(m_pEHSMsgProcThread->ResumeThread());
		}
	}

	void CEHSMsgManager::ExitMsgProcThread()
	{
		if (m_pEHSMsgProcThread != NULL)
		{
			static_cast<void>(SetEvent(m_hEHSMsgProcExitEvent));

			static_cast<void>(WaitForSingleObject(m_pEHSMsgProcThread->m_hThread, static_cast<DWORD>(500U)));

			m_pEHSMsgProcThread = NULL;
		}
	}

	void CEHSMsgManager::EHSMsgProcThread()
	{
		if (m_pSerialMsgEHS != NULL)
		{
			BYTE* pDataPtr = NULL;
			// 수신된 메시지를 한번에 세개까지 처리한다.
			for (INT nCnt = 0; nCnt < 3; nCnt++)
			{
				pDataPtr = m_pSerialMsgEHS->Pop();
				// 데이터가 존재하지 않으면 종료한다.
				if (pDataPtr == NULL)
				{
					break;
				}
				// 메시지 처리 시작이 아니면 큐에 있는 메시지를 버린다.
				if (m_bStarted == TRUE)
				{
					CString strMsg = reinterpret_cast<TCHAR*>(pDataPtr);
					if (m_pMsgParserEHS != NULL)
					{
						const E_PARSING_RESULT eParsingResult = m_pMsgParserEHS->Parsing(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
						UpdateEHSInfo(eParsingResult);
					}
				}
			}
		}
	}

	UINT CEHSMsgManager::EHSMsgProcThread(LPVOID const lpParam)
	{
		CEHSMsgManager* const pMsgMngr = static_cast<CEHSMsgManager*>(lpParam);

		if (pMsgMngr != NULL)
		{
			INT nQuit = 0;

			DWORD dwEvent;

			while (nQuit < 1)
			{
				dwEvent = WaitForSingleObject(pMsgMngr->m_hEHSMsgProcExitEvent, 50U); // 50 ms 마다 동작
				switch (dwEvent)
				{
				case static_cast<DWORD>(WAIT_OBJECT_0 + 0U): // Exit Event
				{
					nQuit++;
					break;
				}
				case static_cast<DWORD>(WAIT_TIMEOUT):		// Time out
				{
					pMsgMngr->EHSMsgProcThread();
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