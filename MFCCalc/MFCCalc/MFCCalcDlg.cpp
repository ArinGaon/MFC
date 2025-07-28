
// MFCCalcDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCCalc.h"
#include "MFCCalcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCalcDlg 대화 상자



CMFCCalcDlg::CMFCCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCALC_DIALOG, pParent)
	, m_EditDisplay(_T(""))
	, m_calcString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, awe);
	DDX_Text(pDX, IDC_EDIT1, m_EditDisplay);
	DDX_Text(pDX, Calc_String, m_calcString);
}

BEGIN_MESSAGE_MAP(CMFCCalcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Number0, &CMFCCalcDlg::OnBnClickedNumber0)
	ON_BN_CLICKED(Number1, &CMFCCalcDlg::OnBnClickedNumber1)
	ON_BN_CLICKED(Number2, &CMFCCalcDlg::OnBnClickedNumber2)
	ON_BN_CLICKED(Number3, &CMFCCalcDlg::OnBnClickedNumber3)
	ON_BN_CLICKED(Number4, &CMFCCalcDlg::OnBnClickedNumber4)
	ON_BN_CLICKED(Number5, &CMFCCalcDlg::OnBnClickedNumber5)
	ON_BN_CLICKED(Number6, &CMFCCalcDlg::OnBnClickedNumber6)
	ON_BN_CLICKED(Number7, &CMFCCalcDlg::OnBnClickedNumber7)
	ON_BN_CLICKED(Number8, &CMFCCalcDlg::OnBnClickedNumber8)
	ON_BN_CLICKED(Number9, &CMFCCalcDlg::OnBnClickedNumber9)
	ON_BN_CLICKED(dot, &CMFCCalcDlg::OnBnClickeddot)
	ON_BN_CLICKED(ADD, &CMFCCalcDlg::OnBnClickedAdd)
	ON_BN_CLICKED(Sub, &CMFCCalcDlg::OnBnClickedSub)
	ON_BN_CLICKED(Mul, &CMFCCalcDlg::OnBnClickedMul)
	ON_BN_CLICKED(DIV, &CMFCCalcDlg::OnBnClickedDiv)
	ON_BN_CLICKED(CLEAR, &CMFCCalcDlg::OnBnClickedClear)
	ON_BN_CLICKED(RESULT, &CMFCCalcDlg::OnBnClickedResult)
END_MESSAGE_MAP()


// CMFCCalcDlg 메시지 처리기

BOOL CMFCCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_selectedOP = NONE;
	m_nResult = 0;
	m_nCurrentInput = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCCalcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 숫자버튼 클릭 이벤트 (dot 포함)
void CMFCCalcDlg::OnBnClickedNumber0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	m_EditDisplay = m_EditDisplay + _T("0");;
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("1");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("2");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("3");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("4");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("5");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("6");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("7");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("8");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedNumber9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T("9");
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickeddot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_EditDisplay = m_EditDisplay + _T(".");
	UpdateData(FALSE);
}


// 사칙연산자 클릭 이벤트
void CMFCCalcDlg::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nCurrentInput = _ttof(m_EditDisplay);

	if (m_selectedOP != NONE)
	{
		switch (m_selectedOP)
		{
		case PLUS:	m_nResult += m_nCurrentInput; break;
		case MINUS: m_nResult -= m_nCurrentInput; break;
		case MUL: m_nResult *= m_nCurrentInput; break;
		case DIVIDE: m_nResult /= m_nCurrentInput; break;
		}
	}
	else
	{
		m_nResult = m_nCurrentInput;
	}
	m_selectedOP = PLUS;
	m_EditDisplay.Format(_T("%.10g"), m_nResult);
	m_calcString.Format(_T("%g + "), m_nResult);
	// 여기서 EditBox를 초기화해주지 않으면 값이 지워지지 않고 반영됨
	// ex) 5 + 6을 출력하려고 하는데 5, +, 6, = 을 차례로 누르면
	//	   5 + 56이 되어 61이 출력되어 아래 코드를 통해 EditBox를 초기화
	m_EditDisplay.Format(_T(""));
	UpdateData(FALSE);

}

