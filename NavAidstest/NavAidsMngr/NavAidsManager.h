#pragma once

#include "SystemTypeDef.h"
#include "AlarmTypeDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_NAV_SOURCE_KIND : INT
	{
		eNAV_SOURCE_NONE = 0,
		eNAV_SOURCE_NETWORK,
		eNAV_SOURCE_SERIAL,
		eNAV_SOURCE_FILE
	};

	struct T_NAV_SOURCE_PARAM
	{
		E_NAV_SOURCE_KIND m_eSourceKind;
		union
		{
			T_NETWORK_INF_PARAM m_tNetworkInfParam;
			T_SERIAL_INF_PARAM m_tSerialInfParam;
			T_FILE_REPLAY_PARAM m_tFileReplayParam;
		};
	};

	class AFX_EXT_CLASS CNavAidsManager
	{
	public:
		CNavAidsManager();
		~CNavAidsManager();

	public:
		static CNavAidsManager* GetInstance();
		static void DeleteInstance();

		void Initialize(CWnd* const pParentWnd);
		void Finalize();

		void SetSourceParam(const T_NAV_SOURCE_PARAM* const pAISSrcParam, const T_NAV_SOURCE_PARAM* const pGPSSrcParam, const T_NAV_SOURCE_PARAM* const pEHSSrcParam);
		void SetSourceParamAIS(const T_NAV_SOURCE_PARAM* const pAISSrcParam);
		void SetSourceParamGPS(const T_NAV_SOURCE_PARAM* const pGPSSrcParam);
		void Start();
		void Stop();
		BOOL StartAIS();
		void StopAIS();

		BOOL StartGPS();
		void StopGPS();
	private:
	

		BOOL StartEHS();
		void StopEHS();

		void FileReplayProc();

		void InitReceiveStatus();
		void CheckReceiveStatus();

		void SendAlarmNotify(const E_ALARM_TYPE eAlarmType, const E_ALARM_KIND eAlarmKind, const E_ALARM_CODE eAlarmCode);

		UINT64 GetTotalMSeconds(const SYSTEMTIME* const pOldTime);

		void CreateDataSyncProcThread();
		void ExitDataSyncProcThread();

		void DataSyncProcThread();
		static UINT DataSyncProcThread(LPVOID const lpParam);

	private:
		static CNavAidsManager* m_pInstance;

		static const UINT m_unAIS_DATA_ERROR_COUNT = 300U; // 300초 동안 데이터 수신하지 못 하면 알람 통지
		//static const UINT m_unAIS_DATA_ERROR_COUNT = 10U; // 10초 동안 데이터 수신하지 못 하면 알람 통지

		CWnd* m_pParentWnd;

		BOOL m_bStartNavAids;
		BOOL m_bStartFileReplay;

		UINT m_unCheckCount;
		UINT m_unAisDataErrorCount;

		T_NAV_SOURCE_PARAM* m_pAISSourceParam;
		T_NAV_SOURCE_PARAM* m_pGPSSourceParam;
		T_NAV_SOURCE_PARAM* m_pEHSSourceParam;

		// Nav Sync
		static const UINT m_unMMSyncTimerDelay = 100U; // 100 ms delay
		UINT m_unMMSyncTimerID;
		HANDLE m_hSyncWorkEvent;
		HANDLE m_hSyncExitEvent;
		CWinThread* m_pDataSyncProcThread;
	};
}	// NS_SALUS_MS_APP


