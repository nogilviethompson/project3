#include <vector>
#include "fifo.h"

using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

int main() {
  
  string userMessage;
  chatroom chat;
  
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  int userNum = 0;
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
	if (inMessage.find("USER") == 0){
		userNum = userNum+1;
		if(userNum <= 2){
			userMessage = "Connected";
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		} else{
			userMessage = "Full";
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		}
	}
	
	if (inMessage.find("SEND") == 0){
		string message = inMessage.substr(4);
	}
	
	if (inMessage.find("REMOVE") == 0){
		userNum = userNum-1;
		if (userNum < 0){
			userNum = 0;
		}
		if (userNum == 0){
			chat.clearChat();
		}
	}
	
	if (inMessage.find("GET") == 0){
	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
  }
  
  return 0;
}