void CMFCCalcDlg::OnBnClickedSub()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nCurrentInput = _ttof(m_EditDisplay);

	if (m_selectedOP != NONE)
	{
		switch (m_selectedOP)
		{
		case PLUS: m_nResult += m_nCurrentInput; break;
		case MINUS: m_nResult -= m_nCurrentInput; break;
		case MUL: m_nResult *= m_nCurrentInput; break;
		case DIVIDE: m_nResult /= m_nCurrentInput; break;
		}
	}
	else
	{
		m_nResult = m_nCurrentInput;
	}
	m_selectedOP = MINUS;
	m_EditDisplay.Format(_T("%.10g"), m_nResult);
	m_calcString.Format(_T("%g - "), m_nResult);
	m_EditDisplay.Format(_T(""));
	UpdateData(FALSE);
}


void CMFCCalcDlg::OnBnClickedMul()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nCurrentInput = _ttof(m_EditDisplay);

	if (m_selectedOP != NONE)
	{
		switch (m_selectedOP)
		{
		case PLUS: m_nResult += m_nCurrentInput; break;
		case MINUS: m_nResult -= m_nCurrentInput; break;
		case MUL: m_nResult *= m_nCurrentInput; break;
		case DIVIDE: m_nResult /= m_nCurrentInput; break;
		}
	}
	else
	{
		m_nResult = m_nCurrentInput;
	}
	m_selectedOP = MUL;
	m_EditDisplay.Format(_T("%.10g"), m_nCurrentInput);
	m_calcString.Format(_T("%g * "), m_nResult);
	m_EditDisplay.Format(_T(""));
	UpdateData(FALSE);
}

void CMFCCalcDlg::OnBnClickedDiv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nCurrentInput = _ttof(m_EditDisplay);

	if (m_selectedOP != NONE)
	{
		switch (m_selectedOP)
		{
		case PLUS: m_nResult += m_nCurrentInput; break;
		case MINUS: m_nResult -= m_nCurrentInput; break;
		case MUL: m_nResult *= m_nCurrentInput; break;
		case DIVIDE: m_nResult /= m_nCurrentInput; break;
		}
	}
	else
	{
		m_nResult = m_nCurrentInput;
	}
	m_selectedOP = DIVIDE;
	m_EditDisplay.Format(_T("%.10g"), m_nCurrentInput);
	m_calcString.Format(_T("%g / "), m_nResult);
	m_EditDisplay.Format(_T(""));
	UpdateData(FALSE);
}

// = 을 누르면 최종 결과가 나옴. (단, 그 전까지 중간결과가 계속 출력됨)
void CMFCCalcDlg::OnBnClickedResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nCurrentInput = _ttof(m_EditDisplay);

	switch (m_selectedOP)
	{
	case PLUS: m_nResult += m_nCurrentInput; break;
	case MINUS: m_nResult -= m_nCurrentInput; break;
	case MUL: m_nResult *= m_nCurrentInput; break;
	case DIVIDE: m_nResult /= m_nCurrentInput; break;
	}
	
	CString resultStr;
	resultStr.Format(_T("= %.10g"), m_nResult);
	m_calcString += m_EditDisplay + _T(" ") + resultStr;

	m_EditDisplay.Format(_T("%.10g"), m_nResult);
	m_selectedOP = NONE;

	UpdateData(FALSE);
}

// 계산기의 C(초기화) 버튼
void CMFCCalcDlg::OnBnClickedClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_nResult = 0;
	m_nCurrentInput = 0;
	m_selectedOP = NONE;
	m_EditDisplay = _T("");
	m_calcString = _T("");
	UpdateData(FALSE);
}
