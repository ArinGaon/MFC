#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsStatic.h"

#include "AlarmListDlg.h"
#include "AlarmTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CArpaAlarmInfoDlg 대화 상자입니다.

class AFX_EXT_CLASS CArpaAlarmInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CArpaAlarmInfoDlg)

public:
	CArpaAlarmInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CArpaAlarmInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedArpaAlarmInfoSoundButton();
	afx_msg void OnBnClickedArpaAlarmInfoVolumeDownButton();
	afx_msg void OnBnClickedArpaAlarmInfoVolumeUpButton();
	afx_msg void OnBnClickedArpaAlarmInfoListButton();
	afx_msg LRESULT OnNotifyAlarm(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateAlarmCount(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	void ArrangeResourceControls();
	void ApplyResourceFont();
	void SetResourceColor();
	void SetResourceImage();

	void DrawAlarmPicture(const E_ALARM_TYPE eAlarmType);
	void ClearAlarm();

	void ChangeSoundStatus();
	void ChangeVolumeStatus();

	void SetWindowAudioMute(const BOOL bSound);

	void SetButtonImage(CMFCButton* const pButton, CImage* const pButtonImage);
	
private:
	static const INT m_nMaxVolumeLevel = 5;

	CSmsStatic m_wndTitle;

	CSmsStatic m_wndMsg;
	CSmsStatic m_wndCreateTime;

	CSmsButton m_wndSound;
	CSmsButton m_wndVolumeDown;
	CSmsButton m_wndVolumeUp;
	CSmsButton m_wndVolumeStatus;

	CSmsStatic m_wndFaultCount;
	CSmsStatic m_wndWarningCount;
	CSmsStatic m_wndCautionCount;
	CSmsButton m_wndListButton;

	CAlarmListDlg* m_pAlarmListDlg;			// Alarm List Dlg

	COLORREF m_clrDlgFace;

	INT m_nVolumeLevel;
	BOOL m_bSoundOn;			// TRUE: Sound On, FALSE : Mute(음소거)

	INT m_nImageWidth;
	INT m_nImageHeight;

	UINT_PTR m_unClearAlarmTimer;
	UINT m_unClearAlarmDelay;
};
