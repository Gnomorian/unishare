#include "net.h"
#include "errors.h"

using namespace unishare::net;

int ServerSocket::listen(const char* host, const char* port, Protocol protocol)
{
	host = const_cast<char*>(host);
	port = const_cast<char*>(port);
	const auto status = listener.listen(std::stoi(port));
	if(status != sf::Socket::Status::Done)
		return ADD_ERROR_DETAILS(US_NotImplemented);
	return US_OK;
}

int ServerSocket::accept(ClientProxySocket& peer)
{
	sf::TcpSocket socket;
	listener.accept();
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