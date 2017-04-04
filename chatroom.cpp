#include <vector>
#include "fifo.h"
#include "chatroom.h"

using namespace std;

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