#pragma once

#include "SmsBaseDlg.h"

#include "SmsStatic.h"
#include "SmsButton.h"
#include "SmsComboBox.h"
#include "SmsEdit.h"
#include "SmsSpinButtonCtrl.h"

#include "UserCommandDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaControlDlg 대화 상자입니다.

class AFX_EXT_CLASS CArpaControlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaControlDlg)

public:
	CArpaControlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArpaControlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void SetSignalParam(const INT nSea, const INT nRain, const INT nGain, const INT nIntensity);
	void SetTrackParam(const FLOAT fVector, const FLOAT fTrackTrail, const FLOAT fEchoTrail);
	void SetCpaAlarmParam(const FLOAT fCPA, FLOAT fTCPA);

protected:
	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeArpaControlRadarKindCombo();
	afx_msg void OnCbnSelchangeArpaControlRadarRunCombo();
	afx_msg void OnCbnSelchangeArpaControlPulseModeCombo();
	afx_msg void OnCbnSelchangeArpaControlPulseStateCombo();
	afx_msg void OnCbnSelchangeArpaControlScopeRangeCombo();
	afx_msg void OnBnClickedArpaControlScopeRingCheck();
	afx_msg void OnEnChangeArpaControlSeaClutterEdit();
	afx_msg void OnEnChangeArpaControlSignalGainEdit();
	afx_msg void OnEnChangeArpaControlRainClutterEdit();
	afx_msg void OnEnChangeArpaControlSignalIntensityEdit();
	afx_msg void OnDeltaposArpaControlSeaClutterSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposArpaControlSignalGainSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposArpaControlRainClutterSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposArpaControlSignalIntensitySpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedArpaControlSeaClutterButton();
	afx_msg void OnBnClickedArpaControlSignalGainButton();
	afx_msg void OnBnClickedArpaControlRainClutterButton();
	afx_msg void OnBnClickedArpaControlSignalIntensityButton();
	afx_msg void OnCbnSelchangeArpaControlTrackViewCombo();
	afx_msg void OnCbnSelchangeArpaControlMotionModeCombo();
	afx_msg void OnCbnSelchangeArpaControlOrientationModeCombo();
	afx_msg void OnCbnSelchangeArpaControlClutterModeCombo();
	afx_msg void OnCbnSelchangeArpaControlTrackVectorCombo();
	afx_msg void OnCbnSelchangeArpaControlTrackTrailCombo();
	afx_msg void OnEnChangeArpaControlCpaLimitEdit();
	afx_msg void OnEnChangeArpaControlTcpaLimitEdit();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void ArrangeResourceControls();				// Arrange controls in dialog
	void ApplyResourceFont();					// Change the font in OnInitDialog();

	void UpdateScopeControl();
	void UpdateScopeViewControl();

	void SendRadarPulseStatus(const INT nPulseType, const INT nTxStatus);
	void SendScopeControlCommand(const E_USER_COMMAND eUserCommand);
	void SendSignalParamCommand();
	void SendScopeViewParam();
	void SendScopeControlParam();
	void SendCpaAlarmParam();

private:
	CSmsStatic			m_wndTitle;
	CSmsComboBox		m_wndRadarKindCombo;
	CSmsComboBox		m_wndRadarRunCombo;
	CSmsComboBox		m_wndPulseModeCombo;
	CSmsComboBox		m_wndPulseStateCombo;
	CSmsComboBox		m_wndScopeRangeCombo;
	CSmsStatic			m_wndScopeRingView;
	CSmsButton			m_wndScopeRingCheck;
	CSmsEdit			m_wndSeaClutterEdit;
	CSmsEdit			m_wndRainClutterEdit;
	CSmsEdit			m_wndSignalGainEdit;
	CSmsEdit			m_wndSignalIntensityEdit;
	CSmsSpinButtonCtrl	m_wndSeaClutterSpin;
	CSmsSpinButtonCtrl	m_wndRainClutterSpin;
	CSmsSpinButtonCtrl	m_wndSignalGainSpin;
	CSmsSpinButtonCtrl	m_wndSignalIntensitySpin;
	CSmsButton			m_wndSeaClutterButton;
	CSmsButton			m_wndRainClutterButton;
	CSmsButton			m_wndSignalGainButton;
	CSmsButton			m_wndSignalIntensityButton;
	CSmsComboBox		m_wndTrackViewCombo;
	CSmsComboBox		m_wndMotionModeCombo;
	CSmsComboBox		m_wndOrientationModeCombo;
	CSmsComboBox		m_wndClutterModeCombo;
	CSmsComboBox		m_wndTrackVectorCombo;
	CSmsComboBox		m_wndTrackTrailCombo;
	CSmsEdit			m_wndCpaLimitEdit;
	CSmsEdit			m_wndTcpaLimitEdit;

	static const INT m_nMAX_TRACK_VECTOR_NUM = 35;
	FLOAT m_fTrackVectorTable[m_nMAX_TRACK_VECTOR_NUM];

	static const INT m_nMAX_TRACK_TRACE_NUM = 6;
	FLOAT m_fTrackTraceTable[m_nMAX_TRACK_TRACE_NUM];

	static const INT m_nMAX_ECHO_NUM = 10;
	FLOAT m_fEchoValue[m_nMAX_ECHO_NUM];

	BOOL			m_bIsViewRings;
	T_SCOPE_SETTING m_tScopeSetting;
	T_SCOPE_VIEW_PARAM m_tScopeViewParam;
	T_SIGNAL_PARAM m_tSignalParam;
	T_CPA_ALARM_PARAM m_tCpaAlaramParam;
	T_SCOPE_CONTROL_PARAM m_tScopeControlParam;
};
