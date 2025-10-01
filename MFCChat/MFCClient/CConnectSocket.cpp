#include "pch.h"
#include "CConnectSocket.h"
#include "MFCClientDlg.h"
#include "resource.h"

void CConnectSocket::OnConnect(int nErrorCode)
{
	CString str;
	str.Format(_T("DEBUG: OnConnect Called (ErrorCode: %d)"), nErrorCode);
	m_pDlg->AddMessageToList(str);
	if (nErrorCode == 0)
	{
		m_pDlg->AddMessageToList(_T("서버 접속 완료"));
		// ��ư ����
		m_pDlg->SetDlgItemText(IDC_BUTTON_CONNECT, _T("Disconnect"));
		m_pDlg->m_bConnected = TRUE;
	}
	else
	{
		m_pDlg->AddMessageToList(_T("서버 접속 실패"));
		m_pDlg->m_ConnectSocket.Close();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CConnectSocket::OnReceive(int nErrorCode)
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
				// 클라이언트 화면에 표시
				m_pDlg->AddMessageToList(strLine);
			}
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnClose(int nErrorCode)
{
	CString str;
	str.Format(_T("DEBUG: OnClose Called (ErrorCode: %d)"), nErrorCode);
	m_pDlg->AddMessageToList(str);
	m_pDlg->AddMessageToList(_T("서버 연결 종료됨"));
	// ��ư ����
	m_pDlg->SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
	m_pDlg->m_bConnected = FALSE;
	CAsyncSocket::OnClose(nErrorCode);
}