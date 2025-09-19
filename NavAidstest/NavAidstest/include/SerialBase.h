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
		// Serial Port�� ����.
		virtual BOOL OpenPort(WORD wPortID, DWORD dwBaud);
		virtual BOOL OpenPort(WORD wPortID, DWORD dwBaud, BYTE byParity, BYTE byDataBits, BYTE byStopBits);
		// Serial Port�� �ݴ´�.
		void ClosePort();
		// serial port�� �����͸� ����.
		DWORD WriteComm(BYTE* pBuffer, DWORD nToWrite);
		// �����尡 �޽����� ������ ��� �� �Լ��� �̿��ؼ� �����͸� �д´�.
		DWORD ReadComm(BYTE* pBuffer, DWORD nToRead);
		// ����� ���� ������ �����ϴ� �Լ�, TRUE�� �������
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
		BOOL			m_bOpened;				// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.

		HANDLE			m_hComm;				// ��� ��Ʈ ���� �ڵ�
		HANDLE			m_hThreadComm;			// ��Ʈ�� ������ ������ �Լ� �ڵ�.
		WORD			m_wPortID;				// �������� ��Ʈ�� ������ ��� � ��Ʈ���� �ĺ��ϱ� ���ؼ� ����Ѵ�.
		OVERLAPPED		m_ovRead;				// ��Ʈ ���� IO�� ���� Overlapped structure
		OVERLAPPED		m_ovWrite;
		DWORD			m_dwCommMask;			// ��Ʈ �̺�Ʈ
		BOOL			m_bBeClosing;			// ��Ʈ�� ���� �ݴ��������� �˼� �ִ� �÷���

	private:
		BOOL			m_bThreadAlive;			// thread ����
		HANDLE			m_hExitEvent;			// Thread ���� �̺�Ʈ

		// synchronisation objects
		CRITICAL_SECTION	m_csCommunicationSync;
	};
}