#pragma once

#include "RadarBaseDef.h"

namespace NS_SALUS_MS_APP
{
	// Network Message Info Code
	static const USHORT m_usINFOCODE_CONTROL_HEARTBEAT_REQ = 50U;	// Heartbeat Request, Client --> Server
	static const USHORT m_usINFOCODE_CONTROL_HEARTBEAT_RES = 55U;	// Heartbeat Response, Server --> Client
	static const USHORT m_usINFOCODE_CONTROL_SIMULATION = 100U;		// Simulation control, Client --> Server
	static const USHORT m_usINFOCODE_REQ_RADAR_INF = 110U;			// Request RADAR Interface Config, Client --> Server
	static const USHORT m_usINFOCODE_RES_RADAR_INF = 111U;			// Response RADAR Interface Config, Server --> Client
	static const USHORT m_usINFOCODE_SET_RADAR_INF = 112U;			// Setting RADAR Inteface Config, Client --> Server
	static const USHORT m_usINFOCODE_REQ_AIS_INF = 120U;			// Request AIS Interface Config, Client --> Server
	static const USHORT m_usINFOCODE_RES_AIS_INF = 121U;			// Response AIS Interface Config, Server --> Client
	static const USHORT m_usINFOCODE_SET_AIS_INF = 122U;			// Setting AIS Interface Config, Client --> Server
	static const USHORT m_usINFOCODE_REQ_GPS_INF = 130U;			// Request GPS Interface Config, Client --> Server
	static const USHORT m_usINFOCODE_RES_GPS_INF = 131U;			// Response GPS Interface Config, Server --> Client
	static const USHORT m_usINFOCODE_SET_GPS_INF = 132U;			// Setting GPS Interface Config, Client --> Server
	static const USHORT m_usINFOCODE_REQ_SIGNAL_PARAM = 140U;		// Request Signal Processing Parameter, Client --> Server
	static const USHORT m_usINFOCODE_RES_SIGNAL_PARAM = 141U;		// Response Signal Processing Parameter, Server --> Client
	static const USHORT m_usINFOCODE_SET_SIGNAL_PARAM = 142U;		// Setting Signal Processing Parameter, Client --> Server
	static const USHORT m_usINFOCODE_REQ_TRACKING_PARAM = 150U;		// Request Tracking Parameter, Client --> Server
	static const USHORT m_usINFOCODE_RES_TRACKING_PARAM = 151U;		// Response Tracking Parameter, Server --> Client
	static const USHORT m_usINFOCODE_SET_TRACKING_PARAM = 152U;		// Setting Tracking Parameter, Client --> Server

#pragma pack(push, 1)

	// Network Message Definition
	struct T_NET_TPG_CFG
	{
		INT m_nPattern;
		FLOAT m_fPeriod;
		INT m_nPRF;
		INT m_nRange;
	};

	struct T_NET_REPLAY_CFG
	{
		TCHAR m_szFileName[g_nMAX_FILE_NAME_SIZE];
		INT m_nFileType;				// 0 = SPx Replay File, 1 = Quantum Replay File
		INT m_nRepeat;					// 0 = No Repeat, 1 = Repeat;
	};

	struct T_NET_SIMUL_CFG
	{
		INT m_nStart;					// 0 = Stop, 1 = Start
		INT m_nVideoType;				// Video Simulation Type, 0 = Test Pattern, 1 = File Replay
		T_NET_TPG_CFG m_tTpg;
		T_NET_REPLAY_CFG m_tReplay;
		BOOL m_bAisFileReplay;			// AIS File Replay, TRUE = File Repaly
		TCHAR m_szAisFileName[g_nMAX_FILE_NAME_SIZE];
		BOOL m_bGpsFileReplay;			// GPS File Replay, TRUE = File Replay
		TCHAR m_szGpsFileName[g_nMAX_FILE_NAME_SIZE];
		BOOL m_bEhsFileReplay;			// EHS File Replay, TRUE = File Replay
		TCHAR m_szEhsFileName[g_nMAX_FILE_NAME_SIZE];
	};

	struct T_NET_SERIAL_SET
	{
		INT m_nPortNo;
		INT m_nBaudrate;
	};

	struct T_NET_ETHERNT_SET
	{
		TCHAR m_szIpAddr[g_nMAX_ETH_IPADDR_SIZE];
		INT m_nPortNo;
	};

