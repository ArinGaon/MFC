#pragma once

#include <AfxDialogEx.h>
#include <afxbutton.h>

#include "SmsBaseColor.h"

namespace NS_SALUS_MS_APP
{
	// CSmsBaseDlg 대화 상자입니다.

	class AFX_EXT_CLASS CSmsBaseDlg : public CDialogEx
	{
		DECLARE_DYNAMIC(CSmsBaseDlg)

	public:
		CSmsBaseDlg(CWnd* pParent = NULL);
		CSmsBaseDlg(UINT unResourceID, CWnd* pParent = NULL); // 표준 생성자입니다.
		CSmsBaseDlg(LPCTSTR pszResourceID, CWnd* pParent = NULL);
		virtual ~CSmsBaseDlg();

	public:
		void EnableTitleBar(BOOL bEnableTitleBar = TRUE);
		void SetTitleHeight(LONG lTitleHeight);

	protected:
		void SetButtonImage(CMFCButton* const pButton, CImage* const pButtonImage);

	protected:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
		afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
		DECLARE_MESSAGE_MAP()

	private:
		void Init();

	protected:
		BOOL m_bEnableTitleBar;
		LONG m_lTitleBarHeight;

		E_DIALOG_COLOR_TYPE m_eColorType;

		CSmsBaseColor* m_pBaseColor;
	};

} // NS_SALUS_MS_APP