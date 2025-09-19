#pragma once

#include "SmsEdit.h"

namespace NS_SALUS_MS_APP
{
	// CSmsNumberEdit

	class AFX_EXT_CLASS CSmsNumberEdit : public CSmsEdit
	{
		DECLARE_DYNAMIC(CSmsNumberEdit)

	public:
		CSmsNumberEdit();
		virtual ~CSmsNumberEdit();

	public:
		enum class E_NUMBER_TYPE
		{
			eINTEGER = 0,
			eFLOAT = 1
		};

		BOOL IsEmpty();
		void AllowMinusValue(const BOOL bAllow);
		void SetFormat(const E_NUMBER_TYPE eType, TCHAR* const pszFormat = NULL);
		void SetValue(const DOUBLE dValue);
		DOUBLE GetValue();
		void SetValue(const E_NUMBER_TYPE eType, TCHAR* const pszFormat, const DOUBLE dValue, const BOOL bAllowMinus = TRUE);
		void SetValue(const E_NUMBER_TYPE eType, TCHAR* const pszFormat, DOUBLE dValue, const DOUBLE dMin, const DOUBLE dMax, const BOOL bAllowMinus = TRUE);

	protected:
		void UpdateDotCount();

		void EndEdit();

	protected:
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg UINT OnGetDlgCode();
		afx_msg void OnKillFocus(CWnd* pNewWnd);
		DECLARE_MESSAGE_MAP()

	private:
		BOOL m_bAllowMinusValue;
		BOOL m_bAllowFloatValue;
		E_NUMBER_TYPE m_eType;
		TCHAR m_szFormat[10];
		INT m_nDotCount;
		INT	m_nValue;
		DOUBLE m_dValue;
		DOUBLE m_dMaxValue;
		DOUBLE m_dMinValue;
		BOOL m_bRange;
	};
}	// NS_SALUS_MS_APP