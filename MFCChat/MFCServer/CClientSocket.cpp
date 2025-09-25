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
	szBuffer[nRead] = '\0';
	// ���� Dlg ListBox�� ���� �޽��� ǥ��
	m_pDlg->AddMessageToList(CString(szBuffer));

	CAsyncSocket::OnReceive(nErrorCode);
}

// ���� ������ �� �ڵ� ȣ��
void CClientSocket::OnClose(int nErrorCode)
{
	// ���� Dlg�� UI�� ������Ʈ �Ͽ� ���� ���� ��� ����
	m_pDlg->AddMessageToList(_T("Ŭ���̾�Ʈ ���� ����"));
	m_pDlg->SetDlgItemTextW(IDC_STATIC_STATUS, _T("Ŭ���̾�Ʈ ��� ��..."));

	CAsyncSocket::OnClose(nErrorCode);
}
