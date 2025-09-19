#pragma once

#include "DataTypeDef.h"
#include "RadarBaseDef.h"

#include "SmsBaseDef.h"

namespace NS_SALUS_MS_APP
{
#define MAX_SERIALNUMBER_SIZE  16   ///< Including the terminating nul character
#define MAX_LOCKID_SIZE       128   ///< Maximum size of a Lock-ID
#define MAX_UNLOCKKEY_SIZE    128   ///< Maximum size of an Unlock-Key

	enum class E_TRACK_VIEW_MODE : INT
	{
		eRADAR = 0,
		eAIS,
		eBOTH,
	};

	enum class E_RADAR_PULSE_MODE : INT
	{
		ePULSE_SP = 0,
		ePULSE_MP = 1,
		ePULSE_LP = 2,
		ePULSE_VLP = 3
	};

	enum class E_RADAR_DUAL_STATUS : INT
	{
		ePRIMARY = 0,
		eSECONDARY
	};

	enum class E_RADAR_OPERATION_MODE : INT
	{
		eSTOP = 0,
		eRUN,
	};

	enum class E_RADAR_TX_MODE : INT
	{
		eStandby = 0,
		eTransmit
	};

	enum class E_SCOPE_ORIENTATION : INT
	{
		eNORTH_UP = 0,
		eCOURSE_UP,
		eHEADING_UP,
	};

	enum class E_SCOPE_MOTION : INT
	{
		eMOTION_REL = 0,
		eMOTION_TRUE,
	};

	enum class E_CLUTTER_MODE : INT
	{
		eSEA = 0,
		eGROUND,
	};

#pragma pack(push, 1)

#define LEN_CALLSIGN			7
#define LEN_SHIPNAME			20
#define LEN_DESTINATION			20

	struct T_SYSTEM_CONTROL_STATUS
	{
		E_RADAR_DUAL_STATUS	m_eDualStatus;
		E_RADAR_OPERATION_MODE m_eOperateMode;
		E_RADAR_PULSE_MODE m_ePulseMode;
		E_RADAR_TX_MODE m_eTxMode;
		E_TRACK_VIEW_MODE m_eTrackViewMode;
		E_SCOPE_MOTION m_eMotionMode;
		E_SCOPE_ORIENTATION m_eOrientationMode;
	};

	struct T_DISPLAY_CONFIG
	{
		INT m_nRotation;

		T_TRACKINFO_VIEW m_tTrackInfoView;
		T_AISINFO_VIEW m_tAisInfoView;
		T_DISPLAY_UNIT m_tDispUnit;
	};

	struct T_COLOR_CONFIG
	{
		INT m_nColorSet;		// Range : 0 ~ 1, Value : 0 = Night, 1 = Day
		INT m_nGroupKind;		// Range : 0 ~ 4, Value : 0 = Default, 1 = User1, 2 = User2, 3 = User3

		COLORREF m_clrUserColor[g_nMAX_COLOR_GROUP_NUM][g_nMAX_USER_DEFINE_COLOR_NUM];
	};

	struct T_SETTING_CONFIG
	{
		T_TRACKVIEW_CONTROL m_tTrackViewCtrl;
		T_CPA_THRESHOLD m_tCpaThreshold;
	};

	struct T_VRMEBL_SETTING
	{
		BOOL m_bShow[2];
		FLOAT m_fVRM[2];
		FLOAT m_fEBL[2];
		BOOL m_bSet[2];
	};

	struct T_RADAR_LOCATION
	{
		TCHAR m_szSiteName[g_nMAX_SITE_NAME_SIZE];
		DOUBLE m_dLat;
		INT m_iLatDir;
		DOUBLE m_dLon;
		INT m_iLonDir;
		DOUBLE m_dHeight;
	};

	struct T_RADAR_BIAS
	{
		DOUBLE m_dRange;
		DOUBLE m_dAzimuth;
	};

	struct T_SERIAL_INF
	{
		UINT m_unPortNo;
		UINT m_unBaudrate;
	};

	struct T_ETHERNET_INF
	{
		TCHAR m_szIpAddr[g_nMAX_ETH_IPADDR_SIZE];
		UINT m_unPortNo;
	};

