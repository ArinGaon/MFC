#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h" // CClientSocket Ŭ������ �˾ƾ� �ϹǷ� �߰�

void CListenSocket::OnAccept(int nErrorCode)
{
	// --- �� �Լ� ��ü�� ��ü�մϴ� ---
	// 1. �� Ŭ���̾�Ʈ�� ���� ������ '���� �Ҵ�'���� ���� ����ϴ�.
	CClientSocket* pClient = new CClientSocket;

	// 2. ������ �����ϰ�, �����ϸ� ����Ʈ�� �߰��մϴ�.
	if (Accept(*pClient)) {
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient); // ����Ʈ�� �� �ڿ� �߰�
		m_pDlg->AddMessageToList(_T("[����] Ŭ���̾�Ʈ�� ����Ǿ����ϴ�."));
		m_pDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("Ŭ���̾�Ʈ �����"));
	}
	else {
		delete pClient; // �����ϸ� ����
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
