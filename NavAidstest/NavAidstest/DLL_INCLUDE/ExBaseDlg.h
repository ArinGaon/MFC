#pragma once

#include <AfxDialogEx.h>

namespace NS_SALUS_MS_APP
{
	// CExBaseDlg ��ȭ �����Դϴ�.

	class AFX_EXT_CLASS CExBaseDlg : public CDialogEx
	{
		DECLARE_DYNAMIC(CExBaseDlg)

	public:
		CExBaseDlg(CWnd* pParent = NULL);
		CExBaseDlg(UINT unResourceID, CWnd* pParent = NULL); // ǥ�� �������Դϴ�.
		virtual ~CExBaseDlg();

	protected:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
		afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
		DECLARE_MESSAGE_MAP()
	};
} // NS_SALUS_MS_APP