	struct T_RADAR_INTERFACE
	{
		UINT m_unCMethod;  // Interface Method, 0 = Serial, 1 = Ethernet
		UINT m_unMethod; // Interface Method, 0 = Analog, 1 = Digital
		UINT m_unPRF;
		UINT m_unRPM;
		UINT m_unMaxACP;
		UINT m_unMode;
		UINT m_unACPType;
		UINT m_unACPInv;
		UINT m_unARPType;
		UINT m_unARPInv;
		UINT m_unTriggerType;
		UINT m_unTriggerInv;
		UINT m_unVideoChannel;
		UINT m_unVideoSample;
		UINT m_unRecvDur;
		UINT m_unRecvChange;			// lsk.. 데이터가 안들어왔을때, Board 자동 전환 시간..
		DOUBLE m_dVideoGain;
		DOUBLE m_dVideoOffset;
		DOUBLE m_dStartRange;
		DOUBLE m_dEndRange;
		T_ETHERNET_INF m_tEthInfC;
		T_ETHERNET_INF m_tEthInf;
		DOUBLE m_dRangeOffset;
		UINT m_unControlComPort;
		UINT m_unControlBaudrate;
	};

	struct T_RADAR_CONFIG
	{
		INT m_nChangeValue;
		INT m_nDeviceID;
		INT m_nDeviceModel;					// Primary : 0, Secondary : 1
		T_RADAR_LOCATION m_tLocation;
		T_RADAR_BIAS m_tBias;
		T_RADAR_INTERFACE m_tInterface;
	};

	struct T_AIS_CONFIG
	{
		INT m_nMethod; // Interface Method, 0 = Serial, 1 = Ethernet
		T_SERIAL_INF m_tSerial;
		T_ETHERNET_INF m_tEth;
	};

	struct T_GPS_CONFIG
	{
		INT m_nMethod; // Interface Method, 0 = Serial, 1 = Ethernet
		T_SERIAL_INF m_tSerial;
		T_ETHERNET_INF m_tEth;
	};

	struct T_SIMRAD_IMG_CONFIG
	{
		
	};

	struct T_CPATCAP_CONFIG
	{
		double m_dCPA;
		double m_dTCPA;
	};

	// Half Window Length -> Box Window Length
	//#define BOXWINDOWLENGTH(N)			((2*N)+1)			
	//#define CFARMULTIPLIER_CV(N)		(10^(N*(-1)))		

	typedef struct tSPConfig {
		UINT8		Status;

		struct  tBScopeSize {
			UINT16		nBScopeCol;				// No. of RangeBin
			UINT16		nBScopeRow;			// No. of ACP
			UINT16		nLastBScopeCol;			// 마지막 B-Scope column 개수
		} SPM;

		struct tSPparameter {

			// Pulse Integration
			UINT16      PI_Gain;							// 1 ~ 100 Scaled by 0.1, Always Enable
			FLOAT      PI_AzimuthBias;					// 0.0 ~ 359.9 degree

			// Sensitivity Time Control
			UINT16      STC_Gain;							// 0 ~ 100 Scaled by 0.1, 0: Disable, otherwise: Enable 
			FLOAT      STC_Range;							// meter (to Acquisition Range Maximally)

			// Median Filter
			UINT16      MF_HalfWindowLength;			// (2*N+1) Box Window, N is 1 to 3, 0: Disable
			UINT16      MF_SelectedIndex;				// Selected Index among 1 ~ (2*N+1)^2

			// Gaussian Filter
			UINT16      GF_HalfWindowLength;			// (2*N+1) Box Window, N is 1 to 3, 0: Disable
			UINT16      GF_Sigma;							// Distribution of sigma Scaled by 0.1

			// Scan Integration
			UINT8      SI_Gain;							// Gain of Current Video, Scaled by 0.1, 0: Disable, otherwise: Enable

			// Constant False Alarm 
			UINT16      CFAR_RefWindowLength;		// Reference Window Length, 10 ~ 50, default 30
			UINT16      CFAR_GrdWindowLength;		// Guard Window Length, 1 ~ 10, default : 5

			UINT16      CFAR_1stMultiplier;				// Probability of False Alarm, 0: Disable, Multiplier is calculated automatically
			FLOAT      CFAR_1stRange;
			UINT16      CFAR_2ndMultiplier;				// Probability of False Alarm, 0: Disable, Multiplier is calculated automatically
			FLOAT      CFAR_2ndRange;

			// Area Masking
			UINT16      AM_Status;							// 0: Disable, 1: Enable
			UINT16      AM_Send;							// 0: Disable, 1: Enable

			// Intensity Control
			UINT8      RVG_Gain;							 // Gain for Intensity Control, Scaled by 0.1, 0: Disable, otherwise: Enable

			// Object Extraction
			UINT16      OE_MinCell;						 // No. of Minimum Cell for Object Extraction, Always Enable

		} SPP;

	} _tSPConfig;


