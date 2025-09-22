
#pragma once
#include <afxsock.h>

// Forward declaration to avoid circular dependency
class CMFCChatDlg;

// 통신 데이터 종류를 정의하는 열거형
enum MessageType
{
    MSG_TYPE_TEXT,      // 일반 텍스트 메시지
    MSG_TYPE_NMEA,      // NMEA 메시지
    MSG_TYPE_FILE_INFO, // 파일 정보 (이름, 크기)
    MSG_TYPE_FILE_DATA, // 파일 실제 데이터
    MSG_TYPE_FILE_END,  // 파일 전송 완료
};

// 모든 패킷의 맨 앞에 붙을 헤더 구조체
struct PacketHeader
{
    MessageType type;   // 메시지 종류
    long dataSize;      // 뒤따라올 데이터의 크기
};

class CMySocket : public CAsyncSocket
{
public:
    CMySocket(CMFCChatDlg* pDlg);
    virtual ~CMySocket();

    CMFCChatDlg* m_pDlg; // 다이얼로그를 가리키는 포인터

protected:
    virtual void OnAccept(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
};
