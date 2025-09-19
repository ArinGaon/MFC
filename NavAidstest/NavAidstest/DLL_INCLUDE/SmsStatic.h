#pragma once
#include <afxwin.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsStatic : public CStatic
	{
		DECLARE_DYNAMIC(CSmsStatic)

	public:
		CSmsStatic() noexcept;
		virtual ~CSmsStatic();

	public:
		void SetBorderStatus(const BOOL bDraw);
		void SetTransparent(const BOOL bTransparent);
		void SetFaceColor(const COLORREF clrNormalFace, const COLORREF clrDisabledFace, const BOOL bRedraw = FALSE);
		void SetTextColor(const COLORREF clrNormalText, const COLORREF clrDisabledText, const BOOL bRedraw = FALSE);
		void SetFrameColor(const COLORREF clrNormalFrame, const COLORREF clrDisabledFrame, const BOOL bRedraw = FALSE);

		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	protected:
		virtual void PreSubclassWindow();

		void ChangeStyle();

		void DrawBackground(CDC* const pDC, const CRect& rtClient);
		void PaintBackground(CDC* const pDC, const CRect& rtClient);

		void DrawBorder(CDC* const pDC, const CRect& rtClient);
		void DrawStaticText(CDC* const pDC, const CRect& rtClient);

	protected:
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnNMThemeChanged(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnNcPaint();
		DECLARE_MESSAGE_MAP()

	protected:
		BOOL m_bDrawBorder;
		BOOL m_bTransparent;

		COLORREF m_clrNormalFace;
		COLORREF m_clrNormalText;
		COLORREF m_clrNormalFrame;

		COLORREF m_clrDisabledFace;
		COLORREF m_clrDisabledText;
		COLORREF m_clrDisabledFrame;

	private:
		LONG m_lTextAlign;

		CDC m_dcBackground;
		CBitmap m_bmpBackground;
		CBitmap* m_pbmpOldBackground;
	};
}	// NS_SALUS_MS_APP

