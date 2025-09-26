#include "pch.h"
#include "CClientSocket.h"
#include "MFCServerDlg.h"
#include "resource.h" // IDC_STATIC_STATUS ����� ����

// Ŭ���̾�Ʈ�κ��� �޽����� �����ϸ� �ڵ����� ȣ��
void CClientSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	// �����͸� szBuffer�� �о����, �о�� ����Ʈ ���� nRead�� ����
	int nRead = Receive(szBuffer, sizeof(szBuffer));
	if (nRead > 0)
	{
		szBuffer[nRead] = '\0';
		CString strMessage(szBuffer);

		m_pDlg->AddMessageToList(strMessage);

		POSITION pos = m_pDlg->m_clientSocketList.GetHeadPosition();
		while (pos != NULL)
		{
			CClientSocket* pClient = (CClientSocket*)m_pDlg->m_clientSocketList.GetNext(pos);
			if (pClient != NULL && pClient != this)
			{
				CT2A ascii(strMessage);
				pClient->Send(ascii.m_psz, strlen(ascii.m_psz));
			}
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

// ���� ������ �� �ڵ� ȣ��
void CClientSocket::OnClose(int nErrorCode)
{
	// ���� Dlg�� UI�� ������Ʈ �Ͽ� ���� ���� ��� ����
	m_pDlg->AddMessageToList(_T("Ŭ���̾�Ʈ ���� ����"));
	POSITION pos = m_pDlg->m_clientSocketList.Find(this);

	if (pos != NULL)
	{
		m_pDlg->m_clientSocketList.RemoveAt(pos);
	}
	delete this;
	// m_pDlg->SetDlgItemTextW(IDC_STATIC_STATUS, _T("Ŭ���̾�Ʈ ��� ��..."));

	CAsyncSocket::OnClose(nErrorCode);
}
