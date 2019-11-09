#pragma once
#include <mbedtls/net_sockets.h>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>

#define ADD_ERROR_DETAILS(result) ErrorHandler::instance->addErrorCallstack(result, __FUNCTION__, __LINE__, __FILE__)
#define CHECK_RESULT if(result != US_OK) return ADD_ERROR_DETAILS(result)

enum errorCode
{
	US_OK				= 0,
	US_NotImplemented,
	US_OutOfMemory,
	// mbedtls
	SocketFailed		= MBEDTLS_ERR_NET_SOCKET_FAILED,
	PortFailed			= MBEDTLS_ERR_NET_CONNECT_FAILED,
	PortBindFailed		= MBEDTLS_ERR_NET_BIND_FAILED,
	ListenFailed		= MBEDTLS_ERR_NET_LISTEN_FAILED,
	AcceptFailed		= MBEDTLS_ERR_NET_ACCEPT_FAILED,
	RecieveFailed		= MBEDTLS_ERR_NET_RECV_FAILED,
	SendFailed			= MBEDTLS_ERR_NET_SEND_FAILED,
	ConnectonReset		= MBEDTLS_ERR_NET_CONN_RESET,
	UnknownHost			= MBEDTLS_ERR_NET_UNKNOWN_HOST,
	BufferTooSmall		= MBEDTLS_ERR_NET_BUFFER_TOO_SMALL,
	InvalidContext		= MBEDTLS_ERR_NET_INVALID_CONTEXT,
	PollFailed			= MBEDTLS_ERR_NET_POLL_FAILED,
	BadNetInput			= MBEDTLS_ERR_NET_BAD_INPUT_DATA
	// end mbedtls
};

static std::map<errorCode, std::string> suplementalErrorText;

inline void setupErrorText()
{
	suplementalErrorText[US_OK] = "No Error.";
	suplementalErrorText[US_NotImplemented] = "Method Functionality not implemented.";
	suplementalErrorText[US_OutOfMemory] = "Out of Memory";
	// mbedtls
	suplementalErrorText[SocketFailed] = "Failed to open a socket.";
	suplementalErrorText[PortFailed] = "The connection to the given server / port failed.";
	suplementalErrorText[PortBindFailed] = "Binding of the socket failed.";
	suplementalErrorText[ListenFailed] = "Could not listen on the socket.";
	suplementalErrorText[AcceptFailed] = "Could not accept the incoming connection.";
	suplementalErrorText[RecieveFailed] = "Reading information from the socket failed.";
	suplementalErrorText[SendFailed] = "Sending information through the socket failed.";
	suplementalErrorText[ConnectonReset] = "Connection was reset by peer.";
	suplementalErrorText[UnknownHost] = "Failed to get an IP address for the given hostname.";
	suplementalErrorText[BufferTooSmall] = "Buffer is too small to hold the data.";
	suplementalErrorText[InvalidContext] = "The context is invalid, eg because it was free()ed.";
	suplementalErrorText[PollFailed] = "Polling the net context failed.";
	suplementalErrorText[BadNetInput] = "Input invalid.";
	// end mbedtls
}

struct ErrorEntry
{
	int errorCode;
	const char* function;
	unsigned line;
	const char* file;
	// can be used for writing the parameters or putting something useful into the callstack
	const char* supplementalText;
};

class ErrorHandler
{
	std::stack<ErrorEntry> callstack;
	std::ostringstream stream;
public:
	static ErrorHandler* instance;

	ErrorHandler()
	{
		setupErrorText();
	}
	~ErrorHandler() = default;

	void printCallstack()
	{
		while (!callstack.empty())
		{
			auto& entry = callstack.top();

			stream << entry.file << " ";
			stream << "(" << entry.line << "): ";
			stream << entry.function << " returns ";
			stream << " \"" << suplementalErrorText[static_cast<errorCode>(entry.errorCode)] << "\" ";
			stream << "(" << entry.errorCode << ")" << std::endl;
			if (entry.supplementalText != nullptr)
				stream << "\t >> " << entry.supplementalText << std::endl;
			callstack.pop();
		}
		printf("Error Callstack:\n%s\n", stream.str().c_str());
		stream.str("");
		stream.clear();
	}

	/*
		intended to build a c++ callstack for when we get some sort of exception that we can then print
	*/
	int addErrorCallstack(int errorCode, const char* function, unsigned line, const char* file, const char* supplemental = nullptr)
	{
		ErrorEntry entry;
		entry.errorCode = errorCode;
		entry.function = function;
		entry.file = file;
		entry.line = line;
		entry.supplementalText = supplemental;
		instance->addCallstackEntry(entry);

		return errorCode;
	}

	void addCallstackEntry(ErrorEntry entry) { callstack.push(entry); }

};