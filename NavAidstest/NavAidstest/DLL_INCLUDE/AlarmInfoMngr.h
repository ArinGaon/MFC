#pragma once

#include <vector>

#include "AlarmTypeDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CAlarmInfoMngr
	{
	public:
		CAlarmInfoMngr();
		~CAlarmInfoMngr();

	public:
		static CAlarmInfoMngr* GetInstance();
		static void DeleteInstance();

		void AddAlarm(const E_ALARM_TYPE eAlarmType, const E_ALARM_KIND eAlarmKind, const E_ALARM_CODE eAlarmCode, const INT nSoundOn);
		void AddAlarm(T_ALARM_INFO* const pAlarmInfo);
		void AlarmAck(UINT unIndex);
		void AlarmAckAuto(UINT unIndex);

		T_ALARM_INFO* GetLastAlarm();

		T_ALARM_INFO* GetActiveAlarm(UINT unIndex);
		T_ALARM_INFO* GetHistoryAlarm(UINT unIndex);

		UINT GetActiveAlarmCount();
		UINT GetHistroyAlarmCount();

		UINT GetTotalCount();
		UINT GetFaultCount();
		UINT GetWarningCount();
		UINT GetCautionCount();

	protected:
		void CalcAlarmCount(const E_ALARM_TYPE eAlarmType);
		void ReCalcAlaramCount(const E_ALARM_TYPE eAlarmType);

		void DeleteActiveAlarm(UINT unIndex);
		void RemoveAllActiveAlarm();
		void RemoveAllHistoryAlarm();

		void CheckActiveAlarmCount();
		void CheckDuplicateAlarm(T_ALARM_INFO* pAlarmInfo);
		void CheckHistoryAlarmCount();

	private:
		void GetAlarmTitle(TCHAR* const pszAlarmTitle, const E_ALARM_KIND eAlarmKind);
		void GetAlarmMsg(TCHAR* const pszAlarmMsg, const E_ALARM_CODE eAlarmCode);
		void GetAlarmDesc(TCHAR* const pszAlarmDesc, T_ALARM_INFO* const pAlarmInfo);

	private:
		static CAlarmInfoMngr* m_pInstance;

		static const UINT m_unMAX_ACTIVE_ALARM_NUM = 100;
		static const UINT m_unMAX_HISTORY_ALARM_NUM = 100;

		std::vector<T_ALARM_INFO*> m_vtAlarmActive;
		std::vector<T_ALARM_INFO*> m_vtAlarmHistory;

		UINT m_unTotalCount;
		UINT m_unFaultCount;
		UINT m_unWarningCount;
		UINT m_unCautionCount;
	};
}

