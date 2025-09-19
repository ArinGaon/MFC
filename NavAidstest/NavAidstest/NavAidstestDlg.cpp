#pragma once
// NavAidstestDlg.cpp: 구현 파일
//
#include <vector>
#include "pch.h"
#include "framework.h"
#include "NavAidstest.h"
#include "NavAidstestDlg.h"
#include "afxdialogex.h"
#include <afxcmn.h>

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


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CNavAidstestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_INPUT, m_editInput);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_editFilePath);
	DDX_Control(pDX, IDC_STATIC_PAGE_INFO, m_staticPageInfo);
	DDX_Control(pDX, IDC_PROGRESS_PARSE, m_progressCtrl);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_staticStatus);
	DDX_Control(pDX, IDC_STATIC_PARSE_RESULT, m_parseResult);
	DDX_Control(pDX, IDC_STATIC_PROGRESS_INFO, m_progressInfo);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNavAidstestDlg 대화 상자
CNavAidstestDlg::CNavAidstestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NAVAIDSTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


BEGIN_MESSAGE_MAP(CNavAidstestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CNavAidstestDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CNavAidstestDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CNavAidstestDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_PREV, &CNavAidstestDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_START_LOG, &CNavAidstestDlg::OnBnClickedBtnStartLog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT, &CNavAidstestDlg::OnDblclkListResult)
END_MESSAGE_MAP()


// CNavAidstestDlg 메시지 처리기

BOOL CNavAidstestDlg::OnInitDialog()
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
	CString inputStr = _T("");
	m_listResult.InsertColumn(0, _T("항목"), LVCFMT_LEFT, 1000);
	m_listResult.SetExtendedStyle(m_listResult.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
	//m_listResult.InsertColumn(1, _T("파싱결과"), LVCFMT_LEFT, 70);
	//m_listResult.InsertColumn(2, _T("요약"), LVCFMT_LEFT, 900);
	m_nCurrentPage = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CNavAidstestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNavAidstestDlg::OnPaint()
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
HCURSOR CNavAidstestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 한 줄짜리 메시지 시작버튼
void CNavAidstestDlg::OnBnClickedBtnStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString input;
	m_editInput.GetWindowText(input);
	if (input.IsEmpty()) return;
	m_staticStatus.SetWindowText(_T("파싱 시작"));
	m_parsedMessages.clear();
	m_parsedMessages.push_back({input, NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT, _T(""), false });
	ParseAllMessages();
	m_nCurrentPage = 0;
	UpdateListForCurrentPage(0);
	m_staticStatus.SetWindowText(_T("파싱 완료"));
}

// 로그 파일 읽어와서 확인
void CNavAidstestDlg::OnBnClickedBtnBrowse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("로그파일 (*.log)|*log|모든 파일 (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		m_editFilePath.SetWindowTextA(dlg.GetPathName());
		ReadFile(dlg.GetPathName());
	}
}

// 로그메시지 파싱 시작버튼
void CNavAidstestDlg::OnBnClickedBtnStartLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString filePath;
	m_editFilePath.GetWindowTextA(filePath);
	if (filePath.IsEmpty())
	{
		AfxMessageBox(_T("파일 경로를 지정하세요."));
		return;
	}
	m_staticStatus.SetWindowText(_T("파싱 시작"));
	ParseAllMessages();
	m_nCurrentPage = 0;
	UpdateListForCurrentPage(0);
	SaveParsingLogsToFile();
	m_staticStatus.SetWindowText(_T("파싱 완료"));
}

// 다음 버튼
void CNavAidstestDlg::OnBnClickedBtnNext()
	{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int totalPage = (m_parsedMessages.size() + ITEMS_PER_BLOCK_PAGE - 1) / ITEMS_PER_BLOCK_PAGE;
	if (m_nCurrentPage < totalPage - 1) {
		m_nCurrentPage++;
		UpdateListForCurrentPage(m_nCurrentPage);
	}
}

// 이전 버튼
void CNavAidstestDlg::OnBnClickedBtnPrev()
	{
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		if (m_nCurrentPage > 0)
		{
			m_nCurrentPage--;
			UpdateListForCurrentPage(m_nCurrentPage);
		}
	}

