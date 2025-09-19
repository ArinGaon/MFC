#pragma once

#include "DataTypeDef.h"

namespace NS_SALUS_MS_APP
{
#pragma pack(push, 1)

	static const WORD g_wMAX_SATELLITE_NUM = 12U;

	///////////////////////////////////////////////////////////////////////////////
	//
	// __AAM - Waypoint Arrival Alarm
	//                                                       11
	//              1 2 3 4 5 6
	//              | | | | | |
	//      $--AAM, A, A, x.x, N, c--c* hh
	// Field Number: 
	//  1) Status, BOOLEAN, A = Arrival circle entered, V = No
	//  2) Status, BOOLEAN, A = perpendicular passed at waypoint, V = No
	//  3) Arrival circle radius
	//  4) Units of radius, nautical miles
	//  5) Waypoint ID
	//  6) Checksum
	//  7) Terminator : CR/LF
	struct T_NMEA_AAM
	{
		BOOL m_bEnteredCircle;  // TRUE = Arrival circle entered
		BOOL m_bPassedWaypoint;	// TRUE = perpendicular passed at waypoint
		FLOAT m_fRadius;		// nautical miles(NM)
		TCHAR m_szID[16];
	};



	///////////////////////////////////////////////////////////////////////////////
	//
	// __GGA - Global Positioning System Fixed Data
	//                                                       11
	//       1     2         3       4 5       6 7 8  9  10   | 12 13 14  15
	//		 |     |         |       | |       | | |  |   |   | |   | |   |
	//   	$__GGA,hhmmss.ss,ddmm.mm,a,ddmm.mm,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
	// 
	//     ex) $GNGGA,001043.00,4404.14036,N,12118.85961,W,1,12,0.98,1113.0,M,-21.3,M*47
	// Field Number:
	//  1) Sentensce ID : $GPGGA
	//  2) UTC TIME : hhmmss.sss, 092204.999, Universal Time Coordinated 
	//  3) Latitude : ddmm.mmmm, 5250.5589
	//  4) N/S Indicator : 'N' or 'S' (North or South)
	//  5) Longitude : dddmm.mmmm, 12723.3334
	//  6) E/W Indicator : 'E' or 'W' (East or West)
	//  7) Position Fix :
	//     0 - invalid, 1 - GPS fix, 2 - Differential GPS fix(values above 2 are 2.3 features), 
	//     3 = PPS fix, 4 = Real Time Kinematic, 5 = Float RTK, 6 = estimated(dead reckoning),
	//     7 = Manual input mode, 8 = Simulation mode
	//  8) Number of satellites in view : 0 - 12
	//  9) Horizontal Dilution of precision : 24.4
	// 10) Antenna Altitude above/below mean-sea-level (geoid) : 19.2
	// 11) Units of antenna altitude, meters : 'M'
	// 12) Geoidal separation, the difference between the WGS-84 earth
	//     ellipsoid and mean-sea-level (geoid), "-" means mean-sea-level
	//     below ellipsoid
	// 13) Units of geoidal separation, meters : 'M'
	// 14) Age of differential GPS data, time in seconds since last SC104
	//     type 1 or 9 update, null field when DGPS is not used
	// 15) Differential reference station ID, 0000-1023
	// 16) Checksum : *FF
	// 17) Terminator : CR/LF
	struct T_NMEA_GGA
	{
		WORD m_wHour;
		WORD m_wMinute;
		DOUBLE m_dSecond;
		SHORT m_sLatDegree;			// < 0 = South, > 0 = North
		DOUBLE m_dLatMinute;
		SHORT m_sLonDegree;			// < 0 = West, > 0 = East
		DOUBLE m_dLonMinute;
		WORD m_wGPSQuality;			// 0 = fix not available, 1 = GPS sps mode, 2 = Differential GPS, SPS mode, fix valid, 3 = GPS PPS mode, fix valid
		WORD m_wNumOfSatsInUse;
		DOUBLE m_dHDOP;
		DOUBLE m_dAltitude;			// altitude : mean-sea-level (gooid) meters
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __GLL - Geographic position - latitude / longitude
	// 
	//               1        2  3         4  5          6  7  8
	//               |        |  |         |  |          |  |  |
	// 	     $--GLL, ddmm.mm, a, dddmm.mm, a, hhmmss.ss, a   * hh<CR><LF>
	//	NMEA 2.3:
	//       $--GLL, ddmm.mm, a, dddmm.mm, a, hhmmss.ss, a, m* hh<CR><LF>
	//     ex) $GNGLL,4404.14012,N,12118.85993,W,001037.00,A,A*67
	// Field Number:
	//  1) Latitude : ddmm.mmmm, 4250.5589
	//  2) N/S Indicator : 'N' or 'S'
	//  3) Logitude : dddmm.mmmm, 14718.5094
	//  4) E/W Indicator : 'E' or 'W'
	//  5) UTC Time : hhmmss.sss, 092204.999
	//  6) Status : 'A' or 'V', A = Valid, V = Invalid
	//  7) FAA mode indicator (NMEA 2.3 and later)
	//  8) Checksum : *FF
	//  9) Terminator : CR/LF
	struct T_NMEA_GLL
	{
		SHORT m_sLatDegree;
		DOUBLE m_dLatMinute;
		SHORT m_sLonDegree;
		DOUBLE m_dLonMinute;
		WORD m_wHour;
		WORD m_wMinute;
		DOUBLE m_dSecond;
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __GSA - GNSS DOP and active satellites
	// 
	//                 1 2 3                                          14 15  16  17  18
	//                 | | |                                           |  |   |   |   |
	//         $--GSA, a, a, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x.x, x.x, x.x* hh<CR><LF>
	//         ex) $GNGSA,A,3,80,71,73,79,69,,,,,,,,1.83,1.09,1.47*17
	// Field Number:
	//  1) Selection Mode : A, A = Auto 2D/3D
	//  2) Mode2 : 3, 1 = No Fix, 2 = 2D, 3= 3D
	//  3) Satellite used 1 : 1, Salellite used on channel 1
	//  4) Satellite used 2 : 20, Salellite used on channel 2
	//  5) Satellite used 3 : 19, Salellite used on channel 3
	//  6) Satellite used 4 : 22, Salellite used on channel 4
	//  7) Satellite used 5 :     Salellite used on channel 5
	//  8) Satellite used 6 :     Salellite used on channel 6
	//  9) Satellite used 7 :     Salellite used on channel 7
	// 10) Satellite used 8 :     Salellite used on channel 8
	// 11) Satellite used 9 :     Salellite used on channel 9
	// 12) Satellite used 10 :     Salellite used on channel 10
	// 13) Satellite used 11 :     Salellite used on channel 11
	// 14) Satellite used 12 :     Salellite used on channel 12
	// 15) PDOP : 40.4, Position dilution of precision
	// 16) HDOP : 24.4, Horizontal dilution of precision
	// 17) VDOP : 32.2 Vertical dilution of precision
	// 18) Checksum : *FF
	// 19) Terminator : CR/LF
	struct T_NMEA_GSA
	{
		TCHAR m_cMode;				// M = manual, A = automatic 2D/3D
		TCHAR m_cReserve;
		BYTE m_byFixMode;			// 1 = fix not available, 2 = 2D, 3 = 3D
		WORD m_wSatsInSolution[g_wMAX_SATELLITE_NUM];	// ID of sats in solution
		DOUBLE m_dPDOP;
		DOUBLE m_dHDOP;
		DOUBLE m_dVDOP;
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __GSV - GNSS satellites in view
	// 
	//              1 2 3 4 5 6 7     n
	//	            | | | | | | |     |
	//	    $--GSV, x, x, x, x, x, x, x, ...*hh<CR><LF>
	//         ex) $GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74 
	//             $GPGSV,3,2,11,14,25,170,00,16,57,208,39,18,67,296,40,19,40,246,00*74 
	//             $GPGSV,3,3,11,22,42,067,42,24,14,311,43,27,05,244,00,,,,*4D
	// Field Number:
	//  1) total number of GSV sentences to be transmitted in this group
	//  2) Sentence number, 1 - 9 of this GSV message within current group
	//  3) total number of satellites in view(leading zeros sent)
	//  4) satellite ID or PRN number(leading zeros sent)
	//  5) elevation in degrees(-90 to 90) (leading zeros sent)
	//  6) azimuth in degrees to true north(000 to 359) (leading zeros sent)
	//  7) SNR in dB(00 - 99) (leading zeros sent)
	//    more satellite info quadruples like 4 - 7 n - 1) Signal ID(NMEA 4.11) n) checksum
	//   ) Checksum : *FF
	//   ) Terminator : CR/LF
	struct T_NMEA_SAT_INFO
	{
		WORD m_wID;
		SHORT m_sElevation;	// in degree, -90 ~ 90
		WORD m_wAzimuth;		// in degree, 0 ~ 359
		WORD m_wSNR;			// in dB, 0 ~ 99
	};

