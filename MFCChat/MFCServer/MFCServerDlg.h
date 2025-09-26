
// MFCServerDlg.h: 헤더 파일
//
#pragma once
#include <afxcoll.h>
#include "CListenSocket.h" // CListenSocket 클래스의 설계도 포함
#include "CClientSocket.h" // CClientSocket 클래스의 설계도 포함

// 전방 선언 (헤더 순환 참조 방지)
class CListenSocket;
class CClientSocket;


// CMFCServerDlg 대화 상자
class CMFCServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();

	// CClientSocket m_ClientSocket; // <-- 이 줄을 주석 처리하거나 삭제합니다.
	CPtrList m_clientSocketList; // <-- 여러 클라이언트를 관리할 리스트 변수를 추가합니다.

	CListenSocket m_ListenSocket;
	// CClientSocket m_ClientSocket; // <-- 여기 있어도 상관없으나, 혼동을 피하기 위해 위쪽으로 옮기고 이전 것은 삭제합니다.
	CListBox m_listLog;

	void AddMessageToList(CString str);
	void RemoveClient(CClientSocket* pClient);
};
