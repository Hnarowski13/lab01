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
    sockaddr_in tcpServerAddr;
     int         tcpConnectionFd;

  // prase the argvs, obtain server_name and tcpServerPort
  parseArgv(argc, argv, &serverNameStr, tcpServerPort);

  std::cout << "[TCP] Tic Tac Toe client started..." << std::endl;
  std::cout << "[TCP] Connecting to server: " << serverNameStr
            << ":" << tcpServerPort << std::endl;
    
    struct hostent *hostEnd = gethostbyname(serverNameStr);
    
//    if (lh)
//        puts(lh->h_name);
//    else
//        herror("gethostbyname");
    while(cin.eof() == false) {
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
        
         MyPacket outgoingPkt;
        memset(&outgoingPkt, 0, sizeof(outgoingPkt));
     //  char typeName[typeNameLen];
      //  memset(&typeName, 0, sizeof(typeName));
        
        outgoingPkt.type = JOIN;
        
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
    }
    
    return 0;
  // Sample use of TicTacToe
//  TicTacToe game;
//  game.printBoard();
//    
//  std::cout << std::endl << std::endl << "MARK a" << std::endl;
//  game.mark('a', 'X');
//  game.printBoard();
//  std::cout << std::endl << std::endl << "MARK d" << std::endl;
//  game.mark('d', 'X');
//  game.printBoard();
//  std::cout << std::endl << std::endl << "MARK g" << std::endl;
//  game.mark('g', 'X');
//  game.printBoard();
//  
//  if(game.hasWon()) {
//    std::cout << "X has won!" << std::endl;
//  }
}