	struct T_NMEA_GSV
	{
		WORD m_wNumSatellite;		// total satellite info
		WORD m_wReverved;
		T_NMEA_SAT_INFO m_tSatInfo[g_wMAX_SATELLITE_NUM]; // satellite info
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __HDG - Heading, Deviation & Variation
	//              1 2 3 4 5 6
	//              | | | | | |
	//      $--HDG, x.x, x.x, a, x.x, a* hh
	// Field Number:
	//  1) Magnetic Sensor heading in degrees
	//  2) Magnetic Deviation, degrees
	//  3) Magnetic Deviation direction, E = Easterly, W = Westerly
	//  4) Magnetic Variation degrees
	//  5) Magnetic Variation direction, E = Easterly, W = Westerly
	//  6) Checksum
	//  7) Terminator : CR/LF
	//  $NXHDG,250.6,1.4,W,2.0,W*59
	struct T_NMEA_HDG
	{
		FLOAT fHeading;		// degree
		FLOAT fDeviation;	// degree, < 0.0 : westerly
		TCHAR m_ucDevitationDir;
		FLOAT fVariation;	// degree, < 0.0 : westerly
		TCHAR m_ucVariationDir;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __HDT - True Heading
	//              1    2  3
	//              |    |  |
	//      $--HDT, x.x, T* hh
	// Field Number:
	//  1) Heading Degrees, true
	//  2) T = True
	//  3) Checksum
	//  4) Terminator : CR/LF
	struct T_NMEA_HDT
	{
		FLOAT fHeading;		// degree
		UINT m_unTimeTag;
	};


