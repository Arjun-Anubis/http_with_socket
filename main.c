#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "netw.h"
#include "args.h"





int main( int argc, char ** argv ) 
{
	char * addr_s;
	if (argc > 1) addr_s = argv[1];
	else addr_s = "192.168.1.37";
	int err;

	char acquired_address_s[INET_ADDRSTRLEN];
	int sockfd = socket( AF_INET, SOCK_STREAM, 0 );


	struct sockaddr addr = getsockaddrbyname( addr_s, 8080 );

	inet_ntop( AF_INET, &( * ( struct sockaddr_in * ) &addr ).sin_addr, acquired_address_s, INET_ADDRSTRLEN );
	printf( "%s is at %s\n", addr_s, acquired_address_s );


	if ( ( err = connect( sockfd, &addr, sizeof( addr ) ) ) < 0 )
	{
		printf( "Could not connect: %s\n", strerror( err )  );
		return err;
	}



	char * response = _http_request( sockfd, "abc/bcd", NULL, 0 );

	printf( "%s\n", response );

	free( response );
	close( sockfd );

}

