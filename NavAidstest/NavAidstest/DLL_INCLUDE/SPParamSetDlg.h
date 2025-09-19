#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsStatic.h"
#include "SmsSliderCtrl.h"

using namespace NS_SALUS_MS_APP;

// CSPParamSetDlg 대화 상자입니다.

class AFX_EXT_CLASS CSPParamSetDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CSPParamSetDlg)

public:
	CSPParamSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSPParamSetDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void SetSignalParam(const INT nSea, const INT nRain, const INT nGain, const INT nIntensity);
	void GetSignalParam(INT& nSea, INT& nRain, INT& nGain, INT& nIntensity);
	void SetFTCParam(UINT Value);

private:
	void UpdateSignalParam();
	void SetResourceColor();

	void ChangeSetValue(CStatic& wndValue, INT nPos);

	void SendChangedSignalParam();
	void SendChangeFTCParam();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	CSmsSliderCtrl m_wndSeaSlider;
	CSmsSliderCtrl m_wndRainSlider;
	CSmsSliderCtrl m_wndGainSlider;
	CSmsSliderCtrl m_wndIntensitySlider;
	
	CSmsStatic m_wndSeaValue;
	CSmsStatic m_wndRainValue;
	CSmsStatic m_wndGainValue;
	CSmsStatic m_wndIntensityValue;

	CSmsStatic m_wndTitleSea;
	CSmsStatic m_wndTitleRain;
	CSmsStatic m_wndTitleThreshhold;
	CSmsStatic m_wndTitleIntensity;

	BOOL	m_bAutoManual;  // FALSE = Manual, TRUE = auto

	INT m_nSea;
	INT m_nRain;
	INT m_nGain;
	INT m_nIntensity;
};
