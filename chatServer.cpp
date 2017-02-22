#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
<<<<<<< HEAD
#include <vector>
=======
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
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
#include "fifo.h"

using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

<<<<<<< HEAD
int main() {
  vector<string> chatLog;
  string username, message, full, outMessage;
 
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  
  chatLog.push_back(" ");
=======
/* Server main line,create name MAP, wait for and serve requests */
int main() {
  vector<string> chatLog;
  string username, message, full;
  
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
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
	
<<<<<<< HEAD
	chatLog.push_back(full);
=======
	chatLog.pushback(full);
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
	
	//Iterate through the positions vector, sending each line out as a message
	for (unsigned int i = 0; i < chatLog.size(); i++)
    {
<<<<<<< HEAD
    outMessage = chatLog[i];
=======
    string outMessage = positions[i];
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
	cout << outMessage << endl;
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
	}
	
	//After all the messages have been sent, send out the $END signal
	outMessage = "$END";
<<<<<<< HEAD
	cout << outMessage << endl;
=======
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
	sendfifo.openwrite();
	sendfifo.send(outMessage);
	sendfifo.fifoclose();
  }
  
  return 0;
}