	//struct T_SIGNAL_PROC_CONFIG
	//{
	//	// Pulse Integration
	//	USHORT m_usPI_Gain;					// 1 ~ 100 Scaled by 0.1, Always Enable
	//	FLOAT m_fPI_AzimuthBias;			// 0.0 ~ 359.9 degree

	//	// Sensitivity Time Control
	//	USHORT m_usSTC_Gain;				// 0 ~ 100 Scaled by 0.1, 0: Disable, otherwise: Enable 
	//	FLOAT m_fSTC_Range;					// meter (to Acquisition Range Maximally)

	//	// Median Filter
	//	USHORT m_usMF_HalfWinLen;			// (2*N+1) Box Window, N is 1 to 3, 0: Disable
	//	USHORT m_usMF_SelectedIndex;		// Selected Index among 1 ~ (2*N+1)^2

	//	// Gaussian Filter
	//	USHORT m_usGF_HalfWinLen;			// (2*N+1) Box Window, N is 1 to 3, 0: Disable
	//	USHORT m_usGF_Sigma;				// Distribution of sigma Scaled by 0.1

	//	// Scan Integration
	//	UCHAR m_ucSI_Gain;					// Gain of Current Video, Scaled by 0.1, 0: Disable, otherwise: Enable

	//	// Constant False Alarm 
	//	USHORT m_usCFAR_RefWinLen;			// Reference Window Length, 10 ~ 50, default 30
	//	USHORT m_usCFAR_GuardWinLen;		// Guard Window Length, 1 ~ 10, default : 5

	//	USHORT m_usCFAR_Multiplier[2];		// Probability of False Alarm, 0: Disable, Multiplier is calculated automatically
	//	FLOAT m_fCFAR_Range[2];

	//	// Intensity Control
	//	UCHAR m_ucRVG_Gain;					 // Gain for Intensity Control, Scaled by 0.1, 0: Disable, otherwise: Enable

	//	// Object Extraction
	//	USHORT m_usOE_MinCell;				 // No. of Minimum Cell for Object Extraction, Always Enable
	//};

	struct T_SIGNAL_PROC_CONFIG
	{
		// Bias Compensation
		FLOAT m_fAzimuthBias;				// 0 ~ 359.9, degree, default 0.0

		// Sensitivity Time Control
		USHORT m_usSTC_Gain;				// 0 ~ 100 Scaled, default 10, 0: Disable, otherwise: Enable 
		FLOAT m_fSTC_Range;					// meter (to Acquisition Range Maximally)

		// Rain Clutter Control
		USHORT m_usRCC_Gain;				// 0 ~ 100, default 0, Screen Signal Control Param Rain

		// Pulse Integration
		USHORT m_usPI_Gain;					// 0 ~ 100, default 10
		USHORT m_usPI_Index;				// Selected Index, 0 ~ 100, default 65
		FLOAT m_fPI_BeamWidth;				// Processed Beam Width, 0 ~ 1.0 %, default 0.2

		// Median Filter
		USHORT m_usMF_Index;				// Selected Index, 0 ~ 100, default 65

		// Scan Integration
		USHORT m_usSI_Gain;					// Gain of Current Video, 0 ~ 100, default 65

		// Constant False Alarm 
		USHORT m_usCFAR_RefWinLen;			// Reference Window Length, 10 ~ 50, default 30
		USHORT m_usCFAR_GuardWinLen;		// Guard Window Length, 10 ~ 50, default : 30
		USHORT m_usCFAR_Multiplier[2];		// Probability of False Alarm, 0 ~ 100, default 20
		FLOAT m_fCFAR_Range[2];				// Adapted Range, 00 ~ Racq, meter, default 0, 

		// Video Intensity
		USHORT m_usVI_Gain;					 // Gain for Intensity Control, 0 ~ 100, default 10

		// Object Extraction
		USHORT m_usOE_MinCell;				 // Size of Minimum Cell for Object Extraction, 0 ~ 100, default 5
	};

