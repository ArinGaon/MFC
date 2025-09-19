#pragma once

#include "RadarDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CRadarDataMngr
	{
	public:
		CRadarDataMngr();
		~CRadarDataMngr();

	public:
		static CRadarDataMngr* GetInstance();
		static void DeleteInstance();

		void Initialize();
		void Finalize();

		void InitRadarData();
		void AddRawVideo(const T_RADAR_SOURCE_HEAD* const pRadarSrcHead, const UCHAR* const ucBuffer);
		T_RADAR_BSCOPE* GetRawVideo();

		HANDLE GetRawVideoDataEvent();
		HANDLE GetSpokeDataEvent();

		void AddSpokeData(UINT unScan, UINT unSector, UINT unAzimuth, UCHAR* pucDataBuff, UINT ucDataLen, DOUBLE dStartRange, DOUBLE dEndRange);
		T_RADAR_SPOKE* GetSpokeData();
	private:
		static CRadarDataMngr* m_pInstance;
	};

} // NS_SALUS_MS_APP