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

void receiveMessage (string message, vector<string>& chatLog);
void sendChatLog (Fifo& sendfifo, vector<string> chatLog);
void clearChatLog (vector<string>& chatLog);

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

int main() {
  vector<string> chatLog;
  
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
	if (inMessage.find("**SEND**") == 0){
		string message = inMessage.substr(8);
		cout << "Received - " << message << endl;
		chatLog.push_back(message);
	}
	
	if (inMessage.find("**KILL**") == 0){
		chatLog.clear();
	}
	
	if (inMessage.find("**GET**") == 0){
		for (unsigned int i = 0; i < chatLog.size(); i++){
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
  }
  return 0;
}