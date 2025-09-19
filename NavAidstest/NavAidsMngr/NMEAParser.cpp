#include "pch.h"
#include "NMEAParser.h"

#include "NMEAUtils.h"
#include "AISMsgUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

#define ROT_NAVALUE 128

#define SOG_NAVALUE 1023

#define LATITUDE_NAVALUE 91
#define LONGITUDE_NAVALUE 181

#define COG_NAVALUE 3600

#define HDT_NAVALUE 511

#define AIS_MSG_SART 14

#define ROT_NOTIMAX 127
#define ROT_NOTIMIN -127

#define SAVELOGAIS 0

namespace NS_SALUS_MS_APP
{
	CNMEAParser::CNMEAParser()
	{
		static_cast<void>(ZeroMemory(&m_tNMEA_CAN, sizeof(T_NMEA_CAN)));
		static_cast<void>(ZeroMemory(&m_tNMEA_GGA, sizeof(T_NMEA_GGA)));
		static_cast<void>(ZeroMemory(&m_tNMEA_GLL, sizeof(T_NMEA_GLL)));
		static_cast<void>(ZeroMemory(&m_tNMEA_GSA, sizeof(T_NMEA_GSA)));
		static_cast<void>(ZeroMemory(&m_tNMEA_GSV, sizeof(T_NMEA_GSV)));
		static_cast<void>(ZeroMemory(&m_tNMEA_MHU, sizeof(T_NMEA_MHU)));
		static_cast<void>(ZeroMemory(&m_tNMEA_MMB, sizeof(T_NMEA_MMB)));
		static_cast<void>(ZeroMemory(&m_tNMEA_MTA, sizeof(T_NMEA_MTA)));
		static_cast<void>(ZeroMemory(&m_tNMEA_MWV, sizeof(T_NMEA_MWV)));
		static_cast<void>(ZeroMemory(&m_tNMEA_RMC, sizeof(T_NMEA_RMC)));
		static_cast<void>(ZeroMemory(&m_tNMEA_VTG, sizeof(T_NMEA_VTG)));
		
		static_cast<void>(ZeroMemory(&m_tAISType1, sizeof(T_AIS_MSG_TYPE1_3)));
		static_cast<void>(ZeroMemory(&m_tAISType2, sizeof(T_AIS_MSG_TYPE1_3)));
		static_cast<void>(ZeroMemory(&m_tAISType3, sizeof(T_AIS_MSG_TYPE1_3)));
		static_cast<void>(ZeroMemory(&m_tAISType4, sizeof(T_AIS_MSG_TYPE4)));
		static_cast<void>(ZeroMemory(&m_tAISType5, sizeof(T_AIS_MSG_TYPE5)));
		static_cast<void>(ZeroMemory(&m_tAISType9, sizeof(T_AIS_MSG_TYPE9)));
		static_cast<void>(ZeroMemory(&m_tAISType14, sizeof(T_AIS_MSG_TYPE14)));
		static_cast<void>(ZeroMemory(&m_tAISType18, sizeof(T_AIS_MSG_TYPE18)));
		static_cast<void>(ZeroMemory(&m_tAISType19, sizeof(T_AIS_MSG_TYPE19)));
		static_cast<void>(ZeroMemory(&m_tAISType21, sizeof(T_AIS_MSG_TYPE21)));
		static_cast<void>(ZeroMemory(&m_tAISType24, sizeof(T_AIS_MSG_TYPE24)));
		static_cast<void>(ZeroMemory(&m_tAISTypeSart, sizeof(T_AIS_MSG_TYPESART)));
		
		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO1, sizeof(T_AIS_MSG_TYPEAIVDO1)));
		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO18, sizeof(T_AIS_MSG_TYPEAIVDO18)));
		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO19, sizeof(T_AIS_MSG_TYPEAIVDO19)));
		
		m_strAisMsgType1 = _T("");
		m_strAisMsgType2 = _T("");
		m_strAisMsgType3 = _T("");
		m_strAisMsgType4 = _T("");
		m_strAisMsgType5 = _T("");
		m_strAisMsgType9 = _T("");
		m_strAisMsgType14 = _T("");
		m_strAisMsgType18 = _T("");
		m_strAisMsgType19 = _T("");
		m_strAisMsgType21 = _T("");
		m_strAisMsgType24 = _T("");

		m_strAIVDOMsgType1 = _T("");
		m_strAIVDOMsgType5 = _T("");
		m_strAIVDOMsgType14 = _T("");
		m_strAIVDOMsgType18 = _T("");
		m_strAIVDOMsgType19 = _T("");

#if SAVELOGAIS
		SYSTEMTIME ste;
		GetLocalTime(&ste);

		CString strDate;
		strDate.Format("%4d-%02d-%02d %02d-%02d", ste.wYear, ste.wMonth, ste.wDay, ste.wHour, ste.wMinute);

		m_strFile.Format("%s", "d:\\" + strDate + ".txt"); 

