#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "TrackDataDef.h"
#include "SmsButton.h"

// CTrackInfoDlg 대화 상자입니다.

using namespace NS_SALUS_MS_APP;

class AFX_EXT_CLASS CTrackInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CTrackInfoDlg)

public:
	CTrackInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTrackInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateTrackInfo(const T_CONFIRMED_TRACK* const pTrackData1, const T_CONFIRMED_TRACK* const pTrackData2, const T_CPA_TRACK* const pCpaTrack1, const T_CPA_TRACK* const pCpaTrack2);

	CBrush m_brush1;

protected:
	void UpdateTrackInfoGroupA();
	void UpdateTrackInfoGroupB();

	void ChangeDetailButtonStatus();

	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedTrackInfoRdrRadio();
	afx_msg void OnBnClickedTrackInfoAisRadio();
	afx_msg void OnBnClickedTrackInfoMixRadio();
	afx_msg void OnBnClickedTrackInfoGrpaDetailButton();
	afx_msg void OnBnClickedTrackInfoGrpbDetailButton();
	afx_msg LRESULT OnUpdateDialogInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	static const INT m_nMAX_DISP_TRACK_DATA = 2;
	static const INT m_nMAX_DISP_TRACK_TYPE = 3;

	CSmsButton m_wndReportDetail[m_nMAX_DISP_TRACK_DATA];	// Report Detail Button of Target A/B
	CSmsButton m_wndTrackType[m_nMAX_DISP_TRACK_TYPE];							// RDR, AIS, MIX Button

	E_TRACK_TYPE m_eSelectedTrackType;		// RDR/AIS/MIX 중 선택된 타입
	INT	m_nOpenReportDetail;				// -1: Close Report, TGT_A: Open Report (TargetA), TGT_B: Open Report (TargetB)

	BOOL m_bIsValidTrackInfo[m_nMAX_DISP_TRACK_DATA];
	BOOL m_bIsValidCpaInfo[m_nMAX_DISP_TRACK_DATA];
	T_CONFIRMED_TRACK* m_pConfirmTrack[m_nMAX_DISP_TRACK_DATA];
	T_CPA_TRACK* m_pCpaTrack[m_nMAX_DISP_TRACK_DATA];

	void SetUnit();

	CSmsStatic m_wndTitle;
	CSmsStatic m_wndTitleID;
	CSmsStatic m_wndTitleLat;
	CSmsStatic m_wndTitleLon;
	CSmsStatic m_wndTitleRNG;
	CSmsStatic m_wndTitleBRG;
	CSmsStatic m_wndTitleSOG;
	CSmsStatic m_wndTitleCOG;
	CSmsStatic m_wndTitleCPA;
	CSmsStatic m_wndTitleTCPA;
	CSmsStatic m_wndTitleType;
	CSmsStatic m_wndTitleMMSI;
	CSmsStatic m_wndTitleCall;

	CSmsStatic m_wndGRPAID;
	CSmsStatic m_wndGRPALat;
	CSmsStatic m_wndGRPALon;
	CSmsStatic m_wndGRPARNG;
	CSmsStatic m_wndGRPABRG;
	CSmsStatic m_wndGRPASOG;
	CSmsStatic m_wndGRPACOG;
	CSmsStatic m_wndGRPACPA;
	CSmsStatic m_wndGRPATCPA;
	CSmsStatic m_wndGRPAType;
	CSmsStatic m_wndGRPAMMSI;
	CSmsStatic m_wndGRPACall;

	CSmsStatic m_wndGRPBID;
	CSmsStatic m_wndGRPBLat;
	CSmsStatic m_wndGRPBLon;
	CSmsStatic m_wndGRPBRNG;
	CSmsStatic m_wndGRPBBRG;
	CSmsStatic m_wndGRPBSOG;
	CSmsStatic m_wndGRPBCOG;
	CSmsStatic m_wndGRPBCPA;
	CSmsStatic m_wndGRPBTCPA;
	CSmsStatic m_wndGRPBType;
	CSmsStatic m_wndGRPBMMSI;
	CSmsStatic m_wndGRPBCall;

	CSmsStatic m_wndGRPAUnitID;
	CSmsStatic m_wndGRPAUnitLAT;
	CSmsStatic m_wndGRPAUnitLon;
	CSmsStatic m_wndGRPAUnitRNG;
	CSmsStatic m_wndGRPAUnitBRG;
	CSmsStatic m_wndGRPAUnitSOG;
	CSmsStatic m_wndGRPAUnitCOG;
	CSmsStatic m_wndGRPAUnitCPA;
	CSmsStatic m_wndGRPAUnitTCPA;

	CSmsStatic m_wndGRPBUnitID;
	CSmsStatic m_wndGRPBUnitLAT;
	CSmsStatic m_wndGRPBUnitLon;
	CSmsStatic m_wndGRPBUnitRNG;
	CSmsStatic m_wndGRPBUnitBRG;
	CSmsStatic m_wndGRPBUnitSOG;
	CSmsStatic m_wndGRPBUnitCOG;
	CSmsStatic m_wndGRPBUnitCPA;
	CSmsStatic m_wndGRPBUnitTCPA;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
