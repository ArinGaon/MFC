#pragma once

#include "SmsBaseDlg.h"
#include "SmsStatic.h"

#include "TrackDataDef.h"

using namespace NS_SALUS_MS_APP;

// CTrackReportDlg 대화 상자입니다.

class AFX_EXT_CLASS CTrackReportDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CTrackReportDlg)


public:
	CTrackReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTrackReportDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void UpdateReport(const T_CONFIRMED_TRACK* const pTrackInfo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	void SetResourceColor();

	CSmsStatic m_wndTrackID;
	CSmsStatic m_wndTrackType;
	CSmsStatic m_wndExpHeading;
	CSmsStatic m_wndExpPosAccuracy;
	CSmsStatic m_wndExpRotation;
	CSmsStatic m_wndExpSensor;
	CSmsStatic m_wndNaviDST;
	CSmsStatic m_wndNaviETA;
	CSmsStatic m_wndNaviStatus;
	CSmsStatic m_wndShipDraught;
	CSmsStatic m_wndShipIMO;
	CSmsStatic m_wndShipLength;
	CSmsStatic m_wndShipMMSI;
	CSmsStatic m_wndShipName;
	CSmsStatic m_wndShipType;
	CSmsStatic m_wndShipWidth;

	CSmsStatic m_wndTItleExpInfo;
	CSmsStatic m_wndTItleROT;
	CSmsStatic m_wndTItleHDG;
	CSmsStatic m_wndTItlePOSA;
	CSmsStatic m_wndTItleSensor;
	CSmsStatic m_wndTItleAISClass;
	CSmsStatic m_wndTItleShipInfo;
	CSmsStatic m_wndTItleName;
	CSmsStatic m_wndTItleMMSI;
	CSmsStatic m_wndTItleIMO;
	CSmsStatic m_wndTItleShip;
	CSmsStatic m_wndTItleNavInfo;
	CSmsStatic m_wndTItleDST;
	CSmsStatic m_wndTItleETA;
	CSmsStatic m_wndTItleStatus;

	CSmsStatic m_wndTItlLength;
	CSmsStatic m_wndTItWidth;
	CSmsStatic m_wndTItDraught;

	CSmsStatic m_wndUnitROT;
	CSmsStatic m_wndUnitHDG;
	CSmsStatic m_wndUnitLength;
	CSmsStatic m_wndUnitWidth;
	CSmsStatic m_wndUnitDraught;
	CSmsStatic m_wndAISClass;
public:
	afx_msg void OnPaint();
};
