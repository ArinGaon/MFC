#pragma once

class AFX_EXT_CLASS CInterCommMngr
{
public:
	CInterCommMngr() noexcept;
	virtual ~CInterCommMngr();

public:
	static CInterCommMngr* GetInstance();
	static void DeleteInstance();

	void Initilize(CWnd* const pParentWnd);

	void ShowNetConnectDlg();
	void CheckNetConnection(const UINT unTimeout);
	void ReceivedHeartBeatResponse(const UINT unHeartBeatCount);

	void AddClient(CString strIpAddr);
	void StartServer(const INT nPortNo);
	void StopServer();

	void StartClient(CString strIpAddr, const INT nPortNo);
	void StopClient();

	void SendNetMsg(USHORT usInfoCode, void* const pDataBuff, const UINT unDataSize);

private:
	static  CInterCommMngr* m_pInstance;
};