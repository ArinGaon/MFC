#pragma once

#include <queue>
#include <afxmt.h>

#include "RadarDataDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CBScopeQueue
	{
	public:
		CBScopeQueue(const UINT unMaxBScopeBuffNum, const UINT unMaxAScopeNum = 0U);
		~CBScopeQueue();

	public:
		T_RADAR_BSCOPE* GetBackBuffer();
		void PushBack();

		T_RADAR_BSCOPE* GetFrontBuffer();
		void PopFront();

		void Clear();

		UINT GetMaxAScopeBuffNum();

	private:
		void AllocMemory();
		void FreeMemory();

		void RemoveAllQueue();

		void LockQueue();
		void UnlockQueue();

	private:
		UINT m_unMaxBScopeBuffer;
		UINT m_unMaxAScopeBuffer;
		T_RADAR_BSCOPE* m_pBScopeBuffer;
		UINT m_unWriteBScopeIndex;

		std::queue<UINT> m_queueBScope; // RAW 비디오 저장 위치 큐
		CCriticalSection* m_pQueueCS;
	};
} // NS_SALUS_MS_APP


