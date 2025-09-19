#include "pch.h"
#include "EHSFileReplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CEHSFileReplay::CEHSFileReplay()
	{
		m_bFirstData = TRUE;
		m_pDataReader = new CDataReader(FALSE);	// text file

		m_pSerialMsgMngr = NULL;

		m_hFileReplayExitEvent = CreateEvent(NULL, FALSE, FALSE, _T("EHS FILE REPLAY EXIT EVENT"));
		m_hFileReplayWorkEvent = CreateEvent(NULL, FALSE, FALSE, _T("EHS FILE REPLAY WORK EVENT"));
		m_pFileReplayThread = NULL;
	}

	CEHSFileReplay::~CEHSFileReplay()
	{
		ExitFileReplayThread();

		if (m_pDataReader != NULL)
		{
			m_pDataReader->Close();

			delete m_pDataReader;
			m_pDataReader = NULL;
		}

		CloseHandle(m_hFileReplayExitEvent);
		CloseHandle(m_hFileReplayWorkEvent);
	}

	void CEHSFileReplay::SetMsgManager(CSerialMsgMngr* const pSerialMsgMngr)
	{
		m_pSerialMsgMngr = pSerialMsgMngr;
	}

	void CEHSFileReplay::StartReplay(const TCHAR* const pszReplayFileName)
	{
		if (m_pDataReader != NULL)
		{
			if (m_pDataReader->IsOpen() == TRUE)
			{
				m_pDataReader->Close();
			}

			if (m_pDataReader->Open(pszReplayFileName) == TRUE)
			{
				m_pDataReader->SeekToBegin();
				m_bFirstData = TRUE;

				CreateFileReplayThread();
			}
		}
	}

	void CEHSFileReplay::StopRepaly()
	{
		ExitFileReplayThread();
	}

	HANDLE CEHSFileReplay::GetReplayWorkEvent()
	{
		return m_hFileReplayWorkEvent;
	}

	void CEHSFileReplay::CreateFileReplayThread()
	{
		m_pFileReplayThread = AfxBeginThread(static_cast<AFX_THREADPROC>(FileReplayThread), static_cast<LPVOID>(this), THREAD_PRIORITY_HIGHEST, 0U, static_cast<DWORD>(CREATE_SUSPENDED));
		if (m_pFileReplayThread != NULL)
		{
			m_pFileReplayThread->m_bAutoDelete = TRUE;
			static_cast<void>(m_pFileReplayThread->ResumeThread());
		}
	}

	void CEHSFileReplay::ExitFileReplayThread()
	{
		if (m_pFileReplayThread != NULL)
		{
			static_cast<void>(SetEvent(m_hFileReplayExitEvent));

			static_cast<void>(WaitForSingleObject(m_pFileReplayThread->m_hThread, static_cast<DWORD>(1000U)));
			m_pFileReplayThread = NULL;
		}
	}

	void CEHSFileReplay::FileReplayThread()
	{
		static UINT unCounter = 0U;
		static SYSTEMTIME tCurTime;
		static SYSTEMTIME tOldDataTime;
		static UINT unCaptureDuration = 50U;
		static USHORT usCounter = 0U;
		static BYTE byReadMsg[g_nMAX_SERIAL_MSG_LENGTH];

		UINT unDuration;
		//CString strOutput;

		if (m_pDataReader != NULL)
		{
			INT nQuit = 0;
			while (nQuit <= 0)
			{
				static_cast<void>(ZeroMemory(byReadMsg, sizeof(BYTE) * g_nMAX_SERIAL_MSG_LENGTH));
				if (m_pDataReader->Read(tCurTime, byReadMsg, g_nMAX_SERIAL_MSG_LENGTH) == TRUE)
				{
					if (m_bFirstData == TRUE)
					{
						usCounter = 0U;

						static_cast<void>(CopyMemory(&tOldDataTime, &tCurTime, sizeof(SYSTEMTIME)));
						m_bFirstData = FALSE;
					}

					// 메시지 저장
					if (m_pSerialMsgMngr != NULL)
					{
						m_pSerialMsgMngr->Push(byReadMsg, g_nMAX_SERIAL_MSG_LENGTH);
					}

					unDuration = ((tCurTime.wHour - tOldDataTime.wHour) * 3600 + (tCurTime.wMinute - tOldDataTime.wMinute) * 60 + (tCurTime.wSecond - tOldDataTime.wSecond)) * 1000;
					unDuration += (tCurTime.wMilliseconds - tOldDataTime.wMilliseconds);
					if (unDuration > unCaptureDuration)
					{
						nQuit++;
					}
				}
				else
				{
					nQuit++;
				}
			}

			static_cast<void>(CopyMemory(&tOldDataTime, &tCurTime, sizeof(SYSTEMTIME)));
		}
	}

	UINT CEHSFileReplay::FileReplayThread(LPVOID const lpParam)
	{
		CEHSFileReplay* const pFileReplay = static_cast<CEHSFileReplay*>(lpParam);

		if (pFileReplay != NULL)
		{
			INT nQuit = 0;
			HANDLE arrEvent[2];

			arrEvent[0] = pFileReplay->m_hFileReplayExitEvent;
			arrEvent[1] = pFileReplay->m_hFileReplayWorkEvent;

			while (nQuit < 1)
			{
				const DWORD dwEvent = WaitForMultipleObjects(2U, arrEvent, FALSE, INFINITE);
				switch (dwEvent)
				{
				case static_cast<DWORD>(WAIT_OBJECT_0 + 0U): // Exit Event
				{
					nQuit++;
					break;
				}
				case static_cast<DWORD>(WAIT_OBJECT_0 + 1U): // Work Event
				{
					pFileReplay->FileReplayThread();
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}

		return 0U;
	}

} // NS_SALUS_MS_APP