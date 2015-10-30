'''
Program:		chatserv.py
Course/Assignment:	CS372, Project 1
Author:			Abby Meunier
Email:			meuniera@oregonstate.edu
Program Description:		
'''

from socket import *
import sys

def start_up(port_input):
	serverPort = port_input
	serverSocket = socket(AF_INET, SOCK_STREAM) #server creates TCP socket
	serverSocket.bind(('', serverPort)) #associate port with welcoming socket
	serverSocket.listen(1) #listen for TCP connection requests from client
	
	while 1:
		print 'Server is listening for connection requests...'
		#create a new socket dedicated to client and create TCP connection between clientSocket and connectionSocket
		connectionSocket, addr = serverSocket.accept()
		print "Server is now connected to client"
		msg_from_client = ""		

		while 1:		
			msg_from_client = connectionSocket.recv(500)
			
			#if client has closed connection, return to listening
			if len(msg_from_client) == 0:
				print "Client has quit. Now closing connection."
				connectionSocket.close()
				print "Connection closed."
				break 
			else:
				#print client message and send response
				print msg_from_client
				response = raw_input('A > ')

			#close connection or send message
			if response == "/quit":
				connectionSocket.close()
				print "Connection closed."
				break 
			else:
				connectionSocket.send(response)
				
def send_msg(handle):
	message = raw_input('')
	connectionSocket.send('A> ' + message) #hardcode server's handle
	
def rec_msg(msg_from_client):
	while 1:
		msg_from_client = connectionSocket.recv(500)
		print 'Client sent to server: ' + msg_from_client


if __name__ == '__main__':
	start_up(int(sys.argv[1])) #get port # from command line


	#send and receive messages here



