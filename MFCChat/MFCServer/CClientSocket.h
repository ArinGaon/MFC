#pragma once
#include <afxsock.h>
// #include "MFCServerDlg.h"

class CMFCServerDlg;

class CClientSocket : public CAsyncSocket
{
public:
	CString m_strBuffer; // 데이터 수신용 버퍼
	CMFCServerDlg* m_pDlg;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};

