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

#define BUFFER_SIZE 20

char * _http_request
( 
	int sock,
	char * url_path,
	char ** parameters,
	int parameter_count
)

{
	int _draft_length;
	int _total_sent = 0;
	int _total_read = 0;
	int cycle_read;
	char * _draft_get = malloc(1);
	char * buffer = malloc( 1 );
	char * response;
	


	_draft_length = 
	(
	 	strlen( "GET /" )
		+ strlen( url_path )
		+ strlen( " " )
	   	+ strlen( "HTTP/1.1" )
	   	+ strlen( "Accept: */*" )
	   	+ strlen( "\n" )
	);

	_draft_get = realloc( _draft_get, _draft_length );

	strcpy( _draft_get, "GET /" );
	strcat( _draft_get, url_path );
	strcat( _draft_get, " " );
	strcat( _draft_get, "HTTP/1.1" );
	strcat( _draft_get, "\n" );
	strcat( _draft_get, "Accept: */*" );
	strcat( _draft_get, "\n" );

	if ( !( parameters == NULL ) ) 
	{
		for ( int i = 0; i < parameter_count; i++ ) 
		{
			_draft_length += strlen( parameters[i] ) + 1;
			_draft_get = realloc( _draft_get, _draft_length );
			strcat( _draft_get, parameters[i] );
			strcat( _draft_get, "\n" );
		}
	}

	_draft_length = strlen( _draft_get );
	if ( ( _total_sent = write( sock, _draft_get, _draft_length ) ) < _draft_length )
	{
		printf( "Could only send %d bytes out of %d\n", _total_sent, _draft_length );
		return NULL;
	}
	free( _draft_get );

	strcpy( buffer, "" );
	for (char cur[ BUFFER_SIZE ];;)
	{
		buffer = realloc( buffer, _total_read + BUFFER_SIZE );
		memset( cur, 0x0, BUFFER_SIZE );
		cycle_read = read( sock, cur, BUFFER_SIZE );
		strcat( buffer, cur );
		_total_read += cycle_read;
		if ( cycle_read < BUFFER_SIZE ) 
		{
			break;
		}

	}
	response = malloc( _total_read );
	strcpy( response, buffer );
	return response;
	
}


int main( int argc, char ** argv ) 
{
	char * addr_s;
	if (argc > 1) addr_s = argv[1];
	else addr_s = "192.168.1.37";
	int err;

	char acquired_address_s[INET_ADDRSTRLEN];
	int sockfd = socket( AF_INET, SOCK_STREAM, 0 );


	struct sockaddr addr = getsockaddrbyname( addr_s, 80 );

	inet_ntop( AF_INET, &( * ( struct sockaddr_in * ) &addr ).sin_addr, acquired_address_s, INET_ADDRSTRLEN );
	printf( "%s is at %s\n", addr_s, acquired_address_s );


	if ( ( err = connect( sockfd, &addr, sizeof( addr ) ) ) < 0 )
	{
		printf( "Could not connect: %s\n", strerror( err )  );
		return err;
	}



	char * response;
	response = _http_request( sockfd, "abc/bcd", NULL, 0 );


	printf( "%s\n", response );

	free( response );
	close( sockfd );

}

