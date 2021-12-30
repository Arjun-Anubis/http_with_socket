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


struct sockaddr getsockaddrbyname( char hostname[ INET_ADDRSTRLEN ], int port ) {

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


