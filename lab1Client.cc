#include "MyPacket.h"    // defined by us
#include "lab1Client.h"  // some supporting functions.
#include "TicTacToe.h"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
  char                 *serverNameStr = 0;
  unsigned short int   tcpServerPort;
  
  int tcpConnectionFd;
  int bytesSent, bytesReceived;
  sockaddr_in tcpServerAddr;

  // parse the argvs, obtain server_name and tcpServerPort
  parseArgv(argc, argv, &serverNameStr, tcpServerPort);

  std::cout << "[TCP] Tic Tac Toe client started..." << std::endl;
  std::cout << "[TCP] Connecting to server: " << serverNameStr
            << ":" << tcpServerPort << std::endl;
            
  struct hostent *hostEnd = gethostbyname(serverNameStr);
  
	// create a TCP socket with protocol family AF_INET
	tcpConnectionFd = socket(AF_INET, SOCK_STREAM, 0);

	// if the return value is -1, the creation of socket is failed.
	if(tcpConnectionFd < 0) {
		 cerr << "[ERR] Unable to create TCP socket." << endl;
		 exit(1);
	}
	
	// initialize the socket address strcut by setting all bytes to 0
	memset(&tcpServerAddr, 0, sizeof(tcpServerAddr));

	// details are covered in class/slides
	tcpServerAddr.sin_family = AF_INET;
	tcpServerAddr.sin_port   = htons(tcpServerPort);

	memcpy(&tcpServerAddr.sin_addr, hostEnd -> h_addr, 
		   hostEnd -> h_length);

	if(connect(tcpConnectionFd, (sockaddr *)&tcpServerAddr, 
			   sizeof(tcpServerAddr)) < 0) {
		cerr << "[ERR] Unable to connect to server." << endl;
		if(close(tcpConnectionFd) < 0) {
			cerr << "[ERR] Error when closing TCP socket" << endl;
		}
		exit(1);
	}
	
	
	MyPacket outPacket;
	MyPacket inPacket;
	char typeName[typeNameLen];
	
	memset(&outPacket, 0, sizeof(outPacket));
	outPacket.type = JOIN;
	
	bytesSent = send(tcpConnectionFd, &outPacket, sizeof(outPacket), 0);

	if(bytesSent < 0) {
		cerr << "[ERR] Error sending message to server." << endl;
		exit(1);
	} else {
		getTypeName(outPacket.type, typeName);
		cout << "[TCP] Sent: " << typeName << endl;
	}
	
	//cout << "WOOOW" << endl;
	
	// wipe out anything in incomingPkt's buffer
	memset(&inPacket, 0, sizeof(inPacket));
	// receive
	bytesReceived = recv(tcpConnectionFd,
			 &inPacket,
			 sizeof(inPacket),
			 0);
	
	// check
	if (bytesReceived < 0) {
	std::cerr << "[ERR] Error receiving message from client" << std::endl;
	return false;
	} else {
	getTypeName(inPacket.type, typeName);
	std::cout << "[TCP] Recv: " << typeName << " "
			  << inPacket.buffer << std::endl;
	}
	//What's my mark?
	char mark = inPacket.buffer[0];
	
	
	//UDP Request
	memset(&outPacket, 0, sizeof(outPacket));
	outPacket.type = GET_UDP_PORT;
	
	bytesSent = send(tcpConnectionFd, &outPacket, sizeof(outPacket), 0);

	if(bytesSent < 0) {
		cerr << "[ERR] Error sending message to server." << endl;
		exit(1);
	} else {
		getTypeName(outPacket.type, typeName);
		cout << "[TCP] Sent: " << typeName << endl;
	}
	// wipe out anything in incomingPkt's buffer
	memset(&inPacket, 0, sizeof(inPacket));
	// receive
	bytesReceived = recv(tcpConnectionFd,
			 &inPacket,
			 sizeof(inPacket),
			 0);
	
	// check
	if (bytesReceived < 0) {
	std::cerr << "[ERR] Error receiving message from client" << std::endl;
	return false;
	} else {
	getTypeName(inPacket.type, typeName);
	std::cout << "[TCP] Recv: " << typeName << " "
			  << inPacket.buffer << std::endl;
	}
	
	unsigned short int   udpServerPort = atoi(inPacket.buffer);
	cout << "That UDP is gon be "<<udpServerPort;
	
	//UDP time
	
	

  
}
