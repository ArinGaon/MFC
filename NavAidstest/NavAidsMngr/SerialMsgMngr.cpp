#include "pch.h"
#include "SerialMsgMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CSerialMsgMngr::CSerialMsgMngr()
	{
		m_nWriteIndex = 0;
		for (INT nCnt = 0; nCnt < g_nMAX_SERIAL_MSG_BUFFER; nCnt++)
		{
			m_pMsgStoreBuff[nCnt] = new BYTE[g_nMAX_SERIAL_MSG_LENGTH];
		}

		m_bActivate = TRUE;

		m_pQueueCS = new CCriticalSection();
	}

	CSerialMsgMngr::~CSerialMsgMngr()
	{
		m_bActivate = FALSE;

		for (INT nCnt = 0; nCnt < g_nMAX_SERIAL_MSG_BUFFER; nCnt++)
		{
			if (m_pMsgStoreBuff[nCnt] != NULL)
			{
				delete[] m_pMsgStoreBuff[nCnt];
				m_pMsgStoreBuff[nCnt] = NULL;
			}
		}

		if (m_pQueueCS != NULL)
		{
			delete m_pQueueCS;
			m_pQueueCS = NULL;
		}
	}

	void CSerialMsgMngr::Push(const BYTE* const pData, const INT nDataSize)
	{
		if (m_bActivate == TRUE)
		{
			LockQueue();

			INT nWriteSize = nDataSize;
			if (nWriteSize > g_nMAX_SERIAL_MSG_LENGTH)
			{
				nWriteSize = g_nMAX_SERIAL_MSG_LENGTH;
			}
			// 데이터 저장
			static_cast<void>(CopyMemory(&m_pMsgStoreBuff[m_nWriteIndex][0], pData, sizeof(BYTE) * nWriteSize));
			// 나머지 공간 클리어
			if (g_nMAX_SERIAL_MSG_LENGTH - nWriteSize > 0)
			{
				static_cast<void>(ZeroMemory(&m_pMsgStoreBuff[m_nWriteIndex][nWriteSize], sizeof(BYTE) * (g_nMAX_SERIAL_MSG_LENGTH - nWriteSize)));
			}

			// 저장 위치 정보가 큐에 있는지 검사
			if ((m_queueMsg.size() > 0) && (m_queueMsg.front() == m_nWriteIndex))
			{
				// 같은 위치 정보가 큐에 있다면 제거한다.
				m_queueMsg.pop();
				// Print
#ifdef _DEBUG
				OutputDebugString(_T("Buffer Full!!\n"));
#endif
			}

			// 저장 위치 큐에 저장
			m_queueMsg.push(m_nWriteIndex);
			// 인덱스 증가
			m_nWriteIndex++;
			if (m_nWriteIndex >= g_nMAX_SERIAL_MSG_BUFFER)
			{
				m_nWriteIndex = 0;
			}

			UnlockQueue();
		}
	}

	BYTE* CSerialMsgMngr::Pop()
	{
		BYTE* pData = NULL;

		if (m_bActivate == TRUE)
		{
			LockQueue();

			if (m_queueMsg.size() > 0)
			{
				INT nIndex = m_queueMsg.front();
				if ((nIndex >= 0) && (nIndex < g_nMAX_SERIAL_MSG_BUFFER))
				{
					pData = &m_pMsgStoreBuff[nIndex][0];
				}
				// 큐에서 버퍼 인덱스 제거
				m_queueMsg.pop();
			}

			UnlockQueue();
		}

		return pData;
	}

	void CSerialMsgMngr::Clear()
	{
		INT nExit = 0;

		while (nExit <= 0)
		{
			if (m_queueMsg.empty() == true)
			{
				nExit++;
				continue;
			}
			// 큐에서 제거
			m_queueMsg.pop();
		}

		m_nWriteIndex = 0;
	}

	void CSerialMsgMngr::LockQueue()
	{
		if (m_pQueueCS != NULL)
		{
			static_cast<void>(m_pQueueCS->Lock());
		}
	}

	void CSerialMsgMngr::UnlockQueue()
	{
		if (m_pQueueCS != NULL)
		{
			static_cast<void>(m_pQueueCS->Unlock());
		}
	}
} // NS_SALUS_MS_APP