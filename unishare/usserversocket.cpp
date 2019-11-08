#include "net.h"
#include "errors.h"

using namespace unishare::net;

int ServerSocket::listen(const char* host, const char* port, Protocol protocol)
{
	this->host = const_cast<char*>(host);
	this->port = const_cast<char*>(port);

	int result = mbedtls_net_bind(&context, nullptr, port, Protocol::TCP);
	CHECK_RESULT;
	return US_OK;
}

int ServerSocket::accept(ClientProxySocket& peer)
{
	ClientSocket client;
	mbedtls_net_accept(context, )

	return ADD_ERROR_DETAILS(US_NotImplemented);
}

int ServerSocket::send(ClientProxySocket& peer, const ByteArray& message)
{
	return ADD_ERROR_DETAILS(US_NotImplemented);
}

int ServerSocket::recieve(ClientProxySocket& peer, ByteArray& message)
{
	return ADD_ERROR_DETAILS(US_NotImplemented);
}