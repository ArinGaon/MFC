#pragma once

#include "SerialBase.h"

#include "SerialMsgMngr.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSerialNMEA : public CSerialBase
	{
	public:
		CSerialNMEA();
		virtual ~CSerialNMEA();

	public:
		BOOL Start(WORD wPortID, DWORD dwBaudrate);
		void Stop();
		// юс╫ц╥н public*********************
		void ParseMsg();
		//***********************************
		void SetMsgMngr(CSerialMsgMngr* const pSerialMsgMngr);

	protected:
		virtual BOOL OnDetectBreak() { return TRUE; }		// A break was detected on input.
		virtual BOOL OnChangedCTS() { return TRUE; }		// The CTS (clear-to-send) signal changed state.
		virtual BOOL OnDetectError() { return TRUE; }		// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY.
		virtual BOOL OnDetectRing() { return TRUE; }		// A ring indicator was detected.
		virtual BOOL OnChangedRLSD() { return TRUE; }		// The RLSD (receive-line-signal-detect) signal changed state.
		virtual BOOL OnReceiveFlag() { return TRUE; }		// The event character was received and placed in the input buffer.
		virtual BOOL OnTxEmpty() { return TRUE; }			// The last character in the output buffer was sent.
		virtual BOOL OnChangedDSR() { return TRUE; }		// The DSR (data-set-ready) signal changed state.
		virtual BOOL OnReceiveData();
		
		

	private:
		CSerialMsgMngr* m_pSerialMsgMngr;
		static const UINT m_unNMEA_BUFF_LENGTH = 2048;

		BYTE* m_pMsgStoreBuffer;
		BYTE* m_pMsgTempBuffer;
		INT m_nRcvDataCnt;
	};
}

