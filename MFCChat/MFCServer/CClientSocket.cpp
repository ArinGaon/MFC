#include "pch.h"
#include "CClientSocket.h"
#include "MFCServerDlg.h"
#include "resource.h" // IDC_STATIC_STATUS

void CClientSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	int nRead = Receive(szBuffer, sizeof(szBuffer) - 1);
	if (nRead > 0)
	{
		szBuffer[nRead] = '\0';
		m_strBuffer += szBuffer; // 받은 데이터를 버퍼에 추가

		int nIndex;
		// 버퍼에서 \r\n (줄바꿈)을 찾는다.
		while ((nIndex = m_strBuffer.Find(_T("\r\n"))) != -1)
		{
			// \r\n 앞까지의 문자열을 한 줄로 처리
			CString strLine = m_strBuffer.Left(nIndex);

			// 처리한 부분은 버퍼에서 제거
			m_strBuffer = m_strBuffer.Mid(nIndex + 2);

			if (!strLine.IsEmpty())
			{
				// 서버 화면에 표시
				m_pDlg->AddMessageToList(strLine);

				// 다른 클라이언트에게 브로드캐스트
				POSITION pos = m_pDlg->m_clientSocketList.GetHeadPosition();
				while (pos != NULL)
				{
					CClientSocket* pClient = (CClientSocket*)m_pDlg->m_clientSocketList.GetNext(pos);
					if (pClient != NULL && pClient != this)
					{
						// 다른 클라이언트에게 보낼 때도 줄바꿈을 추가해준다.
						CString lineToSend = strLine + _T("\r\n");
						CT2A ascii(lineToSend);
						pClient->Send(ascii.m_psz, strlen(ascii.m_psz));
					}
				}
			}
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{

	m_pDlg->AddMessageToList(_T("Client Disconnected"));
	POSITION pos = m_pDlg->m_clientSocketList.Find(this);

	if (pos != NULL)
	{
		m_pDlg->m_clientSocketList.RemoveAt(pos);
	}
	delete this;

	CAsyncSocket::OnClose(nErrorCode);
}
