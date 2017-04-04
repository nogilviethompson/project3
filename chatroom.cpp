#include <vector>
#include "fifo.h"
#include "chatroom.h"

using namespace std;

chatRoom::chatRoom()
{
	roomName="";
	userLimit=2;
}

void chatRoom::setName(string name)
{
	roomName=name;
}

string chatRoom::getName()
{
	return(roomName);
}

void chatRoom::setLimit(int number)
{
	userLimit=number;
}

int chatRoom::getLimit()
{
	return(userLimit);
}

void chatRoom:: addMessage(string message)
{
	chatLog.push_back(message);
}

void chatRoom:: addUser(string userName)
{
	users.push_back(userName);
}

void chatRoom::chatClear()
{
     chatLog.clear();
}

void chatRoom::outputChat(Fifo& sendfifo)
{
   for (unsigned int i = 0; i < chatLog.size(); i++){
		string outMessage = chatLog[i];
		cout << outMessage << endl;
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
}

