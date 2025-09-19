#pragma once
#include "SmsBaseDlg.h"

#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaMotionModeDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CArpaMotionModeDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaMotionModeDlg)

public:
	CArpaMotionModeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArpaMotionModeDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateMotionMode(const E_SCOPE_MOTION eMotionMode);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();

private:
	CSmsStatic m_wndMotionView;
};
