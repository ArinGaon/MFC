#pragma once
#include <afxsock.h>

class CMFCClientDlg;

class CConnectSocket : public CAsyncSocket
{
public:
	CMFCClientDlg* m_pDlg;
	void OnConnect(int nErrorCode);
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};

