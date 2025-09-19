#pragma once

#include <tchar.h>

namespace NS_SALUS_MS_APP
{
	enum class E_COLOR_SET : INT
	{
		eColorSetNight = 0,
		eColorSetDay = 1
	};

	enum class E_DIALOG_COLOR_TYPE : INT
	{
		eColorTypeLight = 0,		// �⺻ ���̾�α�
		eColorTypeDark = 1			// ���̾�α�â�� ���� ���̾�α�
	};

	static const INT g_nMAX_COLOR_GROUP_NUM = 4;

	enum class E_COLOR_GROUP_KIND : INT
	{
		eColorDefault = 0,
		eColorUser1 = 1,
		eColorUser2 = 2,
		eColorUser3 = 3
	};

	static const TCHAR* g_szColorGroupName[g_nMAX_COLOR_GROUP_NUM] =
	{
		_T("Default"),
		_T("User1"),
		_T("User2"),
		_T("User3")
	};

	static const INT g_nMAX_USER_DEFINE_COLOR_NUM = 17;

	enum class E_USER_COLOR_IDX : INT
	{
		eNONE = -1,
		eBACKGROUND = 0,		// PPI Background Color
		eLAND = 1,              // Map
		eRADAR_VIDEO = 2,
		eRANGE_RING = 3,

		eVRMEBL1 = 4,
		eVRMEBL2 = 5,

		eTRACK_TRAIL = 6,
		eECHO_TRAIL = 7,

		eSYMB_RADAR = 8,
		eSYMB_AIS = 9,
		eSYMB_MIX = 10,			// Mixed Target
		eSYMB_VT = 11,			// Virtual Target

		eZONE_TRK = 12,			// Tracking
		eZONE_NONTRK = 13,		// Restricted
		eZONE_ANCH = 14,		// User map
		eZONE_SHADOW = 15,      // Shadow
		eZONE_TARGETINFO =16,
	};

#pragma pack(push, 1)

	struct T_TRACKINFO_VIEW
	{
		INT m_nCoord;			// Lat/Lon ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nRngBrg;			// Range/Bearing ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nCOGSOG;			// Course/Speed ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nAisType;			// AIS TYPE ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nAisMMSI;			// AIS MMSI ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nAisCall;			// AIS CALL ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nTCPA;            // TARGET CPA/TCPA ǥ�� ����, 0 = No View, 1 = View
	};

	struct T_AISINFO_VIEW
	{
		INT m_nHeadingLine;		// Heading Line ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nRot;		        // Rot         ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nClassA;			// AIS Class A ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nClassB;			// AIS Class B ���� ǥ�� ����, 0 = No View, 1 = View
		INT m_nMinRot;			// Min. Rotation ����
	};

	struct T_DISPLAY_UNIT
	{
		INT m_nTime;			// Time ���� ǥ�� ���, 0 = UTC, 1 = Local Time
		INT m_nRange;			// �Ÿ� ���� ǥ�� ���, 0 = NM, 1 = Meter
		INT m_nSpeed;			// �ӷ� ���� ǥ�� ���, 0 = kn, 1 = m/s
		INT m_nCoord;			// ��/�浵 ���� ǥ�� ���, 0 = Degree ǥ��, 1 = Degree, Min ǥ��
		INT m_nVrmLine;         // VRM / EBL Line Type 0 = Dash, 1 = Line
	};

	struct T_TRACKVIEW_CONTROL
	{
		FLOAT m_fVector;			// Track Vector ���� ���
		FLOAT m_fTrackTrail;		// Track Trail ���� ���
		FLOAT m_fEchoTrail;			// Ehco Trail ���� ���
	};

	struct T_CPA_THRESHOLD
	{
		FLOAT m_fCPA;
		FLOAT m_fTCPA;
	};

#pragma pack(pop)
}