#pragma once

#include <map>
#include <afxmt.h>

#include "DataTypeDef.h"
#include "RadarBaseDef.h"

namespace NS_SALUS_MS_APP
{
#pragma pack(push, 1)

	enum class E_AIS_DATA_TYPE
	{
		eAIS_TYPE1 = 0,
		eAIS_TYPE2 = 1,
		eAIS_TYPE3 = 2,
		eAIS_TYPE4 = 3,
		eAIS_TYPE5 = 4,
		eAIS_TYPE9 = 5,
		eAIS_TYPE18 = 6,
		eAIS_TYPE19 = 7,
		eAIS_TYPE21 = 8,
		eAIS_TYPE24 = 9,
	};

	struct T_AIS_DATA
	{
		UINT32 m_unMMSI;
		UCHAR m_ucValidStatus;				// Navigation Status valid, 0 : not valid, 1 : valid
		UCHAR m_ucNaviStatus;				// Navigation Status
											// 0 = 엔진을 사용하여 진행 중
											// 1 = 정박 상태(닻을 내림)
											// 2 = 명령을 받지 않음
											// 3 = 제한된 조정성
											// 4 = 외풍에 의한 제약
											// 5 = 정박 상태(육지 등에 계류)
											// 6 = 좌초된 상태
											// 7 = 어업(낚시 등) 중
											// 8 = 출항 중(sailing)
											// 9 ~ 13 = 향후 계정을  위해 예약된 코드
											// 14 = AIS-SART 활성화 됨
											// 15 = 정의되지 않음(기본값)
		//UCHAR m_ucValidDateTime;			// Date and Time Valid, 0 : not valid, 1 : valid
		//USHORT m_usYear;					// Year(UTC), 1-9999, 0 = N/A (default)
		//UCHAR m_ucMonth;					// Month(UTC), 1-12; 0 = N/A (default)
		//UCHAR m_ucDay;						// Day(UTC), 1-31; 0 = N/A (default)
		//UCHAR m_ucHour;						// Hour(UTC), 0-23; 24 = N/A (default)
		//UCHAR m_ucMinute;					// 0-59; 60 = N/A (default)
		//UCHAR m_ucSecond;					// 0-59; 60 = N/A (default)
		FLOAT m_cTurnRate;					// Rate of turn, 0 ~ 255, scale factor = -127
											// ROT_AIS = 4.733 * SQRT(ROT_sensor) deg/min, 0 ~ 708 deg/min
											// 0 = not turning
											// 1 ~ 126 = turning right at up to 708 degrees per minute or higher
											// -1 ~ -126 = turning left at up to 708 degrees per minute or higher
											// 127 = turning right at more than 5deg/30s
											// -127 = turning left at more than 5deg/30s
											// 128 (80 hex) indicates no turn information available (default)
		//UCHAR m_ucValidSOG;					// SOG valid, 0 : not valid, 1 : valid
		FLOAT m_fSOG;						// Speed over ground, knots, Range : 0 ~ 102.2
		//UCHAR m_ucValidPosition;			// Lat/Lon valid, 0 : not valid, 1 : valid
		UCHAR m_ucAccuracy;					// Position accuracy, 0 ~ 1
											// 0 = accuracy > 10m (default)
											// 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude
		DOUBLE m_dLat;						// latitude
		//UCHAR m_ucValidCOG;					// COG valid, 0 : not valid, 1 : valid
		FLOAT m_fCOG;						// Course over ground, Range : 0 ~ 360.0
		//UCHAR m_ucValidHeading;				// Heading valid, 0 : not valid, 1 : valid
		USHORT m_usHeading;					// Heading, 0 to 359 degrees, 511 = not available.
		UCHAR m_ucTimeStamp;				// Time Stamp, Second of UTC timestamp, 0 ~ 59
											//		60 if time stamp is not available (default)
											//		61 if positioning system is in manual input mode
											//		62 if Electronic Position Fixing System operates in estimated(dead reckoning) mode,
											//		63 if the positioning system is inoperative.
		UCHAR m_ucManeuver;					// Maneuver Indicator 0 ~ 2
											//		0 = Not available(default)
											//		1 = No special maneuver
											//		2 = Special maneuver(such as regional passing arrangement)
		UINT32 m_unIMO;						// IMO ship ID number
		TCHAR m_szCallSign[8];				// 7 six - bit characters
		TCHAR m_szShipName[21];				// Vessel Name, 20 six - bit characters
		UCHAR m_ucShipType;					// Ship Type
											//		0 = Not available(default)
											//		1 ~ 19  = Reserved for future use
											//		20 = Wing in ground(WIG), all ships of this type
											//		21 ~ 24 = Wing in ground(WIG), Hazardous category A ~ D
											//		25 ~ 29 = Wing in ground(WIG), Reserved for future use
											//		30 = Fishing
											//		31 = Towing
											//		32 = Towing: length exceeds 200m or breadth exceeds 25m
											//		33 = Dredging or underwater ops
											//		34 = Diving ops
											//		35 = Military ops
											//		36 = Sailing
											//		37 = Pleasure Craft
											//		38 ~ 39 = Reserved
											//		40 = High speed craft(HSC), all ships of this type
											//		41 ~ 44 = High speed craft(HSC), Hazardous category A ~ D
											//		45 ~ 48 = High speed craft(HSC), Reserved for future use
											//		49 = High speed craft(HSC), No additional information
											//		50 = Pilot Vessel
											//		51 = Search and Rescue vessel
											//		52 = Tug
											//		53 = Port Tender
											//		54 = Anti - pollution equipment
											//		55 = Law Enforcement
											//		56 ~ 57 = Spare - Local Vessel
											//		58 = Medical Transport
											//		59 = Noncombatant ship according to RR Resolution No. 18
											//		60 = Passenger, all ships of this type
											//		61 ~ 64 = Passenger, Hazardous category A ~ D
											//		65 ~ 68 = Passenger, Reserved for future use
											//		69 = Passenger, No additional information
											//		70 = Cargo, all ships of this type
											//		71 ~ 74 = Cargo, Hazardous category A ~ D
											//		75 ~ 78 = Cargo, Reserved for future use
											//		79 = Cargo, No additional information
											//		80 = Tanker, all ships of this type
											//		81 ~ 84 = Tanker, Hazardous category A ~ D
											//		85 ~ 88 = Tanker, Reserved for future use
											//		89 = Tanker, No additional information
											//		90 = Other Type, all ships of this type
											//		91 ~ 94 = Other Type, Hazardous category A ~ D
											//		95 ~ 98 = Other Type, Reserved for future use
											//		99 = Other Type, no additional information
		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
		bool m_blRotNA;
		bool m_blHeadingNA;
		bool m_blSOGNA;
		bool m_blCOGNA;

