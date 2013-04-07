// test2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <errno.h>

#include "ServerOptions.h"
#include "TestServer.h"

#pragma comment(lib, "Ws2_32.lib")

#define MAXLINE 4096
#define LISTENQ 1024

#define LOG_ERROR(sMsg) std::cout << "ERROR|" << sMsg << std::endl;
#define LOG_DEBUG(sMsg) std::cout << "DEBUG|" << sMsg << std::endl;
#define  LOG_INFO(sMsg) std::cout << " INFO|" << sMsg << std::endl;

void ExitWithError (const std::string &sError)
{
	LOG_ERROR (sError);
	exit (EXIT_FAILURE);
}

void SH_WSAStartup (WORD wVersionRequested, LPWSADATA lpWSAData)
{
	int iRes = WSAStartup (wVersionRequested, lpWSAData);

	if ( iRes )
		ExitWithError ("WSAStartup error");
	
	LOG_DEBUG ("WSAStartup");

}

SOCKET SH_Socket (int af, int type, int protocol)
{
	SOCKET s = socket (af, type, protocol);

	if ( s == INVALID_SOCKET )
		ExitWithError ("Socket error");

	LOG_DEBUG ("Socket");

	return s;
}

void SH_Bind (SOCKET s, const sockaddr *name, int namelen)
{
	int iRes = bind (s, name, namelen);

	if ( iRes < 0 )
		ExitWithError ("Bind error");

	LOG_DEBUG ("Bind");
}

void SH_Listen (SOCKET s, int backlog)
{
	int iRes = listen (s, backlog);

	if ( iRes < 0 ) 
		ExitWithError ("Listen error");

	LOG_DEBUG ("Listen");
}

SOCKET SH_Accept (SOCKET s, sockaddr *addr, int *addrlen)
{
	SOCKET sRes = accept(s, addr, addrlen);
	
	if ( sRes == INVALID_SOCKET )
			ExitWithError ("Accept error");

	LOG_DEBUG ("Accept");

	return sRes;
}

int SH_Send (SOCKET s, const char *buf, int len, int flags)
{
	int iRes = send(s, buf, len, flags);
	
	if ( iRes < 0 )
		ExitWithError ("Send error");

	LOG_INFO ("Sent " + std::to_string (iRes) + " bytes");

	return iRes;
}


int _tmain(int argc, _TCHAR* argv[])
{
	const std::string sOptoponFile = "options.cfg";
	const std::string sServerAddress = "127.0.0.1";
	const unsigned int nServerPort = 7777;

	ServerOptions options;
	options.SetServerAddress (sServerAddress);
	options.SetServerPort    (nServerPort);
/*
	try
	{
		options.ReadFromFile (sOptoponFile);
	}
	catch (const ReadConfigException &ex)
	{
		return EXIT_FAILURE;
	}
*/
	TestServer server (options);
	server.Start ();

	for (;;)
	{
		char ch;
		std::cin >> ch;

		if ( ch == 'q' || ch == 'Q')
			break;
	}

	server.Stop ();

	//--------------------------
/*
	sh::Log::SetLogLevel (sh::LOG_LEVEL_DEBUG);
	sh::Log::SaveToFile  ("log2.txt");

	SOCKET listenSocket, connSocket;
	sockaddr_in servaddr;
	char buf[MAXLINE];
	WSADATA wsaData = {0};

	SH_WSAStartup (MAKEWORD(2, 2), &wsaData);

	listenSocket = SH_Socket (AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	SH_Bind   (listenSocket, (sockaddr*) &servaddr, sizeof(servaddr));
	SH_Listen (listenSocket, LISTENQ);

	for (;;)
	{
		connSocket = SH_Accept (listenSocket, NULL, NULL);

		time_t ticks = time(NULL);
		tm today;

		_localtime64_s(&today, &ticks);
		strftime(buf, sizeof(buf), "Today is %A, day %d of %B in the year %Y.\n", &today);

		SH_Send (connSocket, buf, strlen(buf), 0);		

		closesocket (connSocket);
	}
	*/
	return EXIT_SUCCESS;
}

