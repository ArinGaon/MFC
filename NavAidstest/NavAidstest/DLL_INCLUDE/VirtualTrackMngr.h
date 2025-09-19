#pragma once

#include <vector>
#include <afxmt.h>

#include "TrackDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CVirtualTrackMngr
	{
	public:
		CVirtualTrackMngr();
		virtual ~CVirtualTrackMngr();
		void UpdateEnd();
		HANDLE GetUpdateEndEvent();

	public:
		static CVirtualTrackMngr* GetInstance();
		static void DeleteInstance();

		// VIRTUAL TRACK
		UINT AddVirtual(const FLOAT fRange, const FLOAT fAzimuth, const FLOAT fSOG, const FLOAT fCOG);
		UINT AddVirtualPos(const double dLat,const double dLon,const FLOAT fRange, const FLOAT fAzimuth, const FLOAT fSOG, const FLOAT fCOG);

		UINT AddVirtual(const T_VIRTUAL_TRACK* const pVirtual);
		void DeleteVirtual(const UINT unIndex);
		void DeleteVirtualID(const UINT ID);
		void SetDeleteStatus(const UINT unTrackID);
		BOOL ModifyVirtual(const UINT unIndex, const FLOAT fRange, const FLOAT fAzimuth, const FLOAT fSOG, const FLOAT fCOG);
		BOOL ModifyVirtualWithID(const UINT unTrackID, const FLOAT fRange, const FLOAT fAzimuth, const FLOAT fSOG, const FLOAT fCOG);
		T_VIRTUAL_TRACK* GetVirtualTrack(const UINT unIndex);
		T_VIRTUAL_TRACK* GetVirtualTrackWithID(const UINT unTrackID);
		T_CONFIRMED_TRACK* GetVirtualTrackWithIDRadar(const UINT unTrackID);
		UINT GetVirtualCount();
		void RemoveAllVirtual();

		void SetManeuverStatus(BOOL bStatus);
		BOOL IsManeuverStart();

	private:
		void LockVirtual();
		void UnlockVirtual();

	private:
		static CVirtualTrackMngr* m_pInstance;

		BOOL m_bManeuverStart;	// FALSE = Stop, TRUE = Start

		std::vector< T_VIRTUAL_TRACK*> m_vtVirtualTrack;
		UINT m_unLastVirtualTrackID;
		CCriticalSection* m_pVirtualCS;

		HANDLE m_hUpdateEndEvent;
	};
} // namespace NS_SALUS_MS_APP