	struct T_TRACKING_CONFIG
	{
		UINT m_unMaxTargetSpeed;			// Maximum Speed of Track(135KTS)
		UINT m_unMinNoTrackConfirm;		// Minimum No of Hit for Track Confirmation(0~255)
		UINT m_unMaxNoTrackLoss;			// Maximum No of Missing for Track Lost(0~255)
		DOUBLE m_dLikelihoodRatio;
		UINT m_unPixelPointingError;		// Pixel Pointing Error at Track Command Generation(0 ~ 200)
		UINT m_unGatingThreshold;			// Chi-Square Distribution Selection(1:90%, 2:95%, 3:97.5, 4:99%, 5:99.9%)
		FLOAT m_dStdProcessNoise1;			// Process Noise of First Dynamic Model(0.05 ~ 10.0, Increment: 0.05 )
		FLOAT m_dStdProcessNoise2;			// Process Noise of Second Dynamic Model (0.05~10.0, Increment: 0.05 )
		FLOAT m_dStdRangeError;			// Range Error of Radar Measurement
		FLOAT m_dStdAzimuthError;			// Azimuth Error of Radar Measurement 
		FLOAT m_dStdAISPosError;			// Position Error of AIS Object Information
		DOUBLE m_dStdAISVelError;			// Velocity Error of AIS Object Information
		DOUBLE m_dStdHOPosError;			// Position Error of Handover Track Information
		DOUBLE m_dStdHOVelError;			// Velocity Error of Handover Track Information
	};

	struct T_NET_SERIAL_CONFIG
	{
		INT m_nPortNo;
		INT m_nBaudrate;
	};

	struct T_NET_ETHERNT_CONFIG
	{
		TCHAR m_szIpAddr[g_nMAX_ETH_IPADDR_SIZE];
		INT m_nPortNo;
	};

	struct T_NET_AVIDEO_CONFIG		// Analog Video 설정 정보
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
	struct T_NET_RADAR_INF_CONFIG
	{
		TCHAR m_szSiteName[g_nMAX_SITE_NAME_SIZE];

		DOUBLE m_dSiteLat;
		INT Lat_Dir;  //0;N 1;S
		DOUBLE m_dSiteLon; 
		INT Lon_Dir;  //0:E 1:W

		INT m_nCtrlMethod;	// 제어 방법, 0 = Serial, 1 = Ethernet
		T_NET_SERIAL_CONFIG m_tCtrlSerial;
		T_NET_ETHERNT_CONFIG m_tCtrlEth;
		INT m_nVideoKind;		// 비디오 데이터 연결 상태, 0 = Analog, 1 = Ethernet
		T_NET_AVIDEO_CONFIG m_tAVideo;
		T_NET_ETHERNT_CONFIG m_tDVideo;
	};

	struct T_TPG_CONFIG
	{
		INT m_nPattern;
		FLOAT m_fPeriod;
		INT m_nPRF;
		INT m_nRange;
	};

	struct T_REPLAY_CONFIG
	{
		TCHAR m_szFileName[g_nMAX_FILE_NAME_SIZE];
		INT m_nFileType;				// 0 = SPx Replay File, 1 = Quantum Replay File
		INT m_nRepeat;					// 0 = No Repeat, 1 = Repeat;
	};

	struct T_SIMUL_CONFIG
	{
		INT m_nStart;					// 0 = Stop, 1 = Start
		INT m_nVideoType;				// Video Simulation Type, 0 = Test Pattern, 1 = File Replay
		T_TPG_CONFIG m_tTpg;
		T_REPLAY_CONFIG m_tReplay;
		BOOL m_bAisFileReplay;			// AIS File Replay, TRUE = File Repaly
		TCHAR m_szAisFileName[g_nMAX_FILE_NAME_SIZE];
		BOOL m_bGpsFileReplay;			// GPS File Replay, TRUE = File Replay
		TCHAR m_szGpsFileName[g_nMAX_FILE_NAME_SIZE];
		BOOL m_bEhsFileReplay;			// EHS File Replay, TRUE = File Replay
		TCHAR m_szEhsFileName[g_nMAX_FILE_NAME_SIZE];
	};

	enum class E_TIME_FORMAT
	{
		eTIME_UTC = 0,
		eTIME_LOCAL = 1
	};

