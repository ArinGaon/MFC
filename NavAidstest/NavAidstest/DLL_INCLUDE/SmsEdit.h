#pragma once

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsEdit : public CEdit
	{
		DECLARE_DYNAMIC(CSmsEdit)

	public:
		CSmsEdit() noexcept;
		virtual ~CSmsEdit();

	public:
		void SetWindowText(LPCTSTR lpszString, BOOL bNotify = FALSE);

		void SetNormalColor(const COLORREF clrFace, const COLORREF clrText);
		void SetDisabledColor(const COLORREF clrFace);

	protected:
		virtual void PreSubclassWindow();
		virtual BOOL PreTranslateMessage(MSG* pMsg);

	protected:
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnNcPaint();
		afx_msg UINT OnGetDlgCode();
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);
		afx_msg void OnEnSetfocus();
		afx_msg void OnEnKillfocus();
		afx_msg BOOL OnEnChange();
		DECLARE_MESSAGE_MAP()

	protected:
		COLORREF m_clrText;
		COLORREF m_clrNormalFace;
		COLORREF m_clrDisabledFace;
		CBrush   m_brFace;
		BOOL m_bNotify;
		CString m_strOld;
	};
}	// NS_SALUS_MS_APP