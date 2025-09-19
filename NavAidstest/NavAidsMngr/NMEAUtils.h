#pragma once

#include <afxstr.h>

#include "DataTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class CNMEAUtils
	{
	public:
		CNMEAUtils();

	public:
		static BOOL CheckChecksum(BYTE* const pDataPtr, const UINT nDataSize);
		static BYTE CalcChecksum(const BYTE* const pDataPtr, const UINT nDataSize);

		static void DeleteSentense(CString& strData);
		static void GetField(CString& strData, CString& strField);
		static void GetField(CString& strData, const INT nNum, CString& strField);

		static void GetTime(CString& strData, WORD& wHour, WORD& wMinute, DOUBLE& dSecond);
		static void GetDate(CString& strData, WORD& wYear, WORD& wMonth, WORD& wDay);
		static void GetLatitude(CString& strData, SHORT& sDegree, DOUBLE& dMinute);
		static void GetLongitude(CString& strData, SHORT& sDegree, DOUBLE& dMinute);

		static BOOL GetCHAR(CString& strData, TCHAR& cValue);
		static BOOL GetBYTE(CString& strData, BYTE& byValue);
		static BOOL GetWORD(CString& strData, WORD& wValue);
		static BOOL GetSHORT(CString& strData, SHORT& sValue);
		static BOOL GetDWORD(CString& strData, DWORD& dwValue);
		static BOOL GetFLOAT(CString& strData, FLOAT& fValue);
		static BOOL GetDOUBLE(CString& strData, DOUBLE& dValue);

		static UCHAR GetU8FromHEX(CString& strData);
		static SHORT GetI16FromHEX(CString& strData);
		static USHORT GetU16FromHEX(CString& strData);
		static INT32 GetI32FromHEX(CString& strData);
	};
} // NS_SALUS_MS_APP