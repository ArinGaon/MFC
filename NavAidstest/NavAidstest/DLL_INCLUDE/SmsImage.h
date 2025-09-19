#pragma once

#include <atlimage.h>

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSmsImage : public CImage
	{
	public:
		CSmsImage() noexcept;

	public:
		virtual HRESULT Load(_In_z_ LPCTSTR pszFileName);
	};
}	// NS_SALUS_MS_APP