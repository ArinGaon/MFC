#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CCpaControlDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CCpaControlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CCpaControlDlg)

public:
	CCpaControlDlg(CWnd* pParent = NULL);				// ǥ�� �������Դϴ�.
	virtual ~CCpaControlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void SetThreshold(const FLOAT fCPA, const FLOAT fTCPA);			// CPA / TCPA THD - CPA���� Editbox�� ǥ��

protected:
	void SetResourceColor();

	void SendCpaAlarmParam();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeCpaControlCpaThreshold();
	afx_msg void OnEnChangeCpaControlTcpaThreshold();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeCPATCPAUpdate(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	//CSmsEdit m_wndCpaThreshold;
	//CSmsEdit m_wndTcpaThreshold;
	CSmsStatic m_wndTitleCPA;
	CSmsStatic m_wndTitleTCPA;
	CSmsStatic m_wndControlCPA;
	CSmsStatic m_wndControlTCPA;
	CSmsStatic m_wndUnitCPA;
	CSmsStatic m_wndUnitTCPA;

	FLOAT m_fCPA;
	FLOAT m_fTCPA;
public:
	afx_msg void OnPaint();

	void SetCPATCPAUpdate(double CPA, double TCPA);
	void SetUpdateUnit(CString Unit);
};
