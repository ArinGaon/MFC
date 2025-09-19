#pragma once

#include <queue>
#include <afxmt.h>

namespace NS_SALUS_MS_APP
{
	static const INT g_nMAX_SERIAL_MSG_LENGTH = 256;
	static const INT g_nMAX_SERIAL_MSG_BUFFER = 64;

	class CSerialMsgMngr
	{
	public:
		CSerialMsgMngr();
		~CSerialMsgMngr();

	public:
		void Push(const BYTE* const pData, const INT nDataSize);
		BYTE* Pop();

		void Clear();

	protected:
		void LockQueue();
		void UnlockQueue();

	private:
		BYTE* m_pMsgStoreBuff[g_nMAX_SERIAL_MSG_BUFFER];
		INT m_nWriteIndex;

		BOOL m_bActivate;		// 종료 시 동작 상태 확인

		std::queue<INT> m_queueMsg;
		CCriticalSection* m_pQueueCS;
	};
} // NS_SALUS_MS_APP

