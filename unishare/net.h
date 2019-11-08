#pragma once

#include "unishare.h"
#include <mbedtls/net_sockets.h>
#include <vector>

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
			mbedtls_net_context context;
			bool initialised;
			char* host;
			char* port;
		public:
			Socket() : context(), initialised(false), host(const_cast<char*>("0.0.0.0")), port(const_cast < char*>("80")) 
			{
				mbedtls_net_init(&context); 
			}
			~Socket() { mbedtls_net_free(&context); }

			int setBlocking(bool block)
			{
				if (block)
					return mbedtls_net_set_block(&context);

				return mbedtls_net_set_nonblock(&context);
			}
		};

		class ClientSocket;

		typedef ClientSocket ClientProxySocket;

		class ServerSocket : public Socket
		{
			std::vector<ClientProxySocket*> clients;
		public:
			ServerSocket() = default;
			~ServerSocket() = default;

			int listen(const char* host, const char* port, Protocol protocol);
			int accept(ClientProxySocket& peer);
			int send(ClientProxySocket& peer, const ByteArray& message);
			int recieve(ClientProxySocket& peer, ByteArray& message);
		};

		class ClientSocket : public Socket
		{
		public:
			ClientSocket() = default;
			~ClientSocket() { disconnect(); }

			// connect for client connecting to server
			int connect(const char* host, const char* port, Protocol protocol);
			// serverside proxy connect
			int proxyConnect(mbedtls_net_context context, char* const ip, char* const port);
			int disconnect();
			int send(const ByteArray& message);
			int recieve(ByteArray& message);
		};
	}
}