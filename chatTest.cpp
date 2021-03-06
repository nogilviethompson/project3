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
	word = "USER";
	sendfifo.openwrite();
	sendfifo.send(word);
	sendfifo.fifoclose();
	recfifo.openread();
	reply = recfifo.recv();
	if (reply == "Full"){
		cout << "Sorry, the chat is full";
		return 0;
	}
	
  while(1){
   	cout << "Enter a message: ";
   	getline(cin, word);
   	word = "SEND"+username+": "+word;
	cout << "Send:" << word << endl;
	sendfifo.openwrite();
	sendfifo.send(word);
	sendfifo.fifoclose();
	sendfifo.openwrite();
	string get = ("**GET**");
	sendfifo.send(get);
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