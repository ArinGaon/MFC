
// MFCClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
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


// CMFCClientDlg 대화 상자



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
	, m_strIP(_T(""))
	, m_strMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strMsg);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_editFilePath);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_staticStatus);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_SENDLOG, &CMFCClientDlg::OnBnClickedButtonSendlog)
END_MESSAGE_MAP()


// CMFCClientDlg 메시지 처리기

BOOL CMFCClientDlg::OnInitDialog()
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

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCClientDlg::OnPaint()
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
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); // UI의 IP 주소 값을 m_strIP 변수로 가져옵니다.

	m_ConnectSocket.Create(); // 1. 소켓을 생성합니다.
	m_ConnectSocket.m_pDlg = this; // 2. 소켓에 다이얼로그 주소를 알려줍니다.

	// 3. UI에서 입력받은 IP와 7000번 포트로 접속을 시도합니다.
	m_ConnectSocket.Connect(m_strIP, 7000);
	// 접속 성공 여부는 OnConnect 함수에서 처리됩니다.
}


void CMFCClientDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SendMsg(m_strMsg);
}

void CMFCClientDlg::SendMsg(CString string)
{
	UpdateData(TRUE);
	CT2A ascii(string);
	m_ConnectSocket.Send(ascii.m_psz, strlen(ascii.m_psz));

	AddMessageToList(string);
	string = _T("");
	UpdateData(FALSE);
}

void CMFCClientDlg::AddMessageToList(CString str)
{
	m_listMsg.AddString(str);
	m_listMsg.SetCurSel(m_listMsg.GetCount() - 1);
}



void CMFCClientDlg::OnBnClickedButtonSendlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("로그파일 (*.log)|*log|모든 파일 (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		m_editFilePath.SetWindowText(dlg.GetPathName());
		ReadFile(dlg.GetPathName());
	}
}


void CMFCClientDlg::ReadFile(const CString& filePath)
{
	CFile file;
	if (!file.Open(filePath, CFile::modeRead | CFile::typeBinary))
		return;
	m_staticStatus.SetWindowText(_T("파일 로드 중"));
	char ch;
	char prevCh = 0;
	CString currentLine;

	while (file.Read(&ch, 1) == 1)
	{
		// CRLF 처리: \r\n → 줄 나눔
		if (prevCh == '\r' && ch == '\n')
		{
			currentLine.Trim();
			if (!currentLine.IsEmpty())
			{
				
			}
			currentLine.Empty();
			prevCh = 0;
			continue;
		}

		// CR 단독 → 줄 나눔
		if (ch == '\r')
		{
			currentLine.Trim();
			if (!currentLine.IsEmpty())
				SendMsg(currentLine);
			currentLine.Empty();
			prevCh = ch;
			continue;
		}

		// LF 단독 → 줄 나눔
		if (ch == '\n')
		{
			currentLine.Trim();
			if (!currentLine.IsEmpty())
				SendMsg(currentLine);
			currentLine.Empty();
			prevCh = ch;
			continue;
		}

		// 일반 문자 누적
		currentLine += ch;
		prevCh = ch;

	}
	// 파일 끝 처리
	currentLine.Trim();
	if (!currentLine.IsEmpty())
		SendMsg(currentLine);

	file.Close();
	m_staticStatus.SetWindowText(_T("파일 로드 완료"));
}