	struct T_SYSTEM_TIME
	{
		USHORT m_usYear;			// 년도
		UCHAR m_ucMonth;			// 월, 1 ~ 12
		UCHAR m_ucDay;				// 일, 1 ~ 31
		UCHAR m_ucDayOfWeek;		// 주, 0 ~ 6, 일요일 ~ 토요일
		UCHAR m_ucHour;				// 시, 0 ~ 23
		UCHAR m_ucMiniute;			// 분, 0 ~ 59
		UCHAR m_ucSecond;			// 초, 0 ~ 59
		USHORT m_usMiliSecond;		// 밀리초, 0 ~ 999
		E_TIME_FORMAT m_eFormat;	// 시간 형식
	};

	struct T_OWNSHIP_INFO
	{
		T_SYSTEM_TIME m_tSysTime;

		DOUBLE m_dLat;			// 사이트 위도,
		DOUBLE m_dLon;			// 사이트 경도
		DOUBLE m_dCOG;			// Course Of Ground, deg, 0 ~ 359.99999
		DOUBLE m_dSOG;			// Speed Of Ground, m/s
		DOUBLE m_dHDG;			// Heading, deg, 0 ~ 359.99999
		DOUBLE m_dSTW;			// Speed-Through-Water, m/s

		TCHAR m_szSiteID[g_nMAX_SITE_NAME_SIZE + 1];
		TCHAR m_szCallSign[g_nMAX_CALLSIGN_SIZE + 1];
	};

	struct T_NETWORK_INF_PARAM
	{
		TCHAR	m_szIpAddr[20];
		UINT	m_unPortNo;
	};

	struct T_SERIAL_INF_PARAM
	{
		UINT	m_unPortNo;
		UINT	m_unBaudrate;
	};

	struct T_FILE_REPLAY_PARAM
	{
		TCHAR	m_szFileName[g_unREPLAY_FILENAME_SIZE];
	};

	enum class E_OVERLAY_FORMAT : USHORT
	{
		eOVERLAY_CIRCLE = 0,		// Circle(원)
		eOVERLAY_RECT = 1,			// Rectangle(사각형)
		eOVERLAY_ELLIPSE = 2,		// Ellipse(타원)
		eOVERLAY_SECTOR = 3,		// Sector(부채꼴)
		eOVERLAY_WASHER = 4,		// Washer(워셔)
		eOVERLAY_POLYLINE = 5,		// Polyline
		eOVERLAY_POLYGON = 6		// Polygon
	};

	enum class E_OVERLAY_EDIT_TYPE
	{
		eEDIT_GUARD_ZONE = 0,
		eEDIT_USER_MAP = 1
	};

	static const INT g_nMAX_OVERLAY_TAG_SIZE = 8;
	static const INT g_nMAX_OVERLAY_POINT_NUM = 255;

	struct T_OVERLAY_ENTITY
	{
		USHORT m_usIndex;							// 순번
		UCHAR m_ucOperate;							// 운용여부
													//		0x00 : false
													//		0x01 : true
		E_OVERLAY_FORMAT m_eFormat;					// 도형 모형
		TCHAR m_szTagName[g_nMAX_OVERLAY_TAG_SIZE];	// Tag 이름
													// 허용 값 : 최대 영문 8자
		UCHAR m_ucReference;						// Slaved / not slaved 여부
													//		0x00 : Not Slaved, 고정
													//		0x01 : Slaved, 종속
		USHORT m_usPointNum;						// 기준점을 제외한 경계점 리스트 개수
													//		0 ~ g_nMAX_OVERLAY_POINT_NUM
		DOUBLE m_dLat[g_nMAX_OVERLAY_POINT_NUM];	// 위도, 고정일 경우, 선 / 다중선 / 다각형
													// [0] : 기준위치 위도
		DOUBLE m_dLon[g_nMAX_OVERLAY_POINT_NUM];	// 경도, 고정일 경우, 선 / 다중선 / 다각형

		DOUBLE m_fX[g_nMAX_OVERLAY_POINT_NUM];	
												
		DOUBLE m_fY[g_nMAX_OVERLAY_POINT_NUM];

