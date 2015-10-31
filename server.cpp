/************************************************************
Program:	server.cpp
Author:		Abby Meunier
Email:		meuniera@oregonstate.edu
Date:		11/1/2015
Description:

************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <netdb.h>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
	struct sockaddr_in server_addr, client_addr;
	int sockfd, new_sockfd, server_port, bytes_read;
	socklen_t addr_size;
	char buffer[500];
	string msg = "";

	//create socket file descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		cout << "Error creating socket." << endl;
	}

	//initialize socket
	server_port = atoi(argv[1]);
	bzero((char *) &server_addr, sizeof(server_addr));	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(server_port);
	
	//bind to port
	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		cout << "Error binding to host address." << endl;


	//start listening for connections
	if(listen(sockfd, 5) < 0)
		cout << "Error listening for connections." << endl;

	while(1) {
		cout << "Server now listening for connections..." << endl;
		//accept new connection
		addr_size = sizeof(client_addr);
		new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
		if(new_sockfd < 0)
			cout << "Error accepting connection." << endl;
		else
			cout << "Connection to client established. Awaiting message..." << endl;

		while(1) {	
			//receive message
			bytes_read = recv(new_sockfd, buffer, sizeof(buffer), 0);
			//print message or close connection and go back to listening
			if(bytes_read > 0) {
				buffer[bytes_read] = '\0';
				cout << buffer << endl;
			}
			else if(bytes_read < 0)
				cout << "Error receiving message from client." << endl;
			else if(bytes_read == 0) {
				//close connection
				cout << "Client has quit. Now closing connection." << endl;
				if(close(new_sockfd) !=  0)
					cout << "Error closing connection" << endl;
				else
					cout << "Connection closed." << endl;
				break;
			}

			
			//send message or quit
			const char *c_msg;
			cout << "A > ";
			getline(cin, msg, '\n');
			
			//close connection and go back to listening
			if(msg == "/quit") {
				if(close(new_sockfd) !=  0)
					cout << "Error closing connection." << endl;
				cout << "Connection closed." << endl;
				break;
			}
			else {
				//send message
				c_msg = msg.c_str();
				if(send(new_sockfd, c_msg, strlen(c_msg), 0) < 0)
					cout << "Error sending message to client" << endl;
			}
		}
	}

	return 0;
}

