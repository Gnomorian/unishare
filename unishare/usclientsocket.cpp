#include "net.h"
#include "errors.h"

using namespace unishare::net;

int ClientSocket::connect(const char* host, const char* port, Protocol protocol)
{
	return ADD_ERROR_DETAILS(US_NotImplemented);
}

int ClientSocket::send(const ByteArray& message)
{
	sf::Packet packet;
	packet.append(message.c_str(), message.length() * sizeof BYTE);
	const auto result = socket->send(packet);
	if(result != sf::Socket::Status::Done)
		return ADD_ERROR_DETAILS(SendFailed);
	return US_OK;
}

int ClientSocket::recieve(ByteArray& message)
{
	sf::Packet packet;
	auto result = socket->receive(packet);
	if(result != sf::Socket::Status::Done)
		return ADD_ERROR_DETAILS(RecieveFailed);
	return US_OK;
}