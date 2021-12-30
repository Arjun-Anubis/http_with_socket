#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char * get_args( const int argc, char ** argv ) {

	const char delimeter[]  = ", ";
	int size = 0;
	char * buff = ( char * ) malloc( size );

	for ( int i = 0; i < argc; i++ ) {
		size += strlen( argv[i] ) + strlen( delimeter );
		buff = realloc( buff, size );
		strcat( buff, argv[i] );
		if ( i == argc-1 ) { 
			strcat( buff, "." );
		}
		else {
			strcat( buff, delimeter );
		}
	}
	return buff;


}
