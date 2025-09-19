#pragma once
#include "SmsBaseDlg.h"

#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaOrientationModeDlg 대화 상자입니다.

class AFX_EXT_CLASS CArpaOrientationModeDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaOrientationModeDlg)

public:
	CArpaOrientationModeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArpaOrientationModeDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateOrientationMode(const E_SCOPE_ORIENTATION eOrientationMode);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();
	
private:
	CSmsStatic m_wndModeView;
};
