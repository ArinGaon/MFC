#pragma once

#include <afxstr.h>

#include "DataTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class CAISUtils
	{
	public:
		CAISUtils();

	public:
		static TCHAR GetCHAR(const CString strData, const INT nStartBits, const INT nNumBits);
		static UCHAR GetU8(const CString strData, const INT nStartBits, const INT nNumBits);
		static USHORT GetU16(const CString strData, const INT nStartBits, const INT nNumBits);
		static UINT32 GetU32(const CString strData, const INT nStartBits, const INT nNumBits);

		static BYTE ConvertSixBits2ASCII(const TCHAR cSixBits);
	};

} // NS_SALUS_MS_APP