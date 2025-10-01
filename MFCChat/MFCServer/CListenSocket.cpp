#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h" // CClientSocket Ŭ������ �˾ƾ� �ϹǷ� �߰�

void CListenSocket::OnAccept(int nErrorCode)
{
	if (nErrorCode != 0)
	{
		CAsyncSocket::OnAccept(nErrorCode);
		return;
	}
	// �� Ŭ���̾�Ʈ�� ���� ������ ���� ����
	CClientSocket* pClient = new CClientSocket;

	// ������ �����ϰ�, �����ϸ� ����Ʈ�� �߰�
	if (Accept(*pClient)) 
	{
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient);
		m_pDlg->AddMessageToList(_T("서버 접속 완료."));
	}
	else
	{
		delete pClient; // �����ϸ� ����
	}
		
	CAsyncSocket::OnAccept(nErrorCode);
}