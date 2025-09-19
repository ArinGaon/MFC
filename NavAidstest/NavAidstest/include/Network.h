#include <WinSock2.h>
#include <WS2tcpip.h>
#include <system_error>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#pragma once

#include "STXDef.h"

class UDPSocket2
{
private:
	WSAData wsa;
	SOCKET sock;
	
public:
	bool bConnect;
	bool bBind;

public:
	UDPSocket2() 
	{
		bConnect = bBind = false;
		sock = INVALID_SOCKET;
	}
	~UDPSocket2()
	{
		if (sock != INVALID_SOCKET)
			closesocket(sock);
		WSACleanup();
	}

	STX_RLT Connect()
	{
		STX_RLT rlt = STX_ERROR_NETWORK_DISCONNECT;

		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			return rlt;

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == INVALID_SOCKET) {
			return rlt;
		}

		bConnect = true;
		return STX_SUCCESS;
	}

	STX_RLT ConnectAndBind(unsigned short port)
	{
		int ret = 0;
		STX_RLT rlt = STX_ERROR_NETWORK_DISCONNECT;

		if (Connect() == rlt)
			return rlt;
		
		struct sockaddr_in serv_addr;
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);

		ret = bind(sock, reinterpret_cast<SOCKADDR *>(&serv_addr), sizeof(serv_addr));
		if (ret < 0)
			return rlt;
		
		bBind = true;
		return STX_SUCCESS;
	}

	STX_RLT RecvSocket(sockaddr_in* from, char* buffer, int buffsize, int& recvlen, int flags = 0)
	{
		int size = sizeof(sockaddr_in);
		memset(from, 0, sizeof(sockaddr_in));

		int ret = recvfrom(sock, buffer, buffsize, flags, reinterpret_cast<SOCKADDR *>(from), &size);
		if (ret < 0)
			return STX_ERROR_NETWORK_RECV;

		buffer[ret] = 0;
		recvlen = ret;

		return STX_SUCCESS;
	}


	STX_RLT SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0)
	{
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = inet_addr(address.c_str());
		add.sin_port = htons(port);
		int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
		if (ret < 0)
			return STX_ERROR_NETWORK_SEND;

		return STX_SUCCESS;
	}

};