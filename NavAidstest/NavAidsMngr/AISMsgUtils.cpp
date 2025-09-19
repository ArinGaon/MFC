#include "pch.h"
#include "AISMsgUtils.h"

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	static TCHAR g_cSIX_BIT_ASCII[64] = {
	'@',		// 0
	'A',		// 1
	'B',		// 2
	'C',		// 3
	'D',		// 4
	'E',		// 5
	'F',		// 6
	'G',		// 7
	'H',		// 8
	'I',		// 9
	'J',		// 10
	'K',		// 11
	'L',		// 12
	'M',		// 13
	'N',		// 14
	'O',		// 15
	'P',		// 16
	'Q',		// 17
	'R',		// 18
	'S',		// 19
	'T',		// 20
	'U',		// 21
	'V',		// 22
	'W',		// 23
	'X',		// 24
	'Y',		// 25
	'Z',		// 26
	'[',		// 27
	'\\',		// 28
	']',		// 29
	'^',		// 30
	'_',		// 31
	' ',		// 32
	'!',		// 33
	'\"',		// 34
	'#',		// 35
	'$',		// 36
	'%',		// 37
	'&',		// 38
	' ',		// 39
	'(',		// 40
	')',		// 41
	'*',		// 42
	'+',		// 43
	',',		// 44
	'-',		// 45
	'.',		// 46
	'/',		// 47
	'0',		// 48
	'1',		// 49
	'2',		// 50
	'3',		// 51
	'4',		// 52
	'5',		// 53
	'6',		// 54
	'7',		// 55
	'8',		// 56
	'9',		// 57
	':',		// 58
	';',		// 59
	'<',		// 60
	'=',		// 61
	'>',		// 62
	'?'			// 63
	};

	CAISUtils::CAISUtils()
	{
	}

	TCHAR CAISUtils::GetCHAR(const CString strData, const INT nStartBits, const INT nNumBits)
	{
		TCHAR cReturn = 0;
		UCHAR ucIndex = GetU8(strData, nStartBits, nNumBits);

		if (ucIndex > 0 && ucIndex < 64)
		{
			cReturn = g_cSIX_BIT_ASCII[ucIndex];
		}
		return cReturn;
	}

	UCHAR CAISUtils::GetU8(const CString strData, const INT nStartBits, const INT nNumBits)
	{
		UCHAR ucValue = 0U;
		INT nStartPos = nStartBits / 6;
		INT nEndPos = (nStartBits + nNumBits - 1) / 6;
		BYTE byData = 0U;
		UCHAR ucMask = 0U;
		INT nShiftBit;
		INT nLength = strData.GetLength();

		if (nStartPos == nEndPos)
		{
			if (nStartPos < nLength)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nStartPos));
				nShiftBit = 6 - (nStartBits % 6) - nNumBits;
				if (nShiftBit > 0)
				{
					byData = byData >> nShiftBit;
				}

				ucMask = 0U;
				for (INT nBits = 0; nBits < nNumBits; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}

				ucValue = byData & ucMask;
			}
		}
		else
		{
			if (nEndPos < nLength)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nStartPos));
				nShiftBit = (nStartBits % 6);
				ucMask = 0U;
				for (INT nBits = 0; nBits < 6 - nShiftBit; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}
				ucValue = (byData & ucMask);

				INT nRestBit = nNumBits - (6 - nShiftBit);

				byData = ConvertSixBits2ASCII(strData.GetAt(nEndPos));
				ucValue = (ucValue << nRestBit) | (byData >> (6 - nRestBit));
			}
		}

		return ucValue;
	}

	USHORT CAISUtils::GetU16(const CString strData, const INT nStartBits, const INT nNumBits)
	{
		USHORT usValue = 0U;
		BYTE byData;

		INT nStartPos = nStartBits / 6;
		INT nEndPos = (nStartBits + nNumBits - 1) / 6;
		INT nShiftBit;
		UCHAR ucMask;
		INT nLength = strData.GetLength();

		if (nEndPos < nLength)
		{
			nShiftBit = nStartBits % 6;
			if (nShiftBit > 0)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nStartPos));
				ucMask = 0U;
				for (INT nBits = 0; nBits < 6 - nShiftBit; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}
				usValue = byData & ucMask;

				nStartPos++;
			}

			for (INT nPos = nStartPos; nPos < nEndPos; nPos++)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nPos)) & 0x3F;

				usValue = (usValue << 6) | byData;
			}

			nShiftBit = (nStartBits + nNumBits) % 6;
			if (nShiftBit > 0)
			{
				ucMask = 0U;
				for (INT nBits = 0; nBits < nShiftBit; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}
				byData = ConvertSixBits2ASCII(strData.GetAt(nEndPos));

				usValue = (usValue << nShiftBit) | ((byData >> (6 - nShiftBit)) & ucMask);
			}
			else if (nShiftBit == 0)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nEndPos)) & 0x3F;

				usValue = (usValue << 6) | byData;
			}
			else
			{
				// Do nothing
			}
		}
		
		return usValue;
	}

	UINT32 CAISUtils::GetU32(const CString strData, const INT nStartBits, const INT nNumBits)
	{
		UINT32 unValue = 0U;
		BYTE byData;

		INT nStartPos = nStartBits / 6;
		INT nEndPos = (nStartBits + nNumBits - 1) / 6;
		INT nShiftBit;
		UCHAR ucMask;
		INT nLength = strData.GetLength();

		if (nEndPos < nLength)
		{
			nShiftBit = nStartBits % 6;
			if (nShiftBit > 0)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nStartPos));
				ucMask = 0U;
				for (INT nBits = 0; nBits < 6 - nShiftBit; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}
				unValue = byData & ucMask;

				nStartPos++;
			}

			for (INT nPos = nStartPos; nPos < nEndPos; nPos++)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nPos)) & 0x3F;

				unValue = (unValue << 6) | byData;
			}

			nShiftBit = (nStartBits + nNumBits) % 6;
			if (nShiftBit > 0)
			{
				ucMask = 0U;
				for (INT nBits = 0; nBits < nShiftBit; nBits++)
				{
					ucMask = (ucMask | (1 << nBits));
				}
				byData = ConvertSixBits2ASCII(strData.GetAt(nEndPos));

				unValue = (unValue << nShiftBit) | ((byData >> (6 - nShiftBit)) & ucMask);
			}
			else if (nShiftBit == 0)
			{
				byData = ConvertSixBits2ASCII(strData.GetAt(nEndPos)) & 0x3F;

				unValue = (unValue << 6) | byData;
			}
			else
			{
				// Do nothing
			}
		}
		
		return unValue;
	}

	BYTE CAISUtils::ConvertSixBits2ASCII(const TCHAR cSixBits)
	{
		TCHAR cOut;

		if ((cSixBits >= '0') && (cSixBits <= 'W'))
		{
			cOut = cSixBits - 48;
		}
		else if ((cSixBits >= '\'') && (cSixBits <= 'w'))
		{
			cOut = cSixBits - 56;
		}
		else
		{
			cOut = cSixBits;
		}
		return static_cast<BYTE>(cOut);
	}

} // NS_SALUS_MS_APP