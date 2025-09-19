#pragma once

#include "SerialMsgMngr.h"
#include "DataReader.h"

namespace NS_SALUS_MS_APP
{
	class CGPSFileReplay
	{
	public:
		CGPSFileReplay();
		~CGPSFileReplay();

	public:
		void SetMsgManager(CSerialMsgMngr* const pSerialMsgMngr);

		void StartReplay(const TCHAR* const pszReplayFileName);
		void StopRepaly();

		HANDLE GetReplayWorkEvent();

	private:
		void CreateFileReplayThread();
		void ExitFileReplayThread();

		void FileReplayThread();
		static UINT FileReplayThread(LPVOID const lpParam);

	private:
		BOOL m_bFirstData;
		CDataReader* m_pDataReader;

		CSerialMsgMngr* m_pSerialMsgMngr;

		// GPS FILE REPLAY thread
		CWinThread* m_pFileReplayThread;
		HANDLE m_hFileReplayExitEvent;
		HANDLE m_hFileReplayWorkEvent;
	};

}	// NS_SALUS_MS_APP
