#include "pch.h"
#include "CListenSocket.h"
#include "MFCServerDlg.h"
#include "resource.h"
#include "CClientSocket.h" // CClientSocket 클래스를 알아야 하므로 추가

void CListenSocket::OnAccept(int nErrorCode)
{
	// --- 이 함수 전체를 교체합니다 ---
	// 1. 새 클라이언트를 위한 소켓을 '동적 할당'으로 새로 만듭니다.
	CClientSocket* pClient = new CClientSocket;

	// 2. 연결을 수락하고, 성공하면 리스트에 추가합니다.
	if (Accept(*pClient)) {
		pClient->m_pDlg = m_pDlg;
		m_pDlg->m_clientSocketList.AddTail(pClient); // 리스트의 맨 뒤에 추가
		m_pDlg->AddMessageToList(_T("[접속] 클라이언트가 연결되었습니다."));
		m_pDlg->SetDlgItemText(IDC_STATIC_STATUS, _T("클라이언트 연결됨"));
	}
	else {
		delete pClient; // 실패하면 삭제
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
