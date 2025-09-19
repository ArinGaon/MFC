#include "pch.h"
#include "SerialCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CSerialCAN::CSerialCAN()
	{
		m_pSerialMsgMngr = NULL;

		m_pMsgStoreBuffer = new BYTE[m_unCAN_BUFF_LENGTH];
		m_pMsgTempBuffer = new BYTE[m_unCAN_BUFF_LENGTH / 2];
		m_pMsgBuffer = new BYTE[m_unCAN_BUFF_LENGTH / 2];
		m_nRcvDataCnt = 0U;

		_tcscpy_s(reinterpret_cast<TCHAR*>(&m_pMsgBuffer[0]), m_unCAN_BUFF_LENGTH / 2, _T("$__CAN,"));
	}

	CSerialCAN::~CSerialCAN()
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

		if (m_pMsgBuffer != NULL)
		{
			delete[] m_pMsgBuffer;
			m_pMsgBuffer = NULL;
		}
	}

	void CSerialCAN::Start(WORD wPortID, DWORD dwBaud)
	{
		OpenPort(wPortID, dwBaud);
	}

	void CSerialCAN::Stop()
	{
		ClosePort();
	}

	void CSerialCAN::SetMsgMngr(CSerialMsgMngr* const pSerialMsgMngr)
	{
		m_pSerialMsgMngr = pSerialMsgMngr;
	}

	BOOL CSerialCAN::OnReceiveData()
	{
		BOOL bReturnValue = FALSE;
		DWORD dwRead;

		//��� ���۷κ��� ������ �����͸� �о ���ۿ� �����Ѵ�.
		dwRead = ReadComm(m_pMsgTempBuffer, m_unCAN_BUFF_LENGTH / 2);

		if (dwRead > 0)
		{
			bReturnValue = TRUE;

			// �޽��� ���ۿ� ���ŵ� �����͸� �߰��Ѵ�.
			if (m_nRcvDataCnt + dwRead < m_unCAN_BUFF_LENGTH)
			{
				static_cast<void>(CopyMemory(&m_pMsgStoreBuffer[m_nRcvDataCnt], m_pMsgTempBuffer, dwRead));
				m_nRcvDataCnt += dwRead;

				ParseMsg();
			}
		}

		return bReturnValue;
	}

	void CSerialCAN::ParseMsg()
	{
		static const INT nMinMsgLength = 26;
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
				if (m_pMsgStoreBuffer[nStart] == 'e')
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

			// ���ᱸ���� ã�´�.
			for (nEnd = 0; nEnd < m_nRcvDataCnt; nEnd++)
			{
				if (m_pMsgStoreBuffer[nEnd] == 0x0D) // CR
				{
					break;
				}
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

			// PGN �������� ��ȯ
			if ((m_pMsgStoreBuffer[3] == 'F') && (m_pMsgStoreBuffer[4] == '1') && (m_pMsgStoreBuffer[5] == '1'))
			{
				static_cast<void>(CopyMemory(&m_pMsgBuffer[7], &m_pMsgStoreBuffer[3], nLength - 3));

				if (m_pSerialMsgMngr != NULL)
				{
					m_pSerialMsgMngr->Push(m_pMsgBuffer, nLength + 4);
				}
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
