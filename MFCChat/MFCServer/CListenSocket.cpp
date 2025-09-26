#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h" // CClientSocket Ŭ������ �˾ƾ� �ϹǷ� �߰�

void CListenSocket::OnAccept(int nErrorCode)
{
	// �� Ŭ���̾�Ʈ�� ���� ������ ���� ����
	CClientSocket* pClient = new CClientSocket;

	// ������ �����ϰ�, �����ϸ� ����Ʈ�� �߰�
	if (Accept(*pClient)) 
	{
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient); // ����Ʈ�� �� �ڿ� �߰�
		m_pDlg->AddMessageToList(_T("Ŭ���̾�Ʈ�� �����."));
		// m_pDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("Ŭ���̾�Ʈ �����"));
	}
	else
	{
		delete pClient; // �����ϸ� ����
	}
		
	CAsyncSocket::OnAccept(nErrorCode);
}