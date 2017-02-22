#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fifo.h"

using namespace std;
string receive_fifo = "messageReply";
string send_fifo = "messageRequest";

int main() {
  string username, message, reply;
  
  // create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);
  
  cout << "Please enter a username: ";
  getline (cin, username);
  
  while (username.find("~!&") != string::npos)
  {
	  cout << "Sorry, but usernames cannot contain the characters '~!&' " << endl << "Please enter a username: ";
	  cin >> username;
  }
  
  while (1) {
	  //ask for the message
	cout << "Enter a message:";
	getline(cin, message);
	
	message = username + "~!&" + message;
	cout << "Send:" << message << endl;
	sendfifo.openwrite();
	sendfifo.send(message);
	sendfifo.fifoclose();
	
	do{
	/* Get a message from a server */
	/* Repeat until the $END signal is received */
	recfifo.openread();
	reply = recfifo.recv();
	recfifo.fifoclose();
	cout << "Server sent: " << reply << endl;
	} while (reply.find("$END") == string::npos);
  }

  return 0;
}