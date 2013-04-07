#include "stdafx.h"
#include "ServerOptions.h"


ServerOptions::ServerOptions ()
{
}


ServerOptions::~ServerOptions ()
{
}

void ServerOptions::SetServerAddress (const std::string & serverAddress)
{
	m_serverAddrss = serverAddress;
}

const std::string ServerOptions::GetServerAddress () const
{
	return m_serverAddrss;
}

void ServerOptions::SetServerPort (const unsigned int serverPort)
{
	m_serverPort = serverPort;
}
	
const unsigned int ServerOptions::GetServerPort () const
{
	return m_serverPort;
}

void ReadFromFile (const std::string & sFileName)
{

}
