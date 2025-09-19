#pragma once

namespace NS_SALUS_MS_APP
{
	enum class E_ALARM_TYPE : INT
	{
		eALARM_NORMAL = 0,
		eALARM_FALUT = 1,		// Alarm
		eALARM_WARNING = 2,		// Warning
		eALARM_CAUTION = 3,		// Caution
		eALARM_UNDEFINED = 255
	};

	enum class E_ALARM_KIND : UINT
	{
		eRADAR_ERROR = 0U,
		eRIB_ERROR = 1U,
		eAIS_INF_ERROR = 2U,
		eVPASS_INF_ERROR = 3U,
		eCPA_ERROR = 4U,
		eSOS_DETECT = 5U,
		eTARGET_ERROR = 6U,
		eCPUUSAGEERROR = 7U,
		eRAMUSAGEERROR = 8U,
		eDISKUSAGEERROR = 9U,
		eSART_DETECT = 10U
	};

	enum class E_ALARM_CODE : UINT
	{
		// RADAR ERROR
		eRADAR_INF_ERROR = 0x0101,
		eRADAR_ROT_STOP = 0x0102,
		eRADAR_STANDBY = 0x0103,
		eRADAR_SLEEP = 0x0104,
		eRADAR_DEVICE_ERROR = 0x0105,
		eRADAR_NOSCANNER = 0x0106,
		eRADAR_DETECTING_SCANNER = 0x0107,
		// RADAR INTERFACE BOARD ERROR
		eRIB_OPEN_FAIL = 0x0201,
		eRIB_INIT_FAIL = 0x0202,
		eRIB_PLAY_FAIL = 0x0203,
		// AIS INTERFACE ERROR
		eAIS_COM_ERROR = 0x0301,
		//eAIS_RCV_ERROR = 0x0302,
		// VPASS
		//eVPASS_COM_ERR = 0x0401,
		// CPA ERROR
		eCPA_DANGER = 0x0501,
		// 
		eSART_DETECT = 0x0601,
		eSOS_DETECT = 0x0602,
		// TRACK Capacity
		eTARGET_CAPACITY_A = 0x0701,	// Fault,  > g_unMAX_TRACK_NUM 狼 110% 老 版快
		eTARGET_CAPACITY_W = 0x0702,	// Warning, > g_unMAX_TRACK_NUM 狼 100% 老 版快
		eTARGET_CAPACITY_C = 0x0703,	// Caution, > g_unMAX_TRACK_NUM 狼 90% 老 版快

		eTARGET_NEW_FAST = 0x0801,
		eTARGET_NEW = 0x0802,

		eLOST_TARGET = 0x0900,	// Top code
		eTARGET_LOST = 0x0901,

		eCPU_USAGE_A = 0x1000,     //Warning usage > 70%
		eCPU_USAGE_B = 0x1001,     //Alarm usage > 90%

		eDISK_USAGE_A = 0x1002,     //Warning usage > 90%
		eDISK_USAGE_B = 0x1003,     //Alarm usage > 95%

		eRAM_USAGE_A = 0x1004,     //Warning usage > 70%
		eRAM_USAGE_B = 0x1005,     //Alarm usage > 90%

		eErrorPersistenceCorrupt = 0x00000001,
		eErrorZeroBearingFault = 0x00010001,
		eErrorBearingPulseFault = 0x00010002,
		eErrorMotorNotRunning = 0x00010003,
		eErrorCommsNotActive = 0x00010004,
		eErrorMagnetronHeaterVoltage = 0x00010005,
		eErrorModulationVoltage = 0x00010006,
		eErrorTriggerFault = 0x00010007,
		eErrorVideoFault = 0x00010008,
		eErrorFanFault = 0x00010009,
		eErrorScannerConfigFault = 0x0001000A,
		eErrorPowerSupplyTransient = 0x0001000B,
		eErrorScannerDetectFail = 0x0001000C,
		eErrorPASoftOverheat = 0x0001000D,
		eErrorPAHardOverheat = 0x0001000E,
		eErrorGWDatapathError = 0x0001000F,
		eErrorPSUOverheat = 0x00010010,
		eErrorPSUVoltage = 0x00010011,
		eErrorPSUPower = 0x00010012,
		eErrorPSUHWFault = 0x00010013,
		eErrorPSUCommsFault = 0x00010014,
		eErrorMechanicalFault = 0x00010015,
		eErrorLEDFault = 0x00010016,
		eErrorScannerFail = 0x00010017,
		eErrorRIFault = 0x00010018,
		eErrorLowBattery = 0x00010019,
		eErrorMotorStall = 0x0001001A,
		eErrorSafetyMode = 0x0001001B,
		eErrorDopplerFail = 0x0001001C,
		eErrorInstallCacheMismatch = 0x0001001D,
		eErrorTrackingUnavailable = 0x0001001E
	};

#pragma pack(push, 1)

	struct T_ALARM_CPA_ERROR
	{
		UINT m_unTrackID[2];
		FLOAT m_fCPA;
		FLOAT m_fTCPA;
		TCHAR m_szCallSign[2][7];
	};

	struct T_ALARM_SART_DETECT
	{
		UINT m_unMMSI;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		TCHAR m_szCallSign[7];
	};

	struct T_ALARM_SOS_DETECT
	{
		UINT m_unVPassDevID;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
	};

	struct T_ALARM_TRACK_CAPACITY
	{
		UINT m_unCurTrackNum;		// Number of Current Track
		UINT m_unTotalTrackNum;
	};

	struct T_ALARM_FAST_TRACK
	{
		UINT m_unTrackID;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
	};

	struct T_ALARM_NEW_TRACK
	{
		UINT m_unTrackID;
		UINT m_unZoneID;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
	};

	struct T_ALARM_LOST_TRACK
	{
		UINT m_unTrackID;
		UINT m_unZoneID;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
	};

	static const INT g_nMAX_ALARM_TITLE_SIZE = 20;
	static const INT g_nMAX_ALARM_MSG_SIZE = 32;
	static const INT g_nMAX_ALARM_DESC_SIZE = 128;

	struct T_ALARM_INFO
	{
		E_ALARM_TYPE m_eAlarmType;
		E_ALARM_KIND m_eAlarmKind;
		E_ALARM_CODE m_eAlarmCode;
		INT m_nSoundOn;					// 0 = Sound Off, 1 = Sound On
		SYSTEMTIME m_tDetectTime;
		SYSTEMTIME m_tAckTime;
		INT m_nisAutoAck;               // 0 = By Man, 1 = Auto Ack
		TCHAR m_szTitle[g_nMAX_ALARM_TITLE_SIZE];
		//TCHAR m_szMsg[g_nMAX_ALARM_MSG_SIZE];
		TCHAR m_szMsg[g_nMAX_ALARM_DESC_SIZE];
		TCHAR m_szDesc[g_nMAX_ALARM_DESC_SIZE];
		union
		{
			T_ALARM_CPA_ERROR m_tCpaError;
			T_ALARM_SART_DETECT m_tSartDetect;
			T_ALARM_SOS_DETECT m_tSosDetect;
			T_ALARM_TRACK_CAPACITY m_tTrackCapacity;
			T_ALARM_FAST_TRACK m_tFastTrack;
			T_ALARM_NEW_TRACK m_tNewTrack;
			T_ALARM_LOST_TRACK m_tLostTrack;
		};
	};

#pragma pack(pop)
}