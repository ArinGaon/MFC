#pragma once

#include <afxdialogex.h>
#include <afxbutton.h>

#include "SmsBaseDlg.h"
#include "SmsBaseDef.h"

using namespace NS_SALUS_MS_APP;

class CEnvBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnvBaseDlg)
public:
	CEnvBaseDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	~CEnvBaseDlg();

public:
	virtual void UpdateSelectedPosition(const DOUBLE dLat, const DOUBLE dLon) = 0;

protected:
	void SetButtonImage(CMFCButton* const pButton, CImage* const pButtonImage);
	void SendMessageToParent(const UINT unMessage);

protected:	
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

protected:
	E_DIALOG_COLOR_TYPE m_eColorType;

	INT m_nScrollPos;
	CRect m_rtVisibleRect;		// (left : x, top : y, right : cx, bottom :cy)
	CRect m_rtOriginalRect;		// (left : x, top : y, right : cx, bottom :cy)
public:
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


