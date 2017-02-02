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

int main(int argc, char *argv[]) {
  char                 *serverNameStr = 0;
  unsigned short int   tcpServerPort;

  // prase the argvs, obtain server_name and tcpServerPort
  parseArgv(argc, argv, &serverNameStr, tcpServerPort);

  std::cout << "[TCP] Tic Tac Toe client started..." << std::endl;
  std::cout << "[TCP] Connecting to server: " << serverNameStr
            << ":" << tcpServerPort << std::endl;

  // Sample use of TicTacToe
  TicTacToe game;
  game.printBoard();
  std::cout << std::endl << std::endl << "MARK a" << std::endl;
  game.mark('a', 'X');
  game.printBoard();
  std::cout << std::endl << std::endl << "MARK d" << std::endl;
  game.mark('d', 'X');
  game.printBoard();
  std::cout << std::endl << std::endl << "MARK g" << std::endl;
  game.mark('g', 'X');
  game.printBoard();
  
  if(game.hasWon()) {
    std::cout << "X has won!" << std::endl;
  }
}

