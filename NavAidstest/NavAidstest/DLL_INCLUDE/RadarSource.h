#pragma once

#include "RadarBaseDef.h"
#include "SystemTypeDef.h"

using namespace NS_SALUS_MS_APP;

enum class E_RADAR_SOURCE_KIND : INT
{
	eRADAR_SOURCE_NONE = 0,
	eRADAR_SOURCE_SPX_TPG,
	eRADAR_SOURCE_SPX_REPLAY,
	eRADAR_SOURCE_SPX_HPX,
	eRADAR_SOURCE_HALO,
	eRADAR_SOURCE_QUANTUM_REPLAY,
	eRADAR_SOURCE_HALO_REPLAY,
};

struct T_SPX_HPX_CTRL_PARAM
{
	UINT	m_unNumSamples;
	DOUBLE	m_dStartMetres;
	DOUBLE	m_dEndMetres;
	DOUBLE	m_dTriggerDelayMetres;	// range correction
	INT		m_nChannelIndex;		// video channel 0 = VIDEO_A, others = VIDEO_B
	INT		m_nTriggerIndex;
	UINT	m_unTriggerInverted;
	INT		m_nAcpIndex;
	UINT	m_unAcpInverted;
	INT		m_nArpIndex;
	UINT	m_unArpInverted;
	UINT	m_unPRF;
	DOUBLE	m_dGainA;
	DOUBLE	m_dOffsetA_Voltage;
	DOUBLE	m_dGainB;
	DOUBLE	m_dOffsetB_Voltage;
};

struct T_SPX_TPG_CTRL_PARAM
{
	INT		m_nPattern;
	INT		m_nArg1;
	DOUBLE	m_dPeriod;
	UINT	m_unPRF;
	DOUBLE	m_dRange;
};

struct T_REPLAY_CTRL_PARAM
{
	CHAR	m_szFileName[g_unREPLAY_FILENAME_SIZE];
	INT		m_nRepeat;				// 0 = no repeat, 1 = repeat
};

struct T_RADAR_SOURCE_PARAM
{
	E_RADAR_SOURCE_KIND m_eSourceKind;
	union
	{
		T_SPX_TPG_CTRL_PARAM m_tSpxTpgParam;
		T_SPX_HPX_CTRL_PARAM m_tSpxHpxParam;
		T_REPLAY_CTRL_PARAM m_tReplayParam;
	};
};

class AFX_EXT_CLASS CRadarSource
{
public:
	CRadarSource();
	~CRadarSource();

public:
	static CRadarSource* GetInstance();
	static void DeleteInstance();

	BOOL GetConnectHalo();
	void Initialize();
	void Finalize();

	void StartRadarSource(T_RADAR_SOURCE_PARAM* pRadarSourceParam);
	void StopRadarSource();

	void UpdateRPM(int Rpm);
	void UpdateScanerPWR(int Pwr);
	void UpdateTransmit(int Transmit);
	void UpdateUseMode(int Usemode);
	void UpdateFastScan(int FastScan);
	void UpdateLocalIR(int LocalIR);
	void UpdateBeamSharp(int BeamSharp);
	void UpdateVideoAperture(FLOAT VideoAperture);
	void UpdateAllValue(T_SIMRAD_SAVE_DATA* m_tSimradConfig);
	void UpdateTargetBoost(int TargetBoost);
	void UpdateTargetStretch(int TargetBoost);
	void UpdateTargetStretchLegacy(int TargetStretchLegacy);
	void UpdateCurveType(int CurveType);
	void UpdateGain(int Gain, int mode);
	void UpdateRain(int Rain);
	void UpdateRange(UINT Range);
	void UpdateFTC(int FTC);
	void UpdateIRLevel(int IRLevel);
	void UpdateSeaLegacy(int SeaLegacy, int mode);
	void UpdateSeaAuto(int Sea, int SeaOffet, int mode, BOOL bState);
	void UpdateSideLobe(int SideLobe, int mode);
	void UpdateNoiseReject(int NoiseReject);
	void UpdateTimeEnabled(BOOL bState);
	void UpdateTimePeriod(int TransmitPeriod, int StandbyPeriod);
	void UpdateSectorBlanking(int ID, bool bEnabled, int Start, int End);
	void UpdateParkingPosition(int ParkPos);
	void UpdateAntennaHeight(int AntHeight);
	void UpdateAntennaOffet(int xOffset, int yOffset);
	void UpdateZeroRangeOffset(int Offset);
	void UpdateZeroBearingOffset(int Offset);
	void UpdateResetToFactory();
	void UpdateAntType(int Type);

	E_RADAR_SOURCE_KIND GetCurSourceKind();

	UINT GetMaxRangeBins(E_RADAR_SOURCE_KIND eRadarSourceKind);
	UINT GetMaxAzimuthNum(E_RADAR_SOURCE_KIND eRadarSourceKind);

protected:
	void StartSpxTpg(T_SPX_TPG_CTRL_PARAM* pSpxTpgCtrlParam);
	void StopSpxTpg();

	void StartSpxReplay(T_REPLAY_CTRL_PARAM* pReplayCtrlParam);
	void StopSpxReplay();

	void StartSpxHpx(T_SPX_HPX_CTRL_PARAM* pSpxHpxCtrlParam);
	void StopSpxHpx();

	void StartHalo();
	void StopHalo();

	void StartQuantumReplay(T_REPLAY_CTRL_PARAM* pReplayCtrlParam);
	void StopQuantumReplay();

	void StartHaloReplay(T_REPLAY_CTRL_PARAM* pReplayCtrlParam);
	void StopHaloReplay();

private:
	E_RADAR_SOURCE_KIND m_eCurSourceKind;	// 0 : None, 1 : TPG, 2: Network, 3: File, 4: HPx

	static CRadarSource* m_pInstance;
};

