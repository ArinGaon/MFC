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

		// Command�� ������ ��ġ�� ���� �����͸� ��ȯ�Ѵ�.
		T_SIGNAL_PROC_COMMAND* GetBackBuffer();
		// ����� Command�� ť�� �����Ѵ�.
		void PushBack(BOOL bDuplicate = TRUE);

		// Command�� ����� ��ġ�� ���� �����͸� ��ȯ�Ѵ�.
		T_SIGNAL_PROC_COMMAND* GetFrontBuffer();
		// Command�� ť���� �����Ѵ�.
		void PopFront();
		// ť�� Command�� �����ϸ� TRUE
		BOOL IsExistCommand();

	private:
		BOOL IsExistCommand(E_SIGNAL_PROC_COMMAND eCommand);	// �ʿ� �ش� command�� ���� ���� Ȯ��
		void AddCommand(E_SIGNAL_PROC_COMMAND eCommand);		// �ʿ� �ش� command �߰�
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

		std::queue<std::pair<E_SIGNAL_PROC_COMMAND, UINT>> m_queueCommand;	// ��� ������ ���� �ε��� ����
		std::map<E_SIGNAL_PROC_COMMAND, UINT> m_mapCommand;					// ��� ������ ��� �߻� Ƚ�� ����

		CCriticalSection* m_pCommandCS;
	};

} // NS_SALUS_MS_APP