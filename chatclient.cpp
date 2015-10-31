/************************************************************
Program:		chatclient.cpp
Course/Assignment:	CS372, Project 1
Author:			Abby Meunier
Email:			meuniera@oregonstate.edu
Program Description:

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

void init_contact(string server_name, int server_port) {
	//create new socket, returns a file descriptor
//	client_socket = socket(AF_INET, SOCK_STREAM, 0);

}

void send_msg() {

}

void rec_msg() {

}


int main(int argc, char* argv[]) {
	string server_name, handle;
	int server_port, sockfd;
	struct sockaddr_in server_info;
	struct hostent *he;
	char buffer[500];

	//get server port from command line
	server_port = atoi(argv[2]);

	//get client handle
	cout << "Enter username up to 10 characters: ";
	getline(cin, handle, '\n');
	while(strlen(handle.c_str()) > 10 || strlen(handle.c_str()) < 1) {
		cout << "Username must be between 1 and 10 characters. Try again: ";
		getline(cin, handle, '\n');
	} 

	he = gethostbyname(argv[1]);
	memset(&server_info, 0, sizeof(server_info)); //empty server_info
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(server_port);
	server_info.sin_addr = *((struct in_addr *)he->h_addr);

	//create socket and connect to server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 1) 
		cout << "Error creating socket" << endl;
	if(connect(sockfd, (struct sockaddr *)&server_info, sizeof(struct sockaddr)) < 0) 
		cout << "Error connecting to server" << endl;

	//send msg to server
	string msg = "";
	int bytes_read;

	while(1) {
		cout << handle << " > ";
		getline(cin, msg, '\n'); //get new message
		const char *c_msg;

		//close connection 
		if(msg == "/quit") {
			if(close(sockfd) !=  0) 
				cout << "Error closing connection" << endl;	
			cout << "Connection closed. Terminating program." << endl;		
			exit(EXIT_SUCCESS);	
		}
	
		//prepend handle to message before sending
		msg = handle + " > " + msg;
		c_msg = msg.c_str();
		
		//send message
		if(send(sockfd, c_msg, strlen(c_msg), 0) < 0) 
			cout << "Error sending message to server" << endl;
		
		//receive message
		bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
		if(bytes_read > 0) {
			buffer[bytes_read] = '\0';
			cout << "A > " << buffer << endl;

		}
		else if(bytes_read < 0)
			cout << "Error receiving message from server" << endl;
		else if(bytes_read == 0) {
			//close connection
			cout << "Server has quit. Now closing connection." << endl;			
			if(close(sockfd) !=  0)
				cout << "Error closing connection" << endl;	
			else
				cout << "Connection closed. Terminating program." << endl;
			break;
		}
	}


//	`nit_contact(server_name, server_port);


	return 0;
}
