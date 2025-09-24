#include "pch.h"
#include "CConnectSocket.h"
#include "MFCClientDlg.h"

void CConnectSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		m_pDlg->AddMessageToList(_T("������ ���� �Ϸ�"));
	}
	else
	{
		m_pDlg->AddMessageToList(_T("���� ���� ����"));
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
	m_pDlg->AddMessageToList(_T("������ ������ �����"));
	CAsyncSocket::OnClose(nErrorCode);
}