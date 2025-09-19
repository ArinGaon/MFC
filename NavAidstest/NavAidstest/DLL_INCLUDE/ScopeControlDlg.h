#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsStatic.h"

#include "UserCommandDef.h"

using namespace NS_SALUS_MS_APP;

// CScopeControlDlg 대화 상자입니다.

class AFX_EXT_CLASS CScopeControlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CScopeControlDlg)

public:
	CScopeControlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScopeControlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:

protected:
	void UpdateScopeControl();

	void SendUserCommand(E_USER_COMMAND eUserCommand);

	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedScopeControlUpButton();
	afx_msg void OnBnClickedScopeControlDownButton();
	afx_msg void OnBnClickedScopeControlRingCheck();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	CSmsStatic m_wndTitle;
	CSmsButton	m_wndUpButton;
	CSmsButton m_wndDownButton;
	CSmsButton	m_wndRingCheck;

	CSmsStatic m_wndRange;
	CSmsStatic m_wndRingRange;
	CSmsStatic m_wndRangeTitle;

	INT m_nPrevRangeIndex;

	T_SCOPE_SETTING m_tScopeSetting;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};