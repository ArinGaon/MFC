#pragma once

#include "SmsBaseDlg.h"

#include "SmsComboBox.h"
#include "SmsButton.h"
#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CTrackControlDlg 대화 상자입니다.


class AFX_EXT_CLASS CTrackControlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CTrackControlDlg)

public:
	CTrackControlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTrackControlDlg();
	virtual BOOL Create(CWnd* pParentWnd);
	
public:
	void SetTrackParam(const FLOAT fVector, const FLOAT fTrace, const FLOAT fEcho);
	void GetTrackParam(FLOAT& fVector, FLOAT& fTrace, FLOAT& fEcho);

protected:
	void SetSettingValue();
	void UpdateTrackParam();
	
	void SetResourceColor();

	void SendScopeViewParam();

	void ResetEchoTrail();
	void ResetTargetTrail();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeTrackControlVectorCombo();
	afx_msg void OnCbnSelchangeTrackControlTraceCombo();
	afx_msg void OnCbnSelchangeTrackControlEchoCombo();
	afx_msg void OnBnClickedClearVector();
	afx_msg void OnBnClickedClearTargetTrail();
	afx_msg void OnBnClickedClearEchoTrail();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	CSmsComboBox m_wndVectorCombo;
	CSmsComboBox m_wndTraceCombo;
	CSmsComboBox m_wndEchoCombo;
	CSmsButton   m_wndVectorClearBtn;
	CSmsButton   m_wndTTrailClearBtn;
	CSmsButton   m_wndETrailClearBtn;

	FLOAT m_fTrackVector;
	FLOAT m_fTrackTrace;
	FLOAT m_fEchoTrace;

	static const INT m_nMAX_VECTOR_NUM = 35;
	FLOAT m_fVectorTable[m_nMAX_VECTOR_NUM];

	static const INT m_nMAX_TRACE_NUM = 6;
	FLOAT m_fTraceTable[m_nMAX_TRACE_NUM];

	static const INT m_nMAX_ECHO_NUM = 10;
	FLOAT m_fEchoTable[m_nMAX_ECHO_NUM];

	CSmsStatic m_wndTitleVector;
	CSmsStatic m_wndTitleTargetTrail;
	CSmsStatic m_wndTitleEchoTrail;
	CSmsStatic m_wndUnitVector;
	CSmsStatic m_wndUnitTargetTrail;
	CSmsStatic m_wndUnitEchoTrail;
};
