#include "pch.h"
#include "SerialNMEA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CSerialNMEA::CSerialNMEA()
	{
		m_pSerialMsgMngr = NULL;

		m_pMsgStoreBuffer = new BYTE[m_unNMEA_BUFF_LENGTH];
		m_pMsgTempBuffer = new BYTE[m_unNMEA_BUFF_LENGTH / 2];
		m_nRcvDataCnt = 0U;
	}

	CSerialNMEA::~CSerialNMEA()
	{
		ClosePort();

		if (m_pMsgStoreBuffer != NULL)
		{
			delete[] m_pMsgStoreBuffer;
			m_pMsgStoreBuffer = NULL;
		}

		if (m_pMsgTempBuffer != NULL)
		{
			delete[] m_pMsgTempBuffer;
			m_pMsgTempBuffer = NULL;
		}
	}

	BOOL CSerialNMEA::Start(WORD wPortID, DWORD dwBaud)
	{
		BOOL OpenPortSt = FALSE;

		OpenPortSt = OpenPort(wPortID, dwBaud);

		return OpenPortSt;
	}

	void CSerialNMEA::Stop()
	{
		ClosePort();
	}

	void CSerialNMEA::SetMsgMngr(CSerialMsgMngr* const pSerialMsgMngr)
	{
		m_pSerialMsgMngr = pSerialMsgMngr;
	}

	BOOL CSerialNMEA::OnReceiveData()
	{
		BOOL bReturnValue = FALSE;
		DWORD dwRead;

		//통신 버퍼로부터 수신한 데이터를 읽어서 버퍼에 저장한다.
		dwRead = ReadComm(m_pMsgTempBuffer, m_unNMEA_BUFF_LENGTH / 2);

		if (dwRead > 0)
		{
			bReturnValue = TRUE;

			// 메시지 버퍼에 수신된 데이터를 추가한다.
			if (m_nRcvDataCnt + dwRead < m_unNMEA_BUFF_LENGTH)
			{
				static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[m_nRcvDataCnt], m_pMsgTempBuffer, dwRead));
				m_nRcvDataCnt += dwRead;

				ParseMsg();
			}
		}

		return bReturnValue;
	}

	void CSerialNMEA::ParseMsg()
	{
		static const INT nMinMsgLength = 8;
		INT nStart = 0;
		INT nEnd = 0;
		INT nQuitCnt = 0;

		while (nQuitCnt <= 0)
		{
			if (m_bBeClosing == TRUE)
			{
				nQuitCnt++;
				continue;
			}

			if (m_nRcvDataCnt < nMinMsgLength)
			{
				nQuitCnt++;
				continue;
			}

			// 시작 구분자를 찾는다.
			for (nStart = 0; nStart < m_nRcvDataCnt; nStart++)
			{
				if ((m_pMsgStoreBuffer[nStart] == '$') || (m_pMsgStoreBuffer[nStart] == '!'))
				{
					break;
				}
			}

			// 시작구분자 위치가 0보다 크면 그 이전 데이터는 다 버린다.
			if (nStart > 0)
			{
				m_nRcvDataCnt -= nStart;
				if (m_nRcvDataCnt > 0)
				{
					static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nStart], m_nRcvDataCnt));
				}
			}

			// 최소 한 프레임 사이즈가 들어오지 않았으면...다시 기다린다.
			if (m_nRcvDataCnt < nMinMsgLength)
			{
				nQuitCnt++;
				continue;
			}
			BOOL bFound = FALSE;
			// 종료구분자 찾는다.
			for (nEnd = 1; nEnd < m_nRcvDataCnt; nEnd++)
			{
				if (m_pMsgStoreBuffer[nEnd] == '\n') // LF
				{
					bFound = TRUE;
					break;
				}
			}

			if (bFound == FALSE)
			{
				nQuitCnt++;
				continue;
			}

			if (nEnd < nMinMsgLength)
			{
				// 종료구분자가 최소 사이즈보다 작으면 잘못된 메시지이다.
				m_nRcvDataCnt -= nEnd;
				if (m_nRcvDataCnt > 0)
				{
					static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nEnd], m_nRcvDataCnt));
				}

				continue;
			}

			// 정상적인 메시지 수신
			INT nLength = nEnd + 1;
			if (m_pSerialMsgMngr != NULL)
			{
				m_pSerialMsgMngr->Push(m_pMsgStoreBuffer, nLength);
			}

			// 들어온 프레임을 버리고 다음 데이터를 받는다.
			m_nRcvDataCnt -= nLength;
			if (m_nRcvDataCnt > 0)
			{
				static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nLength], m_nRcvDataCnt));
			}
		}
	}
}
