#pragma once

namespace NS_SALUS_MS_APP
{

	static const INT g_nMAX_CIRLCE_VERTEX = 360;

	enum class E_MOUSE_ACT_TYPE
	{
		eMAT_MOVE = 0,
		eMAT_LBUTTON_DOWN = 1,
		eMAT_LBUTTON_UP = 2,
		eMAT_RBUTTON_DOWN = 3,
		eMAT_RBUTTON_UP = 4,
	};

	static const DOUBLE g_dOFF_CENTER_VALID_RATIO = 0.66;   // 66 %

	static const TCHAR* g_szDefaultFontName = _T("NotoSans-Regular.TTF");

} // namespace NS_SALUS_MS_APP