	///////////////////////////////////////////////////////////////////////////////
	//
	// __MHU - Relative Humidity
	//    $__MHU,x.x,,x.x,a,*hh<CR><LF>
	//   ex) $WIMHU,100.0,,-40.0,C*CS
	// 
	// Field Number:
	//  1) Relative Humidity : 0.0 ~ 100.0
	//  2) Dew Point Temperature : -40.0 ~ 70.0
	//  3) Unit : C = ℃
	//  4) Checksum : *FF
	//  5) Terminator : CR/LF
	struct T_NMEA_MHU
	{
		DOUBLE m_dHumidity;		// 0.0 ~ 100.0 %
		DOUBLE m_dTemperature;	// -40.0 ~ 70.0 ℃
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __MMB - Barometric Pressure
	//    $__MMB,,,x.x,a,*hh<CR><LF>
	//   ex) $WIMMB,,,1050.0,B*CS
	// 
	// Field Number:
	//  1) Barometric Pressure : 600.0 ~ 1100.0
	//  2) Unit : B = Aire pressure in hPa
	//  3) Checksum : *FF
	//  4) Terminator : CR/LF
	struct T_NMEA_MMB
	{
		DOUBLE m_dAirPressure; //600.0 ~ 1100.0 hPa
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __MTA - Air Temperature
	//    $__MTA,x.x,a,*hh<CR><LF>
	//   ex) $WIMTA,-25.0,C*CS
	// 
	// Field Number:
	//  1) Temperature : -40 ~ 70.0
	//  2) Unit : C = ℃ 
	//  3) Checksum : *FF
	//  4) Terminator : CR/LF
	struct T_NMEA_MTA
	{
		DOUBLE m_dTemperature;  // -40 ~ 70 degree
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __MWV - Wind Speed and Angle
	//    $__MWV,x.x,a,x.x,a,A*hh<CR><LF>
	//   ex) $WIMWV,357.0,R,5.2,M,A*CS
	// 
	// Field Number:
	//  1) Wind Angle, 0 ~ 3559 degrees
	//  2) Reference, R = Relative, T = True
	//  3) Wind Speed
	//  4) Wind Speed Units, K/M/N, K = Knots, 
	//  5) Data Valid : 'A' or 'V', A = Data Valid, V = Invalid
	//  6) Checksum : *FF
	//  7) Terminator : CR/LF

