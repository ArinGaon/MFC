#pragma once

#include <afxbutton.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsButton : public CMFCButton
	{
		DECLARE_DYNAMIC(CSmsButton)

	public:
		CSmsButton() noexcept;
		virtual ~CSmsButton();

	public:
		void SetHoverFrameColor(const COLORREF clrFrame);
		void SetCheckedColor(const COLORREF clrFace, const COLORREF clrText);
		void SetOptionButton(const BOOL bOption = FALSE);

	protected:
		virtual void PreSubclassWindow();

		virtual void OnFillBackground(CDC* pDC, const CRect& rtClient);
		virtual void OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState);
		virtual CFont* SelectFont(CDC* pDC);

	protected:
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSysColorChange();
		DECLARE_MESSAGE_MAP()

	protected:
		void ChangeStyle();

		void PaintBackground(CDC* const pDC, const CRect& rtClient);
		virtual void OnDrawBorder(CDC* pDC, CRect& rtClient, UINT unState);
		INT DrawCheckBox(CDC* pDC, CRect rtCheck, COLORREF clrBkgnd);
		INT DrawRadioBox(CDC* pDC, CRect rtCheck, COLORREF clrBkgnd);
		void DrawTriangle(CDC* pDC, const CRect& rtButton, const COLORREF clrPen);

	protected:
		UINT m_unButtonStyle;

		COLORREF m_clrCheckedText;
		COLORREF m_clrCheckedFace;

		COLORREF m_clrHoverFrame;

		CDC m_dcBackground;
		CBitmap m_bmpBackground;
		CBitmap* m_pbmpOldBackground;

	private:
		static const INT m_nDefaultMargine = 4;

		BOOL m_bIsOptionButton;
	};
}	// NS_SALUS_MS_APP