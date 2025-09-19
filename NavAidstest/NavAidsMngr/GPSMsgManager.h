#pragma once

#include "SerialMsgMngr.h"
#include "NMEAParser.h"

#include "NavigationInfo.h"

namespace NS_SALUS_MS_APP
{
	class CGPSMsgManager
	{
	public:
		CGPSMsgManager();
		~CGPSMsgManager();

	public:
		void Initialize();
		void Finalize();

		void Start();
		void Stop();

		void ClearMsg();

		BOOL IsStarted();
		CSerialMsgMngr* GetSerialMsgMngr();

	protected:
		void UpdateGPSInfo(const E_PARSING_RESULT eParsingResult);

		void CopyGPSInfo(const T_NMEA_GGA* const pGGA);
		void CopyGPSInfo(const T_NMEA_GLL* const pGLL);
		void CopyGPSInfo(const T_NMEA_RMC* const pRMC);
		void CopyGPSInfo(const T_NMEA_HDT* const pHDT);
		void CopyGPSInfo(const T_NMEA_VTG* const pVTG);

	private:
		void CreateMsgProcThread();
		void ExitMsgProcThread();

		void GPSMsgProcThread();
		static UINT GPSMsgProcThread(LPVOID const lpParam);

	private:
		BOOL m_bStarted;

		T_GPS_DATETIME* m_pGpsDateTime;
		T_GPS_POSITION* m_pGpsPosition;
		T_GPS_SHIP_INFO* m_pGpsShipInfo;

		CSerialMsgMngr* m_pSerialMsgGPS;
		CNMEAParser* m_pMsgParserGPS;

		// GPS MSG Process
		CWinThread* m_pGPSMsgProcThread;
		HANDLE m_hGPSMsgProcExitEvent;
	};

} // NS_SALUS_MS_APP