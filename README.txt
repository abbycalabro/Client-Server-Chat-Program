/****************************************************************************************
File:		README.txt
Author:		Abby Meunier
Email:		abby.meunier@gmail.com
Date:		11/1/2015

(Note: testing machine was a Mac)
******************************************************************************************/


****************
* chatserv.cpp *
****************	

To compile: 	g++ chatserv.cpp -o chatserv
To execute:	./chatserv <port#>

*****************
* chatclient.py *
*****************

To execute:	python chatclient.py <server-hostname> <port#>

****************
* INSTRUCTIONS *
****************

-Compile and execute chatserv.cpp on host A, specifying valid port # on command line.
-Execute chatclient.py on host B, specifying appropriate server hostname and port # on command line.
-Enter handle (username) when prompted by chatclient on host B. This initiates a connection with host A.
-Type the initial message on host B and press enter to send it to host A.
-The message will be displayed on host A, prepended by the user's handle.
-Host A and B can now take turns exchanging messages up to 500 characters. Messages sent by host A 
 will be displayed on host B and vice versa.

(Note: host A's handle is not prompted, but hard-coded as "A")

-To close the connection, enter "/quit" on either host A or B. This results in chatclient terminating 
 and chatserv listening for a new connection. To terminate chatserv, enter a SIGINT such as control+c.
