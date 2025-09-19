#include "pch.h"
#include "NMEAUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CNMEAUtils::CNMEAUtils()
	{}

	BOOL CNMEAUtils::CheckChecksum(BYTE* const pDataPtr, const UINT nDataSize)
	{
		BOOL bCheckResult = FALSE;
		BYTE byChecksum = CalcChecksum(pDataPtr, nDataSize);
		CString strCalcCheckSum;
		CString strCheckSum = reinterpret_cast<TCHAR*>(pDataPtr);

		strCheckSum = strCheckSum.Mid(strCheckSum.Find(_T("*")) + 1);
		strCheckSum = strCheckSum.Left(2);
		strCalcCheckSum.Format(_T("%02X"), byChecksum);

		if (strCalcCheckSum == strCheckSum)
		{
			bCheckResult = TRUE;
		}

		return bCheckResult;
	}

	BYTE CNMEAUtils::CalcChecksum(const BYTE* const pDataPtr, const UINT nDataSize)
	{
		BYTE byChecksum = 0;

		for (UINT nCnt = 0U; nCnt < nDataSize; nCnt++)
		{
			if (pDataPtr[nCnt] == '*')
			{
				break;
			}
			if ((pDataPtr[nCnt] == '$') || ((pDataPtr[nCnt] == '!')))
			{
				continue;
			}
			byChecksum ^= pDataPtr[nCnt];
		}

		return byChecksum;
	}

	void CNMEAUtils::DeleteSentense(CString& strData)
	{
		strData = strData.Mid(strData.Find(_T(",")) + 1);
	}

	void CNMEAUtils::GetField(CString& strData, CString& strField)
	{
		INT nStart;

		// initialize
		strField = _T("");

		// Find delimeter
		nStart = strData.Find(_T(","));
		if (nStart > 0)
		{
			strField = strData.Left(nStart);
		}
		if (nStart >= 0)
		{
			strData = strData.Mid(nStart + 1);
		}
	}

	void CNMEAUtils::GetField(CString& strData, const INT nNum, CString& strField)
	{
		if (nNum > 0)
		{
			strField = strData.Left(nNum);
			strData = strData.Mid(nNum);
		}
	}

	void CNMEAUtils::GetTime(CString& strData, WORD& wHour, WORD& wMinute, DOUBLE& dSecond)
	{
		CString strField;
		CString strTemp;

		// find field
		GetField(strData, strField);

		// Hour 
		strTemp = strField.Left(2);
		wHour = static_cast<WORD>(_tcstoul(strTemp, NULL, 10));
		strField = strField.Mid(2);
		// Minute
		strTemp = strField.Left(2);
		wMinute = static_cast<WORD>(_tcstoul(strTemp, NULL, 10));
		strField = strField.Mid(2);
		// Second
		dSecond = _tcstod(strField, NULL);
	}

	void CNMEAUtils::GetDate(CString& strData, WORD& wYear, WORD& wMonth, WORD& wDay)
	{
		CString strField;
		CString strTemp;

		// find field
		GetField(strData, strField);

		// day 
		strTemp = strField.Left(2);
		wDay = static_cast<WORD>(_tcstoul(strTemp, NULL, 10));
		strField = strField.Mid(2);
		// Month
		strTemp = strField.Left(2);
		wMonth = static_cast<WORD>(_tcstoul(strTemp, NULL, 10));
		strField = strField.Mid(2);
		// Year
		wYear = static_cast<WORD>(_tcstoul(strField, NULL, 10));
	}

	void CNMEAUtils::GetLatitude(CString& strData, SHORT& sDegree, DOUBLE& dMinute)
	{
		CString strField1;
		CString strField2;
		CString strTemp;

		// find field
		GetField(strData, strField1);
		GetField(strData, strField2);

		// degree
		strTemp = strField1.Left(2);
		sDegree = static_cast<SHORT>(_tcstol(strTemp, NULL, 10));
		strField1 = strField1.Mid(2);
		// minute
		dMinute = _tcstod(strField1, NULL);

		if (strField2.GetAt(0) == 'S')
		{
			sDegree = sDegree * -1;
		}
	}

	void CNMEAUtils::GetLongitude(CString& strData, SHORT& sDegree, DOUBLE& dMinute)
	{
		CString strField1;
		TCHAR cIndicator;
		CString strTemp;

		// find filed
		GetField(strData, strField1);
		
		if (strField1.GetLength() > 0)
		{
			// degree
			strTemp = strField1.Left(3);
			sDegree = static_cast<SHORT>(_tcstol(strTemp, NULL, 10));
			strField1 = strField1.Mid(3);
			// minute
			dMinute = _tcstod(strField1, NULL);
		}
		
		if ((GetCHAR(strData, cIndicator) == TRUE) && (cIndicator == 'W'))
		{
			sDegree = sDegree * -1;
		}
	}

	/*
	*	CString strField1;
		CString strField2;
		CString strTemp;

		GetField(strData, strField1);
		GetField(strData, strField2);

		strTemp = strField1.Left(3);
		sDegree = static_cast<SHORT>(_tcstol(strTemp, NULL,10));
		strField1 = strField1.Mid(3);
		dMinute = _tcstod(strField1. NULL);

		if(strfield2.GetAt(0) == 'W')
		{
			sDegree = sDegree * -1;
		}
	*/

	BOOL CNMEAUtils::GetCHAR(CString& strData, TCHAR& cValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			cValue = strField.GetAt(0);
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetBYTE(CString& strData, BYTE& byValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			byValue = static_cast<BYTE>(_tcstoul(strField, NULL, 10));
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetWORD(CString& strData, WORD& wValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			wValue = static_cast<WORD>(_tcstoul(strField, NULL, 10));
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetSHORT(CString& strData, SHORT& sValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			sValue = static_cast<SHORT>(_tcstol(strField, NULL, 10));
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetDWORD(CString& strData, DWORD& dwValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			dwValue = static_cast<DWORD>(_tcstoul(strField, NULL, 10));
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetFLOAT(CString& strData, FLOAT& fValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			fValue = _tcstof(strField, NULL);
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	BOOL CNMEAUtils::GetDOUBLE(CString& strData, DOUBLE& dValue)
	{
		BOOL bReturnValue = FALSE;
		CString strField;

		// find field
		GetField(strData, strField);

		if (strField.GetLength() > 0)
		{
			dValue = _tcstod(strField, NULL);
			bReturnValue = TRUE;
		}

		return bReturnValue;
	}

	UCHAR CNMEAUtils::GetU8FromHEX(CString& strData)
	{
		CString strField;
		CNMEAUtils::GetField(strData, 2, strField);  // 8 Bits

		UCHAR ucValue = 0U;
		TCHAR cHex;

		for (INT nCnt = 0; nCnt < 2; nCnt++)
		{
			// shift
			ucValue = (ucValue << 4);

			cHex = strField.GetAt(nCnt);
			if (cHex >= 'A')
			{
				ucValue |= (cHex - 'A' + 10U);
			}
			else
			{
				ucValue |= (cHex - '0');
			}
		}

		return ucValue;
	}

	SHORT CNMEAUtils::GetI16FromHEX(CString& strData)
	{
		SHORT sValue = 0;
		UCHAR ucValue;

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		sValue = sValue | (ucValue & 0x00FF);

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		sValue = sValue | ((ucValue << 8) & 0xFF00);

		return sValue;
	}

	USHORT CNMEAUtils::GetU16FromHEX(CString& strData)
	{
		USHORT usValue = 0U;
		UCHAR ucValue;

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		usValue = usValue | (ucValue & 0x00FF);

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		usValue = usValue | ((ucValue << 8) & 0xFF00);

		return usValue;
	}

	INT32 CNMEAUtils::GetI32FromHEX(CString& strData)
	{
		INT32 nValue = 0;
		UCHAR ucValue;

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		nValue = nValue | (ucValue & 0x000000FF);

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		nValue = nValue | ((ucValue << 8) & 0x0000FF00);

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		nValue = nValue | ((ucValue << 16) & 0x00FF0000);

		ucValue = GetU8FromHEX(strData);  // 8 Bits
		nValue = nValue | ((ucValue << 24) & 0xFF000000);

		return nValue;
	}

} // NS_SALUS_MS_APP