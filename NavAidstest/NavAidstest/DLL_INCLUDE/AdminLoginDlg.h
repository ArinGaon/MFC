#pragma once


#include <afxdialogex.h>


// CAdminLoginDlg ��ȭ �����Դϴ�.

class AFX_EXT_CLASS CAdminLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminLoginDlg)

public:
	CAdminLoginDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAdminLoginDlg();
	virtual BOOL Create(CWnd* pParentWnd);

public:
	void SetDefaultAdminID(CString strAdminID);
	CString GetAdminId();
	CString GetAdminPw();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
	CEdit m_wndAdminIdEdit;
	CEdit m_wndAdminPwEdit;

	CBitmapButton m_wndOk;
	CBitmapButton m_wndCancel;
	CStatic m_wndComment;

	int		m_retryCount;
	CString m_strAdminId;
	CString m_strAdminPw;

	CString m_strDefaultID;
};
