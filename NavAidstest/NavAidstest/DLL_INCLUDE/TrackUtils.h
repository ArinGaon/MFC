#pragma once

#include "TrackDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CTrackUtils
	{
	public:
		CTrackUtils();
		~CTrackUtils();

	public:
		static CTrackUtils* GetInstance();
		static void DeleteInstance();

		E_TRACK_TYPE GetShowTrackType(const E_TRACK_TYPE eSelectedType, const E_TRACK_TYPE eTrackType);
		T_TRACK_INFO* GetTrackInfo(const E_TRACK_TYPE eTrackType, T_CONFIRMED_TRACK* const pConfirmTrack);

		// TRACK TYPE
		CString GetStrTrackType(const E_TRACK_TYPE eTrackType);
		// Ship Type
		CString GetStrShipType(const UCHAR ucShipType);
		// Navigation Status
		CString GetStrNavStatus(const UCHAR ucNavStat);

	private:
		static CTrackUtils* m_pInstance;
	};
}	// NS_SALUS_MS_APP

