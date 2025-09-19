#pragma once

#include "SmsBaseDlg.h"
#include "EnvBaseDlg.h"
#include "SmsButton.h"
#include "SmsStatic.h"
#include "EnvSetDef.h"
#include "UserCommandDef.h"
#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

// CEnvMenuSetDlg 대화 상자입니다. (2021-02-03 ~)
// - 설명 :
//		환경설정 다이얼로그를 2ndScope 영역에 출력합니다.
//		BGimage, Tab button, Dlgframe 으로 구성되어 있습니다.
//

class AFX_EXT_CLASS CEnvMenuSetDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CEnvMenuSetDlg)

public:
	CEnvMenuSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEnvMenuSetDlg();
	virtual BOOL Create(CWnd* pParentWnd);
	
public:
	void UpdateSelectedPosition(CWnd* const pEventWnd, const DOUBLE dLat, const DOUBLE dLon);
	void SetReportWindow(CWnd* pReportWnd);
	E_ENV_MODE GetSelectedTab();

	void GetDisplayConfig(T_DISPLAY_CONFIG* const pDisplayConfig);
	void SetDisplayConfig(T_DISPLAY_CONFIG* const pDisplayConfig);

	void GetSignalProcConfig(T_SIGNAL_PROC_CONFIG* const pSignalProcConfig);
	void SetSignalProcConfig(const T_SIGNAL_PROC_CONFIG* const pSignalProcConfig);
	void GetTrackingConfig(T_TRACKING_CONFIG* const pTrackingConfig);
	void SetTrackingConfig(const T_TRACKING_CONFIG* const pTrackingConfig);
	void UpdateSimradSetup(const T_SIMRAD_STATE_SETUPDATA* const pSimradSetupData);
	void UpdateSimradSetupExtend(const T_SIMRAD_STATE_SETUPEXTENDDATA* const pSimradSetupExtendData);
	void UpdateSimradSetupConfiguration(const T_SIMRAD_STATE_SETUPCONFIGURATION* const pSimradSetupConfigurationData);
	void UpdateSimradSetupAdvanced(const T_SIMRAD_STATE_ADVANCED* const pSimradSetupAdvancedData);
	void UpdateSimradMode(UINT m_eMode);
	void UpdateSimradAllValue(T_SIMRAD_SAVE_DATA* m_tSimradConfig);
	void SimradSector0Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradSector1Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradSector2Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradSector3Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradSector4Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradSector5Value(UINT* value1, UINT* value2, UINT* value3, UINT* value4);
	void SimradAntParkPosValue(UINT* value);
	void SimradAntHeightValue(INT* value);
	void SimradAntOffsetValue(INT* value1, INT* value2);
	void SimradZeroRangeOffsetValue(UINT* value);
	void SimradZeroBearingOffsetValue(INT* value);
	void SimradAntTypeValue(UINT* value);
	void SimradFTCVlue(UINT value);

protected:
	void ChangeChildDlg(E_ENV_MODE eVisibleMode);					// 자식창 열기 [nVisibleMode = eENV_MODE]

	void SetEnvMenuConfig(E_ENV_MODE eClicked);
	void GetEnvMenuConfig(E_ENV_MODE eClicked);
	void Wait(DWORD dwMillisecond);
	void SetResourceColor();
	void SetResourcePos();
	void SendMessageToParentMSG(const UINT unMessage);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedEnvMenuSettingPpiRadio();
	afx_msg void OnBnClickedEnvMenuSettingColRadio();
	afx_msg void OnBnClickedEnvMenuSettingAlrmRadio();
	afx_msg void OnBnClickedEnvMenuSettingMaskRadio();
	afx_msg void OnBnClickedEnvMenuSettingZoneRadio();
	afx_msg void OnBnClickedEnvMenuSettingUserMapRadio();
	afx_msg void OnBnClickedEnvMenuSettingSignalConfigRadio();
	afx_msg void OnBnClickedEnvMenuSettingTrackConfigRadio();
	afx_msg void OnBnClickedEnvMenuSettingRadarInterfaceButton();
	afx_msg void OnBnClickedEnvMenuSettingAisInterfaceButton();
	afx_msg void OnBnClickedEnvMenuSettingGpsInterfaceButton();
	afx_msg void OnBnClickedEnvMenuSettingSaveButton();
	afx_msg void OnBnClickedEnvMenuSettingCloseButton();
	afx_msg LRESULT OnChangeColorConfig(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradRPMValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradScanPwrValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTransmitValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimraduseModeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradFastScanValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradBeamSharpValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradVideoApertureValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradIRLevelValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradLocalIRValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTargetBoostValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTargetStretchValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTargetLegacyValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradCurveTypeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradGainValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradRainValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradNoiseRejectValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradFTCValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSeaLegacyValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimraSeaLegacyModeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSeaValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSeaModeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSeaAutoOffsetValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSeaCombinedValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSideLobeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSideLobeModeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTransmitPeriodValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradStandbyPeriodValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradTimeTransmitEnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradGainModeValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradAllValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector0EnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector1EnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector2EnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector3EnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector4EnabledValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector5EnabledValue(WPARAM, LPARAM);
	
	afx_msg LRESULT OnChangeSimradSector0StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector1StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector2StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector3StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector4StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector5StartValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector0EndValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector1EndValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector2EndValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector3EndValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector4EndValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradSector5EndValue(WPARAM, LPARAM);
	
	afx_msg LRESULT OnChangeSimradParkPosValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradAntHeightValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradAntXOffsetValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradAntYOffsetValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradZeroRangeOffsetValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradZeroBearingOffsetValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradResetToFactoryValue(WPARAM, LPARAM);
	afx_msg LRESULT OnChangeSimradAntTypeValue(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

private:
	CWnd* m_pReportWnd;									// Main PPI-Scope's CGLView
	CSmsButton	m_wndTabRadio[g_nMAX_ENV_MODE];			// Setting창의 탭 버튼
	CSmsButton	m_wndCloseButton;						// X 버튼 (창 닫기 버튼)
	CSmsButton	m_wndSaveButton;						// SET 버튼 (저장)

	INT m_nButtonWidth;
	INT m_nButtonHeight;

	E_ENV_MODE m_eCurEnvMode;							// 현재 선택된 탭 [eENV_MODE]

	CEnvBaseDlg* m_pChildDlgList[g_nMAX_ENV_MODE];		// 탭별 표시되는 다이얼로그
	CRect m_rtChildDlgPos;

	T_DISPLAY_CONFIG m_tDisplayConfig;
	T_GUARD_ZONE_INFO m_tGuardZoneInfo;
	T_SIGNAL_PROC_CONFIG m_tSignalProcConfig;
	T_TRACKING_CONFIG m_tTrackingConfig;
	T_NET_RADAR_INF_CONFIG m_tNetRadarConfig;
	T_AIS_CONFIG m_tNetAisConfig;
	T_GPS_CONFIG m_tNetGpsConfig;
	T_SIMRAD_SAVE_DATA m_tSimradConfig;

	CSmsStatic m_wndTitle;
};