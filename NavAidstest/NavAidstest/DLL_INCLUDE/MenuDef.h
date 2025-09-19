#pragma once

#include "DataTypeDef.h"

#include <WinUser.h>

static const INT g_nMAX_MENU_KIND = 19;

enum class E_MENU_KIND : INT
{
	eMENU_NONE = -1,
	// TRACK
	eMENU_ACQ = 0,
	eMENU_RLS = 1,
	eMENU_GROUP = 2,
	eMENU_FAST = 3,
	eMENU_SWAP = 4,
	eMENU_RESET = 5,			// RESET
	eMENU_TRACKLIST = 6,		// LIST

	// PPI
	eMENU_SCOPE = 7,			// QM_SUB
	eMENU_CNTR = 8,
	eMENU_MOVE = 9,
	eMENU_OFFCENTER = 10,

	// INFO
	eMENU_SEL = 11,
	eMENU_CPA = 12,

	// VRM/EBL
	eMENU_VRMEBL1 = 13,
	eMENU_VRMEBL2 = 14,

	// UTIL
	eMENU_VT = 15,
	eMENU_ENV = 16,			// ENV
	eMENU_EXIT = 17,          // EXIT
	eMENU_SAVELOG = 18
};

