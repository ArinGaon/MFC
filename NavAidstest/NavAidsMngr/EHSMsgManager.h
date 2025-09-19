#pragma once

#include "SerialMsgMngr.h"
#include "NMEAParser.h"

#include "NavigationInfo.h"

namespace NS_SALUS_MS_APP
{
	class CEHSMsgManager
	{
	public:
		CEHSMsgManager();
		~CEHSMsgManager();

	public:
		void Initialize();
		void Finalize();

		void Start();
		void Stop();

		void ClearMsg();

		BOOL IsStarted();
		CSerialMsgMngr* GetSerialMsgMngr();

	protected:
		void UpdateEHSInfo(const E_PARSING_RESULT eParsingResult);

		void CopyEHSHeading(const T_NMEA_CAN* const pCAN);
		void CopyEHSTurnrate(const T_NMEA_CAN* const pCAN);
		void CopyEHSHeave(const T_NMEA_CAN* const pCAN);
		void CopyEHSAttitude(const T_NMEA_CAN* const pCAN);

	private:
		void CreateMsgProcThread();
		void ExitMsgProcThread();

		void EHSMsgProcThread();
		static UINT EHSMsgProcThread(LPVOID const lpParam);

	private:
		BOOL m_bStarted;

		T_EHS_INFO* m_pEHSInfo;

		CSerialMsgMngr* m_pSerialMsgEHS;
		CNMEAParser* m_pMsgParserEHS;

		// EHS MSG Process
		CWinThread* m_pEHSMsgProcThread;
		HANDLE m_hEHSMsgProcExitEvent;
	};
} // NS_SALUS_MS_APP