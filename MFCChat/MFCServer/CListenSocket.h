#pragma once
#pragma once
#include <afxsock.h>

class CMFCServerDlg;

class CListenSocket : public CAsyncSocket
{
public:
    CMFCServerDlg* m_pDlg;
    void OnAccept(int nErrorCode);
};

