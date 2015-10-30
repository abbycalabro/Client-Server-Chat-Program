from socket import *
import sys

handle = raw_input( "Enter your screen name: ")

#set up socket
serverName = sys.argv[1]
serverPort = int(sys.argv[2])
clientSocket = socket(AF_INET, SOCK_STREAM)

#connect to server
print "Connecting to", serverName, "port #", serverPort
clientSocket.connect((serverName, serverPort))

while(1):
	msg = raw_input(handle + ' > ')
	
	#client quits or sends message
	if msg == "/quit":
		print "Closing connection."
		clientSocket.close()
		print "Connection closed. Terminating program."
		exit()
	else:
		clientSocket.send(handle + ' > ' + msg)

	#receive and print message, or end program
	response = clientSocket.recv(500)
	if len(response) == 0:
		print "Server has quit. Closing connection."
		clientSocket.close()
		print "Connection closed. Now terminating."
		break
	else:
		print 'A > ', response