	// REF
	//	  x = AWS * sin(AWA * 3.14159265 / 180)
	//    y = (x / tan(AWA * 3.14159265 / 180)) - SOG
	//	  TWS(True Wind Speed) = x / sin(TWA * 3.14159265 / 180)
	//	  TWA(True Wind Angle) = atan(x / y) * 180 / 3.14159265
	struct T_NMEA_MWV
	{
		DOUBLE m_dWindAngle;		// degree
		TCHAR m_cReference;
		DOUBLE m_dWindSpeed;
		TCHAR m_cSpeedUnit;
		WORD m_wReserved;
		UINT m_unTimeTag;
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __RMC - Recommended Minimum Navigation Information
	// 
	//                 1          2  3        4  5         6  7    8    9   10    11
	// 	               |          |  |        |  |         |  |    |    |    |     |
	// 	       $--RMC, hhmmss.ss, A, ddmm.mm, a, dddmm.mm, a, x.x, x.x, xxxx, x.x, a* hh<CR><LF>
	// 	NMEA 2.3:
	//         $--RMC, hhmmss.ss, A, ddmm.mm, a, dddmm.mm, a, x.x, x.x, xxxx, x.x, a, m* hh<CR><LF>
	// 	NMEA 4.1 :
	//         $--RMC, hhmmss.ss, A, ddmm.mm, a, dddmm.mm, a, x.x, x.x, xxxx, x.x, a, m, s* hh<CR><LF>
	//         ex) $GNRMC,001031.00,A,4404.13993,N,12118.86023,W,0.146,,100117,,,A*7B
	//             $GPRMC,004952,A,3723.8259,N,12655.3071,E,000.0,088.7,291107,,,A*72
	// Field Number:
	//  1) UTC of position fix, hh is hours, mm is minutes, ss.ss is seconds.
	//  2) Status, A = Valid, V = Warning
	//  3) Latitude, dd is degrees.mm.mm is minutes.
	//  4) N or S
	//  5) Longitude, ddd is degrees.mm.mm is minutes.
	//  6) E or W
	//  7) Speed over ground, knots
	//  8) Track made good, degrees true
	//  9) Date, ddmmyy
	// 10) Magnetic Variation, degrees
	// 11) E or W
	// 12) FAA mode indicator(NMEA 2.3 and later)
	// 13) Nav Status(NMEA 4.1 and later) A = autonomous, D = differential, E = Estimated, M = Manual input mode N = not valid, S = Simulator, V = Valid
	// 14) Checksum
	// 19) Terminator : CR/LF
	struct T_NMEA_RMC
	{
		WORD m_wYear;
		WORD m_wMonth;
		WORD m_wDay;
		WORD m_wHour;
		WORD m_wMinute;
		DOUBLE m_dSecond;
		WORD m_wReserved;
		SHORT m_sLatDegree;		// -90 ~ 90
		DOUBLE m_dLatMinute;	// 0 ~ 60.0
		SHORT m_sLonDegree;		// -180 ~ 180
		DOUBLE m_dLonMinute;	// 0 ~ 60.0
		DOUBLE m_dSpeed;		// knots
		DOUBLE m_dTrackTrue;	// Track Made good, degrees true
		DOUBLE m_dMagVariation;	// Magnetic Variation, degrees
		CHAR m_cMagDir;			// Magnetic Variation Direction, E/W
		CHAR m_cReserved;
		UINT m_unTimeTag;		// time tag
	};

