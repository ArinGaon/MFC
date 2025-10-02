#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h"

void CListenSocket::OnAccept(int nErrorCode)
{
	if (nErrorCode != 0)
	{
		CAsyncSocket::OnAccept(nErrorCode);
		return;
	}
	CClientSocket* pClient = new CClientSocket;

	if (Accept(*pClient)) 
	{
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient);
		m_pDlg->AddMessageToList(_T("서버 접속 완료."));
	}
	else
	{
		delete pClient;
	}
		
	CAsyncSocket::OnAccept(nErrorCode);
}