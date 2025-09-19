#pragma once

#include <afx.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CDataReader
	{
	public:
		CDataReader(BOOL bBinary = FALSE);
		~CDataReader();

	public:
		BOOL Open(const LPCTSTR lpstrFileName);
		void Close();

		UINT GetCount(const UINT unDataSize);

		void SeekToBegin();
		void SetRepeat(BOOL bRepeat = TRUE);

		INT GetFileSize();
		INT GetCurPos();

		BOOL Read(SYSTEMTIME& tTime, void* const pDataPtr, const UINT unDataSize);
		BOOL Read(const UINT unPos, SYSTEMTIME& tTime, void* const pDataPtr, const UINT unDataSize);
		BOOL Read(void* const pDataPtr, const UINT unDataSize);
		BOOL IsOpen();

	protected:
		void ConvertTime(CString strData, SYSTEMTIME& tTime);

	private:
		BOOL m_bBinary;
		CFile* m_pFile;
		CString m_strFileName;
		BOOL m_bOpened;

		BOOL m_bRepeat;
	};

} // namespace NS_SALUS_MS_APP