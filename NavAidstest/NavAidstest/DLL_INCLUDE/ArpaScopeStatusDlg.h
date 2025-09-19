#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CArpaScopeStatusDlg 대화 상자입니다.

class AFX_EXT_CLASS CArpaScopeStatusDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaScopeStatusDlg)

public:
	CArpaScopeStatusDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArpaScopeStatusDlg();
	BOOL Create(CWnd* pParentWnd);

public:
	void UpdateScopeControl(const DOUBLE dRangeNM, const DOUBLE dRingRangeNM);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();

private:
	CSmsStatic m_wndTitle;

	CSmsStatic m_wndRange;
	CSmsStatic m_wndRingRange;
};
