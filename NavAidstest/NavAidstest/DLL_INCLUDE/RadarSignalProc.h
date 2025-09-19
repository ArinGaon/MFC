#pragma once

#include <afxwin.h>

#include "SystemTypeDef.h"
#include "SignalProcCommandDef.h"

using namespace NS_SALUS_MS_APP;

class AFX_EXT_CLASS CRadarSignalProc
{
public:
	CRadarSignalProc();
	~CRadarSignalProc();
	
	static CRadarSignalProc* GetInstance();
	static void DeleteInstance();

	void Initialize();
	void Finalize();

	void SetSignalProcConfig(T_SIGNAL_PROC_CONFIG* const pSignalProcConfig);
	void SetTrackingConfig(T_TRACKING_CONFIG* const pTrackingConfig);
	void SetRadarConfig(T_RADAR_CONFIG* const pRadarConfig);

	void ResetSignalProcessing();

	void AddGuardZone(int index);

	void DeleteGuardZone(int type, int id);

	void SendAISData(T_DYNAMIC_AIS* tDyanmicAIS, T_STATIC_AIS* tStaticAIS);
	void SendAIVDOData(T_AIS_TYPEAIVDOINFO* tAIVDOAIS);
private:
	void ProcGroupTrack(T_TRACK_GROUP_RECT* const pTrackGroupRect);
	void ProcAddTrack(T_TRACK_POS_INFO* const pTrackPosInfo);
	void ProcDelTrack(T_TRACK_SEL_INFO* const pTrackSelInfo);
	void ProcSwapTrack(T_TRACK_SEL_INFO* const pTrackSelInfo);
	void ProcFastTrack(T_TRACK_SEL_INFO* const pTrackSelInfo);
	void ProcResetTrack();
	void ProcAreaMaskData();
	void ProcGuardZoneData();

	void StartSignalProcCommandProcThread();
	void TerminateSignalProcCommandProcThread();

	void SignalProcCommandProc();
	static UINT SignalProcCommandProcThread(LPVOID const lpParam);

private:
	static CRadarSignalProc* m_pInstance;

	HANDLE m_hExitSignalProcCommandProcEvent;
	CWinThread*	m_pSignalProcCommandProcThread;
};

