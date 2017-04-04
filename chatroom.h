#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>

using namespace std;

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

#endif /* CHATROOM_H */