#pragma once

#include <afxstr.h>

#include "NMEAFormat.h"
#include "AISMsgFormat.h"

namespace NS_SALUS_MS_APP
{
	enum class E_PARSING_RESULT : INT
	{
		ePARSING_NO_RESULT = 0,
		ePARSING_DONE_NMEA_GGA = 1,
		ePARSING_DONE_NMEA_GLL = 2,
		ePARSING_DONE_NMEA_GSV = 4,
		ePARSING_DONE_NMEA_MHU = 5,
		ePARSING_DONE_NMEA_MMB = 6,
		ePARSING_DONE_NMEA_MTA = 7,
		ePARSING_DONE_NMEA_MWV = 8,
		ePARSING_DONE_NMEA_RMC = 9,
		ePARSING_DONE_NMEA_HDT = 10,
		ePARSING_DONE_NMEA_VTG = 11,

		ePARSING_DONE_AIS_TYPE1 = 30,
		ePARSING_DONE_AIS_TYPE2 = 31,
		ePARSING_DONE_AIS_TYPE3 = 32,
		ePARSING_DONE_AIS_TYPE4 = 33,
		ePARSING_DONE_AIS_TYPE5 = 34,
		ePARSING_DONE_AIS_TYPE9 = 35,
		ePARSING_DONE_AIS_TYPE18 = 36,
		ePARSING_DONE_AIS_TYPE19 = 37,
		ePARSING_DONE_AIS_TYPE21 = 38,
		ePARSING_DONE_AIS_TYPE24 = 39,
		ePARSING_DONE_AIVDO_TYPE1 = 40,
		ePARSING_DONE_AIVDO_TYPE18 = 41,
		ePARSING_DONE_AIVDO_TYPE19 = 42,

		ePARSING_DONE_EHS_HEADING = 43,
		ePARSING_DONE_EHS_TURNRATE = 44,
		ePARSING_DONE_EHS_HEAVE = 45,
		ePARSING_DONE_EHS_ATTITUDE = 46,
		ePARSING_DONE_NMEA_HDG = 47
	};

	class CNMEAParser
	{
	public:
		CNMEAParser();

	public:
		E_PARSING_RESULT Parsing(BYTE* const pDataPtr, const UINT nDataSize);

		E_PARSING_RESULT Parsing(CString strMsg);

		T_NMEA_CAN* GetNMEA_CAN();
		T_NMEA_GGA* GetNMEA_GGA();
		T_NMEA_GLL* GetNMEA_GLL();
		T_NMEA_GSA* GetNMEA_GSA();
		T_NMEA_GSV* GetNMEA_GSV();
		T_NMEA_MHU* GetNMEA_MHU();
		T_NMEA_MMB* GetNMEA_MMB();
		T_NMEA_MTA* GetNMEA_MTA();
		T_NMEA_MWV* GetNMEA_MWV();
		T_NMEA_RMC* GetNMEA_RMC();
		T_NMEA_HDT* GetNMEA_HDT();
		T_NMEA_VTG* GetNMEA_VTG();

		T_AIS_MSG_TYPE1_3* GetAIS_TYPE1();
		T_AIS_MSG_TYPE1_3* GetAIS_TYPE2();
		T_AIS_MSG_TYPE1_3* GetAIS_TYPE3();
		T_AIS_MSG_TYPE4* GetAIS_TYPE4();
		T_AIS_MSG_TYPE5* GetAIS_TYPE5();
		T_AIS_MSG_TYPE9* GetAIS_TYPE9();
		T_AIS_MSG_TYPE14* GetAIS_TYPE14();
		T_AIS_MSG_TYPE18* GetAIS_TYPE18();
		T_AIS_MSG_TYPE19* GetAIS_TYPE19();
		T_AIS_MSG_TYPE21* GetAIS_TYPE21();
		T_AIS_MSG_TYPE24* GetAIS_TYPE24();
		T_AIS_MSG_TYPESART* GetAIS_TYPESART();
		T_AIS_MSG_TYPEAIVDO1* GetAIS_TYPEAIVDO1();
		T_AIS_MSG_TYPEAIVDO18* GetAIS_TYPEAIVDO18();
		T_AIS_MSG_TYPEAIVDO19* GetAIS_TYPEAIVDO19();

