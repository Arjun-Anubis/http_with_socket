struct sockaddr getsockaddrbyname
(
	char[ INET_ADDRSTRLEN ],
	int port
);

char * _http_request
(
 	int sock, 
	char * url_path,
	char ** get_parameters,
	int parameter_count
);
