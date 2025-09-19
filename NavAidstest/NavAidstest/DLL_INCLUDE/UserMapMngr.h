#pragma once

#include <vector>
#include <afxmt.h>

#include "SystemTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CUserMapMngr
	{
	public:
		CUserMapMngr();
		~CUserMapMngr();

	public:
		static CUserMapMngr* GetInstance();
		static void DeleteInstace();

		UINT GetUserMapCount();
		UINT GetTempCount();

		void AddUserMap(const T_USER_MAP_INFO* const pUserMapInfo);
		void AddTemp(const T_USER_MAP_INFO* const pUserMapInfo);
		void ModifyTemp(const UINT unIndex, const T_USER_MAP_INFO* const pUserMapInfo);
		void DeleteTemp(const UINT unIndex);

		T_USER_MAP_INFO* GetUserMap(const UINT unIndex);
		T_USER_MAP_INFO* GetTemp(const UINT unIndex);

		T_OVERLAY_ENTITY* GetEditingOverlay();
		void ClearEditingOverlay();

		void SaveUserMap();			// UserMap -> Temp
		void RestoreUserMap();		// Temp -> UserMap

		void RemoveAll();

	private:
		void RemoveAllUserMap();
		void RemoveAllTemp();

		void LockData();
		void UnlockData();

	protected:
		static CUserMapMngr* m_pInstance;

		T_OVERLAY_ENTITY* m_pEditingOverlay;

		std::vector<T_USER_MAP_INFO*> m_vtUserMap;	// T_USER_MAP_INFO* 로 구성
		std::vector<T_USER_MAP_INFO*> m_vtTemp;		// 임시 설정용

		CCriticalSection* m_pDataCS;
	};
} // NS_SALUS_MS_APP

