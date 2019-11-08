#include "net.h"
#include "errors.h"

using namespace unishare::net;

int ClientSocket::connect(const char* host, const char* port, Protocol protocol)
{
	this->host = const_cast<char*>(host);
	this->port = const_cast<char*>(port);

	int result = mbedtls_net_connect(&context, host, port, MBEDTLS_NET_PROTO_TCP);
	CHECK_RESULT;

	return US_OK;
}

int ClientSocket::proxyConnect(mbedtls_net_context context, char* const ip, char* const port)
{
	this->context = context;
	this->host = ip;
	this->port = port;
}

int ClientSocket::disconnect()
{
	mbedtls_net_free(&context);
	return US_OK;
}

int ClientSocket::send(const ByteArray& message)
{
	int result = mbedtls_net_send(&context, message.c_str(), message.length());
	if (result < US_OK)
		return ADD_ERROR_DETAILS(result);
	return US_OK;
}

int ClientSocket::recieve(ByteArray& message)
{
	int length = 0;
	BYTE buffer[512] = { 0 };
	auto maxSize = sizeof buffer;
	message.clear();
	do
	{
		length = mbedtls_net_recv(&context, buffer, maxSize);
		if (length < 0)
			return ADD_ERROR_DETAILS(length);

		message.append(buffer, length);
	} 
	while (length == maxSize);
	return US_OK;
}