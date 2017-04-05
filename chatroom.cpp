#include <vector>
#include "fifo.h"
#include "chatroom.h"

using namespace std;

chatRoom::chatRoom(){
	roomName="my chat";
	userLimit = 2;
	currentUsers = 0;
}

void chatRoom::setName(string name){
	roomName=name;
}

string chatRoom::getName(){
	return(roomName);
}

void chatRoom::setLimit(int number){
	userLimit=number;
}

int chatRoom::getLimit(){
	return(userLimit);
}

int chatRoom::getCurrentUsers(){
	return(currentUsers);
}

void chatRoom::addMessage(string message){
	chatLog.push_back(message);
}

void chatRoom::addUser(string username, Fifo sendfifo){
	if (currentUsers+1 > userLimit)
	{
		sendfifo.openwrite();
		sendfifo.send("Full");
		sendfifo.fifoclose();
	}
	else if (currentUsers+1 <= userLimit)
	{
		users.push_back(username);
		currentUsers = currentUsers+1;
		sendfifo.openwrite();
		sendfifo.send("Connected");
		sendfifo.fifoclose();
	}
}

void chatRoom::removeUser(string username){
	for (unsigned int i = 0; i < users.size(); i++){
		if (users[i] == username){
			users.erase(users.begin()+i);
		}
	}
	currentUsers = currentUsers-1;
	if (currentUsers < 0){
		currentUsers = 0;
	}
	
}

void chatRoom::chatClear(){
     chatLog.clear();
}

void chatRoom::outputChat(Fifo sendfifo){
   for (unsigned int i = 0; i < chatLog.size(); i++){
		string outMessage = chatLog[i];
		cout << outMessage << endl;
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
}