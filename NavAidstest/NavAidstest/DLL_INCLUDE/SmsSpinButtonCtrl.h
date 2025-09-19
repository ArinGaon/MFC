#pragma once

#include <afxspinbuttonctrl.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsSpinButtonCtrl : public CMFCSpinButtonCtrl
	{
	public:
		CSmsSpinButtonCtrl();
		virtual ~CSmsSpinButtonCtrl();

	public:
		void SetColor(const COLORREF clrText, const COLORREF clrFace);

	protected:
		afx_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnPaint();
		DECLARE_MESSAGE_MAP()

	protected:
		virtual void PreSubclassWindow();

		void DrawArrowUp(CDC* const pDC, const CRect& rtArrow, const COLORREF clrText, const COLORREF clrFace);
		void DrawArrowDown(CDC* const pDC, const CRect& rtArrow, const COLORREF clrText, const COLORREF clrFace);
		void DrawArrowLeft(CDC* const pDC, const CRect& rtArrow, const COLORREF clrText, const COLORREF clrFace);
		void DrawArrowRight(CDC* const pDC, const CRect& rtArrow, const COLORREF clrText, const COLORREF clrFace);

		void GetDrawColor(const CRect& rtUp, const CRect& rtDown, COLORREF& clrTextUp, COLORREF& clrFaceUp, COLORREF& clrTextDown, COLORREF& clrFaceDown);

	private:
		INT GetAlign(const DWORD dwStyle); // 0 = Outside, 1 = Right Inside, 2 = Left Inside
		void CreateBitmap(CDC* const pDC, const INT nWidth, const INT nHeight);
		void DeleteBitmap();

		void SetDefaultRange();

	protected:
		COLORREF m_clrFace;
		COLORREF m_clrText;

	private:
		static const INT m_nARROW_TRIANGLE_HEIGHT = 4;
		static const INT m_nARROW_TRIANGLE_WIDTH = 8;

		INT m_nMemWidth;
		INT m_nMemHeight;
		CDC* m_pMemDC;
		CBitmap* m_pMemBitmap;
	};
}