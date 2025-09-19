#pragma once

#include <map>

enum class E_FONT_KIND : INT
{
	eNOTOSANS_14_REGULAR = 0,	// Noto Sans 14 Regular
	eNOTOSANS_14_BOLD = 1,		// Noto Sans 14 Bold
	eNOTOSANS_16_REGULAR = 2,	// Noto Sans 16 Regular
	eNOTOSANS_16_BOLD = 3,		// Noto Sans 16 Bold
	eNOTOSANS_18_REGULAR = 4,	// Noto Sans 18 Regular
	eNOTOSANS_18_BOLD = 5,		// Noto Sans 18 Bold
	eNOTOSANS_20_REGULAR = 6,	// Noto Sans 20 Regular
	eNOTOSANS_20_BOLD = 7,		// Noto Sans 20 Bold
	eNOTOSANS_24_REGULAR = 8,	// Noto Sans 24 Regular
	eNOTOSANS_24_BOLD = 9,		// Noto Sans 24 Bold
	eNOTOSANS_30_REGULAR = 10,	// Noto Sans 30 Regular
	eNOTOSANS_30_BOLD = 11,	// Noto Sans 30 Bold
};

class AFX_EXT_CLASS CSmsFont
{
public:
	CSmsFont();
	~CSmsFont();

public:
	static CSmsFont* GetInstance();
	static void DeleteInstance();

	CFont* GetFont(const E_FONT_KIND eFontKind);

protected:
	CFont* MakeFont(const E_FONT_KIND eFontKind);

	INT GetFontHeight(const E_FONT_KIND eFontKind);
	INT GetFontWeight(const E_FONT_KIND eFontKind);

private:
	void RemoveAll();

private:
	static CSmsFont* m_pInstance;

	static FLOAT m_fHeightRatio;

	std::map<E_FONT_KIND, CFont*> m_mapFont;
};
