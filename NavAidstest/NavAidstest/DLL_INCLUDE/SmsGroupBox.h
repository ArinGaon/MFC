#pragma once

namespace NS_SALUS_MS_APP
{
	// CSmsGroupBox

	class AFX_EXT_CLASS CSmsGroupBox : public CStatic
	{
		DECLARE_DYNAMIC(CSmsGroupBox)

	public:
		CSmsGroupBox();
		virtual ~CSmsGroupBox();

		// ¼Ó¼º
	public:
		enum class E_GB_CONTROL_STYLE
		{
			eCONTROL_STYLE_GROUPBOX = 0,
			eCONTROL_STYLE_HEADER
		};

		enum class E_GB_BORDER_STYLE
		{
			eBORDER_STYLE_FLAT = 0,
			eBORDER_STYLE_ETCHED
		};

		enum class E_GB_ALIGNMENT
		{
			eALIGNMENT_LEFT = 0,
			eALIGNMENT_CENTER,
			eALIGNMENT_RIGHT
		};

		CSmsGroupBox& SetAlignment(E_GB_ALIGNMENT eAlign, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetBold(BOOL bBold, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetBorderColor(COLORREF crBorder, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetBorderStyle(E_GB_BORDER_STYLE eStyle, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetControlStyle(E_GB_CONTROL_STYLE eStyle, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetDisabledStyle(BOOL bShowDisabledState, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetFont(CFont* pFont, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetFont(LOGFONT* pLogFont, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetFont(LPCTSTR lpszFaceName, INT nPointSize, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetIcon(HICON hIcon, UINT nIconSize = 16, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetIcon(UINT nIconId, UINT nIconSize = 16, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetIconAlignment(E_GB_ALIGNMENT eAlign, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetIconSpacing(INT nIconSpacing, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetImageList(CImageList* pImageList, INT nIconNo, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetMargins(INT nXMargin, INT nYMargin, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetTextColor(COLORREF cr, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetBackgroundColor(COLORREF cr, BOOL bRedraw = TRUE);
		CSmsGroupBox& SetWindowText(LPCTSTR lpszText, BOOL bRedraw = TRUE);

		E_GB_ALIGNMENT GetAlignment() { return m_eControlAlignment; }
		BOOL GetBold();
		COLORREF GetBorderColor() { return m_clrBorder; }
		E_GB_BORDER_STYLE GetBorderStyle() { return m_eBorderStyle; }
		BOOL GetDisabledStyle() { return m_bShowDisabledState; }
		CFont* GetFont() { return &m_font; }
		BOOL GetFont(LOGFONT* pLF);
		CString GetFontFaceName();
		INT GetFontPointSize();
		E_GB_ALIGNMENT GetIconAlignment() { return m_eIconAlignment; }
		INT GetIconSpacing() { return m_nIconSpacing; }
		void GetMargins(INT& nXMargin, INT& nYMargin)
		{
			nXMargin = m_nXMargin; nYMargin = m_nYMargin;
		}
		E_GB_CONTROL_STYLE GetControlStyle() { return m_eStyle; }
		COLORREF GetTextColor() { return m_clrText; }

		BOOL EnableWindow(BOOL bEnable = TRUE, BOOL bRecurseChildren = FALSE);

	protected:
		virtual void PreSubclassWindow();

		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnPaint();

		HICON CreateGrayscaleIcon(HICON hIcon);
		HICON CreateGrayscaleIcon(HICON hIcon, COLORREF* pPalette);
		void DrawBorder(CDC* pDC, CRect& rect);
		void DrawEtchedLine(CDC* pDC, CRect& rect, COLORREF cr);
		void DrawEtchedRectangle(CDC* pDC, CRect& rect, COLORREF cr);
		void DrawHeader(CDC* pDC, CRect& rectText, CRect& rectIcon);
		INT DrawIcon(CDC* pDC, CRect& rect);
		void DrawItem(CDC* pDC, CRect& rect);
		INT DrawText(CDC* pDC, CRect& rect);
		INT EnableChildWindows(HWND hWnd, BOOL bEnable, BOOL bEnableParent);
		void EraseBorder(CDC* pDC, CRect& rect, COLORREF crBackground);
		void EraseHeaderArea(CDC* pDC, CRect& rect, COLORREF crBackground);
		INT GetFontHeight(INT nPointSize);
		INT GetFontPointSize(INT nHeight);
		void GetHeaderRect(CRect& rect);
		CFont* GetSafeFont();

		DECLARE_MESSAGE_MAP()

		// Implementation
	private:
		static const INT m_nDEFAULT_X_MARGIN = 8;
		static const INT m_nDEFAULT_ICON_SPACING = 8;
		static const INT m_nDEFAULT_ICON_SIZE = 16;

		CFont					m_font;					// font used for text
		COLORREF				m_clrText;				// text color
		COLORREF				m_clrBackground;		// background color
		COLORREF				m_clrBorder;				// user-specified border color
		INT						m_nXMargin;				// x space in pixels between border
		INT						m_nYMargin;				// y space in pixels between border
		// and icon/text
		INT						m_nYOffset;				// y offset of frame (text extends 
		// above frame)
		INT						m_nIconSpacing;			// horizontal space in pixels 
		// between icon	and text
		HICON					m_hIcon;				// icon handle
		HICON					m_hGrayIcon;			// disabled icon handle
		INT						m_nIconSize;			// size of icon, default to 16
		BOOL					m_bDestroyIcon;			// TRUE = icon will be destroyed
		// (internal only)
		CRect					m_rect;
		CSize					m_sizeText;				// size of text from GetTextExtent()
		// enabled
		BOOL					m_bShowDisabledState;	// TRUE = gray text and icon will 
		// be displayed if control is 
		// disabled
		BOOL					m_bGrayPaletteSet;		// used for gray scale icon
		static COLORREF			m_defaultGrayPalette[256]; // used for gray scale icon
		E_GB_CONTROL_STYLE		m_eStyle;				// disabled groupbox or header
		E_GB_BORDER_STYLE		m_eBorderStyle;			// border line style - flat or etched;
		// applies only if no border color
		// and no theme
		E_GB_ALIGNMENT			m_eIconAlignment;		// left (of text) or right;  note 
		// that control's style bits
		// control header alignment
		E_GB_ALIGNMENT			m_eControlAlignment;	// alignment for control
	};
}