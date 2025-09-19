#pragma once

#include "DataTypeDef.h"
#include <tchar.h>

namespace NS_SALUS_MS_APP
{
#pragma pack(push, 1)

	// TYpe 1 ~ 3 : Class A Position Report
	struct T_AIS_MSG_TYPE1_3
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9자리 십진수
		UCHAR m_ucStatus;					// Navigation Status
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
		FLOAT m_fROT;
		FLOAT m_cTurnRate;					// Rate of turn, 0 ~ 255, scale factor = -127
											// ROT_AIS = 4.733 * SQRT(ROT_sensor) deg/min, 0 ~ 708 deg/min
											// 0 = not turning
											// 1 ~ 126 = turning right at up to 708 degrees per minute or higher
											// -1 ~ -126 = turning left at up to 708 degrees per minute or higher
											// 127 = turning right at more than 5deg/30s
											// -127 = turning left at more than 5deg/30s
											// 128 (80 hex) indicates no turn information available (default)
		FLOAT m_fSOG;						// Speed over ground, knots, Range : 0 ~ 1022, Scale Factor : 1/10
		UCHAR m_ucAccuracy;					// Position accuracy, 0 ~ 1
											// 0 = accuracy > 10m (default)
											// 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude, Minutes/10000, 1/600000.0 degrees
		DOUBLE m_dLat;						// latitude, Minutes/10000, 1/600000.0 degrees
		FLOAT m_fCOG;						// Course over ground, Range : 0 ~ 3600, Scale Factor : 1/10
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
		UCHAR m_ucRAIM;						// RAIM 0 = RAIM not in use (default), 1 = RAIM in use
		UINT32 m_unRadioStatus;				// Radio Status
		UINT32 m_unCounter;
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
	};

	// TYPE 4 : Base Station Report
	struct T_AIS_MSG_TYPE4
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 decimal digits
		USHORT m_usYear;					// Year(UTC), 1-9999, 0 = N/A (default)
		UCHAR m_ucMonth;					// Month(UTC), 1-12; 0 = N/A (default)
		UCHAR m_ucDay;						// Day(UTC), 1-31; 0 = N/A (default)
		UCHAR m_ucHour;						// Hour(UTC), 0-23; 24 = N/A (default)
		UCHAR m_ucMinute;					// 0-59; 60 = N/A (default)
		UCHAR m_ucSecond;					// 0-59; 60 = N/A (default)
		UCHAR m_ucQuality;					// Position accuracy, 0 ~1
											// 0 = accuracy > 10m (default)
											// 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude, Minutes/10000, 1/600000.0 degrees
		DOUBLE m_dLat;						// latitude, Minutes/10000, 1/600000.0 degrees
		UCHAR m_ucEPFD;						// EPFD Fix Type
											//	0 = Undefined(default)
											//	1 = GPS
											//	2 = GLONASS
											//	3 = Combined GPS / GLONASS
											//	4 = Loran - C
											//	5 = Chayka
											//	6 = Integrated navigation system
											//	7 = Surveyed
											//	8 = Galileo
		UCHAR m_ucRAIM;
		UINT32 m_unRadioStatus;
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
	};

	// type 5 : Static and Voyage Related Data
	struct T_AIS_MSG_TYPE5
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 digits
		UCHAR m_ucVersion;					// AIS Version, 0 = [ITU1371], 1 - 3 = future editions
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
		USHORT m_usBowDimension;			// Dimension to Bow, Meters
		USHORT m_usSternDimension;			// Dimension to Stern, Meters
		UCHAR m_ucPortDimension;			// Dimension to Port, Meters
		UCHAR m_ucStarboardDimension;		// Dimension to Starboard, Meters
		UCHAR m_ucEPFD;						// Position Fix Type, epfd
		UCHAR m_ucMonth;					// ETA month(UTC), 1 - 12, 0 = N / A(default)
		UCHAR m_ucDay;						// ETA day(UTC), 1 - 31, 0 = N / A(default)
		UCHAR m_ucHour;						// ETA hour(UTC), 0 - 23, 24 = N / A(default)
		UCHAR m_ucMinute;					// ETA minute(UTC), 0 - 59, 60 = N / A(default)
		FLOAT m_fDraught;					// Draught, Meters / 10
		TCHAR m_szDestination[21];			// Destination, 20 6bit characters
		UCHAR m_ucDTE;						// DTE, 0 = Data terminal ready, 1 = Not ready(default).
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;
	};

	// type 9 : Standard SAR Aircraft Position Report, 168 bits(include 8 bits head)
	struct T_AIS_MSG_TYPE9
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 decimal digits
		USHORT m_usAltitude;				// Altitude, Range 0 ~ 4094, Meter
		FLOAT m_fSOG;						// speed, Range : 0 ~ 1022, Scale Fector : 1/10
		UCHAR m_ucAccuracy;					// Position Accuracy
											// 0 = accuracy > 10m (default), 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude, Minutes / 10000
		DOUBLE m_dLat;						// Latitude, Minutes / 10000
		FLOAT m_fCOG;						// Course Over Ground, True bearing, 0.1 degree units
		UCHAR m_ucTimeStamp;				// Time Stamp, UTC second.
		UCHAR m_ucDTE;						// DTE, 0 = Data terminal ready, 1 = Data terminal not ready(default)
		UCHAR m_ucAssigned;					// Assigned, mode flag
		UCHAR m_ucRAIM;						// RAIM flag, As for common navigation block
		UINT32 m_unRadioStatus;				// Radio Status
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
		bool m_blSOGNA;
		bool m_blCOGNA;
	};

	// type 14 : Safety-Related Broadcast Message
	struct T_AIS_MSG_TYPE14
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											
		UINT32 m_unMMSI;					// 9 decimal digits
		UCHAR m_ucSpare;                    // 2 bits   : Spare (not used)
		TCHAR m_szMessage[164];			    // 968 bits : Message in ASCII

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;
	};

	// Type 18 : Standard Class B CS Position Report, total 158 bits
	struct T_AIS_MSG_TYPE18
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// MMSI, 9 decimal digits
		UCHAR m_ucRegionalReserved1;
		FLOAT m_fSOG;						// Speed Over Ground, Range : 0 ~ 1022, Scale Fector : 1/10
		UCHAR m_ucAccuracy;					// Position Accuracy
											// 0 = accuracy > 10m (default), 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude
		DOUBLE m_dLat;						// Latitude
		FLOAT m_fCOG;						// Course Over Ground, True bearing, 0.1 degree units
		USHORT m_usHeading;					// True Heading, 0 to 359 degrees, 511 = N / A
		UCHAR m_ucTimeStamp;				// Time Stamp, Second of UTC timestamp.
		UCHAR m_ucRegionalReserved2;
		UCHAR m_ucClassUnit;				// CS Unit, 0 = Class B SOTDMA unit 1 = Class B CS(Carrier Sense) unit
		UCHAR m_ucDisplay;					// Display flag, 0 = No visual display, 1 = Has display, (Probably not reliable).
		UCHAR m_ucDSC;						// DSC Flag, If 1, unit is attached to a VHF voice radio with DSC capability.
		UCHAR m_ucBand;						// Band flag, Base stations can command units to switch frequency.If this flag is 1, the unit can use any part of the marine channel.
		UCHAR m_ucMsg22;					// Message 22 flag, If 1, unit can accept a channel assignment via Message Type 22.
		UCHAR m_ucAssigned;					// Assigned, Assigned - mode flag : 0 = autonomous mode(default), 1 = assigned mode.
		UCHAR m_ucRAIM;						// RAIM flag, As for common navigation block
		UINT32 m_unRadioStatus;				// Radio Status
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
		bool m_blHeadingNA;
		bool m_blSOGNA;
		bool m_blCOGNA;
	};	// 1 * 11 + 2 * 1 + 4 * 3 + 8 * 2 = 41 bytes

	// Type 19 : Extened Class B CS Position Report, total 312 bits
	struct T_AIS_MSG_TYPE19
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 digits
		FLOAT m_fSOG;						// Speed Over Ground, Range : 0 ~ 1022, Scale Fector : 1/10
		UCHAR m_ucAccuracy;					// Position Accuracy
											// 0 = accuracy > 10m (default), 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude, Minutes / 10000
		DOUBLE m_dLat;						// Latitude, Minutes / 10000
		FLOAT m_fCOG;						// Course Over Ground, True bearing, 0.1 degree units
		USHORT m_usHeading;					// True Heading, 0 to 359 degrees, 511 = N / A
		UCHAR m_ucTimeStamp;				// Time Stamp, Second of UTC timestamp.
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
		USHORT m_usBowDimension;			// Dimension to Bow, Meters
		USHORT m_usSternDimension;			// Dimension to Stern, Meters
		UCHAR m_ucPortDimension;			// Dimension to Port, Meters
		UCHAR m_ucStarboardDimension;		// Dimension to Starboard, Meters
		UCHAR m_ucEPFD;						// Position Fix Type, epfd
		UCHAR m_ucRAIM;						// RAIM flag, As for common navigation block
		UCHAR m_ucDTE;						// DTE, 0 = Data terminal ready, 1 = Not ready(default).
		UCHAR m_ucAssigned;					// Assigned, mode flag
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
		bool m_blHeadingNA;
		bool m_blSOGNA;
		bool m_blCOGNA;
	};

	// Type 21 : Aid-to-Navigation Report
	struct T_AIS_MSG_TYPE21
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 digits
		UCHAR m_ucAidType;					// Aid Type
											//		0	Default, Type of Aid to Navigation not specified
											//		1	Reference point
											//		2	RACON(radar transponder marking a navigation hazard)
											//		3	Fixed structure off shore, such as oil platforms, wind farms, rigs. (Note: This code should identify an obstruction that is fitted with an Aid - to - Navigation AIS station.)
											//		4	Spare, Reserved for future use.
											//		5	Light, without sectors
											//		6	Light, with sectors
											//		7	Leading Light Front
											//		8	Leading Light Rear
											//		9	Beacon, Cardinal N
											//		10	Beacon, Cardinal E
											//		11	Beacon, Cardinal S
											//		12	Beacon, Cardinal W
											//		13	Beacon, Port hand
											//		14	Beacon, Starboard hand
											//		15	Beacon, Preferred Channel port hand
											//		16	Beacon, Preferred Channel starboard hand
											//		17	Beacon, Isolated danger
											//		18	Beacon, Safe water
											//		19	Beacon, Special mark
											//		20	Cardinal Mark N
											//		21	Cardinal Mark E
											//		22	Cardinal Mark S
											//		23	Cardinal Mark W
											//		24	Port hand Mark
											//		25	Starboard hand Mark
											//		26	Preferred Channel Port hand
											//		27	Preferred Channel Starboard hand
											//		28	Isolated danger
											//		29	Safe Water
											//		30	Special Mark
											//		31	Light Vessel / LANBY / Rigs
		TCHAR m_szName[21];					// Name, 20 six - bit characters
		UCHAR m_ucAccuracy;					// Position Accuracy
											// 0 = accuracy > 10m (default), 1 = accuracy < 10m
		DOUBLE m_dLon;						// Longitude, Minutes / 10000
		DOUBLE m_dLat;						// Latitude, Minutes / 10000
		USHORT m_usBowDimension;			// Dimension to Bow, Meters
		USHORT m_usSternDimension;			// Dimension to Stern, Meters
		UCHAR m_ucPortDimension;			// Dimension to Port, Meters
		UCHAR m_ucStarboardDimension;		// Dimension to Starboard, Meters
		UCHAR m_ucEPFD;						// Position Fix Type, epfd
		UCHAR m_ucSecond;					// UTC Second
		UCHAR m_ucOffPosition;				// Off-Position Indicator, 0 means on position; 1 means off position
		UCHAR m_ucRegionalReserved;			// Regional reserved
		UCHAR m_ucRAIM;						// RAIM flag, As for common navigation block
		UCHAR m_ucVirtualAID;				// Virtual-aid flag, 
											//	0(default) = real Aid to Navigation at indicated position; 1 = virtual Aid to Navigation simulated by nearby AIS station.
		UCHAR m_ucAssigned;					// Assigned, mode flag
		TCHAR m_szNameEx[15];				// Name Extension
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		bool m_blPositionNA;
	};

	// Type 24 : Static Data Report, total 168 bits
	struct T_AIS_MSG_TYPE24_PART_A
	{
		TCHAR m_szShipName[21];				// (Part A) Vessel Name, 20 six - bit characters
	};

	struct T_AIS_MSG_TYPE24_PART_B1
	{
		UCHAR m_ucShipType;					// (Part B) Ship Type
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
		TCHAR m_szVendorID[8];				// (Part B) Vendor ID, 3 six - bit chars
		TCHAR m_szCallSign[8];				// (Part B) Call Sign
		USHORT m_usBowDimension;			// (Part B) Dimension to Bow, Meters
		USHORT m_usSternDimension;			// (Part B) Dimension to Stern, Meters
		UCHAR m_ucPortDimension;			// (Part B) Dimension to Port, Meters
		UCHAR m_ucStarboardDimension;		// (Part B) Dimension to Starboard, Meters
	};

	struct T_AIS_MSG_TYPE24_PART_B2
	{
		UCHAR m_ucShipType;					// (Part B) Ship Type
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
		TCHAR m_szVendorID[4];				// (Part B) Vendor ID, 3 six - bit chars
		UCHAR m_ucModelCode;				// (Part B) Unit Model Code	model
		UINT32 m_unSerialNumber;			// (Part B)
		TCHAR m_szCallSign[8];				// (Part B) Call Sign
		UINT32 m_unMotherMMSI;				// (Part B) Mothership MMSI
	};

	struct T_AIS_MSG_TYPE24
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;					// meassage repeat cont
											// 0 = 기본값, 3 = 반복하지 않음
		UINT32 m_unMMSI;					// 9 digits
		UCHAR m_ucPartNumber;				// Part Number, 0 = Part A, 1 = Part B
		
		T_AIS_MSG_TYPE24_PART_A m_tPartA;
		T_AIS_MSG_TYPE24_PART_B1 m_tPartB1;
		T_AIS_MSG_TYPE24_PART_B2 m_tPartB2;
		
	
		UINT32 m_unCounter;

		UCHAR m_ucClassType;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;
	};

	struct T_AIS_MSG_TYPESART
	{
		UCHAR m_ucType;
		UCHAR m_ucRepeat;
		UCHAR m_ucAccuracy;

		UINT32 m_unMMSI;
		UCHAR m_ucStatus;

		DOUBLE m_dLon;
		DOUBLE m_dLat;

		UINT m_uRcvYear;
		UINT m_uRcvMonth;
		UINT m_uRcvDay;
		UINT m_uRcvHour;
		UINT m_uRcvMinute;
		UINT m_uRcvSecond;

		UCHAR m_ucClassType;
		bool m_blPositionNA;
	};

	struct T_AIS_MSG_TYPEAIVDO1 {
		bool bPosAvail;		
		DOUBLE Lat;			
		DOUBLE Long;		
		bool bSogAvail;		
		FLOAT SOG;			
		bool bCogAvail;		
		FLOAT COG;			
		bool bRotAvail;		
		FLOAT ROT;			
		bool bHeadingAvail;	
		FLOAT HDT;			
	};

	struct T_AIS_MSG_TYPEAIVDO18 {
		bool bPosAvail;			// Availability of Position Data
		DOUBLE Lat;				// Latitude
		DOUBLE Long;			// Longitude
		bool bSogAvail;			// Availability of SOG Data
		FLOAT SOG;			// Speed over Ground (m/s)
		bool bCogAvail;			// Availability of COG Data
		FLOAT COG;			// Course over Ground (degree)
		bool bHeadingAvail;		// Availability of True Heading
		FLOAT HDT;			// True Heading
	};

	struct T_AIS_MSG_TYPEAIVDO19 {
		bool bPosAvail;			// Availability of Position Data
		DOUBLE Lat;				// Latitude
		DOUBLE Long;			// Longitude
		bool bSogAvail;			// Availability of SOG Data
		FLOAT SOG;			// Speed over Ground (m/s)
		bool bCogAvail;			// Availability of COG Data
		FLOAT COG;			// Course over Ground (degree)
		bool bHeadingAvail;		// Availability of True Heading
		FLOAT HDT;			// True Heading
	};

#pragma pack(pop)
} // NS_SALUS_MS_APP