#endif
	}

	E_PARSING_RESULT CNMEAParser::Parsing(BYTE* const pDataPtr, const UINT nDataSize)
	{
		CString strMsg = reinterpret_cast<TCHAR*>(pDataPtr);

		return Parsing(strMsg);
	}

	E_PARSING_RESULT CNMEAParser::Parsing(CString strMsg)
	{
		E_PARSING_RESULT eParsingResult = E_PARSING_RESULT::ePARSING_NO_RESULT;

		if (strMsg.Find(_T("CAN")) > 0)
		{
			eParsingResult = FetchCAN(strMsg);
		}
		else
		{
			if (CNMEAUtils::CheckChecksum(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength()) == TRUE)
			{
				if (strMsg.Find(_T("GGA")) > 0)
				{
					FetchGGA(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_GGA;
				}
				else if (strMsg.Find(_T("GLL")) > 0)
				{
					FetchGLL(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_GLL;
				}
				//else if (strMsg.Find(_T("GSA")) > 0)
				//{
				//	FetchGSA(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
				//	eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_GSA;
				//}
				//else if (strMsg.Find(_T("GSV")) > 0)
				//{
				//	FetchGSV(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
				//	eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_GSV;
				//}
				else if (strMsg.Find(_T("MHU")) > 0)
				{
					FetchMHU(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_MHU;
				}
				else if (strMsg.Find(_T("MMB")) > 0)
				{
					FetchMMB(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_MMB;
				}
				else if (strMsg.Find(_T("MTA")) > 0)
				{
					FetchMTA(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_MTA;
				}
				else if (strMsg.Find(_T("MWV")) > 0)
				{
					FetchMWV(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_MWV;
				}
				else if (strMsg.Find(_T("RMC")) > 0)
				{
					FetchRMC(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_RMC;
				}
				else if (strMsg.Find(_T("HDT")) > 0)
				{
					FetchHDT(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_HDT;
				}
				else if (strMsg.Find(_T("HDG")) > 0)
				{
					FetchHDG(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_HDG;
				}
				else if (strMsg.Find(_T("VDM")) > 0)
				{
					eParsingResult = FetchVDM(strMsg);
				}
				else if (strMsg.Find(_T("VDO")) > 0)
				{
					eParsingResult = FetchVDO(strMsg);
				}
				else if (strMsg.Find(_T("VTG")) > 0)
				{
					FetchVTG(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
					eParsingResult = E_PARSING_RESULT::ePARSING_DONE_NMEA_VTG;
				}
				else
				{
				}
			}
		}

		return eParsingResult;
	}

	T_NMEA_CAN* CNMEAParser::GetNMEA_CAN()
	{
		return &m_tNMEA_CAN;
	}

	T_NMEA_GGA* CNMEAParser::GetNMEA_GGA()
	{
		return &m_tNMEA_GGA;
	}

	T_NMEA_GLL* CNMEAParser::GetNMEA_GLL()
	{
		return &m_tNMEA_GLL;
	}

	T_NMEA_GSA* CNMEAParser::GetNMEA_GSA()
	{
		return &m_tNMEA_GSA;
	}

	T_NMEA_GSV* CNMEAParser::GetNMEA_GSV()
	{
		return &m_tNMEA_GSV;
	}

	T_NMEA_MHU* CNMEAParser::GetNMEA_MHU()
	{
		return &m_tNMEA_MHU;
	}

	T_NMEA_MMB* CNMEAParser::GetNMEA_MMB()
	{
		return &m_tNMEA_MMB;
	}

	T_NMEA_MTA* CNMEAParser::GetNMEA_MTA()
	{
		return &m_tNMEA_MTA;
	}

	T_NMEA_MWV* CNMEAParser::GetNMEA_MWV()
	{
		return &m_tNMEA_MWV;
	}

	T_NMEA_RMC* CNMEAParser::GetNMEA_RMC()
	{
		return &m_tNMEA_RMC;
	}

	T_NMEA_HDT* CNMEAParser::GetNMEA_HDT()
	{
		return &m_tNMEA_HDT;
	}

	T_NMEA_VTG* CNMEAParser::GetNMEA_VTG()
	{
		return &m_tNMEA_VTG;
	}

	T_AIS_MSG_TYPE1_3* CNMEAParser::GetAIS_TYPE1()
	{
		return &m_tAISType1;
	}

	T_AIS_MSG_TYPE1_3* CNMEAParser::GetAIS_TYPE2()
	{
		return &m_tAISType2;
	}

	T_AIS_MSG_TYPE1_3* CNMEAParser::GetAIS_TYPE3()
	{
		return &m_tAISType3;
	}

	T_AIS_MSG_TYPE4* CNMEAParser::GetAIS_TYPE4()
	{
		return &m_tAISType4;
	}

	T_AIS_MSG_TYPE5* CNMEAParser::GetAIS_TYPE5()
	{
		return &m_tAISType5;
	}

	T_AIS_MSG_TYPE9* CNMEAParser::GetAIS_TYPE9()
	{
		return &m_tAISType9;
	}

	T_AIS_MSG_TYPE14* CNMEAParser::GetAIS_TYPE14()
	{
		return &m_tAISType14;
	}

	T_AIS_MSG_TYPE18* CNMEAParser::GetAIS_TYPE18()
	{
		return &m_tAISType18;
	}

	T_AIS_MSG_TYPE19* CNMEAParser::GetAIS_TYPE19()
	{
		return &m_tAISType19;
	}

	T_AIS_MSG_TYPE21* CNMEAParser::GetAIS_TYPE21()
	{
		return &m_tAISType21;
	}

	T_AIS_MSG_TYPE24* CNMEAParser::GetAIS_TYPE24()
	{
		return &m_tAISType24;
	}

	T_AIS_MSG_TYPESART* CNMEAParser::GetAIS_TYPESART()
	{
		return &m_tAISTypeSart;
	}

	T_AIS_MSG_TYPEAIVDO1* CNMEAParser::GetAIS_TYPEAIVDO1()
	{
		return &m_tAISTypeAIVDO1;
	}

	T_AIS_MSG_TYPEAIVDO18* CNMEAParser::GetAIS_TYPEAIVDO18()
	{
		return &m_tAISTypeAIVDO18;
	}

	T_AIS_MSG_TYPEAIVDO19* CNMEAParser::GetAIS_TYPEAIVDO19()
	{
		return &m_tAISTypeAIVDO19;
	}
	
	E_PARSING_RESULT CNMEAParser::FetchCAN(const CString strMsg)
	{
		E_PARSING_RESULT eParsingResult = E_PARSING_RESULT::ePARSING_NO_RESULT;

		CString strData = strMsg;
		CString strHead;

		// $__PGN, 제거
		CNMEAUtils::DeleteSentense(strData);
		// Head
		CNMEAUtils::GetField(strData, 9, strHead);

		switch (strHead.GetAt(3))
		{
		case '2':		// vessel heading
			// Heading, unsigned short
			m_tNMEA_CAN.m_dHeading = (CNMEAUtils::GetU16FromHEX(strData) * 0.0001);
			// Deviation, signed short
			m_tNMEA_CAN.m_dDeviation = (CNMEAUtils::GetI16FromHEX(strData) * 0.0001);
			// Variation, signed short
			m_tNMEA_CAN.m_dVariation = (CNMEAUtils::GetI16FromHEX(strData) * 0.0001);
			// Heading Reference
			m_tNMEA_CAN.m_wHeadingRef = (CNMEAUtils::GetU8FromHEX(strData) & 0x0003);
			// time tag 증가
			m_tNMEA_CAN.m_unHeadingCount++;
			// Parsing 완료
			eParsingResult = E_PARSING_RESULT::ePARSING_DONE_EHS_HEADING;
			break;
		case '3':		// rate of turn
			// Rate of Turn, signed int, 32bit
			m_tNMEA_CAN.m_dTurnRate = (CNMEAUtils::GetI32FromHEX(strData) * 3.125e-8);
			// time tag 증가
			m_tNMEA_CAN.m_unTurnRateCount++;
			// Parsing 완료
			eParsingResult = E_PARSING_RESULT::ePARSING_DONE_EHS_TURNRATE;
			break;
		case '4':		// heave
			// Heave
			m_tNMEA_CAN.m_dHeave = (CNMEAUtils::GetI16FromHEX(strData) * 0.01);
			// time tag 증가
			m_tNMEA_CAN.m_unHeaveCount++;
			// Parsing 완료
			eParsingResult = E_PARSING_RESULT::ePARSING_DONE_EHS_HEAVE;
			break;
		case '9':		// attitude
			// Yew
			m_tNMEA_CAN.m_dYaw = CNMEAUtils::GetI16FromHEX(strData) * 0.0001;
			// Pitch
			m_tNMEA_CAN.m_dPitch = CNMEAUtils::GetI16FromHEX(strData) * 0.0001;
			// Roll
			m_tNMEA_CAN.m_dRoll = CNMEAUtils::GetI16FromHEX(strData) * 0.0001;
			// time tag 증가
			m_tNMEA_CAN.m_unAttitudeCount++;
			// Parsing 완료
			eParsingResult = E_PARSING_RESULT::ePARSING_DONE_EHS_ATTITUDE;
			break;
		default:
			break;
		}

		return eParsingResult;
	}

	void CNMEAParser::FetchGGA(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_GGA tNMEA_GGA;
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_GGA, sizeof(T_NMEA_GGA)));

		// $__GGA, 제거
		CNMEAUtils::DeleteSentense(strData);

		// UTC Time 
		CNMEAUtils::GetTime(strData, tNMEA_GGA.m_wHour, tNMEA_GGA.m_wMinute, tNMEA_GGA.m_dSecond);
		// Latitude
		CNMEAUtils::GetLatitude(strData, tNMEA_GGA.m_sLatDegree, tNMEA_GGA.m_dLatMinute);
		// Longitude
		CNMEAUtils::GetLongitude(strData, tNMEA_GGA.m_sLonDegree, tNMEA_GGA.m_dLonMinute);
		// Position Fix
		static_cast<void>(CNMEAUtils::GetWORD(strData, tNMEA_GGA.m_wGPSQuality));
		// Number of satellites in view
		static_cast<void>(CNMEAUtils::GetWORD(strData, tNMEA_GGA.m_wNumOfSatsInUse));
		// Horizontal Dilution of precision - HDOP
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_GGA.m_dHDOP));
		// Antenna Altitude above/below mean-sea-level
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_GGA.m_dAltitude));

		// Valid 한 데이터만 저장한다.
		if (tNMEA_GGA.m_wGPSQuality != 0U)
		{
			tNMEA_GGA.m_unTimeTag = m_tNMEA_GGA.m_unTimeTag;
			static_cast<void>(CopyMemory(&m_tNMEA_GGA, &tNMEA_GGA, sizeof(T_NMEA_GGA)));
			// time tag 증가
			m_tNMEA_GGA.m_unTimeTag++;
		}
	}

	void CNMEAParser::FetchGLL(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_GLL tNMEA_GLL;
		TCHAR cStatus;
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_GLL, sizeof(T_NMEA_GLL)));

		// $__GLL, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Latitude 
		CNMEAUtils::GetLatitude(strData, tNMEA_GLL.m_sLatDegree, tNMEA_GLL.m_dLatMinute);
		// Longitude 
		CNMEAUtils::GetLongitude(strData, tNMEA_GLL.m_sLonDegree, tNMEA_GLL.m_dLonMinute);
		// UTC Time 
		CNMEAUtils::GetTime(strData, tNMEA_GLL.m_wHour, tNMEA_GLL.m_wMinute, tNMEA_GLL.m_dSecond);
		// Status
		cStatus = strData.GetAt(0);
		if (cStatus == 'A')
		{
			tNMEA_GLL.m_unTimeTag = m_tNMEA_GLL.m_unTimeTag;
			static_cast<void>(CopyMemory(&m_tNMEA_GLL, &tNMEA_GLL, sizeof(T_NMEA_GLL)));
			// time tag 증가
			m_tNMEA_GLL.m_unTimeTag++;
		}
	}

	void CNMEAParser::FetchGSA(BYTE* const pDataPtr, const UINT nDataSize)
	{
		BYTE byValue;
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__GSA, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Mode
		if (CNMEAUtils::GetCHAR(strData, reinterpret_cast<TCHAR&>(byValue)) == TRUE)
		{
			m_tNMEA_GSA.m_cMode = byValue;
		}
		// fix mode
		if (CNMEAUtils::GetBYTE(strData, byValue) == FALSE)
		{
			m_tNMEA_GSA.m_byFixMode = byValue;
		}
		// satellite used
		for (INT nCnt = 0; nCnt < 12; nCnt++)
		{
			static_cast<void>(CNMEAUtils::GetWORD(strData, m_tNMEA_GSA.m_wSatsInSolution[nCnt]));
		}
		// PDOP
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_GSA.m_dPDOP));
		// HDOP
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_GSA.m_dHDOP));
		// VDOP
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_GSA.m_dVDOP));
		// time tag 증가
		m_tNMEA_GSA.m_unTimeTag++;
	}

	void CNMEAParser::FetchGSV(BYTE* const pDataPtr, const UINT nDataSize)
	{
		WORD wTotalGroup;
		WORD wSquence;
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__GSV, 제거
		CNMEAUtils::DeleteSentense(strData);

		// total number of GSV sentensce in group
		static_cast<void>(CNMEAUtils::GetWORD(strData, wTotalGroup));
		// Sequence (1 ~ 9)
		static_cast<void>(CNMEAUtils::GetWORD(strData, wSquence));
		// total number of satellites
		static_cast<void>(CNMEAUtils::GetWORD(strData, m_tNMEA_GSV.m_wNumSatellite));
		if ((wSquence > 0U) && (wSquence < 10U))
		{
			// Satellite info
			WORD wStartIndex = (wSquence - 1U) * 4U;
			for (WORD wCnt = 0U; wCnt < 4U; wCnt++)
			{
				if (wStartIndex + wCnt >= g_wMAX_SATELLITE_NUM)
				{
					break;
				}
				// ID or PRN 
				static_cast<void>(CNMEAUtils::GetWORD(strData, m_tNMEA_GSV.m_tSatInfo[wStartIndex + wCnt].m_wID));
				// elevation
				static_cast<void>(CNMEAUtils::GetSHORT(strData, m_tNMEA_GSV.m_tSatInfo[wStartIndex + wCnt].m_sElevation));
				// azimuth
				static_cast<void>(CNMEAUtils::GetWORD(strData, m_tNMEA_GSV.m_tSatInfo[wStartIndex + wCnt].m_wAzimuth));
				// SNR
				static_cast<void>(CNMEAUtils::GetWORD(strData, m_tNMEA_GSV.m_tSatInfo[wStartIndex + wCnt].m_wSNR));
			}
		}
		// time tag 증가
		m_tNMEA_GSV.m_unTimeTag++;
	}

	void CNMEAParser::FetchMHU(BYTE* const pDataPtr, const UINT nDataSize)
	{
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__MHU, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Relative Humidity
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_MHU.m_dHumidity));
		// delete delimiter(,)
		CNMEAUtils::DeleteSentense(strData);
		// Temperature
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_MHU.m_dTemperature));
		// time tag 증가
		m_tNMEA_MHU.m_unTimeTag++;
	}

	void CNMEAParser::FetchMMB(BYTE* const pDataPtr, const UINT nDataSize)
	{
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__MMB, 제거
		CNMEAUtils::DeleteSentense(strData);

		// delete delimiter(,)
		CNMEAUtils::DeleteSentense(strData);
		// delete delimiter(,)
		CNMEAUtils::DeleteSentense(strData);
		// Temperature
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_MMB.m_dAirPressure));
		// time tag 증가
		m_tNMEA_MMB.m_unTimeTag++;
	}

	void CNMEAParser::FetchMTA(BYTE* const pDataPtr, const UINT nDataSize)
	{
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__MTA, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Temperature
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_MTA.m_dTemperature));
		// time tag 증가
		m_tNMEA_MTA.m_unTimeTag++;
	}

	void CNMEAParser::FetchMWV(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_MWV tNMEA_MWV;
		TCHAR cStatus;
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_MWV, sizeof(T_NMEA_MWV)));

		// $__MWV, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Wind Angle
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_MWV.m_dWindAngle));
		tNMEA_MWV.m_dWindAngle *= 0.1;
		// Reference
		static_cast<void>(CNMEAUtils::GetCHAR(strData, tNMEA_MWV.m_cReference));
		// Wind Speed
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_MWV.m_dWindSpeed));
		// Speed Unit
		static_cast<void>(CNMEAUtils::GetCHAR(strData, tNMEA_MWV.m_cSpeedUnit));
		// Status
		if (CNMEAUtils::GetCHAR(strData, cStatus) == TRUE)
		{
			if (cStatus == 'A')  // Valid일 경우만 적용
			{
				tNMEA_MWV.m_unTimeTag = m_tNMEA_MWV.m_unTimeTag;
				// store data
				static_cast<void>(CopyMemory(&m_tNMEA_MWV, &tNMEA_MWV, sizeof(T_NMEA_MWV)));
				// time tag 증가
				m_tNMEA_MWV.m_unTimeTag++;
			} 
		}
		else
		{
			tNMEA_MWV.m_unTimeTag = m_tNMEA_MWV.m_unTimeTag;
			// store data
			static_cast<void>(CopyMemory(&m_tNMEA_MWV, &tNMEA_MWV, sizeof(T_NMEA_MWV)));
			// time tag 증가
			m_tNMEA_MWV.m_unTimeTag++;
		}
	}

	void CNMEAParser::FetchRMC(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_RMC tNMEA_RMC;
		TCHAR cStatus = '\0';
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_RMC, sizeof(T_NMEA_RMC)));

		// $__RMC, 제거
		CNMEAUtils::DeleteSentense(strData);

		// UTC Time 
		CNMEAUtils::GetTime(strData, tNMEA_RMC.m_wHour, tNMEA_RMC.m_wMinute, tNMEA_RMC.m_dSecond);
		// status
		static_cast<void>(CNMEAUtils::GetCHAR(strData, cStatus));
		// Latitude 
		CNMEAUtils::GetLatitude(strData, tNMEA_RMC.m_sLatDegree, tNMEA_RMC.m_dLatMinute);
		// Longitude 
		CNMEAUtils::GetLongitude(strData, tNMEA_RMC.m_sLonDegree, tNMEA_RMC.m_dLonMinute);
		// Speed over ground, knots
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_RMC.m_dSpeed));
		// Track made godd,
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_RMC.m_dTrackTrue));
		// UTC Date
		static_cast<void>(CNMEAUtils::GetDate(strData, tNMEA_RMC.m_wYear, tNMEA_RMC.m_wMonth, tNMEA_RMC.m_wDay));
		// Magnetic Variation
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, tNMEA_RMC.m_dMagVariation));
		// Magnetic Variation Direction
		static_cast<void>(CNMEAUtils::GetCHAR(strData, tNMEA_RMC.m_cMagDir));
		// Status
		if (cStatus == 'A')
		{
			tNMEA_RMC.m_unTimeTag = m_tNMEA_RMC.m_unTimeTag;
			static_cast<void>(CopyMemory(&m_tNMEA_RMC, &tNMEA_RMC, sizeof(T_NMEA_RMC)));
			// time tag 증가
			m_tNMEA_RMC.m_unTimeTag++;
		}
	}

	void CNMEAParser::FetchHDT(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_HDT tNMEA_HDT;
		TCHAR cStatus = '\0';
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_HDT, sizeof(T_NMEA_HDT)));

		// $__HDT, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Heading in degree
		static_cast<void>(CNMEAUtils::GetFLOAT(strData, tNMEA_HDT.fHeading));
		// T: Inidicates heading relative to True Notrh
		cStatus = strData.GetAt(0);
		// Status
		if (cStatus == 'T')
		{
			tNMEA_HDT.m_unTimeTag = m_tNMEA_HDT.m_unTimeTag;
			static_cast<void>(CopyMemory(&m_tNMEA_HDT, &tNMEA_HDT, sizeof(T_NMEA_HDT)));
			// time tag 증가
			m_tNMEA_HDT.m_unTimeTag++;
		}
	}
	void CNMEAParser::FetchHDG(BYTE* const pDataPtr, const UINT nDataSize)
	{
		T_NMEA_HDG tNMEA_HDG;

		TCHAR cStatus = '\0';
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// initialize
		static_cast<void>(ZeroMemory(&tNMEA_HDG, sizeof(T_NMEA_HDG)));

		// $__HDT, 제거
		CNMEAUtils::DeleteSentense(strData);

		// Magnetic Sensor heading in degrees
		static_cast<void>(CNMEAUtils::GetFLOAT(strData, tNMEA_HDG.fHeading));

		// Magnetic Deviation, degrees
		static_cast<void>(CNMEAUtils::GetFLOAT(strData, tNMEA_HDG.fDeviation));

		// Magnetic Deviation direction
		static_cast<void>(CNMEAUtils::GetCHAR(strData, tNMEA_HDG.m_ucDevitationDir));

		// Magnetic Variation degrees
		static_cast<void>(CNMEAUtils::GetFLOAT(strData, tNMEA_HDG.fVariation));

		// Magnetic Variation direction
		tNMEA_HDG.m_ucVariationDir = strData.GetAt(0);
	}

	void CNMEAParser::Savelog(CString MSg)
	{
#if SAVELOGAIS
		CFileFind pFind;

		BOOL vRet = pFind.FindFile(m_strFile);

		FILE* fp;

		if ((fopen_s(&fp,m_strFile, "at+")) != 0)
		{
			TRACE("Log File Open Error");

			AfxMessageBox("파일저장 에러(파일생성할수없음) AIS 저장");
		}
		else
		{

			fseek(fp, SEEK_END, 0);

			fprintf(fp, "%s", MSg);
			fclose(fp);
		}
#endif
	}

	E_PARSING_RESULT CNMEAParser::FetchVDM(const CString strMsg)
	{
		CString strData = strMsg;
		CString strField;
		BYTE byMsgTotal = 0;
		BYTE byMsgScequence = 0;
		
		E_PARSING_RESULT eParsingResult = E_PARSING_RESULT::ePARSING_NO_RESULT;

		// $__VDM, 제거
		CNMEAUtils::DeleteSentense(strData);
		// 총 메시지
		static_cast<void>(CNMEAUtils::GetBYTE(strData, byMsgTotal));
		// 순번
		static_cast<void>(CNMEAUtils::GetBYTE(strData, byMsgScequence));
		CNMEAUtils::DeleteSentense(strData);
		CNMEAUtils::DeleteSentense(strData);
		// 데이터 부분
		CNMEAUtils::GetField(strData, strField);

		// AIS TYPE, 6 bits
		if (byMsgScequence == 1)
		{
			m_ucLastType = CAISUtils::GetU8(strField, 0, 6);
		}

		switch (static_cast<INT>(m_ucLastType))
		{
		case 1:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType1 += strField;
			}
			else
			{
				m_strAisMsgType1 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);

				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				
				static_cast<void>(ZeroMemory(&m_tAISType1, sizeof(T_AIS_MSG_TYPE1_3)));
				FetchAISType1_3(m_strAisMsgType1, m_tAISType1);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1;	
			}
			break;
		}
		case 2:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType2 += strField;
			}
			else
			{
				m_strAisMsgType2 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				static_cast<void>(ZeroMemory(&m_tAISType2, sizeof(T_AIS_MSG_TYPE1_3)));

				FetchAISType1_3(m_strAisMsgType2, m_tAISType2);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE2;
			}
			break;
		}
		case 3:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType3 += strField;
			}
			else
			{
				m_strAisMsgType3 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				static_cast<void>(ZeroMemory(&m_tAISType3, sizeof(T_AIS_MSG_TYPE1_3)));

				FetchAISType1_3(m_strAisMsgType3, m_tAISType3);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE3;
			}
			break;
		}
		case 4:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType4 += strField;
			}
			else
			{
				m_strAisMsgType4 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType4(m_strAisMsgType4);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE4;
			}
			break;
		}
		case 5:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType5 += strField;
			}
			else
			{
				m_strAisMsgType5 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType5(m_strAisMsgType5);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE5;
			}
			break;
		}
		case 9:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType9 += strField;
			}
			else
			{
				m_strAisMsgType9 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType9(m_strAisMsgType9);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE9;
			}
			break;
		}
		case 14:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType14 += strField;
			}
			else
			{
				m_strAisMsgType14 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType14(m_strAisMsgType14);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE18;
			}
			break;
		}
		case 18:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType18 += strField;
			}
			else
			{
				m_strAisMsgType18 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType18(m_strAisMsgType18);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE18;
			}
			break;
		}
		case 19:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType19 += strField;
			}
			else
			{
				m_strAisMsgType19 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType19(m_strAisMsgType19);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE19;
			}
			break;
		}
		case 21:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType21 += strField;
			}
			else
			{
				m_strAisMsgType21 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType21(m_strAisMsgType21);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE21;
			}
			break;
		}
		case 24:
		{
			if (byMsgScequence > 1)
			{
				m_strAisMsgType24 += strField;
			}
			else
			{
				m_strAisMsgType24 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
#if SAVELOGAIS
				CString tmp = strMsg;

				tmp.Remove('\r');

				Savelog(tmp);
				CString strText;
				strText.Format(_T("AIS MSG : %s"), strMsg);
				OutputDebugString(strText);
#endif
				FetchAISType24(m_strAisMsgType24);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE24;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return eParsingResult;
	}

	E_PARSING_RESULT CNMEAParser::FetchVDO(const CString strMsg)
	{
		CString strData = strMsg;
		CString strField;
		BYTE byMsgTotal = 0;
		BYTE byMsgScequence = 0;

		E_PARSING_RESULT eParsingResult = E_PARSING_RESULT::ePARSING_NO_RESULT;

		// $__VDM, 제거
		CNMEAUtils::DeleteSentense(strData);
		// 총 메시지
		static_cast<void>(CNMEAUtils::GetBYTE(strData, byMsgTotal));
		// 순번
		static_cast<void>(CNMEAUtils::GetBYTE(strData, byMsgScequence));
		CNMEAUtils::DeleteSentense(strData);
		CNMEAUtils::DeleteSentense(strData);
		// 데이터 부분
		CNMEAUtils::GetField(strData, strField);

		// AIS TYPE, 6 bits
		if (byMsgScequence == 1)
		{
			m_ucLastType = CAISUtils::GetU8(strField, 0, 6);
		}

		switch (static_cast<INT>(m_ucLastType))
		{
		case 1:
		{
			if (byMsgScequence > 1)
			{
				m_strAIVDOMsgType1 += strField;
			}
			else
			{
				m_strAIVDOMsgType1 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
				FetchAIVDOType1(m_strAIVDOMsgType1);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE1;
			}
			break;
		}
		case 18:
		{
			if (byMsgScequence > 1)
			{
				m_strAIVDOMsgType18 += strField;
			}
			else
			{
				m_strAIVDOMsgType18 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
				FetchAIVDOType18(m_strAIVDOMsgType18);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE18;
			}
			break;
		}
		case 19:
		{
			if (byMsgScequence > 1)
			{
				m_strAIVDOMsgType19 += strField;
			}
			else
			{
				m_strAIVDOMsgType19 = strField;
			}
			if (byMsgTotal == byMsgScequence)
			{
				FetchAIVDOType19(m_strAIVDOMsgType19);
				eParsingResult = E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE19;
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return eParsingResult;
	}

	void CNMEAParser::FetchVTG(BYTE* const pDataPtr, const UINT nDataSize)
	{
		CString strData = reinterpret_cast<TCHAR*>(pDataPtr);

		// $__VTG, 제거
		CNMEAUtils::DeleteSentense(strData);

		// True Course 
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_VTG.m_dCourseTrue));
		// delete 'T' field
		CNMEAUtils::DeleteSentense(strData);
		// Magnetic Course
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_VTG.m_dCourseMag));
		// delete 'M' field
		CNMEAUtils::DeleteSentense(strData);
		// Speed, Knots
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_VTG.m_dSpeedKnots));
		// delete 'N' field
		CNMEAUtils::DeleteSentense(strData);
		// Speed, km/h
		static_cast<void>(CNMEAUtils::GetDOUBLE(strData, m_tNMEA_VTG.m_dSpeedKmPerH));
		// time tag 증가
		m_tNMEA_VTG.m_unTimeTag++;
	}

	void Calc_Pos(INT32 Latitude, INT32 Longitude, DOUBLE* cLatitude, DOUBLE* cLongitude)
	{
		if (Latitude & 0x04000000)
		{
			Latitude = 0x08000000 - Latitude;
			Latitude *= -1;
		}

		if (Longitude & 0x08000000)
		{
			Longitude = 0x10000000 - Longitude;
			Longitude *= -1;
		}

		*cLatitude = (DOUBLE)(Latitude / 600000);
		*cLatitude += (DOUBLE)(Latitude - (*cLatitude * 600000)) / 600000.0;

		*cLongitude = (DOUBLE)(Longitude / 600000);
		*cLongitude += (DOUBLE)(Longitude - (*cLongitude * 600000)) / 600000.0;
	}

	void CNMEAParser::FetchAISType1_3(CString strData, T_AIS_MSG_TYPE1_3& tAisMsg)
	{
		INT nBitIndex = 0;
		USHORT usValue;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&tAisMsg, sizeof(T_AIS_MSG_TYPE1_3)));
		tAisMsg.m_blIsSartMsg = FALSE;
		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 1-3
		tAisMsg.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, Message repeat count
		tAisMsg.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 decimal digits
		tAisMsg.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 41, 4-bits, Navigation Status, e, See "Navigation Status"
		tAisMsg.m_ucStatus = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 42 - 49, 8-bits, Rate of Turn (ROT), signed

		if ((tAisMsg.m_ucStatus == 14) && (tAisMsg.m_ucType == 1))
		{
			tAisMsg.m_blIsSartMsg = TRUE;
		}
		
		CHAR temp = static_cast<CHAR>(CAISUtils::GetU8(strData, nBitIndex, 8));
	
		if (temp == ROT_NAVALUE)
		{
			tAisMsg.m_blRotNA = TRUE;

			tAisMsg.m_cTurnRate = temp;
		}
		else
		{
			tAisMsg.m_blRotNA = FALSE;

			if ((temp == ROT_NOTIMAX) || (temp == ROT_NOTIMIN))
			{
				tAisMsg.m_cTurnRate = temp;
			}
			else
			{
				tAisMsg.m_cTurnRate = temp;

				BOOL minus = FALSE;

				if (tAisMsg.m_cTurnRate < 0)
				{
					tAisMsg.m_cTurnRate = tAisMsg.m_cTurnRate * -1;
					minus = TRUE;
				}

				tAisMsg.m_cTurnRate = (FLOAT)(tAisMsg.m_cTurnRate / 4.733);

				tAisMsg.m_cTurnRate = (FLOAT)(pow(tAisMsg.m_cTurnRate, 2));

				if (minus)
					tAisMsg.m_cTurnRate = tAisMsg.m_cTurnRate * -1;
			}
		}

		nBitIndex += 8;
		// 50 - 59, 10-bits, Speed Over Ground (SOG), unsigned
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);
		
		if (usValue == SOG_NAVALUE)
		{
			tAisMsg.m_blSOGNA = TRUE;

			tAisMsg.m_fSOG = (FLOAT)usValue;
		}
		else
		{
			tAisMsg.m_blSOGNA = FALSE;

			tAisMsg.m_fSOG = (FLOAT)(usValue * 0.1F);
		}
			
		nBitIndex += 10;
		// 60 - 60, 1-bit, Position Accuracy, bool
		tAisMsg.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 61 - 88, 28-bits, Longitude, signed, Minutes/10000
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);
		
		nBitIndex += 28;
		// 89 - 115, 27-bits, Latitude, signed, Minutes/10000
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);
		
		Calc_Pos(unLatitude, unLongitude, &tAisMsg.m_dLat, &tAisMsg.m_dLon);

		if (((INT)tAisMsg.m_dLon == LONGITUDE_NAVALUE) || ((INT)tAisMsg.m_dLat == LATITUDE_NAVALUE))
			tAisMsg.m_blPositionNA = TRUE;
		else
			tAisMsg.m_blPositionNA = FALSE;

		nBitIndex += 27;

		// 116 - 127, 12-bits, Course Over Ground (COG), unsigned, Relative to true north, to 0.1 degree precision
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);
		
		if (usValue == COG_NAVALUE)
		{
			tAisMsg.m_blCOGNA = TRUE;

			tAisMsg.m_fCOG = (FLOAT)usValue;
		}
		else
		{
			tAisMsg.m_blCOGNA = FALSE;

			tAisMsg.m_fCOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;

		// 128 - 136, 9-bits, True Heading (HDG), unsigned, 0 to 359 degrees, 511 = not available.
		tAisMsg.m_usHeading = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (tAisMsg.m_usHeading == HDT_NAVALUE)
			tAisMsg.m_blHeadingNA = TRUE;
		else
			tAisMsg.m_blHeadingNA = FALSE;

		nBitIndex += 9;
		// 137 - 142, 6-bits, Time Stamp second, unsigned, Second of UTC timestamp
		tAisMsg.m_ucTimeStamp = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 143 - 144, 2-bits, Maneuver Indicator, enum, 
		tAisMsg.m_ucManeuver = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 145 - 147, 3-bits, Spare, x, Not used
		nBitIndex += 3;
		// 148 - 148, 1-bit, RAIM flag, bool,
		tAisMsg.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);

		nBitIndex += 1;
		// 149 - 167, 19, Radio status, unsigned, 
		tAisMsg.m_unRadioStatus = CAISUtils::GetU32(strData, nBitIndex, 19);

		tAisMsg.m_ucClassType = 'A';
		nBitIndex += 19;
		// 카운트 증가
		//tAisMsg.m_unCounter++;

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		tAisMsg.m_uRcvYear = (UINT)LocalTime.wYear;
		tAisMsg.m_uRcvMonth = (UINT)LocalTime.wMonth;
		tAisMsg.m_uRcvDay = (UINT)LocalTime.wDay;
		tAisMsg.m_uRcvHour = (UINT)LocalTime.wHour;
		tAisMsg.m_uRcvMinute = (UINT)LocalTime.wMinute;
		tAisMsg.m_uRcvSecond = (UINT)LocalTime.wSecond;

