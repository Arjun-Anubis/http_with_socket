struct sockaddr getsockaddrbyname
(
	const char[ INET_ADDRSTRLEN ],
	const int port
);

char * _http_request
(
 	int sock, 
	const char * host,
	const char * url_path,
	const char ** get_parameters,
	const int parameter_count
);
