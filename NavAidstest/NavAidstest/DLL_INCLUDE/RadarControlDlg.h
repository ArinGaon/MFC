#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsStatic.h"
#include "SmsComboBox.h"

using namespace NS_SALUS_MS_APP;

// CRadarControlDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CRadarControlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CRadarControlDlg)

public:
	CRadarControlDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRadarControlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void ChangedRadarTrxStatus(INT nTrx, UINT iSourceKind);		// 0 = Stop, 1 = Start
	void ChangedRadarPulseModeStatus(INT nPmode);		

protected:
	void SetResourceColor();

	void UpdateTxStatus();
	void SendControlRadarInf();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadarControlOperation();
	afx_msg void OnBnClickedRadarControlPowerMode();

	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
	
private:
	CSmsStatic m_wndTitle;
	CSmsButton m_wndOperation;		// Button Control - Radar Control
	CSmsButton m_wndPowerMode;
	CSmsButton m_wndPulseMode;
	CSmsStatic	m_wndBand;
	CSmsComboBox m_wndPulse;

	UINT_PTR m_unRadarTxTimer;
	INT m_nTxStatus;	

	BOOL m_blOperation;
	BOOL m_blPowerMode;

	UINT m_uiSourceKind;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
