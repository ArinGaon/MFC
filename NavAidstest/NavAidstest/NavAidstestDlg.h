#include <vector>
// NavAidstestDlg.h: 헤더 파일
#include "include/DataTypeDef.h"

#include "SerialBase.h"
#include "SerialCAN.h"
#include "SerialNMEA.h"
#include "SerialMsgMngr.h"
#include "NMEAParser.h"
#include "NMEAUtils.h"
#pragma once

struct ParsedMessageInfo {
	CString OriginalMsg;
	NS_SALUS_MS_APP::E_PARSING_RESULT result;
	CString parsedSummary;
	// 필요 시, 각 타입별 구조체, 또는 union/variant로 저장
	bool isSuccess;
};

// CNavAidstestDlg 대화 상자
class CNavAidstestDlg : public CDialogEx
{
// 생성입니다.
public:
	CNavAidstestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CEdit m_editInput;							// 메세지 입력 컨트롤
	CEdit m_editFilePath;											// 결과 리스트 컨트롤
	CListCtrl m_listResult;						// 결과 리스트 컨트롤	CEdit m_editFilePath;						// 파일 경로
	CStatic m_staticPageInfo;							// 페이지 번호 출력
	CStatic m_staticStatus;

	// 파싱 결과 관리
	std::vector<ParsedMessageInfo> m_parsedMessages;
	int m_nCurrentPage = 0;							// Page index
	int ITEMS_PER_BLOCK_PAGE = 15;				// 15개씩

	// 파서 인스턴스
	NS_SALUS_MS_APP::CNMEAParser m_parser;

	std::vector<std::vector<CString>> m_messageBlocks; // 메시지를 5개씩 저장

	// 로그 관련
	std::vector<CString> m_successLogs;
	std::vector<CString> m_failedLogs;
	// 상태 표시창 & 상태 progressbar
	CProgressCtrl m_progressCtrl;
	CStatic m_parseResult;

	CStatic m_progressInfo;
	std::queue<CString> m_messageQueue;
	//// 리얼 최종
	
	


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAVAIDSTEST_DIALOG };
#endif	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 핵심 로직
	void ReadFile(const CString& filePath);
	void ParseAllMessages();
	void UpdateListForCurrentPage(int pageIdx);
	void SaveParsingLogsToFile();
	CString GetParsedInfoString(const CString& strMsg);


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
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnStartLog();
	afx_msg void OnDblclkListResult(NMHDR* pNMHDR, LRESULT* pResult);
};

