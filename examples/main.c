#include <string.h>
#include "exampletls.h"


int main(int argc, char** args)
{
	if (argc > 1 && strcmp(args[1], "server") == 0)
		server_main(argc, args);
	else
		client_main(argc, args);
	return 0;
}