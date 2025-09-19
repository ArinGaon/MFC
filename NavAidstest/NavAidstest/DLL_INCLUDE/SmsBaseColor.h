#pragma once

#include <winnt.h>

#include "SmsBaseDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsBaseColor
	{
	public:
		CSmsBaseColor() noexcept;
		~CSmsBaseColor();

	public:
		static CSmsBaseColor* GetInstance();
		static void DeleteInstance();

		void SetColorSet(const E_COLOR_SET eColorSet);

		E_COLOR_SET GetColorSet();

		COLORREF GetGreenColor();
		COLORREF GetRedColor();
		COLORREF GetOrangeColor();
		COLORREF GetYellowColor();
		COLORREF GetBlueColor();

		COLORREF GetFace();
		COLORREF GetDialogFace(const E_DIALOG_COLOR_TYPE eDlgColorType);
		COLORREF GetDialogText();
		COLORREF GetDivision(const E_DIALOG_COLOR_TYPE eDlgColorType);

		COLORREF GetTitleText();

		void GetEdit(COLORREF& clrFace, COLORREF& clrText);
		void GetButton(COLORREF& clrFace, COLORREF& clrText);
		void GetButtonSel(COLORREF& clrFace, COLORREF& clrText);
		void GetButtonHoverFrame(COLORREF& clrFrame);
		void GetSlider(COLORREF& clrFace, COLORREF& clrThumb);
		void GetDisabled(COLORREF& clrFace, COLORREF& clrText);
		void GetList(COLORREF& clrFace1, COLORREF& clrFace2, COLORREF& clrHead, COLORREF& clrText);

		COLORREF GetPPIFace();

		E_COLOR_GROUP_KIND GetColorGroupKind();
		void SetColorGroupKind(const E_COLOR_GROUP_KIND eColorGroup);

		void SetUserDefineColor(const E_COLOR_GROUP_KIND eGroupKind, const E_USER_COLOR_IDX eUserDefine, const COLORREF clrUserColor);
		COLORREF GetUserDefineColor(const E_COLOR_GROUP_KIND eGroupKind, const E_USER_COLOR_IDX eUserDefine);
		void GetDefineColor(COLORREF (&clrDefColor)[g_nMAX_USER_DEFINE_COLOR_NUM]);

	private:
		void SetColorSet();
		void SetDefaultUserColor();

	private:
		static CSmsBaseColor* m_pInstance;

		static const COLORREF m_clrNight1 = RGB(0, 0, 0);
		static const COLORREF m_clrNight2 = RGB(30, 30, 30);
		static const COLORREF m_clrNight3 = RGB(50, 50, 50);
		static const COLORREF m_clrNight4 = RGB(100, 100, 100);
		static const COLORREF m_clrNight5 = RGB(160, 160, 160);
		static const COLORREF m_clrNight6 = RGB(190, 190, 190);
		static const COLORREF m_clrNight7 = RGB(255, 255, 255);

		static const COLORREF m_clrDay1 = RGB(0, 0, 0);
		static const COLORREF m_clrDay2 = RGB(70, 70, 70);
		static const COLORREF m_clrDay3 = RGB(170, 170, 170);
		static const COLORREF m_clrDay4 = RGB(210, 210, 210);
		static const COLORREF m_clrDay5 = RGB(230, 230, 230);
		static const COLORREF m_clrDay6 = RGB(245, 245, 245);
		static const COLORREF m_clrDay7 = RGB(255, 255, 255);

		static const COLORREF m_clrA1 = RGB(0, 195, 0);		// Green
		static const COLORREF m_clrA2 = RGB(255, 0, 0);		// Red
		static const COLORREF m_clrA3 = RGB(255, 120, 0);	// Orange
		static const COLORREF m_clrA4 = RGB(255, 240, 0);	// Yellow
		static const COLORREF m_clrA5 = RGB(0, 235, 255);	// Blue

		static const INT m_nMaxImageNum = 6;

		E_COLOR_SET m_eCurColorSet;
		COLORREF m_clrFace;
		COLORREF m_clrLightDlgFace;
		COLORREF m_clrDarkDlgFace;
		COLORREF m_clrTitleText;
		COLORREF m_clrText;

		COLORREF m_clrLightDivision;
		COLORREF m_clrDarkDivision;

		COLORREF m_clrEditFace;
		COLORREF m_clrEditText;

		COLORREF m_clrButtonFace;
		COLORREF m_clrButtonText;

		COLORREF m_clrButtonSelFace;
		COLORREF m_clrButtonSelText;
		COLORREF m_clrButtonHoverFrame;

		COLORREF m_clrDisabledFace;
		COLORREF m_clrDisabledText;

		COLORREF m_clrListFace1;
		COLORREF m_clrListFace2;
		COLORREF m_clrListHeadFace;
		COLORREF m_clrListText;

		COLORREF m_clrSliderThumb;
		COLORREF m_clrSliderFace;

		E_COLOR_GROUP_KIND m_eCurColorGroupKind;

		COLORREF m_clrPPIFace;
		COLORREF m_clrUserDefine[g_nMAX_COLOR_GROUP_NUM][g_nMAX_USER_DEFINE_COLOR_NUM];
	};
}	// NS_SALUS_MS_APP

