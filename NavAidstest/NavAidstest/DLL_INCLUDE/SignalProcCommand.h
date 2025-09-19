#pragma once

#include <queue>
#include <map>
#include <afxmt.h>

#include "SignalProcCommandDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CSignalProcCommand
	{
	public:
		CSignalProcCommand();
		~CSignalProcCommand();

	public:
		static CSignalProcCommand* GetInstance();
		static void DeleteInstance();

		// Command를 저장할 위치의 버퍼 포인터를 반환한다.
		T_SIGNAL_PROC_COMMAND* GetBackBuffer();
		// 저장된 Command를 큐에 저장한다.
		void PushBack(BOOL bDuplicate = TRUE);

		// Command가 저장된 위치의 버퍼 포인터를 반환한다.
		T_SIGNAL_PROC_COMMAND* GetFrontBuffer();
		// Command를 큐에서 제거한다.
		void PopFront();
		// 큐에 Command가 존재하면 TRUE
		BOOL IsExistCommand();

	private:
		BOOL IsExistCommand(E_SIGNAL_PROC_COMMAND eCommand);	// 맵에 해당 command의 존재 여부 확인
		void AddCommand(E_SIGNAL_PROC_COMMAND eCommand);		// 맵에 해당 command 추가
		void DeleteCommand(E_SIGNAL_PROC_COMMAND eCommand);

		void RemoveAllQueue();
		void RemoveAllMap();

		void LockCommand();
		void UnlockCommand();

	private:
		static CSignalProcCommand* m_pInstance;
		static const INT m_unMAX_COMMAND_BUFF_NUM = 20U;

		T_SIGNAL_PROC_COMMAND* m_pCommandBuffer;
		INT m_unWriteBuffIndex;

		std::queue<std::pair<E_SIGNAL_PROC_COMMAND, UINT>> m_queueCommand;	// 명령 종류와 버퍼 인덱스 저장
		std::map<E_SIGNAL_PROC_COMMAND, UINT> m_mapCommand;					// 명령 종류와 명령 발생 횟수 저장

		CCriticalSection* m_pCommandCS;
	};

} // NS_SALUS_MS_APP