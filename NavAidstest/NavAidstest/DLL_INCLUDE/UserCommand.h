#pragma once

#include <queue>
#include <map>
#include <afxmt.h>

#include "UserCommandDef.h"

namespace NS_SALUS_MS_APP
{
	class AFX_EXT_CLASS CUserCommand
	{
	public:
		CUserCommand();
		~CUserCommand();

	public:
		static CUserCommand* GetInstance();
		static void DeleteInstance();

		// Command�� ������ ��ġ�� ���� �����͸� ��ȯ�Ѵ�.
		T_USER_COMMAND* GetBackBuffer();
		// ����� Command�� ť�� �����Ѵ�.
		void PushBack(BOOL bDuplicate = TRUE);

		// Command�� ����� ��ġ�� ���� �����͸� ��ȯ�Ѵ�.
		T_USER_COMMAND* GetFrontBuffer();
		// Command�� ť���� �����Ѵ�.
		void PopFront();
		// ť�� Command�� �����ϸ� TRUE
		BOOL IsExistCommand();

	private:
		BOOL IsExistCommand(E_USER_COMMAND eCommand);	// �ʿ� �ش� command�� ���� ���� Ȯ��
		void AddCommand(E_USER_COMMAND eCommand);		// �ʿ� �ش� command �߰�
		void DeleteCommand(E_USER_COMMAND eCommand);

		void RemoveAllQueue();
		void RemoveAllMap();

		void LockCommand();
		void UnlockCommand();

	private:
		static CUserCommand* m_pInstance;

		static const INT m_unMAX_COMMAND_BUFF_NUM = 50U;

		T_USER_COMMAND* m_pCommandBuffer;
		INT m_unWriteBuffIndex;

		std::queue<std::pair<E_USER_COMMAND, UINT>> m_queueCommand;	// ��� ������ ���� �ε��� ����
		std::map<E_USER_COMMAND, UINT> m_mapCommand;				// ��� ������ ��� �߻� Ƚ�� ����

		CCriticalSection* m_pCommandCS;
	};

}	// NS_SALUS_MS_APP
