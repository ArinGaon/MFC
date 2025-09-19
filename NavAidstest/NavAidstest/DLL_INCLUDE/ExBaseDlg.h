#pragma once

#include <AfxDialogEx.h>

namespace NS_SALUS_MS_APP
{
	// CExBaseDlg 대화 상자입니다.

	class AFX_EXT_CLASS CExBaseDlg : public CDialogEx
	{
		DECLARE_DYNAMIC(CExBaseDlg)

	public:
		CExBaseDlg(CWnd* pParent = NULL);
		CExBaseDlg(UINT unResourceID, CWnd* pParent = NULL); // 표준 생성자입니다.
		virtual ~CExBaseDlg();

	protected:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
		afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
		DECLARE_MESSAGE_MAP()
	};
} // NS_SALUS_MS_APP