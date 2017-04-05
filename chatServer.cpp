#include <vector>
#include "fifo.h"
#include "chatroom.h"
#include <sstream>


using namespace std;

/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";
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
  vector<chatRoom> chatroomList;
  chatroomList.push_back(chat);
  
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
	
	if (inMessage.find("REMOVE") == 0){
		string username = inMessage.substr(6);
		chat.removeUser(username);
		if (chat.getCurrentUsers() == 0){
			chat.chatClear();
		}
	}
	
	if (inMessage.find("GET") == 0){
		chat.outputChat(sendfifo);
		for (unsigned int i = 0; i < chatroomList.size(); i++){
			string roomNum = patch::to_string(i+1);
			string chatname = "Chat"+roomNum+": "+chatroomList[i].getName();
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
