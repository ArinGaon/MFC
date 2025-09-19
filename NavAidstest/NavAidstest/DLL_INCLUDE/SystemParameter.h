#pragma once

#include "SystemTypeDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_DATA_FILE_TYPE : INT
	{
		eGUARD_ZONE_FILE = 0,
		eUSER_MAP_FILE = 1,
		eVIRTUAL_TRACK_FILE = 2
	};

	class AFX_EXT_CLASS CSystemParameter
	{
	public:
		CSystemParameter();
		~CSystemParameter();

	public:
		static CSystemParameter* GetInstance();
		static void DeleteInstance();

		void Initialize(const CString strHomeDirectory);
		void Finalize();

		// SET, GET
		void SetDisplayConfig(const T_DISPLAY_CONFIG* const pDisplayConfig);
		void SetColorConfig(const T_COLOR_CONFIG* const pColorConfig);
		void SetSettingConfig(const T_SETTING_CONFIG* const pSettingConfig);
		void SetVrmEblSetting(const T_VRMEBL_SETTING* const pVrmEblSetting);
		void SetRadarSystem(const T_RADAR_CONFIG* const pRadarConfig);

		void SetSignalProcConfig(const T_SIGNAL_PROC_CONFIG* const pSignalProcConfig);

		void SetTrackingConfig(const T_TRACKING_CONFIG* const pTrackingConfig);

		void SetAisConfig(const T_AIS_CONFIG* const pAisConfig);
		void SetAisConfigByEnv(const T_AIS_CONFIG* const pAisConfig);
		void SetSimradConfigByEnv(const T_SIMRAD_SAVE_DATA* const pSimradConfig);
		void SetSimradFTCValue(UINT Value);
		void SetGpsConfig(const T_GPS_CONFIG* const pGpsConfig);
		void SetGpsConfigByEnv(const T_GPS_CONFIG* const pGpsConfig);
		void SetCPATCPAByEnv(const T_CPATCAP_CONFIG* const pCPATCPAConfig);

		void SetTpgConfig(const T_TPG_CONFIG* const pTpgConfig);
		void SetFileReplayConfig(const T_REPLAY_CONFIG* const pFileReplayConfig);

		T_DISPLAY_CONFIG* GetDisplayConfig();
		T_COLOR_CONFIG* GetColorConfig();
		T_SETTING_CONFIG* GetSettingConfig();
		T_VRMEBL_SETTING* GetVrmEblSetting();

		T_RADAR_CONFIG* GetRadarConfig();
		T_SIGNAL_PROC_CONFIG* GetSignalProcConfig();
		T_TRACKING_CONFIG* GetTrackingConfig();

		T_AIS_CONFIG* GetAisConfig();
		T_SIMRAD_SAVE_DATA* GetSimradConfig();
		T_GPS_CONFIG* GetGpsConfig();
		CString GetClientIPAddr();

		T_CPATCAP_CONFIG* GetCPATCPAConfig();

		T_TPG_CONFIG* GetTpgConfig();
		T_REPLAY_CONFIG* GetFileReplayConfig();

		CString GetHomeDirectory();

		void SaveSystemParameter();

		// Data File
		BOOL OpenDataFile(const E_DATA_FILE_TYPE eDataFileType);
		void CloseDataFile(const E_DATA_FILE_TYPE eDataFileType);
		UINT GetDataCount(const E_DATA_FILE_TYPE eDataFileType);
		void SetDataCount(const E_DATA_FILE_TYPE eDataFileType, const UINT unDataCount);
		BOOL GetDataFile(const E_DATA_FILE_TYPE eDataFileType, const UINT unIndex, void* const pDataPtr, const UINT unDataSize);
		void SetDataFile(const E_DATA_FILE_TYPE eDataFileType, const UINT unIndex, const void* const pDataPtr, const UINT unDataSize);

	protected:
		void InitSystemParameter();

		void StartParamSaveProcThread();
		void TerminateParamSaveProcThread();

		void ParamSaveProc();
		static UINT ParamSaveProcThread(LPVOID const lpParam);

	private:
		static CSystemParameter* m_pInstance;

		CString m_strHomeDirectory;

		HANDLE m_hExitParamSaveProcEvent;
		CWinThread* m_pParamSaveProcThread;
	};

}	// NS_SALUS_MS_APP


