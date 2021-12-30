// Socket
#include <sys/types.h>
#include <sys/socket.h>

// Internet
#include <arpa/inet.h>

// STD
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

// Local
#include "netw.h"
#include "args.h"
#include "http.h"




int main
(
	 int argc,
	 char ** argv
)
{
	char * addr_s;
	int port;
	char * path = "";
	char * response;
	const int param_count = 4;
	const char * params[4] = { "A: 1", "B: 2", "C: 3", "D: 4" };

	addr_s = "127.0.0.1";
	port = 80;
	
	if ( argc > 1 ) addr_s = argv[1];
	if ( argc > 2 ) port = atoi( argv[2] );

	response = http_request( addr_s, port, path, params, param_count );
	printf( "%s", response );
	free( response );

}


