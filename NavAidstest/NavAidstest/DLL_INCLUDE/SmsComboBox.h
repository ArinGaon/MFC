#pragma once
#include <afxwin.h>

namespace NS_SALUS_MS_APP
{
	// ComboBox resource property
	//     - Owner Draw : Fixed
	//     - Has String : True

	class AFX_EXT_CLASS CSmsComboBox : public CComboBox
	{
		DECLARE_DYNAMIC(CSmsComboBox)

	public:
		CSmsComboBox() noexcept;
		virtual ~CSmsComboBox();

	public:
		void SetNormalColor(const COLORREF clrFace, const COLORREF clrText);
		void SetDisabledColor(const COLORREF clrFace, const COLORREF clrText);
		void SetArrowColor(const COLORREF clrFace, const COLORREF clrText);
		void SetSelectColor(const COLORREF clrFace, const COLORREF clrText);

		void SetBoxHeight(const UINT unHeight);

	protected:
		virtual void PreSubclassWindow();
		virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	protected:
		afx_msg void OnPaint();
		afx_msg void OnCbnDropdown();
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		DECLARE_MESSAGE_MAP()

	private:
		void DrawWindowText(CDC* const pDC, CRect& rtItem, const COLORREF clrText);
		void DrawArrowButton(CDC* const pDC, CRect& rtArrow);

	protected:
		UINT m_unBoxHeight;
		BOOL m_bIsDropList;

		CRect m_rtArrow;
		CRect m_rtItem;

		COLORREF m_clrNormalText;
		COLORREF m_clrNormalFace;

		COLORREF m_clrDisabledText;
		COLORREF m_clrDisabledFace;

		COLORREF m_clrArrowText;
		COLORREF m_clrArrowFace;

		COLORREF m_clrSelectText;
		COLORREF m_clrSelectFace;

	private:
		static const UINT m_unBOX_HEIGHT = 46U;
		static const INT m_nARROW_TRIANGLE_HEIGHT = 4;
		static const INT m_nARROW_TRIANGLE_WIDTH = 8;
	};
}	// NS_SALUS_MS_APP

