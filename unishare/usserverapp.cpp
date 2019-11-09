#include "application.h"
#include "errors.h"

#define PORT "8080"
#define HOST "0.0.0.0"

int UnishareServerApp::run()
{
	int result = socket.listen(HOST, PORT, unishare::net::Protocol::TCP);
	CHECK_RESULT;

	unishare::net::ClientProxySocket proxy;
	result = socket.accept(proxy);
	CHECK_RESULT;

	ByteArray message;
	result = proxy.recieve(message);
	CHECK_RESULT;

	result = proxy.send(message);

	proxy.disconnect();

	return US_OK;
}
