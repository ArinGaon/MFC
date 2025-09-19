#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "TrackDataDef.h"

using namespace NS_SALUS_MS_APP;

enum class eTrackPriority : UCHAR
{
	eTrackPrimary = 0U,
	eTrackSecondary,
	eMAX_TRACK
};

// CPA
typedef struct _sCPAData{
	UINT	TgtID[2];
	FLOAT	Tgt_X[2];
	FLOAT	Tgt_Y[2];
	FLOAT	Tgt_Vx[2];
	FLOAT	Tgt_Vy[2];

	FLOAT	CPA;
	FLOAT	TCPA;
	
	FLOAT	BCR;
	FLOAT	BCT;
} sCPAData;

// CArpaTrackInfoDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CArpaTrackInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaTrackInfoDlg)

public:
	CArpaTrackInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CArpaTrackInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);		

public:
	void UpdateTrackInfo(const T_CONFIRMED_TRACK* const pTrackData1, const T_CONFIRMED_TRACK* const pTrackData2, const T_CPA_TRACK* const pCpaTrack1, const T_CPA_TRACK* const pCpaTrack2);

protected:
	void UpdateTrackInfoGroupA();
	void UpdateTrackInfoGroupB();
	void UpdateAisInfoGroupA();
	void UpdateAisInfoGroupB();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnUpdateDialogInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void ArrangeResourceControls();			// Arrange controls in dialog
	void ApplyResourceFont();				// Change the font in OnInitDialog();

	void SetResourceColor();

private:
	CSmsStatic m_wndTitle;

	static const INT m_nMAX_DISP_TRACK_DATA = 2;
	static const INT m_nMAX_DISP_TRACK_TYPE = 3;

	E_TRACK_TYPE m_eSelectedTrackType;		// RDR/AIS/MIX �� ���õ� Ÿ��

	BOOL m_bIsValidTrackInfo[m_nMAX_DISP_TRACK_DATA];
	BOOL m_bIsValidCpaInfo[m_nMAX_DISP_TRACK_DATA];
	T_CONFIRMED_TRACK* m_pConfirmTrack[m_nMAX_DISP_TRACK_DATA];
	T_CPA_TRACK* m_pCpaTrack[m_nMAX_DISP_TRACK_DATA];
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
