#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// COwnshipInfoDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS COwnshipInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(COwnshipInfoDlg)

public:
	COwnshipInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COwnshipInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateOwnshipInfo(const T_OWNSHIP_INFO* const pOwnshipInfo);

protected:
	void UpdateOwnshipInfo();
	void UpdateSystemTime();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnUpdateDialogInfo(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);

	void SetResourceColor();

	DECLARE_MESSAGE_MAP()

private:
	CSmsStatic m_wndSiteID;
	CSmsStatic m_wndTimeUnit;
	CSmsStatic m_wndDate;
	CSmsStatic m_wndTime;
	CSmsStatic m_wndLat;
	CSmsStatic m_wndLatUnit;
	CSmsStatic m_wndLon;
	CSmsStatic m_wndLonUnit;
	CSmsStatic m_wndGeodetic;

	CSmsStatic m_wndTitle;
	CSmsStatic m_wndID;
	CSmsStatic m_wndLAT;
	CSmsStatic m_wndLON;

	T_OWNSHIP_INFO m_tOwnshipInfo;
};
