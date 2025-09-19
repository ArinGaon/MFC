#pragma once

#include <afxtempl.h>
#include "AreaMaskPart.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CAreaMaskMngr
	{
	public:
		CAreaMaskMngr();
		~CAreaMaskMngr();

	public:
		static CAreaMaskMngr* GetInstance();
		static void DeleteInstance();

		void SetHomeDirectory(CString strHomeDirectory);

		void AddAreaMaskPart(CAreaMaskPart* const pAddAreaMask);
		void AddTemp(CAreaMaskPart* const pAddAreaMask);
		void ModifyTemp(const INT nIndex, CAreaMaskPart* const pNewMaskPart);
		void DeleteTemp(const INT nIndex);

		INT GetAreaMaskCount();
		INT GetTempCount();

		CAreaMaskPart* GetAreaMaskPart(const INT nIndex);
		CAreaMaskPart* GetTempPart(const INT nIndex);

		void RemoveAll();

		void SaveAreaMask();		// AreaMask -> Temp
		void RestoreAreaMask();		// Temp -> AreaMask

		void LoadAreaMask(TCHAR* const pszFileName);
		void SaveAreaMask(TCHAR* const pszFileName);

	private:
		void LoadAreaMaskV10(CFile* pFile);

		void RemoveAllAreaMask();
		void RemoveAllTemp();

	private:
		static CAreaMaskMngr* m_pInstance;

		CString m_strHomeDirectory;

		CPtrArray m_paAreaMaskParts;
		CPtrArray m_paTempParts;
	};

} // NS_SALUS_MS_APP