
#pragma once

#include "DataTypeDef.h"
#include "RadarBaseDef.h"

namespace NS_SALUS_MS_APP
{

	static const UINT g_unMAX_PULSE_PER_SCAN = 15000U;		// 1회전당 최대 송신 횟수
	static const DOUBLE g_dMARGIN_BSCOPE_BUFFER = 1.2;		// 1.2배 정도 더 버퍼를 생성한다.
#ifdef USE_ARPA_SYSTEM
	static const UINT g_unMAX_RANGE_BINS = 2048U;
	static const UINT g_unMAX_SPOKE_DATA_PER_SCAN = 2048U;	// 1회전당 최대 azimuth 데이터 개수
#else
	static const UINT g_unMAX_RANGE_BINS = 4096U;
	static const UINT g_unMAX_SPOKE_DATA_PER_SCAN = 4096U;	// 1회전당 최대 azimuth 데이터 개수
#endif // USE_ARPA_SYSTEM
	static const UINT g_unMAX_SECTOR_PER_SCAN = 8U;			// 1회전당 최대 섹터 수
	static const UINT g_unMAX_AZIMUTH_RANGE = 65536U;

	struct T_RADAR_SOURCE_HEAD
	{
		USHORT usRadarVideoSize;	// The size of the encoded video data in bytes. Maximum value is 65535.
		UCHAR ucNumTriggers;		// Number of triggers represented by this data
		UCHAR ucSourceType;			// A code that indicates the source of the return:
									// 0 = Network radar video	(SPX_RIB_SOURCETYPE_NETWORK)
									// 1 = Internal test generator	(SPX_RIB_SOURCETYPE_TEST)
									// 2 = Replay from recording  (SPX_RIB_SOURCETYPE_REPLAY)
									// 3 = Scenario generator  (SPX_RIB_SOURCETYPE_SCENARIO)
									// 4 = HPx radar input	(SPX_RIB_SOURCETYPE_HPX100)
		UCHAR ucSourceCode;			// A code that is specific to the source of the radar.
		USHORT usCount;				// Incrementing counter. Each return sent should send an incrementing number in this field.The number
									//	may jump, for example if the source changes.
		USHORT usNominalLength;		// Expected to be constant. It is the length of the return (in samples) corresponding to full range.
		USHORT usThisLength;		// The length of this return in samples. This may the same as nominal return length, 
									// but may be less if the radar is in staggered mode. (<= nominal length)
		USHORT usAzimuth;			// The azimuth number is in the range 0..65356 - 1, representing 0 to 360 degrees.
		UCHAR ucPacking;			// Packing type
									//	0 = 8 - bits per sample, uncompressed
									//	1 = 4 - bits per sample, uncompressed
									//	2 = 2 - bits per sample, uncompressed
									//	3 = 1 - bit per sample, uncompressed
									//	10 = ORC(Open Radar Coding) standard compression
									//	20 = ZLIB compression.
		UCHAR ucScanMode;			// Defines the mode of the scanning as:
									//	0 = Normal rotating radar.The azimuth values will be increasing around the scan
									//	1 = Normal rotating radar with possible jump - backs through ship's motion compensation.
									//	2 = Sector scan.The radar is scanning in a sector backwards and forwards.
									//	3 = Random scan.An unpredictable azimuth scanning pattern.
									//	4 = Sector scan with flyback.Sector scan in which the radar scans forward only then immediately	returns back to the start azimuth to repeat.
		USHORT usHeading;			// Platform heading (0..65536 = 0..360degs) 
									// Platform heading expressed at a 16-bit number (0 = North, 16384 East, 32768 South etc.
		USHORT usTimeInterval;		// This is the time interval in microseconds between the last return and this return.
									// May be 0 if the time	is unknown, or if the value > 65ms.
		UCHAR ucPimFlags;			// Bitwise combination of SPX_PIM_FLAGS_.
									//	Bit 0: Return is repeat of previous one
									//	Bit 1 : Return is black - filled
									//	Bit 2 : Return is azimuth - correlated
									//	Bit 3 : Valid azimuth ref mode(set in Bit 4)
									//	Bit 4 : 0 = North referenced, 1 = heading referenced (This is only valid if Bit 3 = 1)
									//	Bit 5 : The original azimuth refrence mode before adjustment(0 = North, 1 = heading)
		UCHAR ucDataFlags;          // Bitwise combination of SPX_RIB_DATA_FLAGS_...
		FLOAT fStartRange;			// Start range in world units for first sample
		FLOAT fEndRange;			// End range in world units for nominalLength.
	};

	/******************************************************************************
	*           Data Structure for RADAR B-Scope
	*****************************************************************************/
	struct T_RADAR_ASCOPE
	{
		UINT m_unACP;						// 현재 ACP 정보 (0 ~ 65535), representing 0 to 360 degrees.
		UCHAR m_ucADC[g_unMAX_RANGE_BINS];	// 비디오 데이터
	};

	struct T_RADAR_BSCOPE
	{
		UINT m_unScanCount;		// Scan Counter, 0 ~ 
		UINT m_unCurSector;		// Current Sector, 0 ~ g_unMAX_SECTOR_PER_SCAN - 1
		UINT m_unRangeBin;		// number of A-SCOPE video data
		UINT m_unMaxAScope;		// max number of A-SCOPE video data
		DOUBLE m_dStartRange;	// start range from radar antenna for first sample, meter
		DOUBLE m_dEndRange;		// end range from radar antenna, meter
		T_RADAR_ASCOPE* m_pAScope;
	};


	struct T_RADAR_SPOKE
	{
		UINT m_unScanCount;		// Scan Counter, 0 ~ 
		UINT m_unCurSector;		// Current Sector, 0 ~ g_unMAX_SECTOR_PER_SCAN - 1
		UINT m_unRangeBin;		// number of A-SCOPE video data
		DOUBLE m_dStartRange;	// start range from radar antenna for first sample, meter
		DOUBLE m_dEndRange;		// end range from radar antenna, meter
		UINT m_unAzimuth;		// 현재 azimuth 정보 (0 ~ 65535), representing 0 to 360 degrees.
		UCHAR m_ucADC[g_unMAX_RANGE_BINS];	// 비디오 데이터
	};

} // namespace NS_SALUS_MS_APP