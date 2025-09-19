#pragma once

#include "afxwin.h"
#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaOwnshipInfoDlg 대화 상자입니다.

class AFX_EXT_CLASS CArpaOwnshipInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaOwnshipInfoDlg)

public:
	CArpaOwnshipInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArpaOwnshipInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateOwnShipInfo(const T_OWNSHIP_INFO* const pOwnshipInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUpdateOwnSiteInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void ArrangeResourceControls();		// Arrange controls in dialog
	void ApplyResourceFont();			// Change the font in OnInitDialog();
	void UpdateOwnSiteInfo();			// Fresh the GUI
	void NullOwnSiteInfo();

	void SetResourceColor();

private:
	CSmsStatic m_wndTitle;

	T_OWNSHIP_INFO m_tOwnshipInfo;
	BOOL m_bUpdated;
};
