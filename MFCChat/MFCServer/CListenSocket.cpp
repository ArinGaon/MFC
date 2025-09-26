#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h" // CClientSocket 클래스를 알아야 하므로 추가

void CListenSocket::OnAccept(int nErrorCode)
{
	// 새 클라이언트를 위한 소켓을 새로 만듬
	CClientSocket* pClient = new CClientSocket;

	// 연결을 수락하고, 성공하면 리스트에 추가
	if (Accept(*pClient)) 
	{
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient); // 리스트의 맨 뒤에 추가
		m_pDlg->AddMessageToList(_T("클라이언트가 연결됨."));
		// m_pDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("클라이언트 연결됨"));
	}
	else
	{
		delete pClient; // 실패하면 삭제
	}
		
	CAsyncSocket::OnAccept(nErrorCode);
}