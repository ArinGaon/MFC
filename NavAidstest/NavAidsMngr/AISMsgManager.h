#pragma once

#include "SerialMsgMngr.h"
#include "NMEAParser.h"

#include "AISDataMngr.h"

namespace NS_SALUS_MS_APP
{
	class CAISMsgManager
	{
	public:
		CAISMsgManager();
		~CAISMsgManager();

	public:
		void Initialize();
		void Finalize();

		void Start();
		void Stop();

		void ClearMsg();
		
		BOOL IsStarted();
		CSerialMsgMngr* GetSerialMsgMngr();

		UINT GetUpdateCount();
		SYSTEMTIME* GetLastUpdateTime();

	protected:
		void UpdateAISInfo(const E_PARSING_RESULT eParsingResult);

		void CopyAISInfo(const T_AIS_MSG_TYPE1_3* const pAisType1_3);
		void CopyAISInfo(const T_AIS_MSG_TYPE4* const pAisType4);
		void CopyAISInfo(const T_AIS_MSG_TYPE5* const pAisType5);
		void CopyAISInfo(const T_AIS_MSG_TYPE9* const pAisType9);
		void CopyAISInfo(const T_AIS_MSG_TYPE18* const pAisType18);
		void CopyAISInfo(const T_AIS_MSG_TYPE19* const pAisType19);
		void CopyAISInfo(const T_AIS_MSG_TYPE21* const pAisType21);
		void CopyAISInfo(const T_AIS_MSG_TYPE24* const pAisType24);
		void CopyAISInfo(const T_AIS_MSG_TYPEAIVDO1* const pAisTypeAIVDO);
		void CopyAISInfo(const T_AIS_MSG_TYPEAIVDO18* const pAisTypeAIVDO);
		void CopyAISInfo(const T_AIS_MSG_TYPEAIVDO19* const pAisTypeAIVDO);

	private:
		void CreateMsgProcThread();
		void ExitMsgProcThread();

		void AISMsgProcThread();
		static UINT AISMsgProcThread(LPVOID const lpParam);

	private:
		BOOL m_bStarted;
		T_AIS_DATA* m_pAISData;
		T_AIVDO_AIS* m_pAIVDOData;

		UINT m_unUpdateCount;
		SYSTEMTIME m_tLastUpdateTime;

		CSerialMsgMngr* m_pSerialMsgAIS;
		CNMEAParser* m_pMsgParserAIS;

		// AIS MSG Process
		CWinThread* m_pAISMsgProcThread;
		HANDLE m_hAISMsgProcExitEvent;
	};

} // NS_SALUS_MS_APP

