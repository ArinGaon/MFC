#pragma once

#include <WTypesbase.h>

namespace NS_SALUS_MS_APP
{
	const UINT32 g_unMAX_LOG_MSG_SIZE = 256U;

	enum class E_LOG_MSG_KIND : INT
	{
		eLOG_KIND_UNKNOWN = 0,
		eLOG_KIND_NORMAL_MSG,
		eLOG_KIND_INFO_MSG,
		eLOG_KIND_DEBUG_MSG,
		eLOG_KIND_WARNING_MSG,
		eLOG_KIND_ALARM_MSG,
		eLOG_KIND_ERROR_MSG,
		eLOG_KIND_FAULT_MSG,
	};

	struct T_LOG_MSG_INFO
	{
		E_LOG_MSG_KIND	m_eKind;
		TCHAR			m_szMsg[g_unMAX_LOG_MSG_SIZE];
	};
} // NS_SALUS_MS_APP