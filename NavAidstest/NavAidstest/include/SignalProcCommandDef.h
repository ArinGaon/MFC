
#pragma once

#include "CoordBaseDef.h"

namespace NS_SALUS_MS_APP
{
	enum class E_SIGNAL_PROC_COMMAND : INT
	{
		eSP_CMD_NONE = 0,
		eSP_CMD_RESET = 1,				// Signal Processing Reset
		eSP_CMD_GROUP_TRACK = 10,
		eSP_CMD_ADD_TRACK = 11,
		eSP_CMD_DEL_TRACK = 12,
		eSP_CMD_SWAP_TRACK = 13,
		eSP_CMD_FAST_TRACK = 14,
		eSP_CMD_RESET_TRACK = 15,		// Track Reet
		eSP_CMD_CHANGE_AREA_MASK = 16,
		eSP_CMD_CHANGE_GUARD_ZONE = 17,
	};

	struct T_TRACK_GROUP_RECT
	{
		T_CART_RECT4P m_tRect;		// 회전이 반영된 네개의 위치 점
	};

	/******************************************************************************
	* Manual Tracking Command
	*****************************************************************************/
	struct T_TRACK_POS_INFO
	{
		T_CART_POS2D m_tPos;
		DOUBLE m_dMeterPerPixel;	// Pixel Resolution, Pixel 당 거리
	};

	struct T_TRACK_SEL_INFO
	{
		UINT m_unFirstID;
		UINT m_unSecondID;
		T_CART_POS2D m_tFirstPos;
		T_CART_POS2D m_tSecondPos;
		DOUBLE m_dMeterPerPixel;	// Pixel Resolution, Pixel 당 거리
	};

	struct T_SIGNAL_PROC_COMMAND
	{
		E_SIGNAL_PROC_COMMAND eCommand;
		union
		{
			T_TRACK_GROUP_RECT m_tTrackGroup;		// 추적을 생성할 그룹 사각형 정보
			T_TRACK_POS_INFO m_tTrackPos;
			T_TRACK_SEL_INFO m_tTrackSel;
		};
	};

} // NS_SALUS_MS_APP
