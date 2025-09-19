#pragma once

#include <afxcmn.h>

#include "DataTypeDef.h"

#include "SmsSpinButtonCtrl.h"

namespace NS_SALUS_MS_APP
{
	// CSmsNumberSpinCtrl

	class AFX_EXT_CLASS CSmsNumberSpinCtrl : public CSmsSpinButtonCtrl
	{
		DECLARE_DYNAMIC(CSmsNumberSpinCtrl)

	public:
		CSmsNumberSpinCtrl();
		virtual ~CSmsNumberSpinCtrl();

	public:
		void SetRangeAndDelta(DOUBLE dLower, DOUBLE dUpper, DOUBLE dDelta);
		void GetRangeAndDelta(DOUBLE& dLower, DOUBLE& dUpper, DOUBLE& dDelta);
		void SetPos(DOUBLE dValue);
		DOUBLE GetPos();

		INT  GetDecimalPlaces();
		void SetDecimalPlaces(INT nNumPlaces);
		void SetFormatString(LPCTSTR lpszFormatString = NULL);

		void SetTrimTrailingZeros(BOOL bTrim);
		BOOL GetTrimTrailingZeros();

	protected:
		virtual void PreSubclassWindow();

		void InitSpinCtrl();
		void SetIntPos(DOUBLE dPos);
		void SetValueForBuddy(DOUBLE dValue);
		CString FormatValue(DOUBLE dValue);

	protected:
		afx_msg BOOL OnDeltaPos(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		DECLARE_MESSAGE_MAP()

	protected:
		static const DOUBLE m_dEPS;

		DOUBLE m_dMinValue;
		DOUBLE m_dMaxValue;
		DOUBLE m_dDelta;
		UINT m_nIntRange;
		INT m_nNumDecPlaces;
		CString m_strFormat;
		BOOL m_bTrimTrailingZeros;
		CHAR m_cDecSymbol;
	};
}