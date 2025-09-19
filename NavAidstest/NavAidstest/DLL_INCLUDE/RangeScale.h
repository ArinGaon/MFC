#pragma once

#include "SystemTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CRangeScale
	{
	public:
		CRangeScale();
		~CRangeScale();

	public:
		// Set
		static void SetRangeIndex(const E_VIEW_SCOPE eViewScope, const INT nIndex);
		// Get
		static INT GetRangeIndex(const E_VIEW_SCOPE eViewScope);

		static DOUBLE CurRange_NM(const E_VIEW_SCOPE eViewScope);
		static DOUBLE CurSampleRange_NM(const E_VIEW_SCOPE eViewScope);
		static DOUBLE CurRingRange_NM(const E_VIEW_SCOPE eViewScope);
		static INT CurRingNum(const E_VIEW_SCOPE eViewScope);
		static E_RADAR_PULSE_MODE GetPulseMode(const E_VIEW_SCOPE eViewScope);
		static INT GetPulseModeIndex(const E_VIEW_SCOPE eViewScope);
		static INT GetPRF();
		static DOUBLE GetAcqRange();

		static CString GetRangeString(const E_VIEW_SCOPE eViewScope);
		static CString GetRingRangeString(const E_VIEW_SCOPE eViewScope);
		static CString GetPulseModeString();
		static CString GetPulseModeString(E_RADAR_PULSE_MODE ePulseMode);

		static void GetRangeString(CStringArray& saRange);
		static void GetPulseMode(CStringArray& saPulse);

		static BOOL Up(const E_VIEW_SCOPE eViewScope, BOOL SubMode);		// Up
		static BOOL Down(const E_VIEW_SCOPE eViewScope, BOOL SubMode);	// Down

	private:
		static INT m_nCurRangeIndex[g_nMAX_VIEW_SCOPE];
	};

} // namespace NS_SALUS_MS_APP