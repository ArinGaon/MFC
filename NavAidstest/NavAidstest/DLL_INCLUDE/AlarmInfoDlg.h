#pragma once

#include "SmsBaseDlg.h"

#include "SmsButton.h"
#include "SmsStatic.h"

#include "AlarmListDlg.h"
#include "AlarmTypeDef.h"

using namespace NS_SALUS_MS_APP;

#define WM_COMM_ALARM (WM_USER + 3)

// CAlarmInfoDlg 대화 상자입니다.

class AFX_EXT_CLASS CAlarmInfoDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CAlarmInfoDlg)

public:
	CAlarmInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAlarmInfoDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	afx_msg LRESULT  OnUpdateAlarmCountFromAck(WPARAM ,LPARAM );

protected:
	void SetResourceColor();
	void SetResourceImage();
	void SetResourcePos();

	void DrawAlarmPicture(const E_ALARM_TYPE eAlarmType);
	void ClearAlarm();

	void ChangeSoundStatus();
	void ChangeVolumeStatus();

	void SetWindowAudioMute(const BOOL bSound);

	void SetButtonImage(CMFCButton* const pButton, CImage* const pButtonImage);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAlarmInfoSoundButton();
	afx_msg void OnBnClickedAlarmInfoVolumeDownButton();
	afx_msg void OnBnClickedAlarmInfoVolumeUpButton();
	afx_msg void OnBnClickedAlarmInfoListButton();
	afx_msg LRESULT OnNotifyAlarm(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateAlarmCount(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
	
private:
	static const INT m_nMaxVolumeLevel = 5;

	CSmsStatic m_wndTitleAlarm;
	CSmsStatic m_wndTitle;
	CSmsStatic m_wndCreateTime;

	CSmsButton m_wndSound;
	CSmsButton m_wndVolumeUp;
	CSmsButton m_wndVolumeDown;
	CSmsButton m_wndVolumeStatus;

	CSmsStatic m_wndFaultCount;
	CSmsStatic m_wndWarningCount;
	CSmsStatic m_wndCautionCount;
	CSmsButton m_wndListButton;

	CAlarmListDlg* m_pAlarmListDlg;			// Alarm List Dlg

	COLORREF m_clrDlgFace;

	BOOL m_bSoundOn;			// TRUE: Sound On, FALSE : Mute(음소거)
	INT m_nVolumeLevel;

	INT m_nImageWidth;
	INT m_nImageHeight;

	UINT_PTR m_unClearAlarmTimer;
	UINT m_unClearAlarmDelay;
public:
	afx_msg void OnPaint();
};
