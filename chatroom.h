#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>

using namespace std;

class chatRoom
{
	private: 
	 string roomName;
	 int userLimit;
	 vector<string> chatLog;
	 vector<string> users;
	 
	public:
	 chatRoom();  //default constructor
	 void setName(string name);
	 string getName();
	 void setLimit(int number);
	 int getLimit();
	 void addMessage (string message);
	 void addUser(string userName);
	 void outputChat(Fifo& sendfifo);
	 void chatClear(); //clear the chatLog
	 
};
#endif /* CHATROOM_H */