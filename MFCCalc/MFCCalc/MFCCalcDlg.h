
// MFCCalcDlg.h: 헤더 파일
//

#pragma once


// CMFCCalcDlg 대화 상자
class CMFCCalcDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCCalcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCALC_DIALOG };
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
	CButton awe;	
	// 사용할 변수들
	CString m_EditDisplay;					// 숫자 입력창
	CString m_calcString;					// 연산 결과 출력 문장
	enum FourOP m_selectedOP;				// 어떤 연산자가 선택되었는지
	double m_nCurrentInput;					// 연산결과 중간 저장값(현재 입력값)
	double m_nResult;						// 계산 결과 저장
	bool m_bOperatorJustPressed = false;	// 연사자가 눌렸는지 나타내는 플래그
	// 이벤트
	afx_msg void OnBnClickedNumber0();
	afx_msg void OnBnClickedNumber1();
	afx_msg void OnBnClickedNumber2();
	afx_msg void OnBnClickedNumber3();
	afx_msg void OnBnClickedNumber4();
	afx_msg void OnBnClickedNumber5();
	afx_msg void OnBnClickedNumber6();
	afx_msg void OnBnClickedNumber7();
	afx_msg void OnBnClickedNumber8();
	afx_msg void OnBnClickedNumber9();
	afx_msg void OnBnClickedAdd();	// 더하기
	afx_msg void OnBnClickedSub();	// 빼기
	afx_msg void OnBnClickedMul();	// 곱하기
	afx_msg void OnBnClickedDiv();	// 나누기
	afx_msg void OnBnClickedClear(); // "C"
	afx_msg void OnBnClickedResult();	// "="
	afx_msg void OnBnClickeddot();
};

// 연산자 선택 열거형	
enum FourOP {
	PLUS = 1001,
	MINUS,
	MUL,
	DIVIDE,
	NONE
};
