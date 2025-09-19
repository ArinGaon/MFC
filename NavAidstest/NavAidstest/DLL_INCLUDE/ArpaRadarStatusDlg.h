#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaRadarStatusDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CArpaRadarStatusDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaRadarStatusDlg)

public:
	CArpaRadarStatusDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArpaRadarStatusDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void ChangedRadarTrxStatus(INT nTrx);		// 0 = Stop, 1 = Start
	void ChangedRadarTxPulse(CString strPulseMode);
	void ChangedRadarDualStatus(E_RADAR_DUAL_STATUS eDualStatus);

protected: 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();

	void UpdateTxStatus();

private:
	CSmsStatic m_wndTitle;
	
	CSmsStatic m_wndDualStat;
	CSmsStatic m_wndBand;
	CSmsStatic m_wndPulse;
	CSmsStatic m_wndOperation;		// Button Control - Radar Control

	INT m_nTxStatus;
};
