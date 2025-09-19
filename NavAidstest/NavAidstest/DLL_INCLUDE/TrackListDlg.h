#pragma once

#include "SmsBaseDlg.h"

#include "SmsListCtrl.h"
#include "SmsButton.h"
#include "SmsStatic.h"
#include "SmsGroupBox.h"
#include "SmsEdit.h"

#include "TrackDataDef.h"

using namespace NS_SALUS_MS_APP;

// CTrackListDlg 대화 상자입니다.

class AFX_EXT_CLASS CTrackListDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CTrackListDlg)

public:
	CTrackListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTrackListDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void SetResourceColor();

	void AdjustListItemCount(UINT unTrackCount);

	void UpdateTrackInfo(INT nItemIndex, T_CONFIRMED_TRACK* pTrackInfo);
	void UpdateSelTrackInfo(T_CONFIRMED_TRACK* pTrackInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedTrackListCloseButton();
	afx_msg void OnBnClickedTrackListTagSet();
	afx_msg void OnLvnEndScrollTrackListList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnItemChangedTrackListList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnUpdateTrackData(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeDisplayConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateTrackList(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateSelTrackInfo(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	static const UINT m_unMAX_VIEW_ITEM_NUM = 22U;

	
	CSmsButton m_wndCloseButton;
	CSmsListCtrl m_wndTrackList;
	CSmsGroupBox m_wndGroupBox;
	CSmsStatic m_wndTrackNo;
	CSmsEdit m_wndTrackTag;
	CSmsButton m_wndTrackTagSet;

	CSmsStatic m_wndTotalCount;
	CSmsStatic m_wndTitle;
	CSmsStatic m_wndTitleTotal;

	INT m_nSelTrackIndex;
};

	
	
