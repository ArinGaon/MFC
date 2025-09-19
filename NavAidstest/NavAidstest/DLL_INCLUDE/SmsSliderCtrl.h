#pragma once

#include <afxcmn.h>

namespace NS_SALUS_MS_APP
{
	// CSmsSliderCtrl

	class AFX_EXT_CLASS CSmsSliderCtrl : public CSliderCtrl
	{
		DECLARE_DYNAMIC(CSmsSliderCtrl)

	public:
		CSmsSliderCtrl();
		virtual ~CSmsSliderCtrl();

	public:
		void SetNormalColor(const COLORREF clrFace, const COLORREF clrThumb);
		void SetDisabledColor(const COLORREF clrFace, const COLORREF clrThumb);

	protected:
		void DrawHThumb(CDC* const pDC, CRect rtClient);
		void DrawVThumb(CDC* const pDC, CRect rtClient);
		void DrawSlider(CDC* const pDC, CRect rtClient);

	protected:
		afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnSetFocus(CWnd* pOldWnd);
		DECLARE_MESSAGE_MAP()

	protected:
		COLORREF m_clrNormalThumb;
		COLORREF m_clrNormalFace;
		COLORREF m_clrDisabledFace;
		COLORREF m_clrDisabledThumb;
	};
}	// NS_SALUS_MS_APP