													// [0] : 기준위치 경도
		FLOAT m_fBearing[g_nMAX_OVERLAY_POINT_NUM];	// 방위, deg, 종속일 경우, 선 / 다중선 / 다각형
													// [0] : 기준위치 방위
		FLOAT m_fRange[g_nMAX_OVERLAY_POINT_NUM];	// 거리, m, 종속일 경우, 선 / 다중선 / 다각형
													// [0] : 기준위치 거리
		FLOAT m_fRadius;							// 반경, m, 원 / 부채꼴
		FLOAT m_fWidth;								// 가로 길이, m, 사각형
		FLOAT m_fHeight;							// 세로 길이, m, 사각형
		FLOAT m_fStartAngle;						// 시작 방위, deg, 부채꼴 / 워셔
		FLOAT m_fEndAngle;							// 종료방위, deg, 부채꼴 / 워셔
		FLOAT m_fRotation;							// 회전각, deg, 사각형 / 타원
		FLOAT m_fMajorAxis;							// 가로축, 타원
		FLOAT m_fMinorAxis;							// 세로축, 타원
		FLOAT m_fInnerRadius;						// 반경 최소값, m, 워셔
		FLOAT m_fOuterRadius;						// 반경 최대값, m, 워셔
		FLOAT m_fLimitInnerRadius;						// 반경 최대값, m, 워셔
		UCHAR m_ucInAlert;							// 구역진입경고 여부
													//		0x00 : 안함
													//		0x01 : 수행
		UCHAR m_ucOutAlert;							// 구역이탈경고 여부
													//		0x00 : 안함
													//		0x01 : 수행
		UINT m_clrColor;
		UCHAR m_ucDisplay;							// 전시 설정
													//		0x00 : 미전시
													//		0x01 : 전시
		UCHAR m_ucTagDisplay;						// 태그 전시 여부
													//		0x00 : 미전시
													//		0x01 : 전시
	}; //

	static const UINT g_unMAX_GUARD_ZONE_NAME_SIZE = 16U;
	static const UINT g_unMAX_USER_MAP_NAME_SIZE = 16U;

	enum class E_GUARD_ZONE_TYPE : INT
	{
		eTypeTracking = 0,
		eTypeRestricted = 1,  //Restricted
		eTypeShadow = 2
	};

	struct T_GUARD_ZONE_INFO
	{
		TCHAR m_szName[g_unMAX_GUARD_ZONE_NAME_SIZE + 1];
		E_GUARD_ZONE_TYPE m_eZoneType;
		T_OVERLAY_ENTITY m_tOverlay;

		UINT m_uiIndetiNumber;
		BOOL m_bAdd;
	};

	struct T_USER_MAP_INFO
	{
		TCHAR m_szName[g_unMAX_USER_MAP_NAME_SIZE + 1];
		UCHAR m_ucShow;			// 0 = Hide, 1 = Show
		T_OVERLAY_ENTITY m_tOverlay;
	};

	struct T_BLANK_SECTOR                       ///  Structure for conveying StopTx sector information
	{                                           ///
		UINT8 ucState;                          ///< Non-zero if this stop-tx sector is active/enabled
		UINT16 usSectorStart_ddeg;              ///< Sector start (deci-degrees, or 10ths of a degree)
		UINT16 usSectorEnd_ddeg;                ///< Sector end (deci-degrees, or 10ths of a degree)
	};

	struct T_SIMRAD_STATE_DATA
	{
		UINT m_uieState;
		UINT m_uiRange;
		UINT m_uiPulseWithType;
		UINT m_uiUseMode;
		UINT m_uiGainType;
		UINT m_uiGainValue;
		UINT m_uiSeaType;
		UINT m_uiSeaLegacyValue;
		UINT m_uiRainType;
		UINT m_uiRainValue;
		UINT m_uiFTCValue;
		UINT m_uiIRLevelValue;
		UINT m_uiTargetStretchLevel;
		UINT m_uiTargetBoostLevel;
		UINT m_uiCurveType;
		UINT m_uiLocalIR;
		UINT m_uiFastScanMode;
		UINT m_uiSideLobeType;
		UINT m_uiSideLobeValue;
		UINT m_uiRPMValue;
		UINT m_uiNoiseRejectValue;
		UINT m_uiBeamSharpValue;
		UINT m_uiSeaGainValue;
		UINT m_uiSeaAutoValue;
		UINT m_uiZeroRangeValue;
		UINT m_uiZeroBearingRangeValue;
		UINT m_uiParkPositionValue;
		UINT m_uiAntHeightValue;
		UINT m_uiAntType;
		int m_iAntXOffsetValue;
		int m_iAntYOffsetValue;
		UINT m_uiTansmitPeriodValue;
		UINT m_uiStandbyPeriodValue;
		UINT m_uiErrorType;
		FLOAT m_flVideoApertureValue;