// 전체 파일 읽고, 한 줄씩 읽어서 벡터에 저장
void CNavAidstestDlg::ReadFile(const CString& filePath)
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
				m_parsedMessages.push_back({ 
				currentLine, NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT, _T(""), false });
			currentLine.Empty();
			prevCh = 0;
			continue;
		}

		// CR 단독 → 줄 나눔
		if (ch == '\r')
		{
			currentLine.Trim();
			if (!currentLine.IsEmpty())
				m_parsedMessages.push_back({ 
				currentLine, NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT, _T(""), false });
			currentLine.Empty();
			prevCh = ch;
			continue;
		}

		// LF 단독 → 줄 나눔
		if (ch == '\n')
		{
			currentLine.Trim();
			if (!currentLine.IsEmpty())
				m_parsedMessages.push_back({
				currentLine, NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT, _T(""), false });
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
		m_parsedMessages.push_back({
				currentLine, NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT, _T(""), false });
	
	file.Close();
	m_staticStatus.SetWindowText(_T("파일 로드 완료"));
}

// 모든 메시지 파싱
void CNavAidstestDlg::ParseAllMessages()
{
	size_t total = m_parsedMessages.size();
	// Progress bar
	ULONGLONG currentCount = 0;
	ULONGLONG totalLines = static_cast<int>(m_parsedMessages.size());
	m_progressCtrl.SetRange(0, SHRT_MAX);
	m_progressCtrl.SetPos(0);
	for (size_t i = 0; i < m_parsedMessages.size(); i++)
	{
		CString nmeaMsg;
		int sepPos = m_parsedMessages[i].OriginalMsg.Find(_T('|'));
		if (sepPos != -1)
			nmeaMsg = m_parsedMessages[i].OriginalMsg.Mid(sepPos + 1).Trim();
		else
			nmeaMsg = m_parsedMessages[i].OriginalMsg.Trim();

		m_parsedMessages[i].result = m_parser.Parsing(nmeaMsg);
		m_parsedMessages[i].isSuccess = (m_parsedMessages[i].result != NS_SALUS_MS_APP::E_PARSING_RESULT::ePARSING_NO_RESULT);
		m_parsedMessages[i].parsedSummary = GetParsedInfoString(nmeaMsg);

		currentCount++;
		m_progressCtrl.SetPos((currentCount * SHRT_MAX) / totalLines);
	}	
}

// 페이지 별로 리스트 출력
void CNavAidstestDlg::UpdateListForCurrentPage(int pageIdx)
{
	m_listResult.DeleteAllItems();

	int startIdx = pageIdx * ITEMS_PER_BLOCK_PAGE;
	int endIdx = min(startIdx + ITEMS_PER_BLOCK_PAGE, (int)m_parsedMessages.size());

	int row = 0;
	for (int i = startIdx; i < endIdx; ++i)
	{
		const CString& block = m_parsedMessages[i].parsedSummary;

		// parsedSummary를 \n 기준으로 분할하여 여러 행으로 삽입
		int idx = 0;
		CString line;
		while (AfxExtractSubString(line, block, idx, _T('\n')))
		{
			line.TrimRight(); // \r 제거
			m_listResult.InsertItem(row, line);
			m_listResult.SetItemData(row, (DWORD_PTR)i); // 더블클릭 시 원문 찾기용
			++row;
			++idx;
		}

		// 메시지 사이에 빈 줄 하나
		m_listResult.InsertItem(row, _T(""));
		m_listResult.SetItemData(row, (DWORD_PTR)i);
		++row;
	}

	CString pageInfo;
	int totalPage = (m_parsedMessages.size() + ITEMS_PER_BLOCK_PAGE - 1) / ITEMS_PER_BLOCK_PAGE;
	pageInfo.Format(_T("%d / %d 페이지"), pageIdx + 1, totalPage);
	m_staticPageInfo.SetWindowText(pageInfo);
}


