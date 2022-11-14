#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
	
	// create socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// setting address for socket
	struct sockaddr_in server_address;
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	//INADDR_ANY: four zero
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//connect the socket, and check whether the connection succes
	int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	if ( connection_status == 0 ) printf("Connection succeed!\n");
	else if ( connection_status  == -1 ) printf("There are an error making a connection to remote socket.\n");

	//recieve information from server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	//print server's response
	printf("The server sent the data: %s\n", server_response);

	//close the socket
	close(network_socket);

	return 0;

}