		bool m_blIsSartMsg;

		USHORT	m_usBow;					// Length Toward Ship's Bow from CCRP in meters
		USHORT	m_usStern;					// Length Toward Ship's Stern from CCRP in meters
		USHORT	m_usPort;					// Length Toward Ship's Left Direction from CCRP in meters
		USHORT	m_usStarBoard;				// Length Toward Ship's Right Direction from CCRP in meters
		UCHAR   m_ucETA[4];
		UCHAR m_ucDst[20];
		FLOAT m_fDraught;
		UCHAR m_ucEPFD;

		TCHAR m_szDestination[21];			// Destination, 20 6bit characters
	};

	struct T_AIVDO_AIS {
		bool bPosAvail;			// Availability of Position Data
		DOUBLE Lat;				// Latitude
		DOUBLE Long;			// Longitude
		bool bSogAvail;			// Availability of SOG Data
		FLOAT SOG;			// Speed over Ground (m/s)
		bool bCogAvail;			// Availability of COG Data
		FLOAT COG;			// Course over Ground (degree)
		bool bRotAvail;			// Availability of ROT
		FLOAT ROT;			// Rotation Rate(deg/min)
		bool bHeadingAvail;		// Availability of True Heading
		FLOAT HDT;			// True Heading
	};

#pragma pack(pop)

	class AFX_EXT_CLASS CAISDataMngr
	{
	public:
		CAISDataMngr();
		virtual ~CAISDataMngr();

	public:
		static CAISDataMngr* GetInstance();
		static void DeleteInstance();

		void Initialize();
		void Finalize();

		// Set
		void UpdateData(const E_AIS_DATA_TYPE eAisDataType, const T_AIS_DATA* const pAISData);
		void UpdateAIVDOUpdate(T_AIVDO_AIS* tAIVDOAIS);
		void FindCallSign(UINT MMSI, CHAR* szCallSign);

		// Get
		UINT GetCount();
		T_AIS_DATA* GetAISDataWithKeyValue(UINT unMMSI);
		T_AIS_DATA* GetAISDatWithIndex(UINT unIndex);

		void DeleteData(UINT unMMSI);
		void RemoveAll();

	protected:
		void AllocMemory();
		void FreeMemory();

		BOOL IsExistData(const UINT unMMSI, UINT& unBuffIndex);
		void RemoveMapData();

		void CopyAISData(const E_AIS_DATA_TYPE eAISDataType, const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);

		void CopyAISType1_3(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType4(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType5(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType9(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType18(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType19(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType21(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);
		void CopyAISType24(const T_AIS_DATA* const pSrcData, T_AIS_DATA* const pDstData);

	private:
		void LockData();
		void UnlockData();

	private:
		static CAISDataMngr* m_pInstance;
		static const UINT m_unMAX_AIS_DATA_BUFF = g_unMAX_ALLOW_TRACK_NUM;

		T_AIS_DATA* m_pAISDataBuffer;
		UINT m_unWriteBuffIndex;

		std::map<UINT, UINT> m_mapAISData;	// MMSI를 키값으로 버퍼 인덱스를 포함한다.
		CCriticalSection* m_pDataCS;
	};

} // NS_SALUS_MS_APP

