#pragma once

#include "DataTypeDef.h"
#include "RadarBaseDef.h"

/******************************************************************************
 *  Status Define
 *****************************************************************************/
#define ENABLE						1
#define DISABLE						0
#define SUCCESS						1
#define FAILURE						0
#define NULL						0


/******************************************************************************
 *  RADAR Interfacing Signal Type Define
 *****************************************************************************/
#define SINGLE_ENDED_ISOLATED		0
#define SINGLE_ENDED_75OHM			1
#define DIFFERENTIAL				2
#define NON_INVERTED				0
#define INVERTED					1
#define CH_A						0
#define CH_B						1


/******************************************************************************
*  Fixed Parameter for Signal Processing
*****************************************************************************/
#define SP_UNABLE							0
#define SP_ENABLE							1

#define MAX_ACPCOUNT					65535
#define MAX_PULSECNT					15000
#ifdef USE_ARPA_SYSTEM
#define MAX_nRANGEBIN					2048
#define MAX_nACP						2048
#else
#define MAX_nRANGEBIN					4096
#define MAX_nACP						4096
#endif // USE_ARPA_SYSTEM
#define MAX_SECTOR						8

#define MARGIN_SIZE_BSCOPE			1.2

#define MAX_POLYGON					100
#define MAX_POLYGON_POINT			100


/******************************************************************************
* Object Extraction Parameters
******************************************************************************/
#define FORMING_OPEN					1		
#define FORMING_CLOSED					0		

#define CROSSINGTYPE1					1
#define CROSSINGTYPE2					2
#define NONCROSSING						0

/******************************************************************************
* Unit Conversion Parameter
******************************************************************************/
// Unit Conversion Parameter
#define WGS84PI				3.1415926535898			// Circular Constant
#define DEG2RAD				WGS84PI/180.0			// Degree to Radian Conversion
#define RAD2DEG				180.0/WGS84PI 			// Radian to Degree Conversion

#pragma pack(push, 1)

/******************************************************************************
 *           Data Structure for RADAR B-Scope
 *****************************************************************************/
typedef struct tAScope {
	unsigned int		m_ACP;
	unsigned char		m_ADC[MAX_nRANGEBIN];
}  _tAScope;

typedef struct tBScope {
	unsigned int		m_ScanIndex;				// Scan Index
	unsigned int		m_SectorIndex;				// Sector Index
	unsigned int		m_nRangeBin;				// No. of RangeBIN
	unsigned int		m_nACP;						// No. of ACP
	double				m_StartRange;
	double				m_EndRange;
	_tAScope			*m_AScope;
} _tBScope;


/******************************************************************************
 * Object Information after Blob Processing
 *****************************************************************************/
typedef struct {
	UINT32	TentativeLabel;
	UINT8	FormingStatus;
	UINT8	CrossingStatus;
	UINT32	StartRange;
	UINT32	EndRange;
	UINT32	StartACP;
	UINT32	EndACP;
	UINT16	CellCounter;
	FLOAT	TotalEnergy;
	FLOAT	RangeEnergy;
	FLOAT	AzimuthEnergy;
} _tFormObject;


/* Position in 2D Cartesian Coordinate */
typedef struct {
	FLOAT X;
	FLOAT Y;
} _t2DPos;

typedef struct {
	UINT8		m_nPos;					// No. of Polygons
	_t2DPos	Pos[MAX_POLYGON_POINT];	// East-North Position
} _tAM_Poly;


typedef struct {
	UINT8			 m_nPoly;			// No. of Polygons
	_tAM_Poly	*m_pPoly;
} _tAM_PolyList;

#pragma pack(pop)