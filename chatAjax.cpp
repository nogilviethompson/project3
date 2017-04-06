#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

// fifo for communication
string receive_fifo = "messageReply";
string send_fifo = "messageRequest";

void send (Fifo sendfifo, Cgicc cgi, string stCommand);
//Precondition: sendfifo is the fifo to send messages to the server, cgi is an Ajax object, and stCommand is the command
//Postcondition: The user's message is sent to the server
void get (Fifo sendfifo, Fifo recfifo, string stCommand);
//Precondition: sendfifo is the fifo to send messages to the server, recfifo is the fifo to receive messages from the server, and stCommand is the command
//Postcondition: The entire chatlog has been cout-ed
void getMessages(string stCommand, Fifo sendfifo, Fifo recfifo, Cgicc cgi);
void remove (Fifo sendfifo, Cgicc cgi, string stCommand);
void user (Fifo sendfifo, Fifo recfifo, Cgicc cgi);
void join(Fifo sendfifo, Fifo recfifo, Cgicc cgi, string stCommand);
void createChat(Fifo sendfifo, Fifo recfifo, Cgicc cgi, string stCommand);

int main() {
  Cgicc cgi;    // Ajax object
  
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  // Create AJAX objects to recieve information from web page.
  form_iterator command = cgi.getElement("command");
  string stCommand = **command;
  cout << stCommand;
  
  cout << "Content-Type: text/plain\n\n";  
  
  if (stCommand == "SEND")
  {
	  send(sendfifo, cgi, stCommand);
  }
  
  if (stCommand == "NEWCHAT"){
	createChat(sendfifo, recfifo, cgi, stCommand);
	cout << "New Chat";
  }  
  
  if (stCommand == "JOINCHAT"){
	join(sendfifo, recfifo, cgi, stCommand);
  }
  
  if (stCommand == "GETCHATS"){
	get(sendfifo, recfifo, stCommand);
  }
  
 if (stCommand == "REMOVE"){
      remove(sendfifo, cgi, stCommand);
  }
  
  if (stCommand == "CHECK"){
   user(sendfifo, recfifo, cgi);
  }
  
  if (stCommand == "GETMESSAGES"){
	getMessages(stCommand, sendfifo, recfifo, cgi);
  }
   
	sendfifo.fifoclose();
	recfifo.fifoclose();
  
  return 0;
}

void send (Fifo sendfifo, Cgicc cgi, string stCommand){
	form_iterator uname = cgi.getElement("username");
	form_iterator message = cgi.getElement("message");
	string stUname = **uname;
	string stMessage = **message;
	string full = stCommand+stUname+": "+stMessage;
	sendfifo.openwrite();
	sendfifo.send(full);
}

void get (Fifo sendfifo, Fifo recfifo, string stCommand){
	sendfifo.openwrite();
	sendfifo.send(stCommand);
	recfifo.openread();
	string reply = recfifo.recv();
	while(reply.find("$END") == -1){
		reply = "<p>" + reply + "</p>";
		cout << reply;
		reply = recfifo.recv();
		if (reply.find("$END") != -1){
			cout << "<p>" << reply.substr(0,reply.find("$END")) << "</p>";
		}
	}
}

void getMessages(string stCommand, Fifo sendfifo, Fifo recfifo, Cgicc cgi){
	form_iterator chatName = cgi.getElement("chatName");
	string stChatName = **chatName;
	string send = stCommand+stChatName;
	sendfifo.openwrite();
	sendfifo.send(send);
	recfifo.openread();
	string reply = recfifo.recv();
	while(reply.find("$END") == -1){
		reply = "<p>" + reply + "</p>";
		cout << reply;
		reply = recfifo.recv();
		if (reply.find("$END") != -1){
			cout << "<p>" << reply.substr(0,reply.find("$END")) << "</p>";
		}
	}
}

void remove (Fifo sendfifo, Cgicc cgi, string stCommand){
	sendfifo.openwrite();
    form_iterator uname = cgi.getElement("username");
	string stUname = **uname;
	string full = stCommand+stUname;
	sendfifo.send(full);
}

void user (Fifo sendfifo, Fifo recfifo, Cgicc cgi){
	form_iterator uname = cgi.getElement("username");
	string stUname = **uname;
	string send = "USER "+stUname;
	sendfifo.openwrite();
	sendfifo.send(send);
	recfifo.openread();
	string reply = recfifo.recv();
	if (reply == "Matched"){
		cout << "Sorry, but that username has already been taken";
	}
	else{
		cout << "Good";
	}
}

void createChat(Fifo sendfifo,Fifo recfifo, Cgicc cgi, string stCommand){
	form_iterator chatName = cgi.getElement("chatName");
	form_iterator uname = cgi.getElement("username");
	string stUname = **uname;
	string stChatName = **chatName;
	string send = stCommand+stUname+stChatName;
	sendfifo.openwrite();
	sendfifo.send(send);
	recfifo.openread();
	string reply = recfifo.recv();
	if (reply == "Connected"){
		cout << "You are connected";
	}
	if (reply == "Full"){
		cout << "Sorry, but the chatroom is full";
	}
}

void join(Fifo sendfifo, Fifo recfifo, Cgicc cgi, string stCommand){
	form_iterator uname = cgi.getElement("username");
	form_iterator chatName = cgi.getElement("chatName");
	string stUname = **uname;
	unsigned int unameSize = stUname.size();
	char length = unameSize;
	string stChatName = **chatName;
	string send = stCommand+length+stUname+stChatName;
	sendfifo.openwrite();
	sendfifo.send(send);
	recfifo.openread();
	string reply = recfifo.recv();
	if (reply == "Connected"){
		cout << "You are connected";
	}
	if (reply == "Full"){
		cout << "Sorry, but the chatroom is full";
	}
}