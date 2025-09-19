// SerialBase.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "SerialBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CSerialBase::CSerialBase(void)
		: m_hComm(NULL)
		, m_hExitEvent(NULL)
		, m_wPortID(0U)
		, m_bOpened(FALSE)
		, m_bThreadAlive(FALSE)
		, m_bBeClosing(FALSE)
		, m_hThreadComm(NULL)
	{
		// initialize overlapped structure members to zero
		m_ovRead.Offset = 0;
		m_ovRead.OffsetHigh = 0;
		m_ovRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		m_ovWrite.Offset = 0;
		m_ovWrite.OffsetHigh = 0;
		m_ovWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


		m_dwCommMask = EV_RXCHAR; //  | EV_DSR | EV_CTS | EV_TXEMPTY;

		// Thread Exit Event를 만든다.
		m_hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		// initialize critical section
		InitializeCriticalSection(&m_csCommunicationSync);
	}

	CSerialBase::~CSerialBase(void)
	{
		BOOL bReturn;

		ClosePort();

		bReturn = ResetEvent(m_ovRead.hEvent);
		if (bReturn == FALSE)
		{
#ifdef _DEBUG
			OutputDebugString("ResetEvent Fail\n");
#endif
		}
		CloseHandle(m_ovRead.hEvent);

		bReturn = ResetEvent(m_ovWrite.hEvent);
		if (bReturn == FALSE)
		{
#ifdef _DEBUG
			OutputDebugString("ResetEvent Fail\n");
#endif
		}
		CloseHandle(m_ovWrite.hEvent);

		if (m_hExitEvent)
		{
			CloseHandle(m_hExitEvent);
		}

		DeleteCriticalSection(&m_csCommunicationSync);
	}

	BOOL CSerialBase::OpenPort(WORD wPortID, DWORD dwBaud)
	{
		return OpenPort(wPortID, dwBaud, 0U, 8U, 0U);
	}

	BOOL CSerialBase::OpenPort(WORD wPortID, DWORD dwBaud, BYTE byParity, BYTE byDataBits, BYTE byStopBits)
	{
		DCB				dcb;			// Serial Port의 특성를 설정하기 위한 구조체
		DWORD			dwThreadID;
		COMMTIMEOUTS	tCommTimeouts;	// 포트 time out structure
		char			szPortName[64];
		BOOL			bReturnValue = FALSE;

		if (wPortID >= 4U)		// COM5 이상이면
		{
			_stprintf_s(szPortName, 64, _T("\\\\.\\COM%d"), wPortID + 1U);
		}
		else
		{
			_stprintf_s(szPortName, 64, _T("COM%d"), wPortID + 1U);
		}

		m_bOpened = FALSE;
		m_bBeClosing = FALSE;

		// overlapped structure 초기화
		m_ovRead.Offset = 0;
		m_ovRead.OffsetHigh = 0;
		if (m_ovRead.hEvent != NULL)
		{
			m_ovWrite.Offset = 0;
			m_ovWrite.OffsetHigh = 0;
			if (m_ovWrite.hEvent != NULL)
			{
				CommLock();

				m_wPortID = wPortID;

				//_stprintf_s( szPortName, 100, "\\\\.\\H:");
				m_hComm = CreateFile(szPortName,						// communication port string (COMX)"
					GENERIC_READ | GENERIC_WRITE,		// read/write types
					0,								// comm devices must be opened with exclusive access
					NULL,								// no security attributes
					OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
					FILE_FLAG_OVERLAPPED,				// Async I/O
					0);								// template must be 0 for comm devices

				if (m_hComm == INVALID_HANDLE_VALUE)
				{
					CommUnlock();
				}
				else
				{
					// set the timeout values
					tCommTimeouts.ReadIntervalTimeout = 1000U;
					tCommTimeouts.ReadTotalTimeoutMultiplier = 1000U;
					tCommTimeouts.ReadTotalTimeoutConstant = 1000U;
					tCommTimeouts.WriteTotalTimeoutMultiplier = 1000U;
					tCommTimeouts.WriteTotalTimeoutConstant = 1000U;

					static_cast<void>(SetCommTimeouts(m_hComm, &tCommTimeouts));

					// comm event 설정
					static_cast<void>(SetCommMask(m_hComm, m_dwCommMask));

					// Serial Port장치의 InQueue, OutQueue 크기 설정
					static_cast<void>(SetupComm(m_hComm, 4096U, 4096U));

					// dcb 설정
					dcb.DCBlength = sizeof(DCB);
					GetCommState(m_hComm, &dcb);
					dcb.BaudRate = dwBaud;
					dcb.ByteSize = byDataBits;
					dcb.Parity = byParity;
					dcb.StopBits = byStopBits;
					dcb.fRtsControl = RTS_CONTROL_ENABLE;

					if (SetCommState(m_hComm, &dcb) == FALSE)
					{
						CommUnlock();
					}
					else
					{
						CommUnlock();

						m_hThreadComm = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_WatchingCommThread, this, 0, &dwThreadID);

						if (m_hThreadComm == NULL)
						{
#ifdef _DEBUG
							OutputDebugString("Comm Thread Creating Failed\n");
#endif
							ClosePort();
						}
						else
						{
							m_bOpened = TRUE;
							bReturnValue = TRUE;
						}
					}
				}
			}
		}


		return bReturnValue;
	} 

	void CSerialBase::ClosePort()
	{
		m_bBeClosing = TRUE;

		BOOL bReturn = ResetEvent(m_ovRead.hEvent);
		if (bReturn == FALSE)
		{
#ifdef _DEBUG
			OutputDebugString("ResetEvent Fail\n");
#endif
		}

		int	nTryCnt = 1000;
		BOOL bReturnValue;

		// Thread를 종료 시킨다.
		if (m_hThreadComm > 0)
		{
			while (m_bThreadAlive == TRUE)
			{
				bReturnValue = SetEvent(m_hExitEvent);

				if (bReturnValue == FALSE)
				{
#ifdef _DEBUG
					OutputDebugString("SetEventError!!!\n");
#endif
				}

				--nTryCnt;
				if (nTryCnt < 0)
				{
					TerminateThread(m_hThreadComm, 0);
					break;
				}

				Sleep(5);
			}
		}
		m_hThreadComm = NULL;

		Sleep(50);

		if (m_bOpened == TRUE)
		{
			// 모든 이벤트 Mask를 없앤다.
			SetCommMask(m_hComm, 0);
			// 통신 Queue들을 초기화 한다.
			PurgeComm(m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
		}

		// 파일 핸들을 닫는다.
		if (m_hComm)
			CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	void CSerialBase::CommLock()
	{
		EnterCriticalSection(&m_csCommunicationSync);
	}

	void CSerialBase::CommUnlock()
	{
		LeaveCriticalSection(&m_csCommunicationSync);
	}

	INT CSerialBase::WatchingCommThread()
	{
		DWORD		dwEvent = 0U;
		DWORD		dwError = 0;
		DWORD		dwEventMask = 0;
		BOOL		bResult = TRUE;
		COMSTAT		comstat;
		HANDLE		hEventArray[2];
		BOOL		bQuit = FALSE;
		INT			nWhileQuit = 0;

		m_bThreadAlive = TRUE;

		// 통신 Queue들을 초기화 한다.
		if (m_bOpened == TRUE)
			PurgeComm(m_hComm, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

		// 이벤트를 등록한다.
		hEventArray[0] = m_hExitEvent;
		hEventArray[1] = m_ovRead.hEvent;

		// begin forever loop.  This loop will run as long as the thread is alive.
		while (nWhileQuit <= 0)
		{
			if ((bQuit == TRUE) || (m_bOpened == FALSE))
			{
				nWhileQuit++;
				continue;
			}

			if (m_bBeClosing == TRUE)
			{
				nWhileQuit++;
				continue;
			}

			bResult = WaitCommEvent(m_hComm, &dwEvent, &m_ovRead);

			if (m_bBeClosing == TRUE)
			{
				nWhileQuit++;
				continue;
			}

			if (!bResult)
			{
				// If WaitCommEvent() returns FALSE, process the last error to determin
				// the reason..
				dwError = GetLastError();
				switch (dwError)
				{
				case ERROR_IO_PENDING:
				{
					// This is a normal return value if there are no bytes
					// to read at the port.
					// Do nothing and continue
					break;
				}
				case 87:
				{
					// Under Windows NT, this value is returned for some reason.
					// I have not investigated why, but it is also a valid reply
					// Also do nothing and continue.
					break;
				}
				default:
				{
					// All other error codes indicate a serious error has
					// occured.  Process this error.
					break;
				}
				}
			}
			else
			{
				bResult = ClearCommError(m_hComm, &dwError, &comstat);
				if (comstat.cbInQue == 0 && m_bBeClosing == FALSE)
				{
					nWhileQuit++;
					continue;
				}
			}

			if (bQuit == TRUE)
			{
				nWhileQuit++;
				continue;
			}

			dwEvent = WaitForMultipleObjects(2, hEventArray, FALSE, 100U);

			if (m_bBeClosing == TRUE)
			{
				nWhileQuit++;
				continue;
			}

			switch (dwEvent)
			{
			case WAIT_OBJECT_0 + 0:
				// exit event.  This is event zero so it will be
				// the higest priority and be serviced first.
				bQuit = TRUE;
				break;
			case WAIT_OBJECT_0 + 1:	// comm event
				GetCommMask(m_hComm, &dwEventMask);
				if (dwEventMask & EV_BREAK) {
					OnDetectBreak();
				}
				if (dwEventMask & EV_CTS) {
					OnChangedCTS();
				}
				if (dwEventMask & EV_DSR) {
					OnChangedDSR();
				}
				if (dwEventMask & EV_ERR) {
					OnDetectError();
				}
				if (dwEventMask & EV_RING) {
					OnDetectRing();
				}
				if (dwEventMask & EV_RLSD) {
					OnChangedRLSD();
				}
				if (dwEventMask & EV_RXFLAG) {
					OnReceiveFlag();
				}
				if (dwEventMask & EV_TXEMPTY) {
					OnTxEmpty();
				}
				if (dwEventMask & EV_RXCHAR) {
					// Receive character event from port.
					OnReceiveData();
				}
				break;
			default:
				break;
			}
		}

		m_bThreadAlive = FALSE;
		ExitThread(0);

		return 0;
	}

	// 포트에 pBuff의 내용을 nToWrite만큼 쓴다.
	// 실제로 쓰여진 Byte수를 리턴한다.
	DWORD CSerialBase::WriteComm(BYTE* pBuffer, DWORD nToWrite)
	{
		DWORD	dwWritten = 0, dwError, dwErrorFlags;
		COMSTAT	comstat;
		INT	nWhileQuit = 0;

		CommLock();

		m_ovWrite.Offset = 0;
		m_ovWrite.OffsetHigh = 0;

		if (!WriteFile(m_hComm, pBuffer, nToWrite, &dwWritten, &m_ovWrite))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				// 읽을 문자가 남아 있거나 전송할 문자가 남아 있을 경우 Overapped IO의
				// 특성에 따라 ERROR_IO_PENDING 에러 메시지가 전달된다.
				//timeouts에 정해준 시간만큼 기다려준다.
				while (nWhileQuit <= 0)
				{
					if (GetOverlappedResult(m_hComm, &m_ovWrite, &dwWritten, TRUE) == TRUE)
					{
						nWhileQuit++;
						continue;
					}

					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError(m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				ClearCommError(m_hComm, &dwErrorFlags, &comstat);
			}
		}

		CommUnlock();

		return dwWritten;
	}

	// 포트로부터 pBuff에 nToRead만큼 읽는다.
	// 실제로 읽혀진 Byte수를 리턴한다.
	DWORD CSerialBase::ReadComm(BYTE* pBuffer, DWORD nToRead)
	{
		DWORD	dwRead, dwError, dwErrorFlags;
		BOOL	bResult = TRUE;
		COMSTAT	comstat;
		DWORD dwReturnValue = 0;
		INT nWhileQuit = 0;

		// Gain ownership of the comm port critical section.
		// This process guarantees no other part of this program 
		// is using the port object. 
		CommLock();

		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.
		ClearCommError(m_hComm, &dwErrorFlags, &comstat);
		dwRead = comstat.cbInQue;
		CommUnlock();

		if (dwRead != 0)
		{
			CommLock();

			nToRead = min(nToRead, dwRead);

			bResult = ReadFile(m_hComm, pBuffer, nToRead, &dwRead, &m_ovRead);

			if (!bResult)
			{
				dwError = GetLastError();
				if (dwError == ERROR_IO_PENDING)
				{
					//--------- timeouts에 정해준 시간만큼 기다려준다.
					while (nWhileQuit <= 0)
					{
						if (m_bBeClosing == TRUE)
						{
							nWhileQuit++;
							continue;
						}

						if (GetOverlappedResult(m_hComm, &m_ovRead, &dwRead, TRUE) == TRUE)
						{
							nWhileQuit++;
							continue;
						}

						dwError = GetLastError();
						if (dwError != ERROR_IO_INCOMPLETE)
						{
							ClearCommError(m_hComm, &dwErrorFlags, &comstat);
							break;
						}
					}
				}
				else
				{
					dwRead = 0;
					ClearCommError(m_hComm, &dwErrorFlags, &comstat);
				}
			}
			CommUnlock();

			dwReturnValue = dwRead;
		}

		return dwReturnValue;
	}
}