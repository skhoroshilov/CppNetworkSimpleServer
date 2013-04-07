#include "stdafx.h"
#include "ServerOptions.h"
#include "TestServer.h"
#include <time.h>

TestServer::TestServer (const ServerOptions & options)
	: m_options     (options),
	  m_listenSocket (INVALID_SOCKET),
	  m_connSocket   (INVALID_SOCKET)
{
}

TestServer::~TestServer ()
{
}

void TestServer::Init ()
{
	int iRes = WSAStartup (MAKEWORD(2, 2), &m_wsaData);

	if ( iRes )
		throw std::runtime_error ("WSAStartup error");
}

void TestServer::Start ()
{
	Init ();

	m_listenSocket = socket (AF_INET, SOCK_STREAM, 0);

	if ( m_listenSocket == INVALID_SOCKET )
		throw std::runtime_error ("Listen socket error");

	sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons ( m_options.GetServerPort() );

	int iRes = bind (m_listenSocket, (sockaddr*) &servaddr, sizeof(servaddr));

	if ( iRes < 0 )
		throw std::runtime_error ("Socket bind error");

	iRes = listen (m_listenSocket, LISTENQ);

	if ( iRes < 0 )
		throw std::runtime_error ("Socket listen error");

	char buf[MSG_BUF_SIZE];

	for (;;)
	{
		m_connSocket = accept (m_listenSocket, NULL, NULL);

		if ( m_connSocket == INVALID_SOCKET )
			throw std::runtime_error ("Socket accept error");

		time_t ticks = time (NULL);
		tm today;

		_localtime64_s(&today, &ticks);
		strftime(buf, sizeof(buf), "Today is %A, day %d of %B in the year %Y.\n", &today);

		iRes = send (m_connSocket, buf, strlen(buf), 0);

		if ( iRes < 0 )
			throw std::runtime_error ("Socket send error");

		closesocket (m_connSocket);
	}
}

void TestServer::Stop ()
{
	;
}

const ServerOptions TestServer::GetOptions () const
{
	return m_options;
}
