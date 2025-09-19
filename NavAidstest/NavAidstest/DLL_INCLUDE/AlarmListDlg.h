#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsListCtrl.h"
#include "SmsStatic.h"

#include "AlarmTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CAlarmListDlg 대화 상자입니다.

class AFX_EXT_CLASS CAlarmListDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CAlarmListDlg)

public:
	CAlarmListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAlarmListDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:

protected:
	void UpdateActiveAlarm();
	void UpdateHistoryAlarm();
	void UpdateAlarmInfoToList(const UINT unIndex, const T_ALARM_INFO* const pAlarmInfo);
	void DeleteEmptyItem(const UINT unItemCount);
	void UpdateTotalCount(const UINT unTotalCount);
	void SetPageInfo();

	void UpdateSelectedListItem();

	void UpdateAlarmInfoDetail();

	void CalcPage(const UINT unAlarmCount);

	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedAlarmListCloseButton();
	afx_msg void OnBnClickedAlarmListActiveButton();
	afx_msg void OnBnClickedAlarmListHistoryButton();
	afx_msg void OnBnClickedAlarmListPageDownButton();
	afx_msg void OnBnClickedAlarmListPageUpButton();
	afx_msg void OnBnClickedAlarmListAckButton();
	afx_msg void OnNMClickAlarmListAlarmList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnNotifyAlarm(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateAlarmList(WPARAM, LPARAM lParam);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	//static const UINT m_unMAX_VIEW_LIST_NUM = 12U;
	static const UINT m_unMAX_VIEW_LIST_NUM = 20U;

	CSmsButton m_wndActive;
	CSmsButton m_wndHistory;
	CSmsButton m_wndAck;
	CSmsButton m_wndClose;
	CSmsButton m_wndPageUp;
	CSmsButton m_wndPageDown;

	CSmsListCtrl m_wndAlarmList;

	CSmsStatic m_wndTitleTotal;
	CSmsStatic m_wndTitleCount;
	CSmsStatic m_wndTitlePage;

	INT m_nViewAlarmType; // 0 = Active, 1 = History
	UINT m_unTotalPage;
	UINT m_unCurPage;

	T_ALARM_INFO* m_pSelAlarmInfo;
};
