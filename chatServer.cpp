#include <vector>
#include "fifo.h"
#include "chatroom.h"
#include <sstream>


using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";
/* Found on stack overflow. Tried to use to_string function in std namespace but it didn't work*/
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int main() {
  chatRoom chat;
  chatRoom chat1;
  chat1.setName("your room");
  vector<chatRoom> chatList;
  chatList.push_back(chat);
  chatList.push_back(chat1);
  
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  int userNum = 0;
  vector<string> nameList;
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
	if (inMessage.find("USER") == 0){
		string username = inMessage.substr(4);
		bool match = false;
		if (nameList.size() == 0){
			nameList.push_back(username);
		}
		else{
			for (unsigned int i = 0; i < nameList.size(); i++){
				if (nameList[i] == username){
					match = true;
					sendfifo.openwrite();
					sendfifo.send("Matched");
					sendfifo.fifoclose();
					break;
				}
			}
		}
		chat.addUser(username, sendfifo);
	}
	
	if (inMessage.find("SEND") == 0){
		string message = inMessage.substr(4);
		chat.addMessage(message);
	}
	
	if (inMessage.find("CHECK") == 0){
		string username = inMessage.substr(4);
		bool match = false;
		if (nameList.size() == 0){
			nameList.push_back(username);
		}
		else{
			for (unsigned int i = 0; i < nameList.size(); i++){
				if (nameList[i] == username){
					match = true;
					sendfifo.openwrite();
					sendfifo.send("Matched");
					sendfifo.fifoclose();
					break;
				}
			}
		}
	}
	
	if (inMessage.find("NEWCHAT") == 0){
		string name = inMessage.substr(7);
		chatRoom chat;
		chat.setName(name);
		chatList.push_back(chat);
	}
	
	if (inMessage.find("JOINCHAT") == 0){
		string unsorted = inMessage.substr(8);
		char point = unsorted.at(0);
		unsigned int length = point;
		unsorted = unsorted.substr(1);
		string username = unsorted.substr(0, length);
		string chatName = unsorted.substr(length);
		for (unsigned int i = 0; i < chatList.size(); i++){
			if (chatName == chatList[i].getName()){
				chatList[i].addUser(username, sendfifo);
			}
		}
	}
	
	if (inMessage.find("REMOVE") == 0){
		string username = inMessage.substr(6);
		chat.removeUser(username);
		if (chat.getCurrentUsers() == 0){
			chat.chatClear();
		}
	}
	
	if (inMessage.find("GETCHATS") == 0){
		for (unsigned int i = 0; i < chatList.size(); i++){
			string roomNum = patch::to_string(i+1);
			string chatname = "~chatname~"+chatList[i].getName();
			string outMessage = chatname;
			cout << outMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(outMessage);
			sendfifo.fifoclose();
		}
	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
  }
  
  return 0;
}