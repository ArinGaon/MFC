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

		//��� ���۷κ��� ������ �����͸� �о ���ۿ� �����Ѵ�.
		dwRead = ReadComm(m_pMsgTempBuffer, m_unNMEA_BUFF_LENGTH / 2);

		if (dwRead > 0)
		{
			bReturnValue = TRUE;

			// �޽��� ���ۿ� ���ŵ� �����͸� �߰��Ѵ�.
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

			// ���� �����ڸ� ã�´�.
			for (nStart = 0; nStart < m_nRcvDataCnt; nStart++)
			{
				if ((m_pMsgStoreBuffer[nStart] == '$') || (m_pMsgStoreBuffer[nStart] == '!'))
				{
					break;
				}
			}

			// ���۱����� ��ġ�� 0���� ũ�� �� ���� �����ʹ� �� ������.
			if (nStart > 0)
			{
				m_nRcvDataCnt -= nStart;
				if (m_nRcvDataCnt > 0)
				{
					static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nStart], m_nRcvDataCnt));
				}
			}

			// �ּ� �� ������ ����� ������ �ʾ�����...�ٽ� ��ٸ���.
			if (m_nRcvDataCnt < nMinMsgLength)
			{
				nQuitCnt++;
				continue;
			}
			BOOL bFound = FALSE;
			// ���ᱸ���� ã�´�.
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
				// ���ᱸ���ڰ� �ּ� ������� ������ �߸��� �޽����̴�.
				m_nRcvDataCnt -= nEnd;
				if (m_nRcvDataCnt > 0)
				{
					static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nEnd], m_nRcvDataCnt));
				}

				continue;
			}

			// �������� �޽��� ����
			INT nLength = nEnd + 1;
			if (m_pSerialMsgMngr != NULL)
			{
				m_pSerialMsgMngr->Push(m_pMsgStoreBuffer, nLength);
			}

			// ���� �������� ������ ���� �����͸� �޴´�.
			m_nRcvDataCnt -= nLength;
			if (m_nRcvDataCnt > 0)
			{
				static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[0], &m_pMsgStoreBuffer[nLength], m_nRcvDataCnt));
			}
		}
	}
}
