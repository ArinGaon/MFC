#include "pch.h"
#include "AISMsgManager.h"

#include "UserCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif	// _DEBUG

namespace NS_SALUS_MS_APP
{
	CAISMsgManager::CAISMsgManager()
	{
		m_bStarted = FALSE;
		m_pAISData = NULL;
		m_pAIVDOData = NULL;

		m_unUpdateCount = 0U;
		static_cast<void>(ZeroMemory(&m_tLastUpdateTime, sizeof(SYSTEMTIME)));

		m_pSerialMsgAIS = NULL;
		m_pMsgParserAIS = NULL;

		m_pAISMsgProcThread = NULL;
		m_hAISMsgProcExitEvent = CreateEvent(NULL, FALSE, FALSE, _T("AIS MSG MNGR EXIT EVENT"));
	}

	CAISMsgManager::~CAISMsgManager()
	{
		Finalize();

		CloseHandle(m_hAISMsgProcExitEvent);
	}

	void CAISMsgManager::Initialize()
	{
		if (m_pAISData == NULL)
		{
			m_pAISData = new T_AIS_DATA;
			static_cast<void>(ZeroMemory(m_pAISData, sizeof(T_AIS_DATA)));
		}

		if (m_pAIVDOData == NULL)
		{
			m_pAIVDOData = new T_AIVDO_AIS;
			static_cast<void>(ZeroMemory(m_pAIVDOData, sizeof(T_AIVDO_AIS)));
		}

		if (m_pSerialMsgAIS == NULL)
		{
			m_pSerialMsgAIS = new CSerialMsgMngr();
		}

		if (m_pMsgParserAIS == NULL)
		{
			m_pMsgParserAIS = new CNMEAParser();
		}
	}

	void CAISMsgManager::Finalize()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();

		if (m_pSerialMsgAIS != NULL)
		{
			delete m_pSerialMsgAIS;
			m_pSerialMsgAIS = NULL;
		}

		if (m_pMsgParserAIS != NULL)
		{
			delete m_pMsgParserAIS;
			m_pMsgParserAIS = NULL;
		}

		if (m_pAISData != NULL)
		{
			delete m_pAISData;
			m_pAISData = NULL;
		}

