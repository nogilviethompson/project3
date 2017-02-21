#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "english_stem.h"
#include "meta.h"
#include "stemming.h"
#include "string_util.h"
#include "utilities.h"
#include "fifo.h"

using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

/* Server main line,create name MAP, wait for and serve requests */
int main() {
  vector<string> chatLog;
  string username, message, full;
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
	/* Parse the incoming message */
	/* Form:  username~!&message  */
	int pos = inMessage.find_first_of("~!&");
	username = inMessage.substr(0,pos);
	pos = pos + 3;
	
	//Create a string that is the message term
	message = inMessage.substr(pos,2000);
	cout << "Received: " << username << " - " << message << endl;
	
	full = username + ": " + message;
	
	chatLog.pushback(full);
	
	//Iterate through the positions vector, sending each line out as a message
	for (unsigned int i = 0; i < chatLog.size(); i++)
    {
    string outMessage = positions[i];
	cout << outMessage << endl;
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
	}
	
	//After all the messages have been sent, send out the $END signal
	outMessage = "$END";
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
  }
  
  return 0;
}