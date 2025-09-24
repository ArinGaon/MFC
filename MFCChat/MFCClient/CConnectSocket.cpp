#include "pch.h"
#include "CConnectSocket.h"
#include "MFCClientDlg.h"

void CConnectSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		m_pDlg->AddMessageToList(_T("서버에 접속 완료"));
	}
	else
	{
		m_pDlg->AddMessageToList(_T("서버 접속 실패"));
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CConnectSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	int nRead = Receive(szBuffer, sizeof(szBuffer));
	szBuffer[nRead] = '\0';

	m_pDlg->AddMessageToList(CString(szBuffer));

	CAsyncSocket::OnReceive(nErrorCode);
}

void CConnectSocket::OnClose(int nErrorCode)
{
	m_pDlg->AddMessageToList(_T("서버와 연결이 종료됨"));
	CAsyncSocket::OnClose(nErrorCode);
}