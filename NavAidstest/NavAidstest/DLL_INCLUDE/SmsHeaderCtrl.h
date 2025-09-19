#pragma once

#include <afxheaderctrl.h>

namespace NS_SALUS_MS_APP
{
	// CSmsHeaderCtrl

	class AFX_EXT_CLASS CSmsHeaderCtrl : public CHeaderCtrl
	{
		DECLARE_DYNAMIC(CSmsHeaderCtrl)

	public:
		CSmsHeaderCtrl();
		virtual ~CSmsHeaderCtrl();

	public:
		void SetColor(const COLORREF clrFace, const COLORREF clrText, const COLORREF clrFrame);

	protected:
		void ChangeCheckBox();

	protected:
		afx_msg void OnPaint();
		afx_msg void OnHdnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		DECLARE_MESSAGE_MAP()

	protected:
		COLORREF m_clrFace;
		COLORREF m_clrText;
		COLORREF m_clrFrame;
	};
}	// namespace NS_SALUS_MS_APP

