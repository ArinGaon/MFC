#include "pch.h"
#include "CConnectSocket.h"
#include "MFCClientDlg.h"
#include "resource.h"

void CConnectSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		m_pDlg->AddMessageToList(_T("������ ���� �Ϸ�"));
		// ��ư ����
		m_pDlg->SetDlgItemText(IDC_BUTTON_CONNECT, _T("Disconnect"));
		m_pDlg->m_bConnected = TRUE;
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
	// ��ư ����
	m_pDlg->SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
	m_pDlg->m_bConnected = FALSE;
	CAsyncSocket::OnClose(nErrorCode);
}