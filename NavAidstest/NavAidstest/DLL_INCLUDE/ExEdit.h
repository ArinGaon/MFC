#pragma once

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CExEdit : public CEdit
	{
		DECLARE_DYNAMIC(CExEdit)

	public:
		CExEdit() noexcept;
		virtual ~CExEdit();

	public:
		void SetWindowText(LPCTSTR lpszString, BOOL bNotify = FALSE);

	protected:
		virtual void PreSubclassWindow();
		virtual BOOL PreTranslateMessage(MSG* pMsg);

	protected:
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnEnSetfocus();
		afx_msg void OnEnKillfocus();
		afx_msg BOOL OnEnChange();
		DECLARE_MESSAGE_MAP()

	protected:
		BOOL m_bNotify;
		CString m_strOld;
	};
}	// NS_SALUS_MS_APP