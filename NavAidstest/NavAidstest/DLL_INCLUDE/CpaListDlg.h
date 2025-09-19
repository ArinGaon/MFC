#pragma once

#include "SmsBaseDlg.h"

#include "SmsListCtrl.h"
#include "SmsButton.h"
#include "SmsStatic.h"

#include "TrackDataDef.h"

using namespace NS_SALUS_MS_APP;

// CCpaListDlg 대화 상자입니다.

class AFX_EXT_CLASS CCpaListDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CCpaListDlg)

public:
	CCpaListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCpaListDlg();
	virtual BOOL Create(CWnd* pParentWnd);

	void AddCPAList();
public:
	void UpdateSelectedTrackID(const UINT unTrackID);
	void UpdateSelectedTrackID1(const UINT unTrackID);
	void UpdateSelectedTrackID2(const UINT unTrackID);
	void OnCpaListDelAll();
protected:
	void AddCpaList();
	void DeleteCpaList(INT nIndex);
	void ModifyCpaList(INT nIndex);
	void UpdateSequence();

	void UpdateCpaTrack(const INT nIndex, T_CPA_TRACK* const pCpaTrack);


	void SetResourceColor();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCpaListCloseButton();
	afx_msg void OnLVNItemChangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCpaListDelButton();

	afx_msg LRESULT OnUpdateTrackData(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
	
private:
	CSmsListCtrl m_wndList;
	CSmsButton m_wndDelButton;
	CSmsButton m_wndCloseButton;
	
	UINT m_unTrackID1;
	UINT m_unTrackID2;

	INT m_nSelectTrackIndex;

	int OnCheckEditBoxStr(CString strValue);

	CString m_strOldId1;
	CString m_strOldId2;

	CSmsStatic m_wndTitle;
};

	
	
