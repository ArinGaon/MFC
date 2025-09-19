#pragma once

namespace NS_SALUS_MS_APP
{
	//#define USE_ARPA_SYSTEM

	#define USE_AIS_FILE_REPLAY

	static const INT g_nMAX_CALLSIGN_SIZE = 7;
	static const INT g_nMAX_SHIPNAME_SiZE = 20;

	static const UINT g_unREPLAY_FILENAME_SIZE = 256U;

	static const UINT g_unMAX_TRACK_NUM = 1000U;
	static const UINT g_unMAX_ALLOW_TRACK_NUM = 1200U; // 최대 Track 개수에 1.2배 더 Track를 보유한다.


	static const INT g_nMAX_FILE_NAME_SIZE = 256;

	static const INT g_nMAX_SITE_NAME_SIZE = 30;

	static const INT g_nMAX_CLIENT_IP_SIZE = 16;

	static const INT g_nMAX_ETH_IPADDR_SIZE = 20;

	static const INT g_nMAX_VIEW_SCOPE = 2;

	enum class E_VIEW_SCOPE : INT
	{
		eMAIN_SCOPE = 0,
		eSUB_SCOPE = 1
	};

}	// NS_SALUS_MS_APP