#pragma once

#include "MenuDef.h"

class AFX_EXT_CLASS CMenuManager
{
public:
	CMenuManager();
	~CMenuManager();

public:
	static CMenuManager* GetInstance();
	static void DeleteInstance();

	void Initialize(CWnd* const pParentWnd, const INT nStartX, const INT nStartY, const INT nViewWidth, const INT nViewHeight);
	void Finalize();

	void UnCheckMenu(const INT nSelMenu);

	void ChangedViewSize(const INT nStartX, const INT nStartY, const INT nViewWidth, const INT nViewHeight);
	void ChangeColorConfig();

	void ChangeNextStatus();
	void SetSystemStatus(BOOL bStatus);

	void SetVrmEblShowSetting(BOOL bVrmEbl1, BOOL bVrmEbl2);

	void SerVrmEblSetSetting(BOOL vbVrmebl1, BOOL bVrmEbl2);

	void SetMoveStatus(BOOL bMoveMode);

	void SetGroupStatus(BOOL bGroupMode);

	void SetACQStatus(BOOL bACQMode);

	void SetFastStatus(BOOL bFastMode);

	void SetSubStatus(BOOL bSubMode);

	void SetSwapStatus(BOOL bSwapMode);

	void SetSelectStatus(BOOL bASelectMode);

	void SetRLSStatus(BOOL bRLSMode);

	E_MENU_KIND GetCurMenu();
private:
	static CMenuManager* m_pInstance;
};

