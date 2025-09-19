#pragma once

#include <vector>
#include <afxmt.h>

#include "SystemTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CGuardZoneMngr
	{
	public:
		CGuardZoneMngr();
		~CGuardZoneMngr();

	public:
		static CGuardZoneMngr* GetInstance();
		static void DeleteInstance();

		UINT GetGuardZoneCount();
		UINT GetTempCount();

		void AddGuardZone(const T_GUARD_ZONE_INFO* const pGuardZoneInfo);
		T_GUARD_ZONE_INFO* AddGuardZoneSingle(T_GUARD_ZONE_INFO* pGuardZoneInfo);
		void AddTemp(const T_GUARD_ZONE_INFO* const pGuardZoneInfo);
		void ModifyTemp(const UINT unIndex, const T_GUARD_ZONE_INFO* const pGuardZoneInfo);
		void DeleteTemp(const UINT unIndex);

		T_GUARD_ZONE_INFO* GetGuardZone(const UINT unIndex);
		T_GUARD_ZONE_INFO* GetTemp(const UINT unIndex);

		void SaveGuardZone();		// GuardZone -> Temp
		void RestoreGuardZone();	// Temp -> GuardZone
		void SetColorGuardZone();
		void RemoveAll();

	private:
		void RemoveAllGuardZone();
		void RemoveAllTemp();

		void LockData();
		void UnlockData();

	protected:
		static CGuardZoneMngr* m_pInstance;

		std::vector<T_GUARD_ZONE_INFO*> m_vtGuardZone;	// T_GUARD_ZONE_INFO* 로 구성
		std::vector<T_GUARD_ZONE_INFO*> m_vtTemp;		// 임시 설정용

		CCriticalSection* m_pDataCS;
	};
} // NS_SALUS_MS_APP