		if (m_pAIVDOData != NULL)
		{
			delete m_pAIVDOData;
			m_pAIVDOData = NULL;
		}
	}

	void CAISMsgManager::Start()
	{
		if (m_pSerialMsgAIS != NULL)
		{
			m_pSerialMsgAIS->Clear();
		}

		m_unUpdateCount = 0U;
		GetLocalTime(&m_tLastUpdateTime);

		CreateMsgProcThread();

		m_bStarted = TRUE;
	}

	void CAISMsgManager::Stop()
	{
		m_bStarted = FALSE;

		ExitMsgProcThread();
	}

	void CAISMsgManager::ClearMsg()
	{
		if (m_pSerialMsgAIS != NULL)
		{
			m_pSerialMsgAIS->Clear();
		}
	}

	BOOL CAISMsgManager::IsStarted()
	{
		return m_bStarted;
	}

	CSerialMsgMngr* CAISMsgManager::GetSerialMsgMngr()
	{
		return m_pSerialMsgAIS;
	}

	UINT CAISMsgManager::GetUpdateCount()
	{
		return m_unUpdateCount;
	}

	SYSTEMTIME* CAISMsgManager::GetLastUpdateTime()
	{
		return &m_tLastUpdateTime;
	}

	void CAISMsgManager::UpdateAISInfo(const E_PARSING_RESULT eParsingResult)
	{
		CAISDataMngr* pAISDataMngr = CAISDataMngr::GetInstance();
		if ((pAISDataMngr != NULL) && (m_pMsgParserAIS != NULL))
		{
			BOOL bUpdate = TRUE;

			ZeroMemory(m_pAISData, sizeof(m_pAISData));

			switch (eParsingResult)
			{
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE1());

				if (m_pAISData->m_blIsSartMsg)
				{
					bUpdate = FALSE;

					CUserCommand* pUserCommand = CUserCommand::GetInstance();
										
					if (pUserCommand != NULL)
					{
						T_USER_COMMAND* pUserCmd = pUserCommand->GetBackBuffer();
						pUserCmd->eCommand = E_USER_COMMAND::eUSER_CMD_VIEW_AIS_SART;

						ZeroMemory(&pUserCmd->m_tAISMessageTypeSart, sizeof(pUserCmd->m_tAISMessageTypeSart));

						memcpy(pUserCmd->m_tAISMessageTypeSart.m_cCallSign, "Unknown ", sizeof(pUserCmd->m_tAISMessageTypeSart.m_cCallSign));

						pAISDataMngr->FindCallSign(m_pAISData->m_unMMSI, pUserCmd->m_tAISMessageTypeSart.m_cCallSign);

						pUserCmd->m_tAISMessageTypeSart.m_unMMSI = m_pAISData->m_unMMSI;
						pUserCmd->m_tAISMessageTypeSart.m_dLon = m_pAISData->m_dLat;
						pUserCmd->m_tAISMessageTypeSart.m_dLat = m_pAISData->m_dLon;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvYear = m_pAISData->m_uRcvYear;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvMonth = m_pAISData->m_uRcvMonth;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvDay = m_pAISData->m_uRcvDay;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvHour = m_pAISData->m_uRcvHour;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvMinute = m_pAISData->m_uRcvMinute;
						pUserCmd->m_tAISMessageTypeSart.m_uRcvSecond = m_pAISData->m_uRcvSecond;
						pUserCmd->m_tAISMessageTypeSart.m_blPositionNA = m_pAISData->m_blPositionNA;

						pUserCommand->PushBack(FALSE);
					}
				}
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE2:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE2());

				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE3:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE3());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE4:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE4());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE5:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE5());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE9:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE9());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE18:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE18());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE19:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE19());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE21:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE21());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE24:
			{
				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPE24());
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE1:
			{
				bUpdate = FALSE;

				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPEAIVDO1());

				pAISDataMngr->UpdateAIVDOUpdate(m_pAIVDOData);
				//자선 정보 업데이트 필요
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE18:
			{
				bUpdate = FALSE;

				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPEAIVDO18());

				pAISDataMngr->UpdateAIVDOUpdate(m_pAIVDOData);
				//자선 정보 업데이트 필요
				break;
			}
			case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE19:
			{
				bUpdate = FALSE;

				CopyAISInfo(m_pMsgParserAIS->GetAIS_TYPEAIVDO19());

				pAISDataMngr->UpdateAIVDOUpdate(m_pAIVDOData);
				//자선 정보 업데이트 필요
				break;
			}
			default:
			{
				bUpdate = FALSE;
				break;
			}
			}  // switch

			if (bUpdate == TRUE)
			{
				const INT nType = static_cast<INT>(eParsingResult) - static_cast<INT>(E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1);
				pAISDataMngr->UpdateData(static_cast<E_AIS_DATA_TYPE>(nType), m_pAISData);
				
				m_unUpdateCount++;
				GetLocalTime(&m_tLastUpdateTime);
			}
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE1_3* const pAisType1_3)
	{
		if ((m_pAISData != NULL) && (pAisType1_3 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType1_3->m_unMMSI;
			m_pAISData->m_ucValidStatus = 1U;						// Navigation Status valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucNaviStatus = pAisType1_3->m_ucStatus;	// Navigation Status
			m_pAISData->m_cTurnRate = pAisType1_3->m_cTurnRate;		// Rate of turn, 0 ~ 255, scale factor = -127
			//m_pAISData->m_ucValidSOG = 1;							// SOG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fSOG = pAisType1_3->m_fSOG;				// Speed over ground, knots, Range : 0 ~ 102.2
			//m_pAISData->m_ucValidPosition = 1;						// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType1_3->m_ucAccuracy;	// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType1_3->m_dLon;				// Longitude
			m_pAISData->m_dLat = pAisType1_3->m_dLat;				// latitude
			//m_pAISData->m_ucValidCOG = 1;							// COG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fCOG = pAisType1_3->m_fCOG;				// Course over ground, Range : 0 ~ 360.0
			//m_pAISData->m_ucValidHeading = 1;						// Heading valid, 0 : not valid, 1 : valid
			m_pAISData->m_usHeading = pAisType1_3->m_usHeading;		// Heading, 0 to 359 degrees, 511 = not available.
			m_pAISData->m_ucTimeStamp = pAisType1_3->m_ucTimeStamp;	// Time Stamp, Second of UTC timestamp, 0 ~ 59
			m_pAISData->m_ucManeuver = pAisType1_3->m_ucManeuver;	// Maneuver Indicator 0 ~ 2
			m_pAISData->m_ucClassType = pAisType1_3->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType1_3->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType1_3->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType1_3->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType1_3->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType1_3->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType1_3->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType1_3->m_blPositionNA;
			m_pAISData->m_blRotNA = pAisType1_3->m_blRotNA;
			m_pAISData->m_blHeadingNA = pAisType1_3->m_blHeadingNA;
			m_pAISData->m_blSOGNA = pAisType1_3->m_blSOGNA;
			m_pAISData->m_blCOGNA = pAisType1_3->m_blCOGNA;
			m_pAISData->m_blIsSartMsg = pAisType1_3->m_blIsSartMsg;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE4* const pAisType4)
	{
		if ((m_pAISData != NULL) && (pAisType4 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType4->m_unMMSI;
			//m_pAISData->m_ucValidDateTime = 1;						// Date and Time Valid, 0 : not valid, 1 : valid
			//m_pAISData->m_usYear = pAisType4->m_usYear;				// Year(UTC), 1-9999, 0 = N/A (default)
			//m_pAISData->m_ucMonth = pAisType4->m_ucMonth;			// Month(UTC), 1-12; 0 = N/A (default)
			//m_pAISData->m_ucDay = pAisType4->m_ucDay;				// Day(UTC), 1-31; 0 = N/A (default)
			//m_pAISData->m_ucHour = pAisType4->m_ucHour;				// Hour(UTC), 0-23; 24 = N/A (default)
			//m_pAISData->m_ucMinute = pAisType4->m_ucMinute;			// 0-59; 60 = N/A (default)
			//m_pAISData->m_ucSecond = pAisType4->m_ucSecond;			// 0-59; 60 = N/A (default)
			//m_pAISData->m_ucValidPosition = 1;						// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType4->m_ucQuality;		// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType4->m_dLon;					// Longitude
			m_pAISData->m_dLat = pAisType4->m_dLat;					// latitude
			m_pAISData->m_ucClassType = pAisType4->m_ucClassType;

			m_pAISData->m_uRcvYear   = pAisType4->m_uRcvYear;
			m_pAISData->m_uRcvMonth  = pAisType4->m_uRcvMonth;
			m_pAISData->m_uRcvDay    = pAisType4->m_uRcvDay;
			m_pAISData->m_uRcvHour   = pAisType4->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType4->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType4->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType4->m_blPositionNA;
			m_pAISData->m_ucEPFD = pAisType4->m_ucEPFD;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE5* const pAisType5)
	{
		if ((m_pAISData != NULL) && (pAisType5 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType5->m_unMMSI;
			m_pAISData->m_unIMO = pAisType5->m_unIMO;							// IMO ship ID number
			_tcscpy_s(m_pAISData->m_szCallSign, 8, pAisType5->m_szCallSign);		// 7 six - bit characters
			_tcscpy_s(m_pAISData->m_szShipName, 21, pAisType5->m_szShipName);	// Vessel Name, 20 six - bit characters
			m_pAISData->m_ucShipType = pAisType5->m_ucShipType;					// Ship Type
			m_pAISData->m_ucClassType = pAisType5->m_ucClassType;;

			m_pAISData->m_uRcvYear = pAisType5->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType5->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType5->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType5->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType5->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType5->m_uRcvSecond;

			m_pAISData->m_usBow = pAisType5->m_usBowDimension;
			m_pAISData->m_usStern = pAisType5->m_usSternDimension;
			m_pAISData->m_usPort = pAisType5->m_ucPortDimension;
			m_pAISData->m_usStarBoard = pAisType5->m_ucStarboardDimension;

			m_pAISData->m_ucETA[0] = pAisType5->m_ucMonth;
			m_pAISData->m_ucETA[1] = pAisType5->m_ucDay;
			m_pAISData->m_ucETA[2] = pAisType5->m_ucHour;
			m_pAISData->m_ucETA[3] = pAisType5->m_ucMinute;

			m_pAISData->m_fDraught = pAisType5->m_fDraught;

			memcpy(m_pAISData->m_szDestination, pAisType5->m_szDestination, sizeof(m_pAISData->m_szDestination));
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE9* const pAisType9)
	{
		if ((m_pAISData != NULL) && (pAisType9 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType9->m_unMMSI;
			//m_pAISData->m_ucValidSOG = 1U;							// SOG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fSOG = pAisType9->m_fSOG;					// Speed over ground, knots, Range : 0 ~ 102.2
			//m_pAISData->m_ucValidPosition = 1U;						// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType9->m_ucAccuracy;		// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType9->m_dLon;					// Longitude
			m_pAISData->m_dLat = pAisType9->m_dLat;					// latitude
			//m_pAISData->m_ucValidCOG = 1U;							// COG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fCOG = pAisType9->m_fCOG;					// Course over ground, Range : 0 ~ 360.0
			m_pAISData->m_ucTimeStamp = pAisType9->m_ucTimeStamp;	// Time Stamp, Second of UTC timestamp, 0 ~ 59
			m_pAISData->m_ucClassType = pAisType9->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType9->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType9->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType9->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType9->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType9->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType9->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType9->m_blPositionNA;
			m_pAISData->m_blSOGNA = pAisType9->m_blSOGNA;
			m_pAISData->m_blCOGNA = pAisType9->m_blCOGNA;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE18* const pAisType18)
	{
		if ((m_pAISData != NULL) && (pAisType18 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType18->m_unMMSI;
			//m_pAISData->m_ucValidSOG = 1U;							// SOG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fSOG = pAisType18->m_fSOG;				// Speed over ground, knots, Range : 0 ~ 102.2
			//m_pAISData->m_ucValidPosition = 1U;						// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType18->m_ucAccuracy;	// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType18->m_dLon;				// Longitude
			m_pAISData->m_dLat = pAisType18->m_dLat;				// latitude
			//m_pAISData->m_ucValidCOG = 1U;							// COG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fCOG = pAisType18->m_fCOG;				// Course over ground, Range : 0 ~ 360.0
			//m_pAISData->m_ucValidHeading = 1U;						// Heading valid, 0 : not valid, 1 : valid
			m_pAISData->m_usHeading = pAisType18->m_usHeading;		// Heading, 0 to 359 degrees, 511 = not available.
			m_pAISData->m_ucClassType = pAisType18->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType18->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType18->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType18->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType18->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType18->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType18->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType18->m_blPositionNA;
			m_pAISData->m_blHeadingNA = pAisType18->m_blHeadingNA;
			m_pAISData->m_blSOGNA = pAisType18->m_blSOGNA;
			m_pAISData->m_blCOGNA = pAisType18->m_blCOGNA;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE19* const pAisType19)
	{
		if ((m_pAISData != NULL) && (pAisType19 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType19->m_unMMSI;
			//m_pAISData->m_ucValidSOG = 1U;										// SOG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fSOG = pAisType19->m_fSOG;							// Speed over ground, knots, Range : 0 ~ 102.2
			//m_pAISData->m_ucValidPosition = 1U;									// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType19->m_ucAccuracy;				// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType19->m_dLon;							// Longitude
			m_pAISData->m_dLat = pAisType19->m_dLat;							// latitude
			//m_pAISData->m_ucValidCOG = 1U;										// COG valid, 0 : not valid, 1 : valid
			m_pAISData->m_fCOG = pAisType19->m_fCOG;							// Course over ground, Range : 0 ~ 360.0
			//m_pAISData->m_ucValidHeading = 1U;									// Heading valid, 0 : not valid, 1 : valid
			m_pAISData->m_usHeading = pAisType19->m_usHeading;					// Heading, 0 to 359 degrees, 511 = not available.
			m_pAISData->m_ucTimeStamp = pAisType19->m_ucTimeStamp;				// Time Stamp, Second of UTC timestamp, 0 ~ 59
			_tcscpy_s(m_pAISData->m_szShipName, 21, pAisType19->m_szShipName);	// Vessel Name, 20 six - bit characters
			m_pAISData->m_ucShipType = pAisType19->m_ucShipType;							// Ship Type
			m_pAISData->m_ucClassType = pAisType19->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType19->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType19->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType19->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType19->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType19->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType19->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType19->m_blPositionNA;
			m_pAISData->m_blHeadingNA = pAisType19->m_blHeadingNA;
			m_pAISData->m_blSOGNA = pAisType19->m_blSOGNA;
			m_pAISData->m_blCOGNA = pAisType19->m_blCOGNA;

			m_pAISData->m_usBow = pAisType19->m_usBowDimension;
			m_pAISData->m_usStern = pAisType19->m_usSternDimension;
			m_pAISData->m_usPort = pAisType19->m_ucPortDimension;
			m_pAISData->m_usStarBoard = pAisType19->m_ucStarboardDimension;

		}							
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE21* const pAisType21)
	{
		if ((m_pAISData != NULL) && (pAisType21 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType21->m_unMMSI;
			//m_pAISData->m_ucValidPosition = 1U;								// Lat/Lon valid, 0 : not valid, 1 : valid
			m_pAISData->m_ucAccuracy = pAisType21->m_ucAccuracy;				// Position accuracy, 0 ~ 1
			m_pAISData->m_dLon = pAisType21->m_dLon;							// Longitude
			m_pAISData->m_dLat = pAisType21->m_dLat;							// latitude
			_tcscpy_s(m_pAISData->m_szShipName, 21, pAisType21->m_szName);		// Vessel Name, 20 six - bit characters

			m_pAISData->m_ucClassType = pAisType21->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType21->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType21->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType21->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType21->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType21->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType21->m_uRcvSecond;

			m_pAISData->m_blPositionNA = pAisType21->m_blPositionNA;

			m_pAISData->m_usBow = pAisType21->m_usBowDimension;
			m_pAISData->m_usStern = pAisType21->m_usSternDimension;
			m_pAISData->m_usPort = pAisType21->m_ucPortDimension;
			m_pAISData->m_usStarBoard = pAisType21->m_ucStarboardDimension;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPE24* const pAisType24)
	{
		if ((m_pAISData != NULL) && (pAisType24 != NULL))
		{
			m_pAISData->m_unMMSI = pAisType24->m_unMMSI;
			if (pAisType24->m_ucPartNumber == 0)
			{
				_tcscpy_s(m_pAISData->m_szShipName, 21, pAisType24->m_tPartA.m_szShipName);	// Vessel Name, 20 six - bit characters
			}
			else if (pAisType24->m_ucPartNumber == 1)
			{
				m_pAISData->m_ucShipType = pAisType24->m_tPartB1.m_ucShipType;				// Ship Type
			}
			else if (pAisType24->m_ucPartNumber == 1)
			{
				m_pAISData->m_ucShipType = pAisType24->m_tPartB2.m_ucShipType;				// Ship Type

				m_pAISData->m_usBow = pAisType24->m_tPartB1.m_usBowDimension;
				m_pAISData->m_usStern = pAisType24->m_tPartB1.m_usSternDimension;
				m_pAISData->m_usPort = pAisType24->m_tPartB1.m_ucPortDimension;
				m_pAISData->m_usStarBoard = pAisType24->m_tPartB1.m_ucStarboardDimension;
			}
			else
			{}
			m_pAISData->m_ucClassType = pAisType24->m_ucClassType;

			m_pAISData->m_uRcvYear = pAisType24->m_uRcvYear;
			m_pAISData->m_uRcvMonth = pAisType24->m_uRcvMonth;
			m_pAISData->m_uRcvDay = pAisType24->m_uRcvDay;
			m_pAISData->m_uRcvHour = pAisType24->m_uRcvHour;
			m_pAISData->m_uRcvMinute = pAisType24->m_uRcvMinute;
			m_pAISData->m_uRcvSecond = pAisType24->m_uRcvSecond;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPEAIVDO1* const pAisTypeAIVDO)
	{
		if ((m_pAIVDOData != NULL) && (pAisTypeAIVDO != NULL))
		{
			m_pAIVDOData->bPosAvail = pAisTypeAIVDO->bPosAvail;			
			m_pAIVDOData->Lat = pAisTypeAIVDO->Lat;
			m_pAIVDOData->Long = pAisTypeAIVDO->Long;
			m_pAIVDOData->bSogAvail = pAisTypeAIVDO->bSogAvail;
			m_pAIVDOData->SOG = pAisTypeAIVDO->SOG;
			m_pAIVDOData->bCogAvail = pAisTypeAIVDO->bCogAvail;
			m_pAIVDOData->COG = pAisTypeAIVDO->COG;
			m_pAIVDOData->bRotAvail = pAisTypeAIVDO->bRotAvail;
			m_pAIVDOData->ROT = pAisTypeAIVDO->ROT;
			m_pAIVDOData->bHeadingAvail = pAisTypeAIVDO->bHeadingAvail;
			m_pAIVDOData->HDT = pAisTypeAIVDO->HDT;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPEAIVDO18* const pAisTypeAIVDO)
	{
		if ((m_pAIVDOData != NULL) && (pAisTypeAIVDO != NULL))
		{
			m_pAIVDOData->bPosAvail = pAisTypeAIVDO->bPosAvail;
			m_pAIVDOData->Lat = pAisTypeAIVDO->Lat;
			m_pAIVDOData->Long = pAisTypeAIVDO->Long;
			m_pAIVDOData->bSogAvail = pAisTypeAIVDO->bSogAvail;
			m_pAIVDOData->SOG = pAisTypeAIVDO->SOG;
			m_pAIVDOData->bCogAvail = pAisTypeAIVDO->bCogAvail;
			m_pAIVDOData->COG = pAisTypeAIVDO->COG;
			m_pAIVDOData->bHeadingAvail = pAisTypeAIVDO->bHeadingAvail;
			m_pAIVDOData->HDT = pAisTypeAIVDO->HDT;
		}
	}

	void CAISMsgManager::CopyAISInfo(const T_AIS_MSG_TYPEAIVDO19* const pAisTypeAIVDO)
	{
		if ((m_pAIVDOData != NULL) && (pAisTypeAIVDO != NULL))
		{
			m_pAIVDOData->bPosAvail = pAisTypeAIVDO->bPosAvail;
			m_pAIVDOData->Lat = pAisTypeAIVDO->Lat;
			m_pAIVDOData->Long = pAisTypeAIVDO->Long;
			m_pAIVDOData->bSogAvail = pAisTypeAIVDO->bSogAvail;
			m_pAIVDOData->SOG = pAisTypeAIVDO->SOG;
			m_pAIVDOData->bCogAvail = pAisTypeAIVDO->bCogAvail;
			m_pAIVDOData->COG = pAisTypeAIVDO->COG;
			m_pAIVDOData->bHeadingAvail = pAisTypeAIVDO->bHeadingAvail;
			m_pAIVDOData->HDT = pAisTypeAIVDO->HDT;
		}
	}

	void CAISMsgManager::CreateMsgProcThread()
	{
		m_pAISMsgProcThread = AfxBeginThread(static_cast<AFX_THREADPROC>(AISMsgProcThread), static_cast<LPVOID>(this), THREAD_PRIORITY_ABOVE_NORMAL, 0U, static_cast<DWORD>(CREATE_SUSPENDED));
		if (m_pAISMsgProcThread != NULL)
		{
			m_pAISMsgProcThread->m_bAutoDelete = TRUE;
			static_cast<void>(m_pAISMsgProcThread->ResumeThread());
		}
	}

	void CAISMsgManager::ExitMsgProcThread()
	{
		if (m_pAISMsgProcThread != NULL)
		{
			static_cast<void>(SetEvent(m_hAISMsgProcExitEvent));

			static_cast<void>(WaitForSingleObject(m_pAISMsgProcThread->m_hThread, static_cast<DWORD>(1000U)));
			m_pAISMsgProcThread = NULL;
		}
	}

	void CAISMsgManager::AISMsgProcThread()
	{
		if (m_pSerialMsgAIS != NULL)
		{
			BYTE* pDataPtr = NULL;
			// 수신된 메시지를 한번에 세개까지 처리한다.
			for (INT nCnt = 0; nCnt < 3; nCnt++)
			{
				pDataPtr = m_pSerialMsgAIS->Pop();
				// 데이터가 존재하지 않으면 종료한다.
				if (pDataPtr == NULL)
				{
					break;
				}
				// 메시지 처리 시작이 아니면 큐에 있는 메시지를 버린다.
				if (m_bStarted == TRUE)
				{
					CString strMsg = reinterpret_cast<TCHAR*>(pDataPtr);

					if (m_pMsgParserAIS != NULL)
					{
						E_PARSING_RESULT eParsingResult = m_pMsgParserAIS->Parsing(reinterpret_cast<BYTE*>(strMsg.GetBuffer()), strMsg.GetLength());
						if ((eParsingResult >= E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1 && eParsingResult <= E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE19))
						{
							UpdateAISInfo(eParsingResult);
						}
					}
				}
			}
		}
	}

	UINT CAISMsgManager::AISMsgProcThread(LPVOID const lpParam)
	{
		CAISMsgManager* const pMsgMngr = static_cast<CAISMsgManager*>(lpParam);

		if (pMsgMngr != NULL)
		{
			INT nQuit = 0;

			DWORD dwEvent;

			while (nQuit < 1)
			{
				dwEvent = WaitForSingleObject(pMsgMngr->m_hAISMsgProcExitEvent, static_cast<DWORD>(50U)); // 50 ms 마다 동작
				switch (dwEvent)
				{
				case static_cast<DWORD>(WAIT_OBJECT_0 + 0U): // Exit Event
				{
					nQuit++;
					break;
				}
				case static_cast<DWORD>(WAIT_TIMEOUT):		// Time out
				{
					pMsgMngr->AISMsgProcThread();
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