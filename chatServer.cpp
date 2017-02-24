#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "fifo.h"

using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

int main() {
  vector<string> chatLog;
  
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  
  chatLog.push_back(" ");
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
	/* Parse the incoming message */
	/* Form:  username~!&message  */
	
	//Create a string that is the message term
	cout << "Received - " << inMessage << endl;
	chatLog.push_back(inMessage);
	
	//Iterate through the positions vector, sending each line out as a message
	for (unsigned int i = 0; i < chatLog.size(); i++)
    {
    string outMessage = chatLog[i];
	cout << outMessage << endl;
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
	}
	
	//After all the messages have been sent, send out the $END signal
	string outMessage = "$END";
	cout << outMessage << endl;
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
  }
  
  return 0;
}