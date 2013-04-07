
#ifndef TEST_SERVER
#define TEST_SERVER

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <errno.h>

#include <string>

#define MSG_BUF_SIZE 1024
#define LISTENQ 1024

//-----------------------------------------------------------------------------

class TestServer
{
public:
	TestServer  (const ServerOptions & options);
	~TestServer ();

	void Start ();
	void Stop ();

	const ServerOptions GetOptions () const;
private:
	const ServerOptions & m_options;  

	SOCKET   m_listenSocket,
	         m_connSocket;

	WSAData   m_wsaData;

	void Init ();
};

//-----------------------------------------------------------------------------

#endif