		T_BLANK_SECTOR tBlankSectors[6];
	};

	struct T_SIMRAD_STATE_SETUPDATA
	{
		UINT m_uiRange;
		UINT m_uiUseMode;
		UINT m_uiGainType;
		UINT m_uiGainValue;
		UINT m_uiSeaType;
		UINT m_uiSeaLegacyValue;
		UINT m_uiRainType;
		UINT m_uiRainValue;
		UINT m_uiFTCValue;
		UINT m_uiIRLevelValue;
		UINT m_uiTargetStretchLevel;
		UINT m_uiTargetBoostLevel;
	};
	
	struct T_SIMRAD_STATE_SETUPEXTENDDATA
	{
		UINT m_uiCurveType;
		UINT m_uiLocalIR;
		UINT m_uiFastScanMode;
		UINT m_uiSideLobeType;
		UINT m_uiSideLobeValue;
		UINT m_uiRPMValue;
		UINT m_uiNoiseRejectValue;
		UINT m_uiBeamSharpValue;
		UINT m_uiSeaGainValue;
		UINT m_uiSeaAutoValue;
	};

	struct T_SIMRAD_STATE_SETUPCONFIGURATION
	{
		UINT m_uiZeroRangeValue;
		UINT m_uiZeroBearingRangeValue;
		UINT m_uiParkPositionValue;
		UINT m_uiAntHeightValue;
		UINT m_uiAntType;
		INT  m_iAntXOffsetValue;
		INT  m_iAntYOffsetValue;
		UINT m_uiTansmitPeriodValue;
		UINT m_uiStandbyPeriodValue;

		T_BLANK_SECTOR tBlankSectors[6];
	};

	struct T_BLANK_SECTOR_SAVE              
	{                                       
		UINT8 ucState;                      
		FLOAT m_flSectorStart_ddeg;          
		FLOAT m_flSectorEnd_ddeg;
	};

	struct T_SIMRAD_STATE_ADVANCED
	{
		FLOAT m_flVideoAperture;
	};


	struct T_SIMRAD_SAVESETUPCONFIGURATION
	{
		UINT m_uiZeroRangeValue;
		UINT m_uiZeroBearingRangeValue;
		UINT m_uiParkPositionValue;
		UINT m_uiAntHeightValue;
		UINT m_uiAntType;
		INT  m_iAntXOffsetValue;
		INT  m_iAntYOffsetValue;
		UINT m_uiTansmitPeriodValue;
		UINT m_uiStandbyPeriodValue;

		T_BLANK_SECTOR_SAVE tBlankSectors[6];
	};

	struct T_SIMRAD_STATE_INSTALLDATA
	{
		UINT m_uiZeroRangeValue;
		UINT m_uiZeroBearingRangeValue;
		UINT m_uiParkPositionValue;
		UINT m_uiAntHeightValue;
		UINT m_uiAntType;
		INT  m_iAntXOffsetValue;
		INT  m_iAntYOffsetValue;
	};

