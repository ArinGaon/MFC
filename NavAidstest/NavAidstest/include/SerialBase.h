#pragma once


namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSerialBase
	{
	public:
		// contruction and destruction
		CSerialBase(void);
		virtual ~CSerialBase(void);

	public:
		// Serial Port를 연다.
		virtual BOOL OpenPort(WORD wPortID, DWORD dwBaud);
		virtual BOOL OpenPort(WORD wPortID, DWORD dwBaud, BYTE byParity, BYTE byDataBits, BYTE byStopBits);
		// Serial Port를 닫는다.
		void ClosePort();
		// serial port에 데이터를 쓴다.
		DWORD WriteComm(BYTE* pBuffer, DWORD nToWrite);
		// 쓰레드가 메시지를 보내온 경우 이 함수를 이용해서 데이터를 읽는다.
		DWORD ReadComm(BYTE* pBuffer, DWORD nToRead);
		// 연결된 상태 정보를 리턴하는 함수, TRUE면 연결상태
		BOOL IsOpened() { return m_bOpened; }

	protected:
		virtual BOOL OnDetectBreak() = 0;	// A break was detected on input.
		virtual BOOL OnChangedCTS() = 0;	// The CTS (clear-to-send) signal changed state.
		virtual BOOL OnChangedDSR() = 0;	// The DSR (data-set-ready) signal changed state.
		virtual BOOL OnDetectError() = 0;	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY.
		virtual BOOL OnDetectRing() = 0;	// A ring indicator was detected.
		virtual BOOL OnChangedRLSD() = 0;	// The RLSD (receive-line-signal-detect) signal changed state.
		virtual BOOL OnReceiveFlag() = 0;	// The event character was received and placed in the input buffer.
		virtual BOOL OnTxEmpty() = 0;	// The last character in the output buffer was sent.
		virtual BOOL OnReceiveData() = 0;	// A character was received and placed in the input buffer.

		void CommLock();
		void CommUnlock();

		INT WatchingCommThread();

		static INT __stdcall _WatchingCommThread(void* p) {
			return ((CSerialBase*)p)->WatchingCommThread();
		}

	protected:
		BOOL			m_bOpened;				// 포트가 열렸는지 유무를 나타냄.

		HANDLE			m_hComm;				// 통신 포트 파일 핸들
		HANDLE			m_hThreadComm;			// 포트를 감시할 쓰레드 함수 핸들.
		WORD			m_wPortID;				// 여러개의 포트를 열었을 경우 어떤 포트인지 식별하기 위해서 사용한다.
		OVERLAPPED		m_ovRead;				// 포트 파일 IO를 위한 Overlapped structure
		OVERLAPPED		m_ovWrite;
		DWORD			m_dwCommMask;			// 포트 이벤트
		BOOL			m_bBeClosing;			// 포트가 현재 닫는중인지를 알수 있는 플래그

	private:
		BOOL			m_bThreadAlive;			// thread 상태
		HANDLE			m_hExitEvent;			// Thread 종료 이벤트

		// synchronisation objects
		CRITICAL_SECTION	m_csCommunicationSync;
	};
}