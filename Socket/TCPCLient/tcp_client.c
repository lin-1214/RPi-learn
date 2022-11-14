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
	char server_result[256];
	char client_command[256];
	char client_acceptance[256];
	
	printf("User command: ");
	scanf("%s", &client_command);
	send(network_socket, &client_command, sizeof(client_command), 0);
	recv(network_socket, &server_response, sizeof(server_response), 0);	
	//print server's response
	printf("Server response: %s\n", server_response);

	//Get result
	printf("Do you want to execute the command ?(Exec/Term): ");
	scanf("%s", &client_acceptance);
	send(network_socket, &client_acceptance, sizeof(client_acceptance), 0);
	recv(network_socket, &server_result, sizeof(server_result), 0);
        printf("Result: %s\n", server_result);

	//close the socket
	close(network_socket);

	return 0;

}
