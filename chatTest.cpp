#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fifo.h"

using namespace std;
string receive_fifo = "messageReply";
string send_fifo = "messageRequest";

int main() {
  string username, word, reply;
  
  // create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);
  
  cout << "Please enter a username: ";
  getline (cin, username);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
  string userString = "$User "+username+" has joined the chat";
  sendfifo.openwrite();
  sendfifo.send(userString);
  sendfifo.fifoclose();
  recfifo.openread();
  reply = recfifo.recv();
  cout << reply << endl;
  recfifo.fifoclose();
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
  
  while (username.find("~!&") != string::npos)
  {
	  cout << "Sorry, but usernames cannot contain the characters '~!&' " << endl << "Please enter a username: ";
	  cin >> username;
  }
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD

	word = "USER";
	sendfifo.openwrite();
	sendfifo.send(word);
	sendfifo.fifoclose();
	
  while(1){
   	cout << "Enter a message: ";
   	getline(cin, word);
   	word = "SEND"+username+": "+word;
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
  while(1){
    if(reply == "Too many users"){
    	cout << "chat is closed for now";
    	return 0;
    }
   	cout << "Enter a message: ";
   	getline(cin, word);
   	word = "**SEND**"+username+": "+word;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	cout << "Send:" << word << endl;
	sendfifo.openwrite();
	sendfifo.send(word);
	sendfifo.fifoclose();
	sendfifo.openwrite();
	string get = ("**GET**");
	sendfifo.send(get);
	recfifo.openread();
	/* Get a message from a server */
	reply = recfifo.recv();
	while(reply.find("$END") == -1)
	{
	cout<< reply << endl;
	reply = recfifo.recv();
	}
	
	if (reply.find("$END") != -1)
	{
	
	cout<< reply.substr(0,reply.find("$END")) << endl;
	}
	
	

	recfifo.fifoclose();
	sendfifo.fifoclose();
	}
	
  return 0;
}