	protected:
		E_PARSING_RESULT FetchCAN(const CString strMsg);
		void FetchGGA(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchGLL(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchGSA(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchGSV(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchMHU(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchMMB(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchMTA(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchMWV(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchRMC(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchHDT(BYTE* const pDataPtr, const UINT nDataSize);
		void FetchHDG(BYTE* const pDataPtr, const UINT nDataSize);
		E_PARSING_RESULT FetchVDM(const CString strMsg);
		E_PARSING_RESULT FetchVDO(const CString strMsg);
		void FetchVTG(BYTE* const pDataPtr, const UINT nDataSize);

		void FetchAISType1_3(CString strData, T_AIS_MSG_TYPE1_3& tAisMsg);
		void FetchAISType4(CString strData);
		void FetchAISType5(CString strData);
		void FetchAISType9(CString strData);
		void FetchAISType14(CString strData);
		void FetchAISType18(CString strData);
		void FetchAISType19(CString strData);
		void FetchAISType21(CString strData);
		void FetchAISType24(CString strData);

		void FetchAIVDOType1(CString strData);
		void FetchAIVDOType18(CString strData);
		void FetchAIVDOType19(CString strData);

	private:
		T_NMEA_CAN m_tNMEA_CAN;
		T_NMEA_GGA m_tNMEA_GGA;
		T_NMEA_GLL m_tNMEA_GLL;
		T_NMEA_GSA m_tNMEA_GSA;
		T_NMEA_GSV m_tNMEA_GSV;
		T_NMEA_MHU m_tNMEA_MHU;
		T_NMEA_MMB m_tNMEA_MMB;
		T_NMEA_MTA m_tNMEA_MTA;
		T_NMEA_MWV m_tNMEA_MWV;
		T_NMEA_RMC m_tNMEA_RMC;
		T_NMEA_HDT m_tNMEA_HDT;
		T_NMEA_VTG m_tNMEA_VTG;

		UCHAR m_ucLastType = 0U;

		T_AIS_MSG_TYPE1_3 m_tAISType1;
		T_AIS_MSG_TYPE1_3 m_tAISType2;
		T_AIS_MSG_TYPE1_3 m_tAISType3;
		T_AIS_MSG_TYPE4 m_tAISType4;
		T_AIS_MSG_TYPE5 m_tAISType5;
		T_AIS_MSG_TYPE9 m_tAISType9;
		T_AIS_MSG_TYPE14 m_tAISType14;
		T_AIS_MSG_TYPE18 m_tAISType18;
		T_AIS_MSG_TYPE19 m_tAISType19;
		T_AIS_MSG_TYPE21 m_tAISType21;
		T_AIS_MSG_TYPE24 m_tAISType24;
		T_AIS_MSG_TYPESART   m_tAISTypeSart;

		T_AIS_MSG_TYPEAIVDO1 m_tAISTypeAIVDO1;
		T_AIS_MSG_TYPEAIVDO18 m_tAISTypeAIVDO18;
		T_AIS_MSG_TYPEAIVDO19 m_tAISTypeAIVDO19;

		CString m_strAisMsgType1;
		CString m_strAisMsgType2;
		CString m_strAisMsgType3;
		CString m_strAisMsgType4;
		CString m_strAisMsgType5;
		CString m_strAisMsgType9;
		CString m_strAisMsgType14;
		CString m_strAisMsgType18;
		CString m_strAisMsgType19;
		CString m_strAisMsgType21;
		CString m_strAisMsgType24;

		CString m_strAIVDOMsgType1;
		CString m_strAIVDOMsgType5;
		CString m_strAIVDOMsgType14;
		CString m_strAIVDOMsgType18;
		CString m_strAIVDOMsgType19;

		CString m_strFile;

		void Savelog(CString Msg);
	};

} // NS_SALUS_MS_APP