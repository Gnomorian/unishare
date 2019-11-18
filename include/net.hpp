#pragma once

#define UNISHARE_COMMON
#include "unishare.hpp"
#include <string>
#include <mbedtls/net_sockets.h>

class SocketBase;
class MbedSocket;

// the default socket implementation to use
typedef MbedSocket Socket;

typedef SocketBase SocketProxy;

class DllExport SocketBase
{
protected:
	std::string host;
	std::string port;
	bool blocking;
public:
	virtual USError init()								= 0;
	virtual USError free()								= 0;
	virtual USError connect()							= 0;
	virtual USError bind()								= 0;
	virtual USError send(const std::string& data)		= 0;
	virtual USError recieve(std::string& data)			= 0;
	virtual USError accpet(SocketProxy& remoteSocket)	= 0;
	virtual void* getNativeSocket()						= 0;

	void	set(const std::string& host, const std::string& port)
	{
		this->host = host;
		this->port = port;
	}
};

class DllExport MbedSocket : public SocketBase
{	
protected:
	mbedtls_net_context context;
public:
	USError init() override;
	USError free() override;
	USError connect() override;
	USError bind() override;
	USError send(const std::string& data) override;
	USError recieve(std::string& data) override;
	USError accpet(SocketProxy& remoteSocket) override;

	void*	getNativeSocket() override { return &context; }
};