// 파싱 로그 
void CNavAidstestDlg::SaveParsingLogsToFile()
{
	CStdioFile successFile(_T(".\\Parsing_Success.log"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	CStdioFile failFile(_T(".\\Parsing_Fail.log"), CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	size_t i;
	for (i = 0; i < m_parsedMessages.size(); i++)
	{
		if (m_parsedMessages[i].isSuccess)
			successFile.WriteString(m_parsedMessages[i].OriginalMsg + _T("\n"));
		else
			failFile.WriteString(m_parsedMessages[i].OriginalMsg + _T("\n"));
	}
	successFile.Close();
	failFile.Close();
}


void CNavAidstestDlg::OnDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItem = m_listResult.GetNextItem(-1, LVNI_SELECTED);
	if (nItem >= 0 && nItem < (int)m_parsedMessages.size())
	{
		AfxMessageBox(m_parsedMessages[nItem].parsedSummary);
	}
	*pResult = 0;
}


// 파싱 결과를 문자열로 변환하는 새 함수 (블록 포맷, 성공여부 출력 제거)
CString CNavAidstestDlg::GetParsedInfoString(const CString& strMsg)
{
	using namespace NS_SALUS_MS_APP;

	CString resultText, str;

	CNMEAParser parser;
	E_PARSING_RESULT result = parser.Parsing(strMsg);

	switch (result)
	{
		// --- NMEA 주요 메시지 ---
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_GGA:
	{
		T_NMEA_GGA* p = parser.GetNMEA_GGA();
		if (p)
		{
			str.Format(_T("UTC: %02d:%02d:%06.3f\r\n"), p->m_wHour, p->m_wMinute, p->m_dSecond); resultText += str;
			str.Format(_T("위도: %d도 %.5f분 (%s)\r\n"), abs(p->m_sLatDegree), p->m_dLatMinute, (p->m_sLatDegree < 0 ? _T("S") : _T("N"))); resultText += str;
			str.Format(_T("경도: %d도 %.5f분 (%s)\r\n"), abs(p->m_sLonDegree), p->m_dLonMinute, (p->m_sLonDegree < 0 ? _T("W") : _T("E"))); resultText += str;
			str.Format(_T("품질: %d\r\n"), p->m_wGPSQuality); resultText += str;
			str.Format(_T("고도: %.2f\r\n"), p->m_dAltitude); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_RMC:
	{
		T_NMEA_RMC* p = parser.GetNMEA_RMC();
		if (p)
		{
			str.Format(_T("UTC: %02d:%02d:%06.3f\r\n"), p->m_wHour, p->m_wMinute, p->m_dSecond); resultText += str;
			str.Format(_T("위도: %d도 %.4f분 (%s)\r\n"), abs(p->m_sLatDegree), p->m_dLatMinute, (p->m_sLatDegree < 0 ? _T("S") : _T("N"))); resultText += str;
			str.Format(_T("경도: %d도 %.4f분 (%s)\r\n"), abs(p->m_sLonDegree), p->m_dLonMinute, (p->m_sLonDegree < 0 ? _T("W") : _T("E"))); resultText += str;
			str.Format(_T("속도(knots): %.2f\r\n"), p->m_dSpeed); resultText += str;
			str.Format(_T("코스: %.2f\r\n"), p->m_dTrackTrue); resultText += str;
			str.Format(_T("날짜: %02d%02d%02d\r\n"), p->m_wDay, p->m_wMonth, p->m_wYear); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_GLL:
	{
		T_NMEA_GLL* p = parser.GetNMEA_GLL();
		if (p)
		{
			str.Format(_T("UTC: %02d:%02d:%06.3f\r\n"), p->m_wHour, p->m_wMinute, p->m_dSecond); resultText += str;
			str.Format(_T("위도: %d도 %.4f분 (%s)\r\n"), abs(p->m_sLatDegree), p->m_dLatMinute, (p->m_sLatDegree < 0 ? _T("S") : _T("N"))); resultText += str;
			str.Format(_T("경도: %d도 %.4f분 (%s)\r\n"), abs(p->m_sLonDegree), p->m_dLonMinute, (p->m_sLonDegree < 0 ? _T("W") : _T("E"))); resultText += str;
		}
		break;
	}
	// GSA 미구현 (필요 시 주석 해제 후 상세 필드 추가)
	/*
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_GSA:
	{
		T_NMEA_GSA* p = parser.GetNMEA_GSA();
		if (p)
		{
			str.Format(_T("모드: %c\r\n"), p->m_cMode); resultText += str;
			str.Format(_T("수신위성수: %d\r\n"), p->m_nSVCount); resultText += str;
			str.Format(_T("PDOP: %.2f, HDOP: %.2f, VDOP: %.2f\r\n"), p->m_dPDOP, p->m_dHDOP, p->m_dVDOP); resultText += str;
		}
		break;
	}
	*/
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_GSV:
	{
		T_NMEA_GSV* p = parser.GetNMEA_GSV();
		if (p)
		{
			str.Format(_T("위성 수: %d\r\n"), p->m_wNumSatellite); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_HDT:
	{
		T_NMEA_HDT* p = parser.GetNMEA_HDT();
		if (p)
		{
			str.Format(_T("진북방위: %.2f\r\n"), p->fHeading); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_NMEA_VTG:
	{
		T_NMEA_VTG* p = parser.GetNMEA_VTG();
		if (p)
		{
			str.Format(_T("COG: %.2f\r\n"), p->m_dCourseTrue); resultText += str;
			str.Format(_T("SOG: %.2f\r\n"), p->m_dSpeedKnots); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_EHS_HEADING:
	{
		T_NMEA_CAN* p = parser.GetNMEA_CAN();
		if (p)
		{
			str.Format(_T("자북방위: %.2f\r\n"), p->m_dHeading); resultText += str;
			str.Format(_T("보정: %.2f\r\n"), p->m_dDeviation); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_EHS_TURNRATE:
	{
		T_NMEA_CAN* p = parser.GetNMEA_CAN();
		if (p)
		{
			str.Format(_T("ROT: %.2f\r\n"), p->m_dTurnRate); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_EHS_ATTITUDE:
	{
		T_NMEA_CAN* p = parser.GetNMEA_CAN();
		if (p)
		{
			str.Format(_T("Yaw: %.2f, Pitch: %.2f, Roll: %.2f\r\n"), p->m_dYaw, p->m_dPitch, p->m_dRoll);
			resultText += str; // 누락 보완
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_EHS_HEAVE:
	{
		T_NMEA_CAN* p = parser.GetNMEA_CAN();
		if (p)
		{
			str.Format(_T("Heave: %.2f\r\n"), p->m_dHeave);
			resultText += str; // 누락 보완
		}
		break;
	}

	// --- AIS 메시지 ---
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1:
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE2:
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE3:
	{
		T_AIS_MSG_TYPE1_3* p = nullptr;
		if (result == E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE1) p = parser.GetAIS_TYPE1();
		if (result == E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE2) p = parser.GetAIS_TYPE2();
		if (result == E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE3) p = parser.GetAIS_TYPE3();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 1/2/3)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("상태: %u\r\n"), p->m_ucStatus); resultText += str;
			str.Format(_T("ROT: %.2f (TurnRate: %.2f)\r\n"), p->m_fROT, p->m_cTurnRate); resultText += str;
			str.Format(_T("SOG: %.2f knots\r\n"), p->m_fSOG); resultText += str;
			str.Format(_T("위도: %.5f\r\n"), p->m_dLat); resultText += str;
			str.Format(_T("경도: %.5f\r\n"), p->m_dLon); resultText += str;
			str.Format(_T("COG: %.2f\r\n"), p->m_fCOG); resultText += str;
			str.Format(_T("Heading: %u\r\n"), p->m_usHeading); resultText += str;
			str.Format(_T("TimeStamp: %u\r\n"), p->m_ucTimeStamp); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE5:
	{
		T_AIS_MSG_TYPE5* p = parser.GetAIS_TYPE5();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 5 - Static)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("선박명: %s\r\n"), p->m_szShipName); resultText += str;
			str.Format(_T("호출부호: %s\r\n"), p->m_szCallSign); resultText += str;
			str.Format(_T("선박 종류: %u\r\n"), p->m_ucShipType); resultText += str;
			str.Format(_T("길이: %u m (Bow:%u Stern:%u)\r\n"), p->m_usBowDimension + p->m_usSternDimension, p->m_usBowDimension, p->m_usSternDimension); resultText += str;
			str.Format(_T("폭: %u m (Port:%u Starboard:%u)\r\n"), p->m_ucPortDimension + p->m_ucStarboardDimension, p->m_ucPortDimension, p->m_ucStarboardDimension); resultText += str;
			str.Format(_T("Draught: %.1f m\r\n"), p->m_fDraught); resultText += str;
		}
		break;
	}
	// ePARSING_DONE_AIS_TYPE14 (안전 메시지) 미구현 — 필요 시 추가
	/*
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE14:
	{
		T_AIS_MSG_TYPE14* p = parser.GetAIS_TYPE14();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 14 - Safety-Related)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("안전 메시지: %s\r\n"), p->m_szText); resultText += str;
		}
		break;
	}
	*/
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE18:
	{
		T_AIS_MSG_TYPE18* p = parser.GetAIS_TYPE18();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 18 - Class B 동적)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("SOG: %.2f knots\r\n"), p->m_fSOG); resultText += str;
			str.Format(_T("위도: %.5f\r\n"), p->m_dLat); resultText += str;
			str.Format(_T("경도: %.5f\r\n"), p->m_dLon); resultText += str;
			str.Format(_T("COG: %.2f\r\n"), p->m_fCOG); resultText += str;
			str.Format(_T("Heading: %u\r\n"), p->m_usHeading); resultText += str;
			str.Format(_T("TimeStamp: %u\r\n"), p->m_ucTimeStamp); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE19:
	{
		T_AIS_MSG_TYPE19* p = parser.GetAIS_TYPE19();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 19 - Extended Class B Position)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("SOG: %.2f knots\r\n"), p->m_fSOG); resultText += str;
			str.Format(_T("위도: %.5f\r\n"), p->m_dLat); resultText += str;
			str.Format(_T("경도: %.5f\r\n"), p->m_dLon); resultText += str;
			str.Format(_T("COG: %.2f\r\n"), p->m_fCOG); resultText += str;
			str.Format(_T("Heading: %u\r\n"), p->m_usHeading); resultText += str;
			str.Format(_T("선박명: %s\r\n"), p->m_szShipName); resultText += str;
			str.Format(_T("선박 종류: %u\r\n"), p->m_ucShipType); resultText += str;
		}
		break;
	}
	case E_PARSING_RESULT::ePARSING_DONE_AIS_TYPE24:
	{
		T_AIS_MSG_TYPE24* p = parser.GetAIS_TYPE24();
		if (p)
		{
			resultText += _T("AIS 메시지 (Type 24 - Static)\r\n");
			str.Format(_T("MMSI: %u\r\n"), p->m_unMMSI); resultText += str;
			str.Format(_T("선박명: %s\r\n"), p->m_tPartA.m_szShipName); resultText += str;
			str.Format(_T("호출부호: %s\r\n"), p->m_tPartB1.m_szCallSign); resultText += str;
			str.Format(_T("선박 종류: %u\r\n"), p->m_tPartB1.m_ucShipType); resultText += str;
			str.Format(_T("길이: %u m (Bow:%u Stern:%u)\r\n"),
				p->m_tPartB1.m_usBowDimension + p->m_tPartB1.m_usSternDimension,
				p->m_tPartB1.m_usBowDimension, p->m_tPartB1.m_usSternDimension); resultText += str;
			str.Format(_T("폭: %u m (Port:%u Starboard:%u)\r\n"),
				p->m_tPartB1.m_ucPortDimension + p->m_tPartB1.m_ucStarboardDimension,
				p->m_tPartB1.m_ucPortDimension, p->m_tPartB1.m_ucStarboardDimension); resultText += str;
		}
		break;
	}
	// AIVDO
	case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE1:
	{
		T_AIS_MSG_TYPEAIVDO1* p = m_parser.GetAIS_TYPEAIVDO1();
		if (p)
		{
			resultText += _T("AIVDO 메시지 (Type 1 - Own Ship Dynamic)\r\n");

			str.Format(_T("bPosAvail: %s\r\n"), p->bPosAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("Lat: %.5f\r\n"), p->Lat); resultText += str;
			str.Format(_T("Long: %.5f\r\n"), p->Long); resultText += str;

			str.Format(_T("bSogAvail: %s\r\n"), p->bSogAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("SOG: %.2f m/s\r\n"), p->SOG); resultText += str;

			str.Format(_T("bCogAvail: %s\r\n"), p->bCogAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("COG: %.2f\r\n"), p->COG); resultText += str;

			str.Format(_T("bRotAvail: %s\r\n"), p->bRotAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("ROT: %.2f\r\n"), p->ROT); resultText += str;

			str.Format(_T("bHeadingAvail: %s\r\n"), p->bHeadingAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("HDT: %.2f\r\n"), p->HDT); resultText += str;
		}
		break;
	}

	case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE18:
	{
		T_AIS_MSG_TYPEAIVDO18* p = m_parser.GetAIS_TYPEAIVDO18();
		if (p)
		{
			resultText += _T("AIVDO 메시지 (Type 18 - Own Ship Class B)\r\n");

			str.Format(_T("bPosAvail: %s\r\n"), p->bPosAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("Lat: %.5f\r\n"), p->Lat); resultText += str;
			str.Format(_T("Long: %.5f\r\n"), p->Long); resultText += str;

			str.Format(_T("bSogAvail: %s\r\n"), p->bSogAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("SOG: %.2f m/s\r\n"), p->SOG); resultText += str;

			str.Format(_T("bCogAvail: %s\r\n"), p->bCogAvail ? _T("true") : _T("false")); resultText += str;
				str.Format(_T("COG: %.2f\r\n"), p->COG); resultText += str;

			str.Format(_T("bHeadingAvail: %s\r\n"), p->bHeadingAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("HDT: %.2f\r\n"), p->HDT); resultText += str;
		}
		break;
	}

	case E_PARSING_RESULT::ePARSING_DONE_AIVDO_TYPE19:
	{
		T_AIS_MSG_TYPEAIVDO19* p = m_parser.GetAIS_TYPEAIVDO19();
		if (p)
		{
			resultText += _T("AIVDO 메시지 (Type 19 - Own Ship Ext. Class B)\r\n");

			str.Format(_T("bPosAvail: %s\r\n"), p->bPosAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("Lat: %.5f\r\n"), p->Lat); resultText += str;
			str.Format(_T("Long: %.5f\r\n"), p->Long); resultText += str;

			str.Format(_T("bSogAvail: %s\r\n"), p->bSogAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("SOG: %.2f m/s\r\n"), p->SOG); resultText += str;

			str.Format(_T("bCogAvail: %s\r\n"), p->bCogAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("COG: %.2f\r\n"), p->COG); resultText += str;

			str.Format(_T("bHeadingAvail: %s\r\n"), p->bHeadingAvail ? _T("true") : _T("false")); resultText += str;
			str.Format(_T("HDT: %.2f\r\n"), p->HDT); resultText += str;
		}
		break;
	}

	// --- 미지원/기타 ---
	default:
	{
		if (!strMsg.IsEmpty())
		{
			CString failLog;
			resultText += _T("지원하지 않는 메시지 타입입니다.\r\n");
			failLog.Format(_T("%s\n지원하지 않는 메시지 타입입니다.\n"), strMsg);
			m_failedLogs.push_back(failLog);
		}
		break;
	}
	}

	// ==== 최종 포맷 ====
	CString boxResult;

	// 섹션 제목은 ** 로만 표시하고, 구분선 라인은 쓰지 않음
	boxResult += _T("** 메시지\r\n");
	boxResult += strMsg + _T("\r\n\r\n");  // 원문 뒤 빈 줄

	// 모든 필드 요약 (각 필드는 이미 resultText에 \r\n로 개행됨)
	boxResult += resultText;

	// 마지막에 굳이 별 줄/구분선 넣지 않음. 필요하면 빈 줄 하나 추가
	// boxResult += _T("\r\n");

	return boxResult;
}

