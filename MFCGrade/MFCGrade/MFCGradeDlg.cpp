﻿
// MFCGradeDlg.cpp: 구현 파일
//
#include <queue>
#include <string>
#include "pch.h"
#include "framework.h"
#include "MFCGrade.h"
#include "MFCGradeDlg.h"
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


// CMFCGradeDlg 대화 상자



CMFCGradeDlg::CMFCGradeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGRADE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCORE, m_ClistScore);
}

BEGIN_MESSAGE_MAP(CMFCGradeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Browse, &CMFCGradeDlg::OnBnClickedButtonBrowse)
END_MESSAGE_MAP()


// CMFCGradeDlg 메시지 처리기

BOOL CMFCGradeDlg::OnInitDialog()
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
	m_ClistScore.InsertColumn(0, _T("이름"), LVCFMT_LEFT, 80);
	m_ClistScore.InsertColumn(1, _T("학번"), LVCFMT_LEFT, 100);
	m_ClistScore.InsertColumn(2, _T("국어"), LVCFMT_CENTER, 60);
	m_ClistScore.InsertColumn(3, _T("영어"), LVCFMT_CENTER, 60);
	m_ClistScore.InsertColumn(4, _T("수학"), LVCFMT_CENTER, 60);

	m_ClistScore.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGradeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCGradeDlg::OnPaint()
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
HCURSOR CMFCGradeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// .txt 파일 불러오기
void CMFCGradeDlg::OnBnClickedButtonBrowse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, _T("txt"), nullptr, OFN_FILEMUSTEXIST, _T("텍스트 파일 (*.txt)|*.txt||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName(); // 전체 경로
		ReadTextFile(filePath);
	}
}

// 파일 읽기
void CMFCGradeDlg::ReadTextFile(const CString& filePath)
{
	CString content;
	CFile file(filePath, CFile::modeRead | CFile::typeBinary);
	DWORD dwLen = (DWORD)file.GetLength();
	BYTE* pBuf = new BYTE[dwLen + 1];
	file.Read(pBuf, dwLen);
	pBuf[dwLen] = 0;

	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)pBuf, -1, NULL, 0);
	WCHAR* pWStr = new WCHAR[len];
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)pBuf, -1, pWStr, len);
	content = CString(pWStr);

	delete[] pBuf;
	delete[] pWStr;
	
	// 한 줄씩 분리
	CStringArray lines;
	CString current;
	for (int i = 0; i < content.GetLength(); i++)
	{
		TCHAR ch = content[i];

		if (ch == _T('\r'))
		{
			if (!current.IsEmpty())
			{
				current.Trim();
				if (!current.IsEmpty())
					lines.Add(current);
				current.Empty();
			}
			if (i + 1 < content.GetLength() && content[i + 1] == _T('\n'))
				++i;
		}
		else if (ch == _T('\n'))
		{
			if (!current.IsEmpty())
			{
				current.Trim();
				if (!current.IsEmpty())
					lines.Add(current);
				current.Empty();
			}
		}
		else
			current += ch;
	}

	if (!current.IsEmpty())
	{
		current.Trim();
		if (!current.IsEmpty())
			lines.Add(current);
	}


	// 리스트 초기화
	m_ClistScore.DeleteAllItems();


	file.Close();
}

// 받은 문자열을 parsing
void CMFCGradeDlg::Parsing(const CString& line, TCHAR delimiter, CStringArray& outArray)
{
	outArray.RemoveAll();
	int start = 0, end = 0;

	while ((end = line.Find(delimiter, start)) != -1)
	{
		CString token = line.Mid(start, end - start);
		token.Trim();
		outArray.Add(token);
		start = end + 1;
	}	

	CString lastToken = line.Mid(start);
	lastToken.Trim();
	outArray.Add(lastToken);
}

// 파싱된 문자열을 구조체에 삽입
void CMFCGradeDlg::ProcessLine(const CString& line)
{
	CStringArray tokens;
	Parsing(line, _T(','), tokens);

	if (tokens.GetCount() == 5)
	{
		studentInfo student;
		student.name = tokens[0];
		student.studentID = tokens[1];
		student.korean = _ttoi(tokens[2]);
		student.english = _ttoi(tokens[3]);
		student.math = _ttoi(tokens[4]);
		m_messageQueue.push(student);
	}
}