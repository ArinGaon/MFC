
// MFCServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCServer.h"
#include "MFCServerDlg.h"
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


// CMFCServerDlg 대화 상자



CMFCServerDlg::CMFCServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
}

BEGIN_MESSAGE_MAP(CMFCServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCServerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCServerDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CMFCServerDlg 메시지 처리기

BOOL CMFCServerDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCServerDlg::OnPaint()
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
HCURSOR CMFCServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCServerDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// Listen 소켓을 7000번 포트로 열고, 클라이언트 접속을 대기
	m_ListenSocket.Create(7000);
	m_ListenSocket.Listen();
	m_ListenSocket.m_pDlg = this; // 소켓이 다이얼로그를 제어할 수 있도록 자신의 주소(this)를 넘김

	// --- UI 업데이트 ---
	AddMessageToList(_T(" 서버 시작완료. 클라이언트 접속 대기 중..."));
	SetDlgItemText(IDC_STATIC_STATUS, _T("클라이언트 대기 중..."));
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);					// Start 버튼 비활성화
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);					// Stop 버튼 활성화
}


void CMFCServerDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// --- 이 부분을 수정합니다 ---
	// 리스트에 있는 모든 클라이언트 소켓의 연결을 닫습니다.
	POSITION pos = m_clientSocketList.GetHeadPosition();
	while (pos != NULL)
	{
		CClientSocket* pClient = (CClientSocket*)m_clientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			pClient->Close();
			// OnClose에서 delete this를 하므로 여기서 delete하지 않습니다.
		}
	}
	m_clientSocketList.RemoveAll(); // 리스트를 비웁니다.

	m_ListenSocket.Close(); // Listen 소켓도 닫습니다.
	// --------------------------

	// --- UI 업데이트 ---
	AddMessageToList(_T(" 서버 중지 완료 "));
	SetDlgItemText(IDC_STATIC_STATUS, _T("서버 중지됨..."));
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);					//S Start 버튼과 만대로
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}

void CMFCServerDlg::AddMessageToList(CString str)
{
	// Listbox에 string 추가
	m_listLog.AddString(str);
	// 최신 메시지로 갱신
	m_listLog.SetCurSel(m_listLog.GetCount() - 1);
}