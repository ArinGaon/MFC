#pragma once

#include "CoordBaseDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CAreaMaskPart
	{
	public:
		CAreaMaskPart();
		~CAreaMaskPart();

	public:
		void SetPartName(const TCHAR* const pszPartName);
		CString GetPartName();

		void Add(const DOUBLE dLat, const DOUBLE dLon);
		void Add(T_GEO_POS2D* const pPoint);
		void Insert(const INT nIndex, const DOUBLE dLat, const DOUBLE dLon);
		void Insert(const INT nIndex, T_GEO_POS2D* const pPoint);
		void Delete(const INT nIndex);
		void RemoveAll();

		INT GetCount();
		BOOL GetAt(const INT nIndex, DOUBLE& dLat, DOUBLE& dLon);
		BOOL GetAt(const INT nIndex, T_GEO_POS2D& tPos);
		BOOL SetAt(const INT nIndex, const DOUBLE dLat, const DOUBLE dLon);
		BOOL SetAt(const INT nIndex, const T_GEO_POS2D tPos);

		CPtrArray* GetMaskParts();

	private:
		CString m_strPartName;
		CPtrArray m_paPoints;
	};

} // NS_SALUS_MS_APP