#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
	char server_message[256] = "Server accepted!!!";

	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	//setting server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 3); //listen to 3 client program
	
	
	int client_socket;
	char command[256];
	char client_response[256];
	char success_result[256] = "Command executed!";
	char failure_result[256] = "Command terminated :(";
	char undefined_result[256] = "Type error, undefined command.";
		
	client_socket = accept(server_socket, NULL, NULL);
	//send message to client socket
	send(client_socket, server_message, sizeof(server_message),0);
	recv(client_socket, &command, sizeof(command), 0);
	recv(client_socket, &client_response, sizeof(client_response), 0);
	if (strcmp(client_response, "Exec") == 0 ) send(client_socket, success_result, sizeof(success_result), 0);
	else if (strcmp(client_response, "Term") == 0 ) send(client_socket, failure_result, sizeof(failure_result), 0);
	else send(client_socket, undefined_result, sizeof(undefined_result), 0);

	//close socket
	close(server_socket);
	
	return 0;
}
