
#ifndef SERVER_OPTIONS
#define SERVER_OPTIONS

#include <string>
#include <exception>

class ReadConfigException : std::runtime_error
{
	ReadConfigException (const std::string & msg)
		: std::runtime_error (msg)
	{
	}
};

class ServerOptions
{
public:
	ServerOptions ();
	virtual ~ServerOptions ();

	void SetServerAddress (const std::string & serverAddress);
	const std::string GetServerAddress () const;

	void SetServerPort (const unsigned int serverPort);
	const unsigned int GetServerPort () const;

	void ReadFromFile (const std::string & sFileName);

private:
	std::string m_serverAddrss;
	unsigned int m_serverPort;
};

#endif	// SERVER_OPTIONS
