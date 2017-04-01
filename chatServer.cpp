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
class chatroom
{
public:
    chatroom(); //Default constructor
	chatroom(string name, string creator);
	void addMessageToChat(string message);
	void displayChat(Fifo sendfifo);
	void clearChat();
	void addUser(string uname);
private:
    string admin;
    vector<string> users;
    string chatname;
    vector<string> chatLog;
};

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
		string username = inMessage.substr(5);
		chat.addUser(username);
		cout << "Current Users: " << userNum << endl;
		if(userNum <= 2){
			userMessage = "Connected";
			cout << userMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		} else{
			cout << "Current Users: " << userNum << endl;
			userMessage = "Full";
			cout << userMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		}
	}
	
	if (inMessage.find("SEND") == 0){
		string message = inMessage.substr(4);
		cout << "Received - " << message << endl;
		chat.addMessageToChat(message);
	}
	
	if (inMessage.find("REMOVE") == 0){
		userNum = userNum-1;
		string message = inMessage.substr(6);
		cout << "Removed User " << message << " - Current Users: " << userNum << endl;
		if (userNum == 0){
			chat.clearChat();
		}
	}
	
	if (inMessage.find("GET") == 0){
		chat.displayChat(sendfifo);
	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		cout << outMessage << endl;
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
	
	if (inMessage.find("KILL") == 0){
		userNum = userNum-1;
		cout << "Removed User - Current Users: " << userNum << endl;
		if (userNum == 0){
			chat.clearChat();
		}
	}
  }
  
  return 0;
}

chatroom::chatroom(){
	chatname = " ";
	admin = " ";
}
chatroom::chatroom(string name, string creator){
	chatname = name;
	admin = creator;
}
void chatroom::addMessageToChat(string message){
	chatLog.push_back(message);
}
void chatroom::displayChat(Fifo sendfifo){
	for (unsigned int i = 0; i < chatLog.size(); i++){
			string outMessage = chatLog[i];
			cout << outMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(outMessage);
			sendfifo.fifoclose();
		}
}
void chatroom::clearChat(){
	chatLog.clear();
}
void chatroom::addUser(string uname){
	users.push_back(uname);
}