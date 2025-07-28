
// MFCGradeDlg.h: 헤더 파일
//

#pragma once


// CMFCGradeDlg 대화 상자
class CMFCGradeDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCGradeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGRADE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CListCtrl m_ClistScore;
	void ReadTextFile(const CString& filePath);									// 텍스트 파일 읽기
	void Parsing(const CString& line, TCHAR delimeter, CStringArray& outArray); \

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//
public:
	afx_msg void OnBnClickedButtonBrowse();
	
};
