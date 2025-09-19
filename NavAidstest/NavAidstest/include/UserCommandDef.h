
#pragma once

#include "SystemTypeDef.h"
#include "AlarmTypeDef.h"

#include "GraphicsDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_USER_COMMAND : INT
	{
		eUSER_CMD_NONE = 0,
		eUSER_CMD_RENDER_PRIMARY = 1,			// Primary Scope Render
		eUSER_CMD_RENDER_SECONDARY = 2,			// Secondary Scope Render
		eUSER_CMD_CHANGE_SECONDARY_CENTER = 3,	// Secondary Scope Ceneter Designation
		eUSER_CMD_UPDATE_CURSOR_INFO = 4,		// Update Cursor Information
		eUSER_CMD_MOUSE_INFO = 5,
		// VRM/EBL
		eUSER_CMD_CHANGE_VRMEBL_STAT = 8,
		eUSER_CMD_UPDATE_VRMEBL_INFO = 9,
		// QUICK MENU
		eUSER_CMD_SELECTED_QUICK_MENU = 10,
		eUSER_CMD_UNSELECED_QUICK_MENU = 11,
		// Range/Ring
		eUSER_CMD_CHANGE_PRIMARY_SCOPE_SETTING = 20,
		eUSER_CMD_CHANGE_PRIMARY_RING_VIEW = 21,
		eUSER_CMD_CHANGE_SECONDARY_SCOPE_SETTING = 22,
		eUSER_CMD_CHANGE_SECONDARY_RING_VIEW = 23,
		// Area Masking
		eUSER_CMD_CONTROL_EDIT_MASK = 30,
		eUSER_CMD_SELECTED_SCOPE_POS = 31,
		// Guard Zone and User Map Position
		eUSER_CMD_CONTROL_EDIT_OVERLAY = 40,
		// Track Selection
		eUSER_CMD_START_TRACK_SELECT = 45,
		eUSER_CMD_END_TRACK_SELECT = 46,
		// ALARM
		eUSER_CMD_CPA_ALARM_PARAM = 50,
		eUSER_CMD_VIEW_ALARM_LIST = 51,
		eUSER_CMD_ALARM_NOTIFY = 52,
		// Scope View Param
		eUSER_CMD_SCOPE_VIEW_PARAM = 60,
		eUSER_CMD_SCOPE_CONTROL_PARAM = 61,
		// SIMULATED GPS DATA
		eUSER_CMD_RECIEVED_SIMUL_GPS_DATA = 70,
		// Change Signal Processing Paramter
		eUSER_CMD_SIGNAL_PARAM = 90,
		// Virtual Track Control
		eUSER_CMD_CONTROL_VIRTUAL_TRACK = 95,
		// Network Message Info
		eUSER_CMD_RECEIVED_NET_MSG = 100,
		// Radar Interface 시작/정지
		eUSER_CMD_CONTROL_RADAR_INF = 101,
		eUSER_CMD_VIRTUAL_TRACK_POS = 102,
		eUSER_CMD_UPDATE_VTPOS_INFO = 103,
		eUSER_CMD_VIRTUAL_TRACK_CANCEL = 104,
		eUSER_CMD_ADD_GUARDZONE = 105,
		eUSER_CMD_ADD_GUARDZONE_LOAD = 106,
		eUSER_CMD_VIRTUAL_TRACK_SAVE = 107,
		eUSER_CMD_DELETE_GUARDZONE = 108,
		eUSER_CMD_CPA_TARGET1 = 109,
		eUSER_CMD_CPA_TARGET2 = 110,
		eUSER_CMD_CPA_TARGETADD = 111,
		eUSER_CMD_HALO_UPDATESETUP = 112,
		eUSER_CMD_HALO_UPDATESETUPEXTEND = 113,
		eUSER_CMD_HALO_UPDATECONFIGURATION = 114,
		eUSER_CMD_HALO_UPDATEMODE = 115,
		eUSER_CMD_HALO_UPDATESECTOR0 = 116,
		eUSER_CMD_HALO_UPDATESECTOR1 = 117,
		eUSER_CMD_HALO_UPDATESECTOR2 = 118,
		eUSER_CMD_HALO_UPDATESECTOR3 = 119,
		eUSER_CMD_HALO_UPDATESECTOR4 = 120,
		eUSER_CMD_HALO_UPDATESECTOR5 = 121,
		eUSER_CMD_HALO_UPDATEPARKPOS = 122,
		eUSER_CMD_HALO_UPDATEANTHEIGHT = 123,
		eUSER_CMD_HALO_UPDATEANTOFFSET = 124,
		eUSER_CMD_HALO_UPDATEZERORANGEOFFSET = 126,
		eUSER_CMD_HALO_UPDATEZEROBEARINGOFFSET = 127,
		eUSER_CMD_HALO_UPDATEINSTALLRESETRTOFACTORY = 128,
		eUSER_CMD_HALO_UPDATEANTTYPE = 129,
		eUSER_CMD_HALO_UPDATEERROR = 130,
		eUSER_CMD_HALO_ERRORMSG = 131,
		eUSER_CMD_HALO_FTCUPDATE = 132,
		eUSER_CMD_HALO_RADARSTANDBY = 133,
		eUSER_CMD_HALO_RADARTRANSMIT = 134,
		eUSER_CMD_HALO_RADARPOWEROFF = 135,
		eUSER_CMD_HALO_RADARPOWERON = 136,
		eUSER_CMD_HALO_RADARANGECHANGED = 137,
		eUSER_CMD_HALO_UPDATEADVANCED = 138,
		eUSER_CMD_HALO_UPDATEAHALONETWORK = 139,
		eUSER_CMD_VIEW_AIS_SART = 140,
		eUSER_CMD_RESET_ECHOTRAILS = 141,
		eUSER_CMD_RESET_TARGETTRAILS = 142,
		eUSER_CMD_CPA_SET = 143,
		eUSER_CMD_VRMEBL1RESET = 144,
		eUSER_CMD_VRMEBL2RESET = 145,
		eUSER_CMD_UPDATE_RADARLOCATION = 146,
		eUSER_CMD_GUARDZONE_SET_EXIT = 147,
		eUSER_CMD_CHANGE_VRMEBL_RESET = 148
	};

	struct T_MOUSE_INFO
	{
		E_MOUSE_ACT_TYPE m_eMouseType;
		LONG m_lMouseX;
		LONG m_lMouseY;

		BOOL m_bMouseInScope;	// mouse가 scope 안에 들어오면 TRUE
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		DOUBLE m_dRange;
		DOUBLE m_dBearing;
	};

	struct T_GEO_POS_INFO
	{
		CWnd* m_pEventWnd;
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		DOUBLE m_dRange;
		DOUBLE m_dBearing;
	};

	struct T_VRMEBL_STATUS
	{
		INT m_nIndex;			// 0 = VRM/EBL1, 1 = VRM/EBL2
		BOOL m_bShow;			// 0 = no show, 1 = show
	};

	struct T_VRMEBL_INFO
	{
		INT m_nIndex;			// 0 = VRM/EBL1, 1 = VRM/EBL2
		DOUBLE m_dRange;
		DOUBLE m_dBearing;
	};

	struct T_QUICK_MENU_STATUS
	{
		INT m_nCurSelectedMenu;
		INT m_nPrevSelectedMenu;
		INT m_nCheckStatus;		// 0 = no check, 1 = check
		INT m_nParam;			// VRM/EBL시 SHOW 상태 정보로 사용
	};

	struct T_SCOPE_SETTING
	{
		DOUBLE m_dRangeNM;		// 반경, NM
		DOUBLE m_dRangeMPS;		// 반경, m/s
		BOOL m_bViewRing;
		DOUBLE m_dRingRangeNM;	// 링 반경, NM
		INT m_nRingNum;			// Ring 개수
		INT m_nIndex;
		BOOL m_bRangeChange;
	};

	enum class E_MASK_CONTROL_KIND
	{
		eMASK_ALL_PARTS_SHOW = 0,
		eMASK_ALL_PARTS_HIDE = 1,
		eMASK_EDIT_PARTS_ADD = 2,
		eMASK_EDIT_PARTS_DEL = 3,
		eMASK_EDIT_PARTS_MOD = 4,
		eMASK_EDIT_PARTS_SEL = 5,
		eMASK_EDIT_SEL_POS = 7,
	};

	struct T_MASK_CONTROL_INFO
	{
		E_MASK_CONTROL_KIND m_eControlKind;
		CWnd* m_pEventWnd;			// 포인트 지정 시 시용
		INT m_nIndex;				// Add, Delete, Modify 시 사용
		CPtrArray* m_pEditPos;		// 편집 중 Mask 위치 정보
	};

	enum class E_OVERLAY_CONTROL_KIND
	{
		eOVERLAY_SHOW = 0,
		eOVERLAY_HIDE = 1,
		eOVERLAY_CHANGING = 2,
		eOVERLAY_CHANGED = 3,
	};

	struct T_OVERLAY_CONTROL_INFO
	{
		E_OVERLAY_CONTROL_KIND m_eControlKind;
		CWnd* m_pEventWnd;
		E_OVERLAY_EDIT_TYPE m_eEditType;
		T_OVERLAY_ENTITY* m_pOverlayEntity;
	};

	struct T_TRACK_SELECT_INFO
	{
		CWnd* m_pEventWnd;
		UINT m_unTrackID;
		UINT m_unTrackID2;
	};

	struct T_RADAR_TRX_INFO
	{
		INT m_nStart;						// 0 = Stop, 1 = Start
		E_RADAR_PULSE_MODE m_ePulseMode;	// Tx Pulse Mode
	};

	struct T_VIRTUAL_CONTROL_STAT
	{
		INT m_nStart;					// 0 = Stop, 1 = Start
	};

	struct T_SIGNAL_PARAM
	{
		INT m_nSea;
		BOOL m_bSeaAuto;		// FALSE = Manual, TRUE = AUTO
		INT m_nGain;
		BOOL m_bGainAuto;		// FALSE = Manual, TRUE = AUTO
		INT m_nRain;
		BOOL m_bRainAuto;		// FALSE = Manual, TRUE = AUTO
		INT m_nIntensity;
		BOOL m_bIntensityAuto;	// FALSE = Manual, TRUE = AUTO
	};

	struct T_SCOPE_VIEW_PARAM
	{
		FLOAT m_fVector;		// vector size, minute
		FLOAT m_fTrackTrail;	// track trail, minute
		FLOAT m_fEchoTrail;		// echo trail, minute
	};

	struct T_SCOPE_CONTROL_PARAM
	{
		E_TRACK_VIEW_MODE m_eTrackView;
		E_RADAR_DUAL_STATUS m_eDualStat;
		E_SCOPE_MOTION m_eMotionMode;
		E_SCOPE_ORIENTATION m_eOrientationMode;
		E_CLUTTER_MODE m_eClutterMode;
	};

	struct T_CPA_ALARM_PARAM
	{
		FLOAT m_fCpaThresholdNM;	// CPA Threshold, range, NM
		FLOAT m_fTcpaThresholdMIN;	// TCPA Threshold, time, minute
	};

	struct T_NET_MSG_INFO
	{
		USHORT m_usInfoCode;
		void* m_pDataBuff;
	};

	struct T_SIMUL_GPS_DATA
	{
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		DOUBLE m_dSOG;
		DOUBLE m_dCOG;
		DOUBLE m_dHDG;
	};

	struct T_AIS_MSG_TYPESART_COMMAND
	{
		UINT32 m_unMMSI;
	
		DOUBLE m_dLon;
		DOUBLE m_dLat;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		CHAR m_cCallSign[8];

		BOOL m_blPositionNA;
	};

	struct T_USER_COMMAND
	{
		E_USER_COMMAND eCommand;
		USHORT m_usIndex;
		USHORT m_usType;
		UINT m_uiHaloFtc;

		USHORT m_usGZType[255];
		USHORT m_usDelCount;
		USHORT m_usDelID[255];

		USHORT m_usAddCount;
		USHORT m_usAddID[255];

		union
		{
			T_MOUSE_INFO m_tMouseInfo;
			T_GEO_POS_INFO m_tGeoPosInfo;
			T_VRMEBL_STATUS m_tVrmEblStat;
			T_VRMEBL_INFO m_tVrmEblInfo;
			T_QUICK_MENU_STATUS m_tMenuStat;
			T_SCOPE_SETTING m_tScopeSetting;
			T_MASK_CONTROL_INFO m_tMaskCtrlInfo;
			T_OVERLAY_CONTROL_INFO m_tOverlayCtrlInfo;
			T_NET_MSG_INFO m_tNetMsgInfo;
			T_RADAR_TRX_INFO m_tRadarTrxInfo;
			T_ALARM_INFO m_tAlarmInfo;
			T_TRACK_SELECT_INFO m_tTrackSelInfo;
			T_SIGNAL_PARAM m_tSignalParam;
			T_SCOPE_VIEW_PARAM m_tScopeViewParam;
			T_SCOPE_CONTROL_PARAM m_tScopeControlParam;
			T_CPA_ALARM_PARAM m_tCpaAlarmParam;
			T_VIRTUAL_CONTROL_STAT m_tVirtualCtrlStat;
			T_SIMUL_GPS_DATA m_tSimulGpsData;
			T_SIMRAD_STATE_DATA m_tSimradStateData;
			T_AIS_MSG_TYPESART_COMMAND m_tAISMessageTypeSart;
		};
	};
}	// NS_SALUS_MS_APP