#pragma once

#include <AfxListCtrl.h>

#include "SmsHeaderCtrl.h"

namespace NS_SALUS_MS_APP
{
	//-----------------------------------------------------------------
	// CSmsImgList: Ŀ���� �̹��� ����Ʈ
	// Ư¡:
	//		1. ��Ʈ�� ���� 24bit�� ����(ILC_COLOR24)
	//		2. �̹��� ���� �þ�� �ʵ��� ����
	//-----------------------------------------------------------------
	class CSmsImgList : public CImageList
	{
	public:
		CSmsImgList();
		virtual ~CSmsImgList();

		// ImgList ����
		// numImg: �̹��� ����, img_width: �̹����� ���� ũ��(pixel), img_height: �̹����� ���� ũ��(pixel)
		void Create(const INT nNumImage, const INT nImageWidth, const INT nImageHeight);

		// Bitmap �߰�
		// nIDResource: Bitmap ���ҽ� �ڵ�(IDB_~), crMask: ����ũ�� �÷�
		void Add(const UINT nIDResource, const COLORREF clrMask);


		INT GetNumImage();
		INT GetImageWidth();
		INT GetImageHeight();

	private:
		INT m_nNumImages;				// Bitmap�� ����
		INT	m_nImageWidth;				// Bitmap ����/���� ũ��(pixel)
		INT m_nImageHeight;

		INT	m_nImageCount;				// Add()�� �̹����� ����
		CBitmap* m_pBitmap;
	};

	//-----------------------------------------------------------------
	// CSmsListCtrl: OTUS Ŀ���� ����Ʈ ��Ʈ��
	//-----------------------------------------------------------------
	class AFX_EXT_CLASS CSmsListCtrl : public CListCtrl
	{
		DECLARE_DYNAMIC(CSmsListCtrl)

	public:
		CSmsListCtrl();
		CSmsListCtrl(const INT nNumImage, const INT nImageWidth, const INT nImageHeight);		// �̹��� ����Ʈ ���
		virtual ~CSmsListCtrl();

		// Image List
		void AddImage(const UINT nIDResource1, const UINT nIDResource2, const UINT nIDResourceSel, const COLORREF clrMask);
		void SetImageList();					// �̹��� ����Ʈ ����

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
		COLORREF m_clrBkgnd1;		// Item Background color (¦����)
		COLORREF m_clrBkgnd2;		// Item Background color (Ȧ����)
		COLORREF m_clrSelBkgnd;		// Selected Item Background color
		COLORREF m_clrText;			// Text color

		CSmsImgList* m_pImageList;	// ����Ʈ�� ǥ���� ������ �̹��� ����Ʈ (LVSIL_NORMAL �� ���)

		CImageList* m_pCheckImgList;

		CFont* m_pFont;

		CSmsHeaderCtrl m_wndHeaderCtrl;
	public:
		afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	};
}	// namespace NS_SALUS_MS_APP
