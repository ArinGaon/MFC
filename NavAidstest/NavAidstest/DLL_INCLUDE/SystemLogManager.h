#pragma once

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.

#include "LogDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSystemLogManager
	{
	public:
		CSystemLogManager();
		~CSystemLogManager();

	public:
		static CSystemLogManager* GetInstance();
		static void DeleteInstance();

		void Initialize(CString strHomeDirectory);
		void Finalize();
		void SetReportWindow(CWnd* pReportWnd, UINT unReportID);

		void OutputMsg(E_LOG_MSG_KIND eMsgKind, LPCTSTR pszFormat, ...);
		void OutputMsg(E_LOG_MSG_KIND eMsgKind, TCHAR* pszFormat, ...);

		void ShowConsole(BOOL bShow);

		TCHAR* GetLogMsg(INT nIndex);

		void EnableSaveLog(BOOL bEnable = TRUE);
	protected:
		void TerminateLogMsgProcThread();
		void ProcSystemLogMessage();

		static UINT32 LogMsgProcThread(LPVOID const lpParam);

	private:
		static CSystemLogManager* m_pInstance;

		CWnd* m_pReportWindow;
		UINT m_unReportID;

		TCHAR m_szMsgBuffer[g_unMAX_LOG_MSG_SIZE];

		BOOL m_bSaveLog;

		BOOL m_bExitLogMsgProcThread;
		CWinThread* m_pLogMsgProcThread;
	};

} // NS_SALUS_MS_APP

