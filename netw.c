#include <unistd.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

// Socket
#include <sys/types.h>
#include <sys/socket.h>

// Internet
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 20

char * _http_request
( 
	int sock,
	const char * host,
	const char * url_path,
	const char ** parameters,
	const int parameter_count
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
	   	+ strlen( "\r\n" )
		+ strlen( "Host: " )
		+ strlen( host )
	   	+ strlen( "\r\n" )
	   	+ strlen( "User-Agent: custom" )
	   	+ strlen( "\r\n" )
	   	+ strlen( "Accept: */*" )
		+ strlen( "\r\n" )
	);

	_draft_get = realloc( _draft_get, _draft_length );

	strcpy( _draft_get, "GET /" );
	strcat( _draft_get, url_path );
	strcat( _draft_get, " " );
	strcat( _draft_get, "HTTP/1.1" );
	strcat( _draft_get, "\r\n" );
	strcat( _draft_get, "Host: " );
	strcat( _draft_get, host );
	strcat( _draft_get, "\r\n" );
	strcat( _draft_get, "User-Agent: custom" );
	strcat( _draft_get, "\r\n" );
	strcat( _draft_get, "Accept: */*" );
	strcat( _draft_get, "\r\n" );

	if ( !( parameters == NULL ) ) 
	{
		for ( int i = 0; i < parameter_count; i++ ) 
		{
			_draft_length += strlen( parameters[i] ) + 1;
			_draft_get = realloc( _draft_get, _draft_length );
			strcat( _draft_get, parameters[i] );
			strcat( _draft_get, "\r\n" );
		}
	}

	_draft_length = strlen( _draft_get );
	if ( ( _total_sent = write( sock, _draft_get, _draft_length ) ) < _draft_length )
	{
		// printf( "Could only send %d bytes out of %d\r\n", _total_sent, _draft_length );
		return NULL;
	}
	free( _draft_get );
	write( sock, "\n\n", 2 );

	strcpy( buffer, "" );
	for (char cur[ BUFFER_SIZE ];;)
	{
		memset( cur, 0x0, BUFFER_SIZE );
		cycle_read = read( sock, cur, BUFFER_SIZE );
		buffer = realloc( buffer, strlen( buffer ) + cycle_read + 1);
		strncat( buffer, cur, BUFFER_SIZE );
		if ( cycle_read < BUFFER_SIZE ) 
		{
			break;
		}

	}
	_total_read = strlen( buffer );
	response = malloc( _total_read );
	strcpy( response, buffer );
	return response;
	
}

struct sockaddr getsockaddrbyname( char hostname[ INET_ADDRSTRLEN ], int port ) 
{
	struct hostent * hp;
	struct sockaddr_in addr;
	
	if ( ( hp = gethostbyname( hostname ) ) == NULL ) 
	{
		herror( "gethostbyname" );
		exit( -1 );	
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );

	memcpy( &addr.sin_addr, hp->h_addr, hp->h_length );

	return *( struct sockaddr * ) &addr ;
}


