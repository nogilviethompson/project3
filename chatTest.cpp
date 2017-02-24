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
  string username, word, reply;
  
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
  
  while(1){
   	cout << "Enter a message: ";
   	getline(cin, word);
   	word = username+": "+word;
	cout << "Send:" << word << endl;
	sendfifo.openwrite();
	sendfifo.send(word);
	
	
	recfifo.openread();
	
	/* Get a message from a server */
	reply = recfifo.recv();
	while(reply.find("$END") == -1)
	{
	cout<< reply << endl;
	reply = recfifo.recv();
	}
	
	if (reply.find("$END") != -1)
	{
	
	cout<< reply.substr(0,reply.find("$END")) << endl;
	}
	
	

	recfifo.fifoclose();
	sendfifo.fifoclose();
	}
	
  return 0;
}