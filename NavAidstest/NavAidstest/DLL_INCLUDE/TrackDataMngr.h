#pragma once

#include <afxmt.h>
#include <map>
#include <vector>

#include "TrackDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CTrackDataMngr
	{
	public:
		CTrackDataMngr();
		~CTrackDataMngr();

	public:
		static CTrackDataMngr* GetInstance();
		static void DeleteInstance();

		void Initialize();
		void Finalize();

		// Set
		void UpdateTrack(const T_CONFIRMED_TRACK* const pTrack);
		void UpdateEnd();
		// Get
		UINT GetTrackCount();
		T_CONFIRMED_TRACK* GetTrackWithKeyValue(UINT unID);
		T_CONFIRMED_TRACK* GetTrackWithIndex(UINT unIndex);

		void DeleteTrack(UINT unID);
		void RemoveAllTrack();

		HANDLE GetUpdateEndEvent();

		// CPA
		void AddCpa(const UINT unTrackID1, const UINT unTrackID2);
		T_CPA_TRACK* GetCpaWithIndex(const UINT unIndex);
		T_CPA_TRACK* GetCpaWithTrackID(const UINT unSearchTrackID);
		UINT GetCpaCount();
		void DeleteCpaWithIndex(const UINT unIndex);
		void DeleteCpaWithID(const UINT unID);
		void RemoveAllCpa();

	protected:
		void AllocMemory();
		void FreeMemory();

		BOOL IsExistTrack(const UINT unID, UINT& unBuffIndex);
		void RemoveMapData();
		UINT GetEmptyBuffIndex(const UINT nStartIndex);

	private:
		void LockTrack();
		void UnlockTrack();

		void LockCpa();
		void UnlockCpa();

	private:
		static CTrackDataMngr* m_pInstance;
		static const UINT m_unMAX_TRACK_BUFF = g_unMAX_ALLOW_TRACK_NUM;

		T_CONFIRMED_TRACK* m_pTrackDataBuffer;
		UINT m_unWriteBuffIndex;
		UINT m_unTrackCount;

		HANDLE m_hUpdateEndEvent;

		std::map<UINT, UINT> m_mapTrack;		// ID를 키값으로 버퍼 인덱스를 포함한다.
		std::map<UINT, UINT> m_mapTrackStat;	// TRACK STATUS, 0 = Normal, > 0 = Delete
		std::map<UINT, UINT> m_mapBuffStat;		// Buffer USE STATUS, 0 = Empty, 1 = USE
		CCriticalSection* m_pTrackCS;

		std::vector<T_CPA_TRACK*> m_vtCpaTrack;
		CCriticalSection* m_pCpaCS;
	};
} // NS_SALUS_MS_APP

