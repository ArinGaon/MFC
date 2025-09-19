
#pragma once

#include "DataTypeDef.h"

static const INT g_nMAX_ENV_MODE = 11;

enum class E_ENV_MODE : INT
{
	eENV_MODE_PPI = 0,		// PPI		(PPI-Scope)
	eENV_MODE_COL = 1,		// COL		(Color)
	eENV_MODE_ALRM = 2,		// ALRM		(Alarm)
	eENV_MODE_ZONE = 3,		// ZONE		(Guard Zone)
	eENV_MODE_MASK = 4,		// MASK		(Area Masking)
	eENV_MODE_MAP = 5,		// User MAP
	eENV_MODE_SP = 6,
	eENV_MODE_TRK = 7,
	eENV_MODE_RADARINF = 8,
	eENV_MODE_AISINF = 9,
	eENV_MODE_GPSINF = 10
};
