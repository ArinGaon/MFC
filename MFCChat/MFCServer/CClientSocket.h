#pragma once
#include <afxsock.h>
// #include "MFCServerDlg.h"

class CMFCServerDlg;

class CClientSocket : public CAsyncSocket
{
public:
	CMFCServerDlg* m_pDlg;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};

