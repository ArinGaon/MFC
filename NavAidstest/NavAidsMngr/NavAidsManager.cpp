#include "pch.h"
#include "NavAidsManager.h"

#include <mmsystem.h>

#include "NavigationInfo.h"

#include "AISMsgManager.h"
#include "GPSMsgManager.h"
#include "EHSMsgManager.h"

#include "SerialNMEA.h"

#include "AISFileReplay.h"
#include "GPSFileReplay.h"
#include "EHSFileReplay.h"

#include "UserCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	// MSG Manager
	static CAISMsgManager* g_pAISMsgManager = NULL;
	static CGPSMsgManager* g_pGPSMsgManager = NULL;
	static CEHSMsgManager* g_pEHSMsgManager = NULL;
	// Serial Interface
	static CSerialNMEA* g_pAISSerialNMEA = NULL;
	static CSerialNMEA* g_pGPSSerialNMEA = NULL;
	static CSerialNMEA* g_pEHSSerialNMEA = NULL;
	// FILE Replay
	static CAISFileReplay* g_pAISFileReplay = NULL;
	static CGPSFileReplay* g_pGPSFileReplay = NULL;
	static CEHSFileReplay* g_pEHSFileReplay = NULL;

	void CALLBACK NavReplayTimerProc(UINT, UINT, DWORD_PTR dwUser, DWORD_PTR, DWORD_PTR)
	{
		HANDLE hEvent = reinterpret_cast<HANDLE>(dwUser);

		SetEvent(hEvent);
	}

	CNavAidsManager* CNavAidsManager::m_pInstance = NULL;

	CNavAidsManager::CNavAidsManager()
	{
		m_pParentWnd = NULL;

		m_bStartNavAids = FALSE;
		m_bStartFileReplay = FALSE;

		m_unCheckCount = 0U;
		m_unAisDataErrorCount = 0U;

		m_pAISSourceParam = NULL;
		m_pGPSSourceParam = NULL;
		m_pEHSSourceParam = NULL;

		m_unMMSyncTimerID = 0U;
		m_hSyncExitEvent = CreateEvent(NULL, FALSE, FALSE, _T("NAV DATA SYNC EXIT EVENT"));
		m_hSyncWorkEvent = CreateEvent(NULL, FALSE, FALSE, _T("NAV DATA SYNC WORK EVENT"));
		m_pDataSyncProcThread = NULL;
	}

	CNavAidsManager::~CNavAidsManager()
	{
		Finalize();

		CloseHandle(m_hSyncExitEvent);
		CloseHandle(m_hSyncWorkEvent);
	}

	CNavAidsManager* CNavAidsManager::GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CNavAidsManager();
		}

		return m_pInstance;
	}

	void CNavAidsManager::DeleteInstance()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	void CNavAidsManager::Initialize(CWnd* const pParentWnd)
	{
		m_pParentWnd = pParentWnd;

		if (m_pAISSourceParam == NULL)
		{
			m_pAISSourceParam = new T_NAV_SOURCE_PARAM;
			static_cast<void>(ZeroMemory(m_pAISSourceParam, sizeof(T_NAV_SOURCE_PARAM)));
		}
		if (m_pGPSSourceParam == NULL)
		{
			m_pGPSSourceParam = new T_NAV_SOURCE_PARAM;
			static_cast<void>(ZeroMemory(m_pGPSSourceParam, sizeof(T_NAV_SOURCE_PARAM)));
		}
		if (m_pEHSSourceParam == NULL)
		{
			m_pEHSSourceParam = new T_NAV_SOURCE_PARAM;
			static_cast<void>(ZeroMemory(m_pEHSSourceParam, sizeof(T_NAV_SOURCE_PARAM)));
		}

		// Create Message Manager
		if (g_pAISMsgManager == NULL)
		{
			g_pAISMsgManager = new CAISMsgManager();
			g_pAISMsgManager->Initialize();
		}
		if (g_pGPSMsgManager == NULL)
		{
			g_pGPSMsgManager = new CGPSMsgManager();
			g_pGPSMsgManager->Initialize();
		}
		if (g_pEHSMsgManager == NULL)
		{
			g_pEHSMsgManager = new CEHSMsgManager();
			g_pEHSMsgManager->Initialize();
		}

		// 여기서 Navigation Info 클래스를 생성한다.
		CNavigationInfo* pNaviInfo = CNavigationInfo::GetInstance();
		if (pNaviInfo != NULL)
		{
			pNaviInfo->Initialize();
		}
		// Data Sync Thread 생성
		CreateDataSyncProcThread();

		// m_unMMSyncTimerDelay 마다 MM Timer 발생
		m_unMMSyncTimerID = timeSetEvent(m_unMMSyncTimerDelay, 0, &NavReplayTimerProc, reinterpret_cast<DWORD_PTR>(m_hSyncWorkEvent), static_cast<UINT>(TIME_PERIODIC));
	}

	void CNavAidsManager::Finalize()
	{
		if (m_unMMSyncTimerID > 0U)
		{
			static_cast<void>(timeKillEvent(m_unMMSyncTimerID));
		}
		m_unMMSyncTimerID = 0U;

		ExitDataSyncProcThread();

		if (m_pAISSourceParam != NULL)
		{
			delete m_pAISSourceParam;
			m_pAISSourceParam = NULL;
		}
		if (m_pGPSSourceParam != NULL)
		{
			delete m_pGPSSourceParam;
			m_pGPSSourceParam = NULL;
		}
		if (m_pEHSSourceParam != NULL)
		{
			delete m_pEHSSourceParam;
			m_pEHSSourceParam = NULL;
		}

		// Delete Message Manager
		if (g_pAISMsgManager != NULL)
		{
			delete g_pAISMsgManager;
			g_pAISMsgManager = NULL;
		}
		if (g_pGPSMsgManager != NULL)
		{
			delete g_pGPSMsgManager;
			g_pGPSMsgManager = NULL;
		}
		if (g_pEHSMsgManager != NULL)
		{
			delete g_pEHSMsgManager;
			g_pEHSMsgManager = NULL;
		}

		// 여기서 Navigation Info 클래스를 해제한다.
		CNavigationInfo::DeleteInstance();
	}

	void CNavAidsManager::SetSourceParam(const T_NAV_SOURCE_PARAM* const pAISSrcParam, const T_NAV_SOURCE_PARAM* const pGPSSrcParam, const T_NAV_SOURCE_PARAM* const pEHSSrcParam)
	{
		if ((pAISSrcParam != NULL) && (m_pAISSourceParam != NULL))
		{
			static_cast<void>(CopyMemory(m_pAISSourceParam, pAISSrcParam, sizeof(T_NAV_SOURCE_PARAM)));
		}

		if ((pGPSSrcParam != NULL) && (m_pGPSSourceParam != NULL))
		{
			static_cast<void>(CopyMemory(m_pGPSSourceParam, pGPSSrcParam, sizeof(T_NAV_SOURCE_PARAM)));
		}

		if ((pEHSSrcParam != NULL) && (m_pEHSSourceParam != NULL))
		{
			static_cast<void>(CopyMemory(m_pEHSSourceParam, pEHSSrcParam, sizeof(T_NAV_SOURCE_PARAM)));
		}
	}

	void CNavAidsManager::SetSourceParamAIS(const T_NAV_SOURCE_PARAM* const pAISSrcParam)
	{
		if ((pAISSrcParam != NULL) && (m_pAISSourceParam != NULL))
		{
			static_cast<void>(CopyMemory(m_pAISSourceParam, pAISSrcParam, sizeof(T_NAV_SOURCE_PARAM)));
		}
	}

	void CNavAidsManager::SetSourceParamGPS(const T_NAV_SOURCE_PARAM* const pGPSSrcParam)
	{
		if ((pGPSSrcParam != NULL) && (m_pGPSSourceParam != NULL))
		{
			static_cast<void>(CopyMemory(m_pGPSSourceParam, pGPSSrcParam, sizeof(T_NAV_SOURCE_PARAM)));
		}
	}

	void CNavAidsManager::Start()
	{
		BOOL bMMStart = FALSE;

		m_bStartFileReplay = FALSE;

		// AIS
		if (StartAIS() == TRUE)
		{
			bMMStart = TRUE;
		}
		// GPS
		if (StartGPS() == TRUE)
		{
			bMMStart = TRUE;
		}
		// EHS
		if (StartEHS() == TRUE)
		{
			bMMStart = TRUE;
		}

		if (bMMStart == TRUE)
		{
			m_bStartFileReplay = TRUE;
		}

		m_bStartNavAids = TRUE;
	}

	void CNavAidsManager::Stop()
	{
		m_bStartNavAids = FALSE;

		m_bStartFileReplay = FALSE;

		// MM Timer stop
		if (m_unMMSyncTimerID > 0U)
		{
			static_cast<void>(timeKillEvent(m_unMMSyncTimerID));
		}
		m_unMMSyncTimerID = 0U;

		// AIS
		StopAIS();
		
		// GPS
		StopGPS();
	
		// EHS
		StopEHS();
	}

	BOOL CNavAidsManager::StartAIS()  //cslee AIS 접속
	{
		BOOL bIsReplay = FALSE;

		if (g_pAISMsgManager != NULL)
		{
			g_pAISMsgManager->Start();
		}

		//m_pAISSourceParam->m_eSourceKind = E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE;
		switch (m_pAISSourceParam->m_eSourceKind)
		{
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_SERIAL:
		{
			if (m_pAISSourceParam->m_tSerialInfParam.m_unPortNo != 0)
			{
				if (g_pAISSerialNMEA == NULL)
				{
					g_pAISSerialNMEA = new CSerialNMEA();
				}
				if ((g_pAISSerialNMEA != NULL) && (g_pAISMsgManager != NULL) && (m_pAISSourceParam != NULL))
				{
					g_pAISSerialNMEA->SetMsgMngr(g_pAISMsgManager->GetSerialMsgMngr());
					if (g_pAISSerialNMEA->Start(static_cast<WORD>(m_pAISSourceParam->m_tSerialInfParam.m_unPortNo), static_cast<DWORD>(m_pAISSourceParam->m_tSerialInfParam.m_unBaudrate)) == FALSE)
						SendAlarmNotify(E_ALARM_TYPE::eALARM_WARNING, E_ALARM_KIND::eAIS_INF_ERROR, E_ALARM_CODE::eAIS_COM_ERROR);
				}
			}
	
			break;
		}
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE:
		{
			// Create File Replay
			if (g_pAISFileReplay == NULL)
			{
				g_pAISFileReplay = new CAISFileReplay();
			}
			if ((g_pAISFileReplay != NULL) && (g_pAISMsgManager != NULL) && (m_pAISSourceParam != NULL))
			{
				g_pAISFileReplay->SetMsgManager(g_pAISMsgManager->GetSerialMsgMngr());
				g_pAISFileReplay->StartReplay(m_pAISSourceParam->m_tFileReplayParam.m_szFileName);
				bIsReplay = TRUE;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return bIsReplay;
	}

	void CNavAidsManager::StopAIS()
	{
		if (g_pAISSerialNMEA != NULL)
		{
			g_pAISSerialNMEA->Stop();

			delete g_pAISSerialNMEA;
			g_pAISSerialNMEA = NULL;
		}

		// Delete File Replay
		if (g_pAISFileReplay != NULL)
		{
			g_pAISFileReplay->StopRepaly();

			delete g_pAISFileReplay;
			g_pAISFileReplay = NULL;
		}
		
		if (g_pAISMsgManager != NULL)
		{
			g_pAISMsgManager->Stop();
		}
	}

	BOOL CNavAidsManager::StartGPS()
	{
		BOOL bIsReplay = FALSE;

		if (g_pGPSMsgManager != NULL)
		{
			g_pGPSMsgManager->Start();
		}

		switch (m_pGPSSourceParam->m_eSourceKind)
		{
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_SERIAL:
		{
			if (g_pGPSSerialNMEA == NULL)
			{
				g_pGPSSerialNMEA = new CSerialNMEA();
			}
			if ((g_pGPSSerialNMEA != NULL) && (g_pGPSMsgManager != NULL) && (m_pGPSSourceParam != NULL))
			{
				g_pGPSSerialNMEA->SetMsgMngr(g_pGPSMsgManager->GetSerialMsgMngr());
				g_pGPSSerialNMEA->Start(static_cast<WORD>(m_pGPSSourceParam->m_tSerialInfParam.m_unPortNo), static_cast<DWORD>(m_pGPSSourceParam->m_tSerialInfParam.m_unBaudrate));
			}
			break;
		}
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE:
		{
			// Create File Replay
			if (g_pGPSFileReplay == NULL)
			{
				g_pGPSFileReplay = new CGPSFileReplay();
			}
			if ((g_pGPSFileReplay != NULL) && (g_pGPSMsgManager != NULL) && (m_pGPSSourceParam != NULL))
			{
				g_pGPSFileReplay->SetMsgManager(g_pGPSMsgManager->GetSerialMsgMngr());
				g_pGPSFileReplay->StartReplay(m_pGPSSourceParam->m_tFileReplayParam.m_szFileName);
				bIsReplay = TRUE;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return bIsReplay;
	}

	void CNavAidsManager::StopGPS()
	{
		if (g_pGPSSerialNMEA != NULL)
		{
			g_pGPSSerialNMEA->Stop();

			delete g_pGPSSerialNMEA;
			g_pGPSSerialNMEA = NULL;
		}

		// Delete File Replay
		if (g_pGPSFileReplay != NULL)
		{
			g_pGPSFileReplay->StopRepaly();

			delete g_pGPSFileReplay;
			g_pGPSFileReplay = NULL;
		}
		
		if (g_pGPSMsgManager != NULL)
		{
			g_pGPSMsgManager->Stop();
		}
	}

	BOOL CNavAidsManager::StartEHS()
	{
		BOOL bIsReplay = FALSE;

		if (g_pEHSMsgManager != NULL)
		{
			g_pEHSMsgManager->Start();
		}

		switch (m_pEHSSourceParam->m_eSourceKind)
		{
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_SERIAL:
		{
			if (g_pEHSSerialNMEA == NULL)
			{
				g_pEHSSerialNMEA = new CSerialNMEA();
			}
			if ((g_pEHSSerialNMEA != NULL) && (g_pEHSMsgManager != NULL) && (m_pEHSSourceParam != NULL))
			{
				g_pEHSSerialNMEA->SetMsgMngr(g_pEHSMsgManager->GetSerialMsgMngr());
				g_pEHSSerialNMEA->Start(static_cast<WORD>(m_pEHSSourceParam->m_tSerialInfParam.m_unPortNo), static_cast<DWORD>(m_pEHSSourceParam->m_tSerialInfParam.m_unBaudrate));
			}
			break;
		}
		case E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE:
		{
			// Create File Replay
			if (g_pEHSFileReplay == NULL)
			{
				g_pEHSFileReplay = new CEHSFileReplay();
			}
			if ((g_pEHSFileReplay != NULL) && (g_pEHSMsgManager != NULL) && (m_pEHSSourceParam != NULL))
			{
				g_pEHSFileReplay->SetMsgManager(g_pEHSMsgManager->GetSerialMsgMngr());
				g_pEHSFileReplay->StartReplay(m_pEHSSourceParam->m_tFileReplayParam.m_szFileName);
				bIsReplay = TRUE;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return bIsReplay;
	}
	
	void CNavAidsManager::StopEHS()
	{
		if (g_pEHSSerialNMEA != NULL)
		{
			g_pEHSSerialNMEA->Stop();

			delete g_pEHSSerialNMEA;
			g_pEHSSerialNMEA = NULL;
		}

		// Delete File Replay
		if (g_pEHSFileReplay != NULL)
		{
			g_pEHSFileReplay->StopRepaly();

			delete g_pEHSFileReplay;
			g_pEHSFileReplay = NULL;
		}

		if (g_pEHSMsgManager != NULL)
		{
			g_pEHSMsgManager->Stop();
		}
	}

	void CNavAidsManager::FileReplayProc()
	{
		// AIS
		if ((m_pAISSourceParam != NULL) && (m_pAISSourceParam->m_eSourceKind == E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE))
		{
			if (g_pAISFileReplay != NULL)
			{
				SetEvent(g_pAISFileReplay->GetReplayWorkEvent());
			}
		}
		// GPS
		if ((m_pGPSSourceParam != NULL) && (m_pGPSSourceParam->m_eSourceKind == E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE))
		{
			if (g_pGPSFileReplay != NULL)
			{
				SetEvent(g_pGPSFileReplay->GetReplayWorkEvent());
			}
		}
		// EHS
		if ((m_pEHSSourceParam != NULL) && (m_pEHSSourceParam->m_eSourceKind == E_NAV_SOURCE_KIND::eNAV_SOURCE_FILE))
		{
			if (g_pEHSFileReplay != NULL)
			{
				SetEvent(g_pEHSFileReplay->GetReplayWorkEvent());
			}
		}
	}

	void CNavAidsManager::InitReceiveStatus()
	{
		m_unCheckCount = 0U;
		m_unAisDataErrorCount = 0U;
	}

	void CNavAidsManager::CheckReceiveStatus() //cslee AIS 데이터 수신 체크
	{
		if (g_pAISMsgManager != NULL)
		{
			UINT unUpdateCount = g_pAISMsgManager->GetUpdateCount();
			SYSTEMTIME* pUpdateTime = g_pAISMsgManager->GetLastUpdateTime();

			BOOL bAlarmNotify = FALSE;

			if (unUpdateCount == 0)
			{
				m_unAisDataErrorCount++;
				if (m_unAisDataErrorCount > m_unAIS_DATA_ERROR_COUNT)
				{
					m_unAisDataErrorCount = 0U;
					bAlarmNotify = TRUE;
				}
			}
			else
			{
				// 1초 동안 데이터를 수신하지 못 하면 에러 카운트 증가
				if (GetTotalMSeconds(pUpdateTime) > 1000U)
				{
					m_unAisDataErrorCount++;
				}
				else
				{
					m_unAisDataErrorCount = 0U;
				}

				if (m_unAisDataErrorCount >= m_unAIS_DATA_ERROR_COUNT)
				{
					m_unAisDataErrorCount = 0U;
					bAlarmNotify = TRUE;
				}
			}

			//if (bAlarmNotify == TRUE)
			//{
			//	SendAlarmNotify(E_ALARM_TYPE::eALARM_WARNING, E_ALARM_KIND::eAIS_INF_ERROR, E_ALARM_CODE::eAIS_RCV_ERROR);
			//}
		}
	}

	void CNavAidsManager::SendAlarmNotify(const E_ALARM_TYPE eAlarmType, const E_ALARM_KIND eAlarmKind, const E_ALARM_CODE eAlarmCode)
	{
		CUserCommand* pUserCommand = CUserCommand::GetInstance();

		if (pUserCommand != NULL)
		{
			T_USER_COMMAND* pUserCmd = pUserCommand->GetBackBuffer();
			pUserCmd->eCommand = E_USER_COMMAND::eUSER_CMD_ALARM_NOTIFY;
			pUserCmd->m_tAlarmInfo.m_eAlarmType = eAlarmType;
			pUserCmd->m_tAlarmInfo.m_eAlarmKind = eAlarmKind;
			pUserCmd->m_tAlarmInfo.m_eAlarmCode = eAlarmCode;
			pUserCommand->PushBack(FALSE);
		}
	}

	UINT64 CNavAidsManager::GetTotalMSeconds(const SYSTEMTIME* const pOldTime)
	{
		COleDateTime oleOldTime;
		COleDateTime oleCurTime;
		COleDateTimeSpan oleTimeSpan;

		SYSTEMTIME tSysTime;


		UINT64 unReturnValue = 0U;

		if (pOldTime != NULL)
		{
			GetLocalTime(&tSysTime);

			static_cast<void>(oleOldTime.SetDateTime(
				static_cast<INT>(pOldTime->wYear),
				static_cast<INT>(pOldTime->wMonth),
				static_cast<INT>(pOldTime->wDay),
				static_cast<INT>(pOldTime->wHour),
				static_cast<INT>(pOldTime->wMinute),
				static_cast<INT>(pOldTime->wSecond)));

			const INT nOldMSec = static_cast<INT>(pOldTime->wMilliseconds);

			static_cast<void>(oleCurTime.SetDateTime(
				static_cast<INT>(tSysTime.wYear),
				static_cast<INT>(tSysTime.wMonth),
				static_cast<INT>(tSysTime.wDay),
				static_cast<INT>(tSysTime.wHour),
				static_cast<INT>(tSysTime.wMinute),
				static_cast<INT>(tSysTime.wSecond)));
			const INT nCurMSec = static_cast<INT>(tSysTime.wMilliseconds);

			oleTimeSpan = oleCurTime - oleOldTime;

			const DOUBLE dSeconds = oleTimeSpan.GetTotalSeconds();
			INT nMSecDiff = 0;
			if (nCurMSec > nOldMSec)
			{
				nMSecDiff = (nCurMSec - nOldMSec);
			}
			else
			{
				nMSecDiff = (nOldMSec - nCurMSec - 1000);
			}
			if (dSeconds < 1.0)
			{
				if (nMSecDiff < 0)
				{
					unReturnValue = 0U;
				}
				else
				{
					unReturnValue = nMSecDiff;
				}
			}
			else
			{
				const DOUBLE dTmp = dSeconds * 1000.0 + static_cast<DOUBLE>(nMSecDiff);
				unReturnValue = static_cast<UINT64>(dTmp);
			}
		}

		return unReturnValue;
	}

	void CNavAidsManager::CreateDataSyncProcThread()
	{
		if (m_pDataSyncProcThread == NULL)
		{
			m_pDataSyncProcThread = AfxBeginThread(static_cast<AFX_THREADPROC>(DataSyncProcThread), static_cast<LPVOID>(this), THREAD_PRIORITY_TIME_CRITICAL, 0U, static_cast<DWORD>(CREATE_SUSPENDED));
			if (m_pDataSyncProcThread != NULL)
			{
				m_pDataSyncProcThread->m_bAutoDelete = TRUE;
				static_cast<void>(m_pDataSyncProcThread->ResumeThread());
			}
		}
	}

	void CNavAidsManager::ExitDataSyncProcThread()
	{
		static_cast<void>(SetEvent(m_hSyncExitEvent));

		if (m_pDataSyncProcThread != NULL)
		{
			static_cast<void>(WaitForSingleObject(m_pDataSyncProcThread->m_hThread, static_cast<DWORD>(1000U)));
			m_pDataSyncProcThread = NULL;
		}
	}

	void CNavAidsManager::DataSyncProcThread()
	{
		if (m_bStartNavAids == TRUE)
		{
			if (m_bStartFileReplay == TRUE)
			{
				FileReplayProc();
			}

			m_unCheckCount++;
			if (m_unCheckCount > 1000U / m_unMMSyncTimerDelay)	// 1초 마다 체크
			{
				m_unCheckCount = 0U;
				CheckReceiveStatus();
			}
		}
	}

	UINT CNavAidsManager::DataSyncProcThread(LPVOID const lpParam)
	{
		CNavAidsManager* const pAisMsgMngr = static_cast<CNavAidsManager*>(lpParam);

		if (pAisMsgMngr != NULL)
		{
			INT nQuit = 0;
			HANDLE arrEvent[2];

			arrEvent[0] = pAisMsgMngr->m_hSyncExitEvent;	// Exit Event
			arrEvent[1] = pAisMsgMngr->m_hSyncWorkEvent;	// Work Event

			DWORD dwEvent;

			while (nQuit < 1)
			{
				dwEvent = WaitForMultipleObjects(2U, arrEvent, FALSE, INFINITE);
				switch (dwEvent)
				{
				case static_cast<DWORD>(WAIT_OBJECT_0) + 0U: // Exit Event
				{
					nQuit++;
					break;
				}
				case static_cast<DWORD>(WAIT_OBJECT_0) + 1U: // Work Event
				{
					pAisMsgMngr->DataSyncProcThread();
					break;
				}
				default:
				{
					// Do Nothing
					break;
				}
				}
			}
		}

		return 0U;
	}
}
