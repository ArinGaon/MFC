#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CArpaScopeStatusDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CArpaScopeStatusDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaScopeStatusDlg)

public:
	CArpaScopeStatusDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArpaScopeStatusDlg();
	BOOL Create(CWnd* pParentWnd);

public:
	void UpdateScopeControl(const DOUBLE dRangeNM, const DOUBLE dRingRangeNM);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
