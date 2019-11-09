#pragma once

#include "unishare.h"
#include <vector>
#include "errors.h"

#include <SFML/Network.hpp>


namespace unishare
{
	namespace net
	{

		enum Protocol
		{
			TCP = MBEDTLS_NET_PROTO_TCP,
			UDP = MBEDTLS_NET_PROTO_UDP
		};

		class Socket
		{
		protected:
			char* host;
			char* port;
			sf::TcpSocket* socket;
		public:
			Socket() : host(const_cast<char*>("0.0.0.0")), port(const_cast < char*>("80")), socket(nullptr)
			{

			}
			~Socket() { disconnect(); }

			sf::TcpSocket* getImplementation() { return socket; }

			int disconnect()
			{
				socket->disconnect();
				return US_OK;
			}

			int setBlocking(bool block)
			{
				socket->setBlocking(block);
				return US_OK;
			}
		};

		class ClientSocket : public Socket
		{
			
		public:
			ClientSocket() = default;
			~ClientSocket() { disconnect(); }

			// connect for client connecting to server
			int connect(const char* host, const char* port, Protocol protocol);
			// serverside proxy connect
			int send(const ByteArray& message);
			int recieve(ByteArray& message);
		};

		typedef ClientSocket ClientProxySocket;

		class ServerSocket : public Socket
		{
			sf::TcpListener listener;
			std::vector<ClientProxySocket*> clients;
		public:
			ServerSocket() = default;
			~ServerSocket() = default;

			int listen(const char* host, const char* port, Protocol protocol);
			int accept(ClientProxySocket& peer);
			int send(ClientProxySocket& peer, const ByteArray& message);
			int recieve(ClientProxySocket& peer, ByteArray& message);
		};
	}
}