#pragma once

#include <afx.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CDataWriter
	{
	public:
		CDataWriter(BOOL bBinary = FALSE);
		~CDataWriter();

	public:
		BOOL Open(LPCTSTR lpstrFileName);
		void Close();

		void Store(const void* pDataPtr, const UINT unDataSize);
		BOOL IsOpen();

	private:
		BOOL m_bBinary;
		CFile* m_pFile;
		CString m_strFileName;
		BOOL m_bOpened;
	};
}	// namespace NS_SALUS_MS_APP