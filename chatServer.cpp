#include <vector>
#include "fifo.h"
#include "chatroom.h"

using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

int main() {
  chatRoom chat;
  
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
		string username = inMessage.substr(4);
		chat.addUser(username, sendfifo);
	}
	
	if (inMessage.find("SEND") == 0){
		string message = inMessage.substr(4);
		chat.addMessage(message);
	}
	
	if (inMessage.find("REMOVE") == 0){
		string username = inMessage.substr(6);
		chat.removeUser(username);
		if (chat.getCurrentUsers() == 0){
			chat.chatClear();
		}
	}
	
	if (inMessage.find("GET") == 0){
		chat.outputChat(sendfifo);
	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
  }
  
  return 0;
}