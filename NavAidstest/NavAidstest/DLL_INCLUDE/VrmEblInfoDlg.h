#pragma once

#include "SmsBaseDlg.h"

#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CVrmEblInfoDlg 대화 상자입니다.
class AFX_EXT_CLASS CVrmEblInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CVrmEblInfoDlg)

public:
	CVrmEblInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVrmEblInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void ChangeShowStatus(INT nIndex, BOOL bShow);
	void ChangeSetStatus(INT nIndex, BOOL bShow);
	void UpdateVRMEBL(INT nIndex, DOUBLE dRange, DOUBLE dBearing,BOOL bSet);

protected:
	void SetResourceColor();

	void UpdateVRM(INT nIndex);
	void UpdateEBl(INT nIndex);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
	
private:
	static const INT m_nMAX_VRMEBL_NUM = 2;

	BOOL m_bShowVRMEBL[m_nMAX_VRMEBL_NUM];
	BOOL m_bSetVRMEBL[m_nMAX_VRMEBL_NUM];
	DOUBLE m_dRangeVRM[m_nMAX_VRMEBL_NUM];
	DOUBLE m_dBearingEBl[m_nMAX_VRMEBL_NUM];

	CSmsStatic m_wndTitle;
	CSmsStatic m_wndVrmValue[m_nMAX_VRMEBL_NUM];
	CSmsStatic m_wndEblValue[m_nMAX_VRMEBL_NUM];
	CSmsStatic m_wndVrmUnit[m_nMAX_VRMEBL_NUM];
	CSmsStatic m_wndEblUnit[m_nMAX_VRMEBL_NUM];

	CSmsStatic m_wndEBL1Title;
	CSmsStatic m_wndEBL2Title;
	CSmsStatic m_wndVRM1Title;
	CSmsStatic m_wndVRM2Title;
};
