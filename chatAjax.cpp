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
	  string full = "**"+stCommand+"**"+stUname+": "+stMessage;
	  sendfifo.openwrite();
	  sendfifo.send(full);
	  
  }
  
  if (stCommand == "GET"){
	string signal = "**GET**";
	sendfifo.openwrite();
	sendfifo.send(signal);
	cout << "Content-Type: text/plain\n\n";
	recfifo.openread();
	reply = recfifo.recv();
	while(reply.find("$END") == -1){
	reply = reply + "<p>";
	cout<< reply << endl;
	reply = recfifo.recv();
	}
	if (reply.find("$END") != -1){
	cout<< reply.substr(0,reply.find("$END")) << endl;
	}
  }
  
  if (stCommand == "KILL"){
	  string signal = "**KILL**";
	  sendfifo.openwrite();
	  sendfifo.send(signal);
  }
	  
	sendfifo.fifoclose();
	recfifo.fifoclose();
  
  return 0;
  }
