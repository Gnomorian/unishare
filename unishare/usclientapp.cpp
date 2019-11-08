#include "application.h"
#include "errors.h"

#define HOST "0.0.0.0"
#define PORT "8080"

int UnishareClientApp::run()
{
	int result = socket.connect(HOST, PORT, unishare::net::Protocol::TCP);
	CHECK_RESULT;

	ByteArray message((BYTE*)"hello, friend!");
	result = socket.send(message);
	CHECK_RESULT;

	result = socket.recieve(message);
	CHECK_RESULT;

	puts("RESPONCE:\n");
	puts((const char*)message.c_str());



	return US_OK;
}