	struct T_SIMRAD_SAVE_DATA
	{
		UINT m_uiUseMode;
		UINT m_uiFastScan;
		UINT m_uiIRLevel;
		UINT m_uiLocalIR;
		UINT m_uiRPM;
		UINT m_uiBeamSharp;
		UINT m_uiTargetBoost;
		UINT m_uiTargetStretch;
		UINT m_uiTartgetStretchLegacy;
		UINT m_uiCurveType;
		UINT m_uiGain;
		UINT m_uiGainType;
		UINT m_uiNoiseReject;
		UINT m_uiSeaLegacy;
		UINT m_uiSeaLegacyType;
		UINT m_uiSea;
		UINT m_uiSeaType;
		int  m_iSeaAutoOffset;
		UINT m_uiSeaCombined;
		UINT m_uiSideLobe;
		UINT m_uiSideLobeType;
		UINT m_uiRain;
		UINT m_uiFTC;
		UINT m_uiTimeModeEnabled;
		UINT m_uiTransmitPeriod;
		UINT m_uiStandbyPeriod;
		UINT m_uiSector0Enabled;
		UINT m_uiSector1Enabled;
		UINT m_uiSector2Enabled;
		UINT m_uiSector3Enabled;
		UINT m_uiSector4Enabled;
		UINT m_uiSector5Enabled;
		FLOAT m_flSector0Start;
		FLOAT m_flSector0End;
		FLOAT m_flSector1Start;
		FLOAT m_flSector1End;
		FLOAT m_flSector2Start;
		FLOAT m_flSector2End;
		FLOAT m_flSector3Start;
		FLOAT m_flSector3End;
		FLOAT m_flSector4Start;
		FLOAT m_flSector4End;
		FLOAT m_flSector5Start;
		FLOAT m_flSector5End;
		UINT m_uiParkPos;
		UINT m_uiZeroRangeOffset;
		FLOAT m_flAntHeight;
		INT m_iAntXOffset;
		INT m_iAntYOffset;
		FLOAT m_flZeroBearingOffset;
		UINT m_uiAntType;
		DOUBLE m_dblVideoAperture;
		DOUBLE m_dblSTCRangeTrim;
		UINT m_uiSTCRangeRate;
		DOUBLE m_dblSTRSeaTrim;
		UINT m_uiSTCSeaRate1;
		UINT m_uiSTCSeaRate2;
		DOUBLE m_dblSTCRainTrim;
		UINT m_uiSTCRainRate;
		DOUBLE m_dblUserMinSNR;
		UINT m_uiBangSuppression;

		CString m_szSerialNum;
		CString m_szLockID;
		CString m_szUnLockID;
	};

	struct T_DYNAMIC_AIS {
		UINT32 MMSI;					// MMSI of Ship
		UCHAR Class;					// AIS Class(1: A, 2: B, 3: SAR Aircraft, 4: AtoN, 5: Base 6: Virtual)
		bool bPosAvail;				// Availability of Position Data
		DOUBLE Lat;					// Latitude
		DOUBLE Long;					// Longitude
		bool bSogAvail;				// Availability of SOG Data
		FLOAT SOG;					// Speed over Ground (m/s)
		bool bCogAvail;				// Availability of COG Data
		FLOAT COG;					// Course over Ground (degree)
		bool bRotAvail;				// Availability of ROT
		FLOAT ROT;					// Rotation Rate(deg/min)
		bool bHeadingAvail;			// Availability of True Heading
		FLOAT HDT;					// True Heading
		UCHAR NavStatus;				// Navigation Status 0 ~ 15
		UCHAR PosAccuracy;			// 0: > 10m, 1 : < 10 m
		UCHAR Device;					// 0: Undefined, 1~8 : Normal, 9 ~ 15: Not Used
		time_t CmdEpoch;			// 
	};

	struct T_STATIC_AIS {
		UINT32	MMSI;					// MMSI of Ship
		UINT32	IMONO;					// IMO Number
		UCHAR	ShipType;				// Ship Type (0 ~ 99)
		UCHAR	CallSign[LEN_CALLSIGN];	// Callsign : 7 Characters
		UCHAR	ShipName[LEN_SHIPNAME];	// Shipname : 20 Characters
		USHORT	Bow;					// Length Toward Ship's Bow from CCRP in meters
		USHORT	Stern;					// Length Toward Ship's Stern from CCRP in meters
		USHORT	Port;					// Length Toward Ship's Left Direction from CCRP in meters
		USHORT	StarBoard;				// Length Toward Ship's Right Direction from CCRP in meters
		UCHAR	ETA[4];					// ETA : Month, Day, Hour, Minute by 1 Byte
		UCHAR	Dst[LEN_DESTINATION];	// Destination : 20 Characters
		FLOAT Draught;				// Ship's Draught
		time_t RcvdTime;
	};

	struct T_AIS_TYPEAIVDOINFO {
		bool bPosAvail;			// Availability of Position Data
		DOUBLE Lat;				// Latitude
		DOUBLE Long;			// Longitude
		bool bSogAvail;			// Availability of SOG Data
		FLOAT SOG;			// Speed over Ground (m/s)
		bool bCogAvail;			// Availability of COG Data
		FLOAT COG;			// Course over Ground (degree)
		bool bRotAvail;			// Availability of ROT
		FLOAT ROT;			// Rotation Rate(deg/min)
		bool bHeadingAvail;		// Availability of True Heading
		FLOAT HDT;			// True Heading
	};
#pragma pack(pop)

} // namespace NS_SALUS_MS_APP
