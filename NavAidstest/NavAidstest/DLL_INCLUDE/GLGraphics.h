#pragma once

#include <afxwin.h>
#include <afxmt.h>

#include "GraphicsDef.h"

#include "RadarDataDef.h"
#include "GeoCoord.h"
#include "UserCommandDef.h"
#include "TrackDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CGLGraphics
	{
	public:
		CGLGraphics();
		~CGLGraphics();

	public:
		static CGLGraphics* GetInstance();
		static void DeleteInstance();

		void SetHomeDirectory(const CString strHomeDirectory);

		void InitMain(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void InitSub(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void ResizeMain(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void ResizeSub(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void RenderMain(const E_VIEW_SCOPE eViewScope);
		void RenderSub(const E_VIEW_SCOPE eViewScope);
		
		void InitScope(const UINT unMaxAzimuthNum, const UINT unMaxRangeBins);
		void SetOrientationMode(E_SCOPE_ORIENTATION eOrientationMode);
		// Spoke  and Track Info
		BOOL UpdateSpokeData(const T_RADAR_SPOKE* const pSpokeData);
		void UpdateTrackData(const T_CONFIRMED_TRACK* const pTrackData);
		void UpdateSelectTrackData(const T_CONFIRMED_TRACK* const pFirstTrackData, const T_CONFIRMED_TRACK* const pSecondTrackData);
		void CalcTrackDraw();
		void CalcTrackDrawByID(UINT uID);
		void ResetEchoTrails();
		void ResetTargetTrails();
		void SetRPMValue(UINT m_uiRPMValue);
		void DeleteTrackData(const UINT unTrackID);
		void DeleteAllTrackData();
		void SetScopeViewParam(T_TRACKVIEW_CONTROL* pTrackView);
		// Virtual Track
		void UpdateVirtualTrack(const T_VIRTUAL_TRACK* const pVirtualTrack);
		void CalcVirtualDraw();
		void DeleteVirtualTrack(const UINT unTrackID);
		void DeleteAllVirtualTrack();
		void SetTrackInfoView(T_TRACKINFO_VIEW* const pTrackInfoView);

		void SetCenter();
		void SetCenterMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetCenterSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void GetCenter(DOUBLE& dLatDegree, DOUBLE& dLonDegree);
		void GetScopeCenterMain(const E_VIEW_SCOPE eViewScope, DOUBLE& dLatDegree, DOUBLE& dLonDegree);
		void GetScopeCenterSub(const E_VIEW_SCOPE eViewScope, DOUBLE& dLatDegree, DOUBLE& dLonDegree);
		void SetRadiusMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dRadiusMeter, const INT nNumRangeRing);
		void SetRadiusSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dRadiusMeter, const INT nNumRangeRing);
		void SetInitImage(BOOL m_blRanged);
		void GetRadiusMain(const E_VIEW_SCOPE eViewScope, DOUBLE& dRange);
		void GetRadiusSub(const E_VIEW_SCOPE eViewScope, DOUBLE& dRange);
		void SetRingViewMain(const E_VIEW_SCOPE eViewScope, const BOOL bViewStatus);
		void SetRingViewSub(const E_VIEW_SCOPE eViewScope, const BOOL bViewStatus);
		void SetMove(const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetOffCenter(const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetRotation(const DOUBLE dRotation);

		void SetOwnInfo(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dHDG, const DOUBLE dCOG);

		void SetGroupAreaShow(const BOOL bShow);
		void SetGroupArea(const DOUBLE dMinLat, const DOUBLE dMinLon, const DOUBLE dMaxLat, const DOUBLE dMaxLon);

		void SetVrmEblShow(const INT nIndex, const INT nShow);

		void SetVrmEbl(const INT nIndex, const DOUBLE dRange, const DOUBLE dBearing);

		void EnableChangeVrmEbl(const INT nIndex);
		void ChangeDrawLineType(const INT nIndex);
		void DisableChagneVrmEbl();
		void ChangeVrmEbl(const DOUBLE dRange, const DOUBLE dBearing);
		// Area Masking Process
		void ShowAreaMask(const BOOL bShow);
		void AddAreaMask(const INT nIndex, CPtrArray* const pParts);
		void DeleteAreaMask(const INT nIndex);
		void ModifyAreaMask(const INT nIndex, CPtrArray* const pParts);
		void RemoveAllAreaMask();
		void SetAreaMaskEditing(CPtrArray* const pParts);
		void ChangedAreaMaskEditing();
		// Guard Zone and User Map
		void SetEditOverlayEntity(const E_OVERLAY_EDIT_TYPE eEditType, T_OVERLAY_ENTITY* const pOverlayEntity);
		void ChangedOverlayEditing(const E_OVERLAY_EDIT_TYPE eEditType);
		void StartOverlayEditing(const E_OVERLAY_EDIT_TYPE eEditType, T_OVERLAY_ENTITY* const pOverlayEntity);
		void StopOverlayEditing();
		BOOL MoveOverlayEditPoint(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dRange, const DOUBLE dBearing);
		BOOL SetOverlayEditPoint(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dRange, const DOUBLE dBearing);
		
		void UpdateZoneOverlay(T_OVERLAY_ENTITY* pOverlayEntity);
		void UpdateZoneOverlayNull();
		void RemoveAllZoneOverlay();

		void UpdateUserMapOverlay(T_OVERLAY_ENTITY* pOverlayEntity);
		void UpdateUserMapOverlayNull();

		void DeleteUserMapOverlay(const USHORT usIndex);
		void RemoveAllUserMapOverlay();

		void SetDefineColor(const COLORREF clrFace, const COLORREF clrText, COLORREF (&clrDefColor)[g_nMAX_USER_DEFINE_COLOR_NUM]);

		void GetRangeBearing(const DOUBLE dLat, const DOUBLE dLon, DOUBLE& dRange, DOUBLE& dBearing);
		void GetGeoPosition(const DOUBLE dLat, const DOUBLE dLon, DOUBLE& dX, DOUBLE& dY);

		void MouseMove(CPoint& point);
		void MouseClick(const E_MOUSE_ACT_TYPE eMouseType, CPoint& point);

		DOUBLE GetScreenRatio(const DOUBLE dRange);
		DOUBLE GetMetersPerPixel();

	private:
		void CalcViewportMain(const E_VIEW_SCOPE eViewScope);
		void CalcViewportSub(const E_VIEW_SCOPE eViewScope);
		void InitGLMain(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void InitGLSub(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void ResizeGLMain(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void ResizeGLSub(const E_VIEW_SCOPE eViewScope, const HWND hWnd);
		void RenderGLMainScope();
		void RenderGLSubScope();
		void SetRadiusGLMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dRadiusMeter, const INT nNumRangeRing);
		void SetRadiusGLSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dRadiusMeter, const INT nNumRangeRing);
		void SetCenterGLMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dLat, const DOUBLE dLon);
		void SetCenterGLSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dLat, const DOUBLE dLon);
		void SetMoveGLMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetMoveGLSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetOffCenterGLMain(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void SetOffCenterGLSub(const E_VIEW_SCOPE eViewScope, const DOUBLE dLatDegree, const DOUBLE dLonDegree);
		void MoveCenterGLMain(const E_VIEW_SCOPE eViewScope);
		void MoveCenterGLSub(const E_VIEW_SCOPE eViewScope);
		void SetDefineColorGLMain(const E_VIEW_SCOPE eViewScope);
		void SetDefineColorGLSub(const E_VIEW_SCOPE eViewScope);
		void SetOwnPosGL(const DOUBLE dLat, const DOUBLE dLon, const DOUBLE dHDG, const DOUBLE dCOG);
		
		void ProcMouseAction(const E_MOUSE_ACT_TYPE eMouseType, const LONG lX, const LONG lY);

		void StartGraphicCommandProcThread();
		void TerminateGraphicCommandProcThread();

		void MainScopeGraphicCmdProc();
		static UINT MainScopeGraphicCmdProcThread(LPVOID const lpParam);

		void SubScopeGraphicCmdProc();
		static UINT SubScopeGraphicCmdProcThread(LPVOID const lpParam);

		void LockRenderMain(const E_VIEW_SCOPE eViewScope);
		void LockRenderSub(const E_VIEW_SCOPE eViewScope);
		void UnlockRenderMain(const E_VIEW_SCOPE eViewScope);
		void UnlockRenderSub(const E_VIEW_SCOPE eViewScope);

	private:
		static CGLGraphics* m_pInstance;

		CString m_strHomeDirectory;
		BOOL m_bFontInitialized;

		E_SCOPE_ORIENTATION m_eOrientationMode;

		T_GEO_POS2D m_tOriginalCenter;		// 
		T_GEO_POS2D m_tCenter[g_nMAX_VIEW_SCOPE];
		DOUBLE m_dScopeMoveX;			// Original Center에서 이동 센터 xy
		DOUBLE m_dScopeMoveY;
		DOUBLE m_dScopeOffX;
		DOUBLE m_dScopeOffY;
		DOUBLE m_dScopeRotation;
		T_GEO_RECT m_tWorldViewPort[g_nMAX_VIEW_SCOPE];

		T_OWNSHIP_INFO m_tOwnshipInfo;

		COLORREF m_clrFace;
		COLORREF m_clrText;
		COLORREF m_clrUserDefColor[g_nMAX_USER_DEFINE_COLOR_NUM];

		E_OVERLAY_EDIT_TYPE m_eOverlayEditType;

		DOUBLE m_dRadius[g_nMAX_VIEW_SCOPE];			// 반경, meter
		INT m_nNumRangeRing[g_nMAX_VIEW_SCOPE];			// 링 개수
		DOUBLE m_dMetersPerPixel[g_nMAX_VIEW_SCOPE];	// Pixel Resolution

		UINT m_unPrevScanCount;
		UINT m_unPrevSectorIndex;

		UINT m_unCurScanCount;
		UINT m_unCurSectorIndex;

		BOOL m_bEmptyVideoImage;

		HANDLE m_hExitGraphicCmdProcEventMain;
		CWinThread* m_pGraphicCmdProcThreadMain;

		HANDLE m_hExitGraphicCmdProcEventSub;
		CWinThread* m_pGraphicCmdProcThreadSub;

		CCriticalSection* m_pRenderCSMain;
		CCriticalSection* m_pRenderCSSub;

		INT m_iDrawLineType;
	};
}	// NS_SALUS_MS_APP

