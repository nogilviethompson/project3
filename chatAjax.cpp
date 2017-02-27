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

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  string reply;
  
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  // Create AJAX objects to recieve information from web page.
  form_iterator command = cgi.getElement("command");
  string stCommand = **command;
  
  if (stCommand == "SEND")
  {
	  form_iterator uname = cgi.getElement("username");
	  form_iterator message = cgi.getElement("message");
	  string stUname = **uname;
	  string stMessage = **message;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	  string full = stCommand+stUname+": "+stMessage;
	  sendfifo.openwrite();
	  sendfifo.send(full);
  }
  
  if (stCommand == "GET"){
	sendfifo.openwrite();
	sendfifo.send(stCommand);
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	  string full = "**"+stCommand+"**"+stUname+": "+stMessage;
	  sendfifo.openwrite();
	  sendfifo.send(full);
	  
  }
  
  if (stCommand == "GET"){
	string signal = "**GET**";
	sendfifo.openwrite();
	sendfifo.send(signal);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	cout << "Content-Type: text/plain\n\n";
	recfifo.openread();
	reply = recfifo.recv();
	while(reply.find("$END") == -1){
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		reply = reply + "<p>";
		cout<< reply << endl;
		reply = recfifo.recv();
=======
	reply = reply + "<p>";
	cout<< reply << endl;
	reply = recfifo.recv();
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
	reply = reply + "<p>";
	cout<< reply << endl;
	reply = recfifo.recv();
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
	reply = reply + "<p>";
	cout<< reply << endl;
	reply = recfifo.recv();
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	}
	if (reply.find("$END") != -1){
	cout<< reply.substr(0,reply.find("$END")) << endl;
	}
  }
  
  if (stCommand == "KILL"){
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	  sendfifo.openwrite();
	  sendfifo.send(stCommand);	  
  }
  
  if (stCommand == "USER"){
	string send = "USER";
	sendfifo.openwrite();
	sendfifo.send(send);
	cout << "Content-Type: text/plain\n\n";
	recfifo.openread();
	reply = recfifo.recv();
	if (reply == "Connected"){
		form_iterator uname = cgi.getElement("username");
		string stUname = **uname;
		string outMessage = "Your username is " + stUname + ". You are connected";
		cout << outMessage << endl;
	} else if (reply == "Full"){
		string outMessage = "Sorry, but the chatroom is full";
		cout << outMessage << endl;
	}
  }  
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	  string signal = "**KILL**";
	  sendfifo.openwrite();
	  sendfifo.send(signal);
  }
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	  
	sendfifo.fifoclose();
	recfifo.fifoclose();
  
  return 0;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  }
=======
  }
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
  }
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
  }
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
