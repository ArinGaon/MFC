#pragma once

#include <AfxListCtrl.h>

#include "SmsHeaderCtrl.h"

namespace NS_SALUS_MS_APP
{
	//-----------------------------------------------------------------
	// CSmsImgList: 커스텀 이미지 리스트
	// 특징:
	//		1. 비트맵 형식 24bit로 고정(ILC_COLOR24)
	//		2. 이미지 버퍼 늘어나지 않도록 고정
	//-----------------------------------------------------------------
	class CSmsImgList : public CImageList
	{
	public:
		CSmsImgList();
		virtual ~CSmsImgList();

		// ImgList 생성
		// numImg: 이미지 개수, img_width: 이미지의 가로 크기(pixel), img_height: 이미지의 세로 크기(pixel)
		void Create(const INT nNumImage, const INT nImageWidth, const INT nImageHeight);

		// Bitmap 추가
		// nIDResource: Bitmap 리소스 코드(IDB_~), crMask: 마스크할 컬러
		void Add(const UINT nIDResource, const COLORREF clrMask);


		INT GetNumImage();
		INT GetImageWidth();
		INT GetImageHeight();

	private:
		INT m_nNumImages;				// Bitmap의 개수
		INT	m_nImageWidth;				// Bitmap 가로/세로 크기(pixel)
		INT m_nImageHeight;

		INT	m_nImageCount;				// Add()된 이미지의 개수
		CBitmap* m_pBitmap;
	};

	//-----------------------------------------------------------------
	// CSmsListCtrl: OTUS 커스텀 리스트 컨트롤
	//-----------------------------------------------------------------
	class AFX_EXT_CLASS CSmsListCtrl : public CListCtrl
	{
		DECLARE_DYNAMIC(CSmsListCtrl)

	public:
		CSmsListCtrl();
		CSmsListCtrl(const INT nNumImage, const INT nImageWidth, const INT nImageHeight);		// 이미지 리스트 사용
		virtual ~CSmsListCtrl();

		// Image List
		void AddImage(const UINT nIDResource1, const UINT nIDResource2, const UINT nIDResourceSel, const COLORREF clrMask);
		void SetImageList();					// 이미지 리스트 연동

		void SetListHScrollType(BOOL ListHScrollType);

		virtual INT InsertColumn(INT nCol, const LVCOLUMN* pColumn);
		virtual INT InsertColumn(INT nCol, LPCTSTR lpszColumnHeading, INT nFormat = LVCFMT_LEFT, INT nWidth = -1, INT nSubItem = -1);

		// Set Function
		void SetItemBackgoundColor(const COLORREF clrBkgnd1, const COLORREF clrBkgnd2);
		void SetTextColor(const COLORREF color);
		void SetHeaderColor(const COLORREF clrFace, const COLORREF clrText, const COLORREF clrFrame);

		INT GetCurSel();
		
	private:
		void DrawSubItem(CDC* pDC, INT nItem, INT nSubItem, CRect rtCell, BOOL bEraseBkgn = TRUE);
		INT DrawSubItemCheckBox(CDC* pDC, INT nCheck, CRect rtCheck, COLORREF clrBkgnd);
		void DrawSubItemText(CDC* const pDC, INT nItem, INT nSubItem, CRect rtText, COLORREF clrText, COLORREF clrBkgnd);
		void GetDrawColors(INT nItem, INT nSubItem, COLORREF& clrText, COLORREF& clrBkgnd);

		void ChangeStyle();
		void ChangeFont();
		void SetCheckBoxImage();
		void CheckAllItems(BOOL bChecked);

		BOOL m_blListStyleHScroll;
	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		virtual void PreSubclassWindow();
		afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg BOOL OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
		DECLARE_MESSAGE_MAP()

	private:
		static const INT m_nDEFAULT_CHECKBOX_SIZE = 16;
		COLORREF m_clrBkgnd1;		// Item Background color (짝수행)
		COLORREF m_clrBkgnd2;		// Item Background color (홀수행)
		COLORREF m_clrSelBkgnd;		// Selected Item Background color
		COLORREF m_clrText;			// Text color

		CSmsImgList* m_pImageList;	// 리스트에 표시할 아이콘 이미지 리스트 (LVSIL_NORMAL 만 사용)

		CImageList* m_pCheckImgList;

		CFont* m_pFont;

		CSmsHeaderCtrl m_wndHeaderCtrl;
	public:
		afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	};
}	// namespace NS_SALUS_MS_APP
