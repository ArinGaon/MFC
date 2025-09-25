#include "pch.h"
#include "CClientSocket.h"
#include "MFCServerDlg.h"
#include "resource.h" // IDC_STATIC_STATUS 사용을 위함

// 클라이언트로부터 메시지가 도착하면 자동으로 호출
void CClientSocket::OnReceive(int nErrorCode)
{
	char szBuffer[1024];
	// 데이터를 szBuffer로 읽어오고, 읽어온 바이트 수를 nRead에 저장
	int nRead = Receive(szBuffer, sizeof(szBuffer));
	szBuffer[nRead] = '\0';
	// 메인 Dlg ListBox에 받은 메시지 표시
	m_pDlg->AddMessageToList(CString(szBuffer));

	CAsyncSocket::OnReceive(nErrorCode);
}

// 연결 끊겼을 때 자동 호출
void CClientSocket::OnClose(int nErrorCode)
{
	// 메인 Dlg의 UI를 업데이트 하여 연결 종료 사실 전달
	m_pDlg->AddMessageToList(_T("클라이언트 연결 종료"));
	m_pDlg->SetDlgItemTextW(IDC_STATIC_STATUS, _T("클라이언트 대기 중..."));

	CAsyncSocket::OnClose(nErrorCode);
}
