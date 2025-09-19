#pragma once

#include "SmsBaseDlg.h"
#include "SmsButton.h"
#include "SmsListCtrl.h"
#include "SmsEdit.h"
#include "SmsComboBox.h"
#include "SmsGroupBox.h"
#include "SmsStatic.h"

using namespace NS_SALUS_MS_APP;

// CVirtualTrackCtrlDlg 대화 상자

class AFX_EXT_CLASS CVirtualTrackCtrlDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CVirtualTrackCtrlDlg)

public:
	CVirtualTrackCtrlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVirtualTrackCtrlDlg();
	virtual BOOL Create(CWnd* pParentWnd);

	void SetUpdateValue(double lat, double lon, double range, double bearing);
protected:
	void AddVirtualList(const UINT unTrackID);
	void DeleteVirtualList(const INT nIndex);
	void ModifyVirtualList(const INT nIndex);

	void ChangeTrackActivate(const UINT unTrackID, const INT nChecked);
	void UpdateSettingInfo(const UINT unTrackID);
	void UpdateTrackInfo();
	void InitTrackInfo();

	void SendVirtualControlStatus(BOOL bStatus);

	void SetResourceColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedVirtualTrackCloseButton();
	afx_msg void OnBnClickedVirtualTrackPlayButton();
	afx_msg void OnBnClickedVirtualTrackStopButton();
	afx_msg void OnLVNItemChangedVirtualTrackList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeVirtualTrackRangeEdit();
	afx_msg void OnEnChangeVirtualTrackAzimuthEdit();
	afx_msg void OnEnChangeVirtualTrackSogEdit();
	afx_msg void OnEnChangeVirtualTrackCogEdit();
	afx_msg void OnBnClickedVirtualTrackAddButton();
	afx_msg void OnBnClickedVirtualTrackDelButton();
	afx_msg void OnBnClickedVirtualTrackModButton();
	afx_msg void OnBnClickedVirtualTrackResetButton();
	afx_msg void OnBnClickedVirtualTrackScreenButton();

	afx_msg void OnBnClickedVTAutoManualRadio();

	afx_msg LRESULT OnUpdateVirtualTrack(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnUpdateVTPosValue(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

	void SendMessageToParent(const UINT unMessage);
private:
	CSmsButton m_wndCloseButton;
	CSmsListCtrl m_wndTrackList;			// Virtual List 컨트롤
	CPtrArray m_pVirtualTrack;				// Virtual Target 데이터

	CSmsButton m_wndPlayButton;
	CSmsButton m_wndStopButton;
	CSmsButton m_wndAddButton;
	CSmsButton m_wndDelButton;
	CSmsButton m_wndModButton;
	CSmsButton m_wndResetButton;

	CSmsStatic m_wndTrackID;
	CSmsEdit m_wndRangeEdit;
	CSmsEdit m_wndAzimuthEdit;
	CSmsEdit m_wndSogEdit;
	CSmsEdit m_wndCogEdit;

	CSmsEdit m_wndOrigin1Edit;
	CSmsEdit m_wndOrigin2Edit;
	CSmsComboBox m_wndOrigin1Dir;
	CSmsComboBox m_wndOrigin2Dir;
	CSmsButton m_wndCtlScrBtn;

	CSmsButton m_wndAutoPosRadio;
	CSmsButton m_wndManualPosRadio;

	CSmsGroupBox m_wndVirtualtrackGrp;

	FLOAT m_fRange;
	FLOAT m_fAzimuth;
	FLOAT m_fSOG;
	FLOAT m_fCOG;
	
	UINT m_uiRangeUnit;
	UINT m_uiSpeedUnit;

	CSmsStatic m_wndTItle;
	CSmsStatic m_wndTItleID;
	CSmsStatic m_wndTItleRange;
	CSmsStatic m_wndTItleSOG;
	CSmsStatic m_wndTItleAzimuth;
	CSmsStatic m_wndTItleCOG;
	CSmsStatic m_wndTItleLAT;
	CSmsStatic m_wndTItleLON;
	CSmsStatic m_wndTItleUnitRange;
	CSmsStatic m_wndTItleUnitSOG;
	CSmsStatic m_wndTItleUnitAzimuth;
	CSmsStatic m_wndTItleUnitCOG;

	void SetResourceImage();

	CBrush m_brush;

	double m_dblLat;
	double m_dblLon;
public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
