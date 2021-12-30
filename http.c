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

char * http_request
(
	const char * addr_s,
	const int port,
	const char * path,
	const char ** params,
	const int param_count
) 
{
	int err;

	struct sockaddr addr = getsockaddrbyname( addr_s, port );
	char * response;
	int sockfd = socket( AF_INET, SOCK_STREAM, 0 );

	if ( ( err = connect( sockfd, &addr, sizeof( addr ) ) ) < 0 )
	{
		printf( "Connection refused\n" );
		return NULL;
	}

	response = _http_request( sockfd, addr_s, path, NULL, param_count );
	close( sockfd );
	return response;

}
