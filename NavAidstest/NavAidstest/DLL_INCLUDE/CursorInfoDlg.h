#pragma once

#include "SmsBaseDlg.h"

#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CCursorInfoDlg 대화 상자입니다.

class AFX_EXT_CLASS CCursorInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CCursorInfoDlg)

public:
	CCursorInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCursorInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateCursorInfo(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dRange, const DOUBLE dBearing);
	void InitDispCusorInfor();

protected:
	void SetResourceColor();
	void SetResourceValue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:	
	CSmsStatic m_wndTitle;
	CSmsStatic m_wndLatStatic;
	CSmsStatic m_wndLonStatic;
	CSmsStatic m_wndRangeStatic;
	CSmsStatic m_wndBaringStatic;
	CSmsStatic m_wndLatUnit; 
	CSmsStatic m_wndLonUnit;
	CSmsStatic m_wndRangeUnit;
	CSmsStatic m_wndBearingUnit;

	CSmsStatic m_wndLatTitle;
	CSmsStatic m_wndLonTitle;
	CSmsStatic m_wndRngTitle;
	CSmsStatic m_wndBrgTitle;

	DOUBLE m_dLat;
	DOUBLE m_dLon;
	DOUBLE m_dRange;
	DOUBLE m_dBearing;
};