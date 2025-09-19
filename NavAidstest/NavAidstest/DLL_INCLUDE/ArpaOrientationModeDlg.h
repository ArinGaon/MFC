#pragma once
#include "SmsBaseDlg.h"

#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaOrientationModeDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CArpaOrientationModeDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaOrientationModeDlg)

public:
	CArpaOrientationModeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArpaOrientationModeDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateOrientationMode(const E_SCOPE_ORIENTATION eOrientationMode);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();
	
private:
	CSmsStatic m_wndModeView;
};