#if SAVELOGAIS
		
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tNavigation Status : %d\tROT : %.1f\tSOG : %.1f\tPosition Accuracy : %d\tLongitude : %.7lf\tLatitude : %.7lf\tCOG : %.1f\tHDG : %d\tTime Stamp : %d\tManeuver Indicator : %d\tRAIM flag : %d\tRadio status : %d\tClassType : %c\r\n"),
			tAisMsg.m_ucType, tAisMsg.m_ucRepeat, tAisMsg.m_unMMSI, tAisMsg.m_ucStatus, tAisMsg.m_cTurnRate, tAisMsg.m_fSOG, tAisMsg.m_ucAccuracy,
			tAisMsg.m_dLon, tAisMsg.m_dLat , tAisMsg.m_fCOG , tAisMsg.m_usHeading , tAisMsg.m_ucTimeStamp , tAisMsg.m_ucManeuver , tAisMsg.m_ucRAIM,
			tAisMsg.m_unRadioStatus, tAisMsg.m_ucClassType);

		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType4(CString strData)
	{
		INT nBitIndex = 0;
		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISType4, sizeof(T_AIS_MSG_TYPE4)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 4
		m_tAISType4.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, 
		m_tAISType4.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 decimal digits
		m_tAISType4.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 51, 14-bits, Year (UTC), unsigned, UTC, 1-9999, 0 = N/A (default)
		m_tAISType4.m_usYear = CAISUtils::GetU16(strData, nBitIndex, 14);
		nBitIndex += 14;
		// 52 - 55, 4-bits, Month (UTC), unsigned, 1-12; 0 = N/A (default)
		m_tAISType4.m_ucMonth = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 56 - 60, 5-bits, Day (UTC), unsigned, 1-31; 0 = N/A (default)
		m_tAISType4.m_ucDay = CAISUtils::GetU8(strData, nBitIndex, 5);
		nBitIndex += 5;
		// 61 - 65, 5-bits, Hour (UTC), unsigned, 0-23; 24 = N/A (default)
		m_tAISType4.m_ucHour = CAISUtils::GetU8(strData, nBitIndex, 5);
		nBitIndex += 5;
		// 66 - 71, 6-bits, Minute (UTC), unsigned, 0-59; 60 = N/A (default)
		m_tAISType4.m_ucMinute = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 72 - 77, 6-bits, Second (UTC), unsigned, 0-59; 60 = N/A (default)
		m_tAISType4.m_ucSecond = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 78 - 78, 1-bit, Fix quality, bool, As in Common Navigation Block
		m_tAISType4.m_ucQuality = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;

		// 79 - 106, 28-bits, Longitude, signed, As in Common Navigation Block
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);

		nBitIndex += 28;

		// 107 - 133, 27-bits, Latitude, signed, As in Common Navigation Block
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);

		Calc_Pos(unLatitude, unLongitude, &m_tAISType4.m_dLat, &m_tAISType4.m_dLon);

		if (((INT)m_tAISType4.m_dLon == LONGITUDE_NAVALUE) || ((INT)m_tAISType4.m_dLat == LATITUDE_NAVALUE))
			m_tAISType4.m_blPositionNA = TRUE;
		else
			m_tAISType4.m_blPositionNA = FALSE;

		nBitIndex += 27;
		// 134 - 137, 4-bits, Type of EPFD, enum, See "EPFD Fix Types"
		m_tAISType4.m_ucEPFD = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 138 - 147, 10-bits, Spare, x, Not used
		nBitIndex += 10;
		// 148 - 148, 1-bit, RAIM flag, bool, As for common navigation block
		m_tAISType4.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 149 - 167, 19-bits, SOTDMA state	radio, unsigned, As in same bits for Type 1
		m_tAISType4.m_unRadioStatus = CAISUtils::GetU8(strData, nBitIndex, 19);

		m_tAISType4.m_ucClassType = 'A';
		nBitIndex += 19;
		// 카운트 증가
		//m_tAISType4.m_unCounter++;

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType4.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType4.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType4.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType4.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType4.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType4.m_uRcvSecond = (UINT)LocalTime.wSecond;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tYear : %d\tMonth : %d\tDay : %d\tHour : %d\tMinute : %d\tSecond : %d\tQuality : %d\tLongitude : %.7lf\tLatitude : %.7lf\tEPFD : %d\tRAIM : %d\tRadioStatus : %d\tClassType : %c\r\n"),
			m_tAISType4.m_ucType, m_tAISType4.m_ucRepeat, m_tAISType4.m_unMMSI, m_tAISType4.m_usYear , m_tAISType4.m_ucMonth , m_tAISType4.m_ucDay , 
			m_tAISType4.m_ucHour, m_tAISType4.m_ucMinute, m_tAISType4.m_ucSecond, m_tAISType4.m_ucQuality, m_tAISType4.m_dLon, m_tAISType4.m_dLat,
			m_tAISType4.m_ucEPFD, m_tAISType4.m_ucRAIM, m_tAISType4.m_unRadioStatus, m_tAISType4.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType5(CString strData)
	{
		INT nBitIndex = 0;

		static_cast<void>(ZeroMemory(&m_tAISType5, sizeof(T_AIS_MSG_TYPE5)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 5
		m_tAISType5.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, Message repeat count
		m_tAISType5.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 digits
		m_tAISType5.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 39, 2-bits, AIS Version, unsigned, 0 = [ITU1371], 1-3 = future editions
		m_tAISType5.m_ucVersion = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 40 - 69, 30-bits, IMO Number, unsigned, IMO ship ID number
		m_tAISType5.m_unIMO = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 70 - 111, 42-bits, Call Sign, text, 7 six-bit characters
		for (INT nCnt = 0; nCnt < 7; nCnt++)
		{
			m_tAISType5.m_szCallSign[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
		}
		// 112 - 231, 120-bits, Vessel Name, text, 20 six-bit characters
		for (INT nCnt = 0; nCnt < 20; nCnt++)
		{
			m_tAISType5.m_szShipName[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
		}
		// 232 - 239, 8-bits, Ship Type, enum, See "Codes for Ship Type"
		m_tAISType5.m_ucShipType = CAISUtils::GetU8(strData, nBitIndex, 8);
		nBitIndex += 8;
		// 240 - 248, 9-bits, Dimension to Bow, unsigned, Meters
		m_tAISType5.m_usBowDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 249 - 257, 9-bits, Dimension to Stern, unsigned, Meters
		m_tAISType5.m_usSternDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 258 - 263, 6-bits, Dimension to Port, unsigned, Meters
		m_tAISType5.m_ucPortDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 264 - 269, 6-bits, Dimension to Starboard, unsigned, Meters
		m_tAISType5.m_ucStarboardDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 270 - 273, 4-bits, Position Fix Type	epfd, enum, See "EPFD Fix Types"
		m_tAISType5.m_ucEPFD = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 274 - 277, 4-bits, ETA month (UTC), unsigned, 1-12, 0=N/A (default)
		m_tAISType5.m_ucMonth = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 278 - 282, 5-bits, ETA day (UTC), unsigned, 1-31, 0=N/A (default)
		m_tAISType5.m_ucDay = CAISUtils::GetU8(strData, nBitIndex, 5);
		nBitIndex += 5;
		// 283 - 287, 5-bits, ETA hour (UTC), unsigned, 0-23, 24=N/A (default)
		m_tAISType5.m_ucHour = CAISUtils::GetU8(strData, nBitIndex, 5);
		nBitIndex += 5;
		// 288 - 293, 6-bits, ETA minute (UTC), unsigned, 0-59, 60=N/A (default)
		m_tAISType5.m_ucMinute = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 294 - 301, 8-bits, Draught, unsigned, Meters/10
		m_tAISType5.m_fDraught = CAISUtils::GetU8(strData, nBitIndex, 8) * 0.1F;
		nBitIndex += 8;
		// 302 - 421, 120-bits, Destination, text, 20 6-bit characters
		for (INT nCnt = 0; nCnt < 20; nCnt++)
		{
			m_tAISType5.m_szDestination[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
		}
		// 422 - 422, 1-bit, DTE, bool, 0=Data terminal ready, 1=Not ready (default).
		m_tAISType5.m_ucDTE = CAISUtils::GetU8(strData, nBitIndex, 1);

		m_tAISType5.m_ucClassType = ' ';

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType5.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType5.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType5.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType5.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType5.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType5.m_uRcvSecond = (UINT)LocalTime.wSecond;

		nBitIndex += 1;
		// 423 - 423, 1-bit, Spare, x, Not used

		// 카운트 증가
		//m_tAISType5.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tAIS Version : %d\tIMO : %d\tCall Sign : %s\tVessel Name : %s\tShip Type : %d\tDimension to Bow : %d\tDimension to Stern : %d\tDimension to Port : %d\tDimension to Starboard : %d\tEPFD : %d\tETA month : %d\tETA day : %d\tETA Hour : %d\tETA Minute : %d\tDraught : %.1f\tDestination : % s\tDTE : %d\tClassType :%c\r\n"),
			m_tAISType5.m_ucType, m_tAISType5.m_ucRepeat, m_tAISType5.m_unMMSI, m_tAISType5.m_ucVersion, m_tAISType5.m_unIMO, m_tAISType5.m_szCallSign, m_tAISType5.m_szShipName,
			m_tAISType5.m_ucShipType, m_tAISType5.m_usBowDimension, m_tAISType5.m_usSternDimension, m_tAISType5.m_ucPortDimension, m_tAISType5.m_ucStarboardDimension, m_tAISType5.m_ucEPFD,
			m_tAISType5.m_ucMonth, m_tAISType5.m_ucDay, m_tAISType5.m_ucHour, m_tAISType5.m_ucMinute, m_tAISType5.m_fDraught, m_tAISType5.m_szDestination, m_tAISType5.m_ucDTE , m_tAISType5.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType9(CString strData)
	{
		INT nBitIndex = 0;
		//UINT32 unValue;
		USHORT usValue;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISType9, sizeof(T_AIS_MSG_TYPE9)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 9
		m_tAISType9.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, As in Common Navigation Block
		m_tAISType9.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 decimal digits
		m_tAISType9.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 49, 12-bits, Altitude, unsigned, See below
		m_tAISType9.m_usAltitude = CAISUtils::GetU16(strData, nBitIndex, 12);
		nBitIndex += 12;
		// 50 - 59, 10-bits, SOG, unsigned, See below
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISType9.m_blSOGNA = TRUE;

			m_tAISType9.m_fSOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType9.m_blSOGNA = FALSE;

			m_tAISType9.m_fSOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 10;
		// 60 - 60, 1-bit, Position Accuracy, unsigned, See below
		m_tAISType9.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 61 - 88, 28-bits, Longitude, signed, Minutes/10000 (as in CNB)
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);
		
		nBitIndex += 28;

		// 89 - 115, 27-bits, Latitude, signed, Minutes/10000 (as in CNB)
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);
		
		Calc_Pos(unLatitude, unLongitude, &m_tAISType9.m_dLat, &m_tAISType9.m_dLon);

		if (((INT)m_tAISType9.m_dLon == LONGITUDE_NAVALUE) || ((INT)m_tAISType9.m_dLat == LATITUDE_NAVALUE))
			m_tAISType9.m_blPositionNA = TRUE;
		else
			m_tAISType9.m_blPositionNA = FALSE;

		nBitIndex += 27;
		// 116 - 127, 12-bits, Course Over Ground, unsigned, True bearing, 0.1 degree units
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);
		
		if (usValue == COG_NAVALUE)
		{
			m_tAISType9.m_blCOGNA = TRUE;

			m_tAISType9.m_fCOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType9.m_blCOGNA = FALSE;

			m_tAISType9.m_fCOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;
		// 128 - 133, 6-bits, Time Stamp, unsigned, UTC second.
		m_tAISType9.m_ucTimeStamp = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 134 - 141, 8-bits, Regional reserved, x, Reserved
		nBitIndex += 8;
		// 142 - 142, 1-bit, DTE, bool, 0=Data terminal ready, 1=Data terminal not ready (default)
		m_tAISType9.m_ucDTE = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 143 - 145, 3-bits, Spare, x, Not used
		nBitIndex += 3;
		// 146 - 146, 1-bit, Assigned, bool, Assigned-mode flag
		m_tAISType9.m_ucAssigned = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 147 - 147, 1-bit, RAIM flag, bool, As for common navigation block
		m_tAISType9.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 148 - 167, 20-bits, Radio status, unsigned, See [IALA] for details.
		m_tAISType9.m_unRadioStatus = CAISUtils::GetU32(strData, nBitIndex, 20);
		nBitIndex += 20;

		m_tAISType9.m_ucClassType = 'A';
		
		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType9.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType9.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType9.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType9.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType9.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType9.m_uRcvSecond = (UINT)LocalTime.wSecond;

		// 카운트 증가
		//m_tAISType9.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tAltitude : %d\tSOG : %.1f\tPosition Accuracy : %d\tLongitude : %.7lf\tLatitude : %.7lf\tCOG : %.1f\tTime Stamp : %d\tDTE : %d\tAssigned : %d\tRAIM : %d\tRadio status : %d\tClassType : %c\r\n"),
			m_tAISType9.m_ucType, m_tAISType9.m_ucRepeat, m_tAISType9.m_unMMSI, m_tAISType9.m_usAltitude, m_tAISType9.m_fSOG, m_tAISType9.m_ucAccuracy,
			m_tAISType9.m_dLon, m_tAISType9.m_dLat, m_tAISType9.m_fCOG, m_tAISType9.m_ucTimeStamp, m_tAISType9.m_ucDTE, m_tAISType9.m_ucAssigned,
			m_tAISType9.m_ucRAIM, m_tAISType9.m_unRadioStatus, m_tAISType9.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType14(CString strData)
	{
		INT nBitIndex = 0;

		static_cast<void>(ZeroMemory(&m_tAISType14, sizeof(T_AIS_MSG_TYPE14)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 9
		m_tAISType14.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, As in Common Navigation Block
		m_tAISType14.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 decimal digits
		m_tAISType14.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		
		m_tAISType14.m_ucSpare = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;

		INT length = strData.GetLength() * 6;

		if ((length < 40) || (length > 1008))
			return;

		INT i = 0;

		while (i != (length - 40) / 6)
		{
			m_tAISType14.m_szMessage[i] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
			i++;
		}

		m_tAISType9.m_ucClassType = ' ';

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType14.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType14.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType14.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType14.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType14.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType14.m_uRcvSecond = (UINT)LocalTime.wSecond;

		// 카운트 증가
		//m_tAISType9.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tSpare : %d\tMessage : %s\r\n"),
			m_tAISType14.m_ucType, m_tAISType14.m_ucRepeat, m_tAISType14.m_unMMSI, m_tAISType14.m_ucSpare, m_tAISType14.m_szMessage);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType18(CString strData)
	{
		USHORT usValue;
		//UINT32 unValue;
		INT nBitIndex = 0;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISType18, sizeof(T_AIS_MSG_TYPE18)));

		// 0 - 5, 6-bit, Message Type, unsigned, Constant : 18
		m_tAISType18.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bit, Repeat Indicator, unsigned, As in Common Navigation Block
		m_tAISType18.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bit, MMSI, unsigned, 9 decimal digits
		m_tAISType18.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 45, 8-bit, Regional Reserved, x, Not used
		m_tAISType18.m_ucRegionalReserved1 = CAISUtils::GetU8(strData, nBitIndex, 8);
		nBitIndex += 8;
		// 46 - 55, 10-bit, Speed Over Ground, unsigned,	As in common navigation block
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISType18.m_blSOGNA = TRUE;

			m_tAISType18.m_fSOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType18.m_blSOGNA = FALSE;

			m_tAISType18.m_fSOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 10;
		// 56 - 56, 1-bit, Position Accuracy, bool, 0 = accuracy > 10m (default), 1 = accuracy < 10m
		m_tAISType18.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 57 - 84, 28-bit, Longitude, signed, Minutes/10000
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);
		
		nBitIndex += 28;

		// 85 - 111, 27-bit, Latitude, signed, Minutes/10000
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);
		
		Calc_Pos(unLatitude, unLongitude, &m_tAISType18.m_dLat, &m_tAISType18.m_dLon);

		if (((INT)m_tAISType18.m_dLon == LONGITUDE_NAVALUE) || ((INT)m_tAISType18.m_dLat == LATITUDE_NAVALUE))
			m_tAISType18.m_blPositionNA = TRUE;
		else
			m_tAISType18.m_blPositionNA = FALSE;

		nBitIndex += 27;
		// 112 - 123, 12-bit, Course Over Ground, Unsigned,	0.1 degrees from true north
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);

		if (usValue == COG_NAVALUE)
		{
			m_tAISType18.m_blCOGNA = TRUE;

			m_tAISType18.m_fCOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType18.m_blCOGNA = FALSE;

			m_tAISType18.m_fCOG = (FLOAT)(usValue * 0.1F);
		}
		
		nBitIndex += 12;
		// 124 - 132, 9-bit, True Heading, unsigned, 0 to 359 degrees, 511 = N/A
		m_tAISType18.m_usHeading = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (m_tAISType18.m_usHeading == HDT_NAVALUE)
			m_tAISType18.m_blHeadingNA = TRUE;
		else
			m_tAISType18.m_blHeadingNA = FALSE;

		nBitIndex += 9;
		// 133 - 138, 6-bit, Time Stamp	second, unsigned, Second of UTC timestamp.
		m_tAISType18.m_ucTimeStamp = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 139 - 140, 2-bit, Regional reserved, unsigned, Uninterpreted
		m_tAISType18.m_ucRegionalReserved2 = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 141 - 141, 1-bit, CS Unit, bool, 0 = Class B SOTDMA unit 1 = Class B CS(Carrier Sense) unit
		m_tAISType18.m_ucClassUnit = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 142 - 142, 1-bit, Display flag, bool, 0 = No visual display, 1 = Has display, (Probably not reliable).
		m_tAISType18.m_ucDisplay = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 143 - 143, 1-bit, DSC Flag, bool, If 1, unit is attached to a VHF voice radio with DSC capability.
		m_tAISType18.m_ucDSC = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 144 - 144, 1-bit, Band flag, bool, Base stations can command units to switch frequency. If this flag is 1, the unit can use any part of the marine channel.
		m_tAISType18.m_ucBand = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 145 - 145, 1-bit, Message 22 flag, bool, If 1, unit can accept a channel assignment via Message Type 22.
		m_tAISType18.m_ucMsg22 = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 146 - 146, 1-bit, Assigned, bool, Assigned-mode flag: 0 = autonomous mode (default), 1 = assigned mode.
		m_tAISType18.m_ucAssigned = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 147 - 147, 1-bit, RAIM flag, bool, As for common navigation block
		m_tAISType18.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 148 - 167, 20-bit, Radio status, unsigned, 
		m_tAISType18.m_unRadioStatus = CAISUtils::GetU32(strData, nBitIndex, 20);
		
		m_tAISType18.m_ucClassType = 'B';

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType18.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType18.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType18.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType18.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType18.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType18.m_uRcvSecond = (UINT)LocalTime.wSecond;

		nBitIndex += 20;
		// 카운트 증가
		//m_tAISType18.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tRegional Reserved 1 : %d\tSOG : %.1f\tPosition Accuracy : %d\tLongitude : %.7lf\tLatitude : %.7lf\tCOG : %.1f\tHDG : %d\tTime Stamp : %d\tRegional Reserved2 : %d\tCS Unit : %d\tDisplay flag : %d\tDSC : %d\tBand : %d\t Message 22 : %d\tAssigned : %d\tRAIM : %d\tRadio status : %d\tClassType : %c\r\n"),
			m_tAISType18.m_ucType, m_tAISType18.m_ucRepeat, m_tAISType18.m_unMMSI, m_tAISType18.m_ucRegionalReserved1, m_tAISType18.m_fSOG, m_tAISType18.m_ucAccuracy,
			m_tAISType18.m_dLon, m_tAISType18.m_dLat, m_tAISType18.m_fCOG, m_tAISType18.m_usHeading, m_tAISType18.m_ucTimeStamp, m_tAISType18.m_ucRegionalReserved2, m_tAISType18.m_ucClassUnit,
			m_tAISType18.m_ucDisplay, m_tAISType18.m_ucDSC, m_tAISType18.m_ucBand, m_tAISType18.m_ucMsg22, m_tAISType18.m_ucAssigned, m_tAISType18.m_ucRAIM,
			m_tAISType18.m_unRadioStatus, m_tAISType18.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType19(CString strData)
	{
		USHORT usValue;
		//UINT32 unValue;
		INT nBitIndex = 0;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISType19, sizeof(T_AIS_MSG_TYPE19)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 19
		m_tAISType19.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, As in CNN
		m_tAISType19.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 digits
		m_tAISType19.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 45, 8-bits, Regional Reserved, unsigned
		nBitIndex += 8;
		// 46 - 55, 10-bits, Speed Over Ground, unsigned, As in CNB.
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISType19.m_blSOGNA = TRUE;

			m_tAISType19.m_fSOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType19.m_blSOGNA = FALSE;

			m_tAISType19.m_fSOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 10;
		// 56 - 56, 1-bit, Position Accuracy, bool, As in CNB.
		m_tAISType19.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 57 - 84, 28-bits, Longitude, signed, Minutes/10000 (as in CNB)
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);
	
		nBitIndex += 28;

		// 85 - 111, 27-bits, Latitude, signed, Minutes/10000 (as in CNB)
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);
		
		Calc_Pos(unLatitude, unLongitude, &m_tAISType19.m_dLat, &m_tAISType19.m_dLon);

		if (((INT)m_tAISType19.m_dLon == LONGITUDE_NAVALUE) || ((INT)m_tAISType19.m_dLat == LATITUDE_NAVALUE))
			m_tAISType19.m_blPositionNA = TRUE;
		else
			m_tAISType19.m_blPositionNA = FALSE;

		nBitIndex += 27;
		// 112 - 123, 12-bits, Course Over Ground, unsigned, Relative to true north, units of 0.1 degrees
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);

		if (usValue == COG_NAVALUE)
		{
			m_tAISType19.m_blCOGNA = TRUE;

			m_tAISType19.m_fCOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISType19.m_blCOGNA = FALSE;

			m_tAISType19.m_fCOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;
		// 124 - 132, 9-bits, True Heading, unsigned, 0 to 359 degrees, 511 = N/A
		m_tAISType19.m_usHeading = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (m_tAISType19.m_usHeading == HDT_NAVALUE)
			m_tAISType19.m_blHeadingNA = TRUE;
		else
			m_tAISType19.m_blHeadingNA = FALSE;

		nBitIndex += 9;
		// 133 - 138, 6-bits, Time Stamp second, unsigned, Second of UTC timestamp.
		m_tAISType19.m_ucTimeStamp = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 139 - 142, 4-bits, Regional reserved, unsigned, Uninterpreted
		nBitIndex += 4;
		// 143 - 262, 120-bits, Ship Name, signed, 20 6-bit characters
		for (INT nCnt = 0; nCnt < 20; nCnt++)
		{
			m_tAISType19.m_szShipName[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
		}
		// 263 - 270, 8-bits, Type of ship and cargo, unsigned, As in Message 5
		m_tAISType19.m_ucShipType = CAISUtils::GetU8(strData, nBitIndex, 8);
		nBitIndex += 8;
		// 271 - 279, 9-bits, Dimension to Bow, unsigned, Meters
		m_tAISType19.m_usBowDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 280 - 288, 9-bits, Dimension to Stern, unsigned, Meters
		m_tAISType19.m_usSternDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 289 - 294, 6-bits, Dimension to Port, unsigned, Meters
		m_tAISType19.m_ucPortDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 295 - 300, 6-bits, Dimension to Starboard, unsigned, Meters
		m_tAISType19.m_ucStarboardDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 301 - 304, 4-bits, Position Fix Type	epfd, enum, See "EPFD Fix Types"
		m_tAISType19.m_ucEPFD = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 305 - 305, 1-bit, RAIM flag, bool, As in CNB.
		m_tAISType19.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 306 - 306, 1-bit, DTE, bool, 0=Data terminal ready, 1=Not ready (default).
		m_tAISType19.m_ucDTE = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 307 - 307, 1-bit, Assigned mode flag, unsigned, See [IALA] for details
		m_tAISType19.m_ucAssigned = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 308 - 311, 4-bits, Spare, x, Unused, should be zero

		m_tAISType19.m_ucClassType = 'B';

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType19.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType19.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType19.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType19.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType19.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType19.m_uRcvSecond = (UINT)LocalTime.wSecond;

		// 카운트 증가
		//m_tAISType19.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tSOG : %.1f\tPosition Accuracy : %d\tLongitude : %.7lf\tLatitude : %.7lf\tCOG : %.1f\tHDG : %d\tTime Stamp : %d\tShip Name : %s\tShip Type : %d\tDimension to Bow : %d\tDimension to Stern : %d\tDimension to Port : %d\tDimension to Starboard : %d\tEPFD : %d\tRAIM : %d\tDTE : %d\tAssigned : %d\tClassType : %c\r\n"),
			m_tAISType19.m_ucType, m_tAISType19.m_ucRepeat, m_tAISType19.m_unMMSI, m_tAISType19.m_fSOG, m_tAISType19.m_ucAccuracy,
			m_tAISType19.m_dLon, m_tAISType19.m_dLat, m_tAISType19.m_fCOG, m_tAISType19.m_usHeading, m_tAISType19.m_ucTimeStamp, m_tAISType19.m_szShipName,
			m_tAISType19.m_ucShipType, m_tAISType19.m_usBowDimension, m_tAISType19.m_usSternDimension, m_tAISType19.m_ucPortDimension, m_tAISType19.m_ucStarboardDimension,
			m_tAISType19.m_ucEPFD, m_tAISType19.m_ucRAIM, m_tAISType19.m_ucDTE, m_tAISType19.m_ucAssigned, m_tAISType19.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType21(CString strData)
	{
		INT nBitIndex = 0;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISType21, sizeof(T_AIS_MSG_TYPE21)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant: 21
		m_tAISType21.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, As in CNB
		m_tAISType21.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 digits
		m_tAISType21.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 42, 5-bits, Aid type, enum, See "Navaid Types"
		m_tAISType21.m_ucAidType = CAISUtils::GetU8(strData, nBitIndex, 5);
		nBitIndex += 5;
		// 43 - 162, 120-bits, Name, text, Name in sixbit chars
		for (INT nCnt = 0; nCnt < 20; nCnt++)
		{
			m_tAISType21.m_szName[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
			nBitIndex += 6;
		}
		// 163 - 163, 1-bit, Position Accuracy, bool, As in CNB
		m_tAISType21.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 164 - 191, 28-bits, Longitude, signed, Minutes/10000 (as in CNB)
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);
		
		nBitIndex += 28;

		// 192 - 218, 27-bits, Latitude, signed, Minutes/10000 (as in CNB)
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);
		
		Calc_Pos(unLatitude, unLongitude, &m_tAISType21.m_dLat, &m_tAISType21.m_dLon);

		if (((INT)m_tAISType21.m_dLon == LONGITUDE_NAVALUE) || ((INT)m_tAISType21.m_dLat == LATITUDE_NAVALUE))
			m_tAISType21.m_blPositionNA = TRUE;
		else
			m_tAISType21.m_blPositionNA = FALSE;

		nBitIndex += 27;
		// 219 - 227, 9-bits, Dimension to Bow, unsigned, Meters
		m_tAISType21.m_usBowDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 228 - 236, 9-bits, Dimension to Stern, unsigned, Meters
		m_tAISType21.m_usSternDimension = CAISUtils::GetU16(strData, nBitIndex, 9);
		nBitIndex += 9;
		// 237 - 242, 6-bits, Dimension to Port, unsigned, Meters
		m_tAISType21.m_ucPortDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 243 - 248, 6-bits, Dimension to Starboard, 	to_starboard	u	Meters
		m_tAISType21.m_ucStarboardDimension = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 249 - 252, 4-bits, Type of EPFD, enum, As in Message Type 4
		m_tAISType21.m_ucEPFD = CAISUtils::GetU8(strData, nBitIndex, 4);
		nBitIndex += 4;
		// 253 - 258, 6-bits, UTC second, unsigned, As in Message Types 1-3
		m_tAISType21.m_ucSecond = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 259 - 259, 1-bit, Off-Position Indicator, bool, See Below
		m_tAISType21.m_ucOffPosition = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 260 - 267, 8-bit, Regional. unsigned, Uninterpreted
		m_tAISType21.m_ucRegionalReserved = CAISUtils::GetU8(strData, nBitIndex, 8);
		nBitIndex += 8;

		// 268 - 268, 1-bit, RAIM flag, bool, As in CNB
		m_tAISType21.m_ucRAIM = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 269 - 269, 1-bit, Virtual-aid flag, bool, See Below
		m_tAISType21.m_ucVirtualAID = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 270 - 270, 1-bit, Assigned-mode flag, bool, See [IALA] for details
		m_tAISType21.m_ucAssigned = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 271 - 271, 1-bit, Spare, x, Not used
		nBitIndex += 1;

		INT nStart = strData.Find(_T(",")) * 6;

		if (nStart < 300)
		{
			static_cast<void>(ZeroMemory(&m_tAISType21.m_szNameEx[0], 15));
		}
		else
		{
			// 272 - 360, 88-bit, Name Extension, text
			for (INT nCnt = 0; nCnt < 14; nCnt++)
			{
				m_tAISType21.m_szNameEx[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
				nBitIndex += 6;

				if (m_tAISType21.m_szNameEx[nCnt] == '\0')
				{
					break;
				}
			}
		}

		m_tAISType21.m_ucClassType = ' ';

		SYSTEMTIME LocalTime = { 0 };
		GetSystemTime(&LocalTime);

		m_tAISType21.m_uRcvYear = (UINT)LocalTime.wYear;
		m_tAISType21.m_uRcvMonth = (UINT)LocalTime.wMonth;
		m_tAISType21.m_uRcvDay = (UINT)LocalTime.wDay;
		m_tAISType21.m_uRcvHour = (UINT)LocalTime.wHour;
		m_tAISType21.m_uRcvMinute = (UINT)LocalTime.wMinute;
		m_tAISType21.m_uRcvSecond = (UINT)LocalTime.wSecond;

		// 카운트 증가
		//m_tAISType21.m_unCounter++;

#if SAVELOGAIS
		CString strText;
		strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tAid type : %d\tName : %s\tPosition Accuracy : %d\tLongitude : %.7lf\tLatitude : %.7lf\tDimension to Bow : %d\tDimension to Stern : %d\tDimension to Port : %d\tDimension to Starboard : %d\tEPFD : %d\tSecond : %d\tOff-Position : %d\tRegional Reserved : %d\tRAIM : %d\tVirtual-aid : %d\tAssigned : %d\tName Extension : %s\tClassType : %c\r\n"),
			m_tAISType21.m_ucType, m_tAISType21.m_ucRepeat, m_tAISType21.m_unMMSI, m_tAISType21.m_ucAidType, m_tAISType21.m_szName, m_tAISType21.m_ucAccuracy,
			m_tAISType21.m_dLon, m_tAISType21.m_dLat, m_tAISType21.m_usBowDimension, m_tAISType21.m_usSternDimension, m_tAISType21.m_ucPortDimension, m_tAISType21.m_ucStarboardDimension,
			m_tAISType21.m_ucEPFD, m_tAISType21.m_ucSecond, m_tAISType21.m_ucOffPosition, m_tAISType21.m_ucRegionalReserved, m_tAISType21.m_ucRAIM, m_tAISType21.m_ucVirtualAID, m_tAISType21.m_ucAssigned,
			m_tAISType21.m_szNameEx, m_tAISType21.m_ucClassType);
		Savelog(strText);
		OutputDebugString(strText);
#endif
	}

	void CNMEAParser::FetchAISType24(CString strData)
	{
		INT nBitIndex = 0;

		static_cast<void>(ZeroMemory(&m_tAISType24, sizeof(T_AIS_MSG_TYPE24)));

		// 0 - 5, 6-bits, Message Type, unsigned, Constant : 24
		m_tAISType24.m_ucType = CAISUtils::GetU8(strData, nBitIndex, 6);
		nBitIndex += 6;
		// 6 - 7, 2-bits, Repeat Indicator, unsigned, As in CNB
		m_tAISType24.m_ucRepeat = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		// 8 - 37, 30-bits, MMSI, unsigned, 9 digits
		m_tAISType24.m_unMMSI = CAISUtils::GetU32(strData, nBitIndex, 30);
		nBitIndex += 30;
		// 38 - 39, 2-bits, Part Number, unsigned, 0-1
		m_tAISType24.m_ucPartNumber = CAISUtils::GetU8(strData, nBitIndex, 2);
		nBitIndex += 2;
		if (m_tAISType24.m_ucPartNumber == 0)		// PART-A
		{
			// 40 - 159, 120-bits, Vessel Name, text, (Part A) 20 sixbit chars
			for (INT nCnt = 0; nCnt < 20; nCnt++)
			{
				m_tAISType24.m_tPartA.m_szShipName[nCnt] = CAISUtils::GetCHAR(strData, nBitIndex, 6);
				nBitIndex += 6;
			}
			// 160 - 167, 8-bits, Spare, x(Part A), Not used

			m_tAISType24.m_ucClassType = 'B';
			// 카운트 증가
			//m_tAISType24.m_unCounter++;

#if SAVELOGAIS
			CString strText;
			strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tPart Number :%d\tShip Name : %s\r\n"),
				m_tAISType24.m_ucType, m_tAISType24.m_ucRepeat, m_tAISType24.m_unMMSI, m_tAISType24.m_ucPartNumber, m_tAISType24.m_tPartA.m_szShipName);
			Savelog(strText);
			OutputDebugString(strText);
#endif
		}
		else		// PART-B
		{
			
			INT nBitIndexV3 = nBitIndex;
			INT nBitIndexV4 = nBitIndex;

			///////V3 Parsing
			{
				// 40 - 47, 8-bits, Ship Type, enum, (Part B) See "Ship Types"
				m_tAISType24.m_tPartB1.m_ucShipType = CAISUtils::GetU8(strData, nBitIndexV3, 8);
				nBitIndexV3 += 8;
				// 48 - 65, 18-bits, Vendor ID, text, (Part B) 3 six-bit chars
				for (INT nCnt = 0; nCnt < 7; nCnt++)
				{
					m_tAISType24.m_tPartB1.m_szVendorID[nCnt] = CAISUtils::GetCHAR(strData, nBitIndexV3, 6);
					nBitIndexV3 += 6;
				}

				// 90 - 131, 42-bits, Call Sign, text, (Part B) As in Message Type 5
				for (INT nCnt = 0; nCnt < 7; nCnt++)
				{
					m_tAISType24.m_tPartB1.m_szCallSign[nCnt] = CAISUtils::GetCHAR(strData, nBitIndexV3, 6);
					nBitIndexV3 += 6;
				}

				// 132 - 140, 9-bits, Dimension to Bow, unsigned, (Part B) Meters
				m_tAISType24.m_tPartB1.m_usBowDimension = CAISUtils::GetU16(strData, nBitIndexV3, 9);
				nBitIndexV3 += 9;

				// 141 - 149, 9-bits, Dimension to Stern, unsigned, (Part B) Meters
				m_tAISType24.m_tPartB1.m_usSternDimension = CAISUtils::GetU16(strData, nBitIndexV3, 9);
				nBitIndexV3 += 9;

				// 150 - 155, 6-bits, Dimension to Port, unsigned, (Part B) Meters
				m_tAISType24.m_tPartB1.m_ucPortDimension = CAISUtils::GetU8(strData, nBitIndexV3, 6);
				nBitIndexV3 += 6;

				// 156 - 161, 6-bits, Dimension to Starboard, unsigned, (Part B) Meters
				m_tAISType24.m_tPartB1.m_ucStarboardDimension = CAISUtils::GetU8(strData, nBitIndexV3, 6);
				nBitIndexV3 += 6;
			}

			///////V4 Parsing
			{
				// 40 - 47, 8-bits, Ship Type, enum, (Part B) See "Ship Types"
				m_tAISType24.m_tPartB2.m_ucShipType = CAISUtils::GetU8(strData, nBitIndexV4, 8);
				nBitIndexV4 += 8;
				// 48 - 65, 18-bits, Vendor ID, text, (Part B) 3 six-bit chars
				for (INT nCnt = 0; nCnt < 3; nCnt++)
				{
					m_tAISType24.m_tPartB2.m_szVendorID[nCnt] = CAISUtils::GetCHAR(strData, nBitIndexV4, 6);
					nBitIndexV4 += 6;
				}

				//// 66 - 69, 4-bits, Unit Code Model,  unsigned, (Part B)
				m_tAISType24.m_tPartB2.m_ucModelCode = CAISUtils::GetU8(strData, nBitIndexV4, 4);
				nBitIndexV4 += 4;
				//
				//// 70 - 89, 20-bits, Serial Number, unsigned, (Part B)
				m_tAISType24.m_tPartB2.m_unSerialNumber = CAISUtils::GetU32(strData, nBitIndexV4, 20);
				nBitIndexV4 += 20;

				// 90 - 131, 42-bits, Call Sign, text, (Part B) As in Message Type 5
				for (INT nCnt = 0; nCnt < 7; nCnt++)
				{
					m_tAISType24.m_tPartB2.m_szCallSign[nCnt] = CAISUtils::GetCHAR(strData, nBitIndexV3, 6);
					nBitIndexV3 += 6;
				}

				m_tAISType24.m_tPartB2.m_unMotherMMSI = CAISUtils::GetU32(strData, nBitIndexV4, 30);
			}

			m_tAISType24.m_ucClassType = 'B';

			SYSTEMTIME LocalTime = { 0 };
			GetSystemTime(&LocalTime);

			m_tAISType24.m_uRcvYear = (UINT)LocalTime.wYear;
			m_tAISType24.m_uRcvMonth = (UINT)LocalTime.wMonth;
			m_tAISType24.m_uRcvDay = (UINT)LocalTime.wDay;
			m_tAISType24.m_uRcvHour = (UINT)LocalTime.wHour;
			m_tAISType24.m_uRcvMinute = (UINT)LocalTime.wMinute;
			m_tAISType24.m_uRcvSecond = (UINT)LocalTime.wSecond;

			// 카운트 증가
			//m_tAISType24.m_unCounter++;

#if SAVELOGAIS
			CString strText;
			strText.Format(_T("MSG Type : %d\tRepeat Indicator : %d\tMMSI : %d\tPart Number :%d\tShip Type(B1) : %d\tVendor ID(B1) : %s\tCallSign(B1) : %s\tDimension to Bow(B1) : %d\tDimension to Stern(B1) : %d\tDimension to Port(B1) : %d\tDimension to Stern(B1) : %d\tVendor ID(B2) : %s\t Unit Model Code(B2) : %d\tSerial Number(B2) : %d\tCallSign(B2) : %s\tMotherShip MMSI(B2) : %d\r\n"),
				m_tAISType24.m_ucType, m_tAISType24.m_ucRepeat, m_tAISType24.m_unMMSI, m_tAISType24.m_ucPartNumber, m_tAISType24.m_tPartB1.m_ucShipType, 
				m_tAISType24.m_tPartB1.m_szVendorID, m_tAISType24.m_tPartB1.m_szCallSign, m_tAISType24.m_tPartB1.m_usBowDimension, 
				m_tAISType24.m_tPartB1.m_usSternDimension, m_tAISType24.m_tPartB1.m_ucPortDimension, m_tAISType24.m_tPartB1.m_ucStarboardDimension,
				m_tAISType24.m_tPartB2.m_szVendorID, m_tAISType24.m_tPartB2.m_ucModelCode, m_tAISType24.m_tPartB2.m_unSerialNumber, m_tAISType24.m_tPartB2.m_szCallSign, m_tAISType24.m_tPartB2.m_unMotherMMSI);
			Savelog(strText);
			OutputDebugString(strText);
#endif
		}
	}

	void CNMEAParser::FetchAIVDOType1(CString strData)
	{
		INT nBitIndex = 0;
		USHORT usValue;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO1, sizeof(T_AIS_MSG_TYPEAIVDO1)));
		
		nBitIndex += 42;

		CHAR temp = static_cast<CHAR>(CAISUtils::GetU8(strData, nBitIndex, 8));

		if (temp == ROT_NAVALUE)
		{
			m_tAISTypeAIVDO1.bRotAvail = false;

			m_tAISTypeAIVDO1.ROT = temp;
		}
		else
		{
			m_tAISTypeAIVDO1.bRotAvail = true;

			if ((temp == ROT_NOTIMAX) || (temp == ROT_NOTIMIN))
			{
				m_tAISTypeAIVDO1.ROT = temp;
			}
			else
			{
				m_tAISTypeAIVDO1.ROT = temp;

				bool minus = false;

				if (m_tAISTypeAIVDO1.ROT < 0)
				{
					m_tAISTypeAIVDO1.ROT = m_tAISTypeAIVDO1.ROT * -1;
					minus = true;
				}

				m_tAISTypeAIVDO1.ROT = (FLOAT)(m_tAISTypeAIVDO1.ROT / 4.733);

				m_tAISTypeAIVDO1.ROT = (FLOAT)(pow(m_tAISTypeAIVDO1.ROT, 2));

				if (minus)
					m_tAISTypeAIVDO1.ROT = m_tAISTypeAIVDO1.ROT * -1;
			}
		}

		nBitIndex += 8;
		// 50 - 59, 10-bits, Speed Over Ground (SOG), unsigned
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISTypeAIVDO1.bSogAvail = false;

			m_tAISTypeAIVDO1.SOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO1.bSogAvail = true;

			m_tAISTypeAIVDO1.SOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 11;
		
		// 61 - 88, 28-bits, Longitude, signed, Minutes/10000
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);

		nBitIndex += 28;
		// 89 - 115, 27-bits, Latitude, signed, Minutes/10000
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);

		Calc_Pos(unLatitude, unLongitude, &m_tAISTypeAIVDO1.Lat, &m_tAISTypeAIVDO1.Long);

		if (((INT)m_tAISTypeAIVDO1.Long == LONGITUDE_NAVALUE) || ((INT)m_tAISTypeAIVDO1.Lat == LATITUDE_NAVALUE))
			m_tAISTypeAIVDO1.bPosAvail = false;
		else
			m_tAISTypeAIVDO1.bPosAvail = true;

		nBitIndex += 27;

		// 116 - 127, 12-bits, Course Over Ground (COG), unsigned, Relative to true north, to 0.1 degree precision
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);

		if (usValue == COG_NAVALUE)
		{
			m_tAISTypeAIVDO1.bCogAvail = false;

			m_tAISTypeAIVDO1.COG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO1.bCogAvail = true;

			m_tAISTypeAIVDO1.COG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;

		// 128 - 136, 9-bits, True Heading (HDG), unsigned, 0 to 359 degrees, 511 = not available.
		m_tAISTypeAIVDO1.HDT = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (m_tAISTypeAIVDO1.HDT == HDT_NAVALUE)
			m_tAISTypeAIVDO1.bHeadingAvail = false;
		else
			m_tAISTypeAIVDO1.bHeadingAvail = true;
	}

	void CNMEAParser::FetchAIVDOType18(CString strData)
	{
		USHORT usValue;
		INT nBitIndex = 46;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO18, sizeof(T_AIS_MSG_TYPEAIVDO18)));

		// 46 - 55, 10-bit, Speed Over Ground, unsigned,	As in common navigation block
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISTypeAIVDO18.bSogAvail = false;

			m_tAISTypeAIVDO18.SOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO18.bSogAvail = true;

			m_tAISTypeAIVDO18.SOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 10;
		// 56 - 56, 1-bit, Position Accuracy, bool, 0 = accuracy > 10m (default), 1 = accuracy < 10m
		m_tAISType18.m_ucAccuracy = CAISUtils::GetU8(strData, nBitIndex, 1);
		nBitIndex += 1;
		// 57 - 84, 28-bit, Longitude, signed, Minutes/10000
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);

		nBitIndex += 28;

		// 85 - 111, 27-bit, Latitude, signed, Minutes/10000
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);

		Calc_Pos(unLatitude, unLongitude, &m_tAISTypeAIVDO18.Lat, &m_tAISTypeAIVDO18.Long);

		if (((INT)m_tAISTypeAIVDO18.Long == LONGITUDE_NAVALUE) || ((INT)m_tAISTypeAIVDO18.Lat == LATITUDE_NAVALUE))
			m_tAISTypeAIVDO18.bPosAvail = false;
		else
			m_tAISTypeAIVDO18.bPosAvail = true;

		nBitIndex += 27;
		// 112 - 123, 12-bit, Course Over Ground, Unsigned,	0.1 degrees from true north
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);

		if (usValue == COG_NAVALUE)
		{
			m_tAISTypeAIVDO18.bCogAvail = false;

			m_tAISTypeAIVDO18.COG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO18.bCogAvail = true;

			m_tAISTypeAIVDO18.COG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;
		// 124 - 132, 9-bit, True Heading, unsigned, 0 to 359 degrees, 511 = N/A
		m_tAISTypeAIVDO18.HDT = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (m_tAISTypeAIVDO18.HDT == HDT_NAVALUE)
			m_tAISTypeAIVDO18.bHeadingAvail = false;
		else
			m_tAISTypeAIVDO18.bHeadingAvail = true;
	}

	void CNMEAParser::FetchAIVDOType19(CString strData)
	{
		USHORT usValue;
		//UINT32 unValue;
		INT nBitIndex = 0;

		INT32 unLatitude, unLongitude;

		static_cast<void>(ZeroMemory(&m_tAISTypeAIVDO19, sizeof(T_AIS_MSG_TYPE19)));

		nBitIndex += 38;

		// 38 - 45, 8-bits, Regional Reserved, unsigned
		nBitIndex += 8;
		// 46 - 55, 10-bits, Speed Over Ground, unsigned, As in CNB.
		usValue = CAISUtils::GetU16(strData, nBitIndex, 10);

		if (usValue == SOG_NAVALUE)
		{
			m_tAISTypeAIVDO19.bSogAvail = false;

			m_tAISTypeAIVDO19.SOG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO19.bSogAvail = true;

			m_tAISTypeAIVDO19.SOG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 11;
		
		// 57 - 84, 28-bits, Longitude, signed, Minutes/10000 (as in CNB)
		unLongitude = CAISUtils::GetU32(strData, nBitIndex, 28);

		nBitIndex += 28;

		// 85 - 111, 27-bits, Latitude, signed, Minutes/10000 (as in CNB)
		unLatitude = CAISUtils::GetU32(strData, nBitIndex, 27);

		Calc_Pos(unLatitude, unLongitude, &m_tAISTypeAIVDO19.Lat, &m_tAISTypeAIVDO19.Long);

		if (((INT)m_tAISTypeAIVDO19.Long == LONGITUDE_NAVALUE) || ((INT)m_tAISTypeAIVDO19.Lat == LATITUDE_NAVALUE))
			m_tAISTypeAIVDO19.bPosAvail = false;
		else
			m_tAISTypeAIVDO19.bPosAvail = true;

		nBitIndex += 27;
		// 112 - 123, 12-bits, Course Over Ground, unsigned, Relative to true north, units of 0.1 degrees
		usValue = CAISUtils::GetU16(strData, nBitIndex, 12);

		if (usValue == COG_NAVALUE)
		{
			m_tAISTypeAIVDO19.bCogAvail = false;

			m_tAISTypeAIVDO19.COG = (FLOAT)usValue;
		}
		else
		{
			m_tAISTypeAIVDO19.bCogAvail = true;

			m_tAISTypeAIVDO19.COG = (FLOAT)(usValue * 0.1F);
		}

		nBitIndex += 12;
		// 124 - 132, 9-bits, True Heading, unsigned, 0 to 359 degrees, 511 = N/A
		m_tAISTypeAIVDO19.HDT = CAISUtils::GetU16(strData, nBitIndex, 9);

		if (m_tAISTypeAIVDO19.HDT == HDT_NAVALUE)
			m_tAISTypeAIVDO19.bHeadingAvail = true;
		else
			m_tAISTypeAIVDO19.bHeadingAvail = false;
	}

} // NS_SALUS_MS_APP
