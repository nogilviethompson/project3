#include <vector>
#include "fifo.h"

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

void User(int& userNum, string& userMessage, Fifo& sendfifo,chatRoom& room);
void Send(string inMessage, chatRoom& room);
void Remove(int& userNum, string inMessage, chatRoom& room);
void Get(chatRoom& room, Fifo& sendfifo);
void Kill(int& userNum, chatRoom& room);

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";


  
  int main() {
   //vector<string> chatLog;
   
   chatRoom chatRoom1;
   string userMessage,name;
   int userLimit;
   
   cout<< "Would you like to enter an existing chatroom or create a new chatroom?"<<endl;
   
   cout<<"How many users are allowed for this chatroom?" << endl;
   cin >> userLimit;
   cout<<"How would you like to name your chatroom?" << endl;
   cin >> name;
   
   chatRoom1.setLimit(userLimit);
   chatRoom1.setName(name);
   
   
 // create the FIFOs for communication
   Fifo recfifo(receive_fifo);
   Fifo sendfifo(send_fifo); 
   int userNum = 0;
   
   while (1) 
   {
 
     /* Get a message from a client */
     recfifo.openread();
     string inMessage = recfifo.recv();
 	recfifo.fifoclose();
 	
 	if (inMessage.find("USER") == 0)
 	{
 		User(userNum, userMessage,sendfifo,chatRoom1);
 	}
 	
 	if (inMessage.find("SEND") == 0)
 	{
 		Send(inMessage, chatRoom1);
 	}
 	
 	if (inMessage.find("REMOVE") == 0)
 	{
 		Remove(userNum,inMessage,chatRoom1);
 	}
 	
 	if (inMessage.find("GET") == 0)
 	{	
		Get(chatRoom1,sendfifo);
 	}
 	
 	if (inMessage.find("KILL") == 0)
 	{
 		Kill(userNum, chatRoom1);
 	}
   }
   
   return 0;
 } 




void User(int& userNum, string& userMessage, Fifo& sendfifo,chatRoom& room)
{
 		userNum = userNum+1;
		cout << "Current Users: " << userNum << endl;
		if(userNum <= room.getLimit()){
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

void Send(string inMessage, chatRoom& room)
{
	string message = inMessage.substr(4);
	cout << "Received - " << message << endl;
	room.addMessage(message);
}

void Remove(int& userNum, string inMessage, chatRoom& room)
{
 	userNum = userNum-1;
	string message = inMessage.substr(6);
	cout << "Removed User " << message << " - Current Users: " << userNum << endl;
	if (userNum == 0){
		room.chatClear();
	}
}

void Get(chatRoom& room, Fifo& sendfifo)
{
   /*for (unsigned int i = 0; i < chatLog.size(); i++){
		string outMessage = chatLog[i];
		cout << outMessage << endl;
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}*/
	

	room.outputChat(sendfifo);

	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
}

void Kill(int& userNum, chatRoom& room)
{
	userNum = userNum-1;
	cout << "Removed User - Current Users: " << userNum << endl;
	if (userNum == 0){
		room.chatClear();
	}

}
 
 
//class member functions

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

