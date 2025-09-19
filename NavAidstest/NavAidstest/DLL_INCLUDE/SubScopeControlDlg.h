#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "RangeScale.h"
#include "SmsStatic.h"
#include "UserCommandDef.h"

using namespace NS_SALUS_MS_APP;

// CSubScopeCtrlDlg 대화 상자입니다.

class AFX_EXT_CLASS CSubScopeCtrlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CSubScopeCtrlDlg)

public:
	CSubScopeCtrlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSubScopeCtrlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

	BOOL m_bSubScopeMode;

	void SetSubScope(BOOL ScopeMode);
public:


protected:
	void UpdateScopeControl();
	void SendUserCommand(E_USER_COMMAND eUserCommand);

	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedSubScopeControlDownButton();
	afx_msg void OnBnClickedSubScopeControlUpButton();
	afx_msg void OnBnClickedSubScopeControlRingCheck();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	CSmsButton m_wndDownButton;
	CSmsButton m_wndUpButton;
	CSmsButton m_wndRingCheck;

	CSmsStatic m_wndRange;
	CSmsStatic m_wndRingRange;
	CSmsStatic m_wndTitleRES;

	INT m_nPrevRangeIndex;
	CRangeScale* m_pRangeScale;

	T_SCOPE_SETTING m_tScopeSetting;
};