	struct T_NET_AVIDEO_SET		// Analog Video 설정 정보
	{
		DOUBLE m_dRangeStart;
		DOUBLE m_dRangeEnd;
		DOUBLE m_dRangeOffset;
		INT m_nChannel;
		DOUBLE m_dGain;
		DOUBLE m_dOffset;
		INT m_nAcpKind;
		INT m_nAcpInv;		// ACP Inverse, 0 = FALSE, others = TRUE
		INT m_nArpKind;
		INT m_nArpInv;		// ARP Inverse, 0 = FALSE, others = TRUE
		INT m_nTriggerKind;
		INT m_nTriggerInv;	// Triger Inverse, 0 = FALSE, others = TRUE
	};

	struct T_NET_RADAR_INF_CFG
	{
		CString m_szSiteName;

		DOUBLE m_dSiteLat;
		DOUBLE m_dSiteLon;

		INT m_nCtrlMethod;	// 제어 방법, 0 = Serial, 1 = Ethernet
		T_NET_SERIAL_SET m_tCtrlSerial;
		T_NET_ETHERNT_SET m_tCtrlEth;
		INT m_nVideoKind;		// 비디오 데이터 연결 상태, 0 = Analog, 1 = Ethernet
		T_NET_AVIDEO_SET m_tAVideo;
		T_NET_ETHERNT_SET m_tDVideo;
	};

	struct T_NET_AIS_INF_CFG
	{
		INT m_nInfMethod;		// 연동 방법, 0 = Serial, 1 = Ethernet
		T_NET_SERIAL_SET m_tSerial;
		T_NET_ETHERNT_SET m_tEthernet;
	};

	struct T_NET_GPS_INF_CFG
	{
		INT m_nInfMethod;		// 연동 방법, 0 = Serial, 1 = Ethernet
		T_NET_SERIAL_SET m_tSerial;
		T_NET_ETHERNT_SET m_tEthernet;
	};

	struct T_NET_SIGNAL_PROC_PARAM
	{
		// Pulse Integration
		USHORT m_usPI_Gain;				// 1 ~ 100 Scaled by 0.1, Always Enable
		UINT m_unPI_CellIndex;
		// Sensitivity Time Control
		USHORT m_usSTC_Gain;			// 0 ~ 100 Scaled by 0.1, 0: Disable, otherwise: Enable 
		FLOAT  m_fSTC_Range;			// meter (to Acquisition Range Maximally)
		// Rain Clutter Control
		USHORT m_usRCC_Gain;			// 0 ~ 100
		// Scan Integration
		USHORT m_usSI_Gain;				// Gain of Current Video, Scaled by 0.1, 0: Disable, otherwise: Enable
		// Constant False Alarm 
		USHORT m_usCFAR_Multiplier[2];	// Probability of False Alarm, 0: Disable, Multiplier is calculated automatically
		FLOAT m_fCFAR_Range[2];
		// Intensity Control
		USHORT m_usRVG_Gain;			 // Gain for Intensity Control, Scaled by 0.1, 0: Disable, otherwise: Enable
	};

	struct T_NET_TRACKING_PARAM
	{
		UINT m_unMaxTargetSpeed;			// Maximum Speed of Track(135KTS)
		UINT m_unMinNoTrackConfirm;		// Minimum No of Hit for Track Confirmation(0~255)
		UINT m_unMaxNoTrackLoss;			// Maximum No of Missing for Track Lost(0~255)
		UINT m_unGatingThreshold;			// Chi-Square Distribution Selection(1:90%, 2:95%, 3:97.5, 4:99%, 5:99.9%)
		DOUBLE m_dStdProcessNoise1;			// Process Noise of First Dynamic Model(0.05 ~ 10.0, Increment: 0.05 )
		DOUBLE m_dStdProcessNoise2;			// Process Noise of Second Dynamic Model (0.05~10.0, Increment: 0.05 )
		DOUBLE m_dStdRangeError;			// Range Error of Radar Measurement
		DOUBLE m_dStdAzimuthError;			// Azimuth Error of Radar Measurement 
		DOUBLE m_dStdAISPosError;			// Position Error of AIS Object Information
	};

#pragma pack(pop)
}