	///////////////////////////////////////////////////////////////////////////////
	//
	// __VTG - Track made good and Ground speed
	// 
	//                 1  2  3  4  5  6  7  8 9
	//                 |  |  |  |  |  |  |  | |
	// 	       $--VTG, x.x, T, x.x, M, x.x, N, x.x, K* hh<CR><LF>
	// 	NMEA 2.3:
	//         $--VTG, x.x, T, x.x, M, x.x, N, x.x, K, m* hh<CR><LF>
	//         ex) $GPVTG,220.86,T,,M,2.550,N,4.724,K,A*34
	//             $GPVTG,088.7,T,,M,000.0,N,000.0,K,A*0A
	// Field Number:
	//  1) Course over ground, degrees True
	//  2) T = True
	//  3) Course over ground, degrees Magnetic
	//  4) M = Magnetic
	//  5) Speed over ground, knots
	//  6) N = Knots
	//  7) Speed over ground, km / hr
	//  8) K = Kilometers Per Hour
	//  9) FAA mode indicator(NMEA 2.3 and later)
	// 10) Checksum
	// 11) Terminator : CR/LF
	struct T_NMEA_VTG
	{
		DOUBLE m_dCourseTrue;		// True course, in degree
		DOUBLE m_dCourseMag;		// Magnetic course, in degree
		DOUBLE m_dSpeedKnots;		// Knots
		DOUBLE m_dSpeedKmPerH;		// km/Hr
		UINT m_unTimeTag;			// time tag
	};

	// __CAN : 전자헤딩센서 정보
	//     F112 : vessel Heading
	//                        1 2  3    4    5    6
	//                        | |  |    |    |    |
	//          $__CAN,F11200 8 00 2BF2 FF7F FF7F FD
	//     F113 : Rate of Turn
	//                        1 2  7
	//                        | |  |
	//          $__CAN,F11300 8 00 41EFFFFF 2802FF
	//     F114 : Heave
	//                        1 2  8
	//                        | |  |    
	//          $__CAN,F11400 8 00 FDFF FFFFFF7FFD
	//     F119 : Attitude
	//                        1 2  9   10    11
	//                        | |  |    |    |
	//          $__CAN,F11900 8 00 FF7F E9FC 2E00 FF	
	// Field Number:
	//  1) Data Size
	//  2) SID
	//  3) Heading : unsigned short(16 Bits), Radian, x0.0001
	//  4) Deviation : signed short(16 Bits), Radian, x0.0001
	//  5) Variation : signed short(16 Bits), Radian, x0.0001
	//  6) Heading Reference : unsigned char(2 Bits), 0 = true, 1 = magnetic, 2 = error, 3 = null
	//  7) Rate of Turn : signed int(32 Bits), Rad/s, x3.125e-8
	//  8) Heave : signed short(16 Bits), m, x0.01
	//  9) Attitude Yaw : signed short(16 Bits), Radian, x0.0001
	// 10) Attitude Pitch : signed short(16 Bits), Radian, x0.0001
	// 11) Attitude Roll : signed short(16 Bits), Radian, x0.0001
	// 12) Terminator : CR/LF+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	struct T_NMEA_CAN
	{
		DOUBLE m_dHeading;		// Radian
		DOUBLE m_dDeviation;	// Radian
		DOUBLE m_dVariation;	// Radian
		WORD m_wHeadingRef;		// Heading Sesnor Reference
								// 0 = true, 1 = magnetic, 2 = error, 3 = Null
		WORD m_wReserved;
		DOUBLE m_dTurnRate;		// Rate of Turn, RAD/s
		DOUBLE m_dYaw;			// Attitude yaw, Radian
		DOUBLE m_dPitch;		// Attitude pitch, Radian
		DOUBLE m_dRoll;			// Attitude roll, Radian
		DOUBLE m_dHeave;		// m
		UINT m_unHeadingCount;	// Heading time tag
		UINT m_unTurnRateCount;	// Turn Rate time tag
		UINT m_unAttitudeCount;	// Attitude time tag
		UINT m_unHeaveCount;	// Heave time tag
	};

#pragma pack(pop)

} // NS_SALUS_MS_APP