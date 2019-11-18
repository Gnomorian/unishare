#include "net.hpp"

/*
	convert the mbedtls error to unishare error
*/
inline USError convertedError(int result)
{
	switch (result)
	{
	case 0:
		return OK;
	default:
		return (USError)result;
	}
}

USError MbedSocket::init()
{
	mbedtls_net_init(&context);
	return OK;
}

USError MbedSocket::free()
{
	mbedtls_net_free(&context);
	return OK;
}

USError MbedSocket::connect()
{
	int result = mbedtls_net_connect(&context, host.c_str(), port.c_str(), MBEDTLS_NET_PROTO_TCP);
	return convertedError(result);
}
USError MbedSocket::bind()
{
	int result = mbedtls_net_bind(&context, nullptr, port.c_str(), MBEDTLS_NET_PROTO_TCP);
	return convertedError(result);
}
USError MbedSocket::send(const std::string& data)
{
	int result = mbedtls_net_poll(&context, MBEDTLS_NET_POLL_WRITE, 1000u);
	if (result & ~MBEDTLS_NET_POLL_WRITE)
		return Timeout;
	result = mbedtls_net_send(&context, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());

	// only less than 0 is an error
	return convertedError(result > 0 ? 0 : result);
}
USError MbedSocket::recieve(std::string& data)
{
	unsigned char buffer[4096] = { 0 };
	int result = 0;
	do 
	{
		if (result > 0)
		{
			data.append(reinterpret_cast<char*>(buffer), result);
			if (result < sizeof buffer / sizeof(char))
				break;
		}
		result = mbedtls_net_poll(&context, MBEDTLS_NET_POLL_READ, 1000u);
		if (result & ~MBEDTLS_NET_POLL_READ)
			return Timeout;
		result = mbedtls_net_recv(&context, buffer, sizeof buffer);
	} 
	while (result > 0);

	// only less than 0 is an error
	return convertedError(result > 0 ? OK : result);
}
USError MbedSocket::accpet(SocketProxy& remoteSocket)
{
	char ip[100] = { 0 };
	size_t iplen = 0;
	int result = mbedtls_net_accept(
		&context,															// my context
		static_cast<mbedtls_net_context*>(remoteSocket.getNativeSocket()),	// context to accpet
		ip,																	// what their ip will be
		sizeof ip,															
		&iplen																// length of ip
	);

	if (result == OK)
	{
		std::string host;
		host.assign(ip, iplen);
		dynamic_cast<MbedSocket*>(&remoteSocket)->set(host, this->port);
	}

	return convertedError(result);
}