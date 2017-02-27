#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "fifo.h"

using namespace std;

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
void receiveMessage (string message, vector<string>& chatLog);
void sendChatLog (Fifo& sendfifo, vector<string> chatLog);
void clearChatLog (vector<string>& chatLog);

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
/* Fifo names */
string receive_fifo = "messageRequest";
string send_fifo = "messageReply";

int main() {
  vector<string> chatLog;
  string userMessage;
  
// create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo); 
  int userNum = 0;
  
  while (1) {

    /* Get a message from a client */
    recfifo.openread();
    string inMessage = recfifo.recv();
	recfifo.fifoclose();
	
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	if (inMessage.find("USER") == 0){
		userNum = userNum+1;
		cout << "Current Users: " << userNum << endl;
		if(userNum <= 2){
			userMessage = "Connected";
			cout << userMessage << endl;
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	if (inMessage.find("$User") == 0){
		userNum++;
		if(userNum <= 2){
			string message = inMessage.substr(1);
			cout << "Current Users: " << userNum << endl;
			cout << message << endl;
			userMessage = "good on users bro";
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
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		} else{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
			cout << "Current Users: " << userNum << endl;
			userMessage = "Full";
			cout << userMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
		}
	}
	
	if (inMessage.find("SEND") == 0){
		string message = inMessage.substr(4);
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
			userMessage = "Too many users";
			sendfifo.openwrite();
			sendfifo.send(userMessage);
			sendfifo.fifoclose();
			
		}
	}
	
	if (inMessage.find("**SEND**") == 0){
		string message = inMessage.substr(8);
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
		cout << "Received - " << message << endl;
		chatLog.push_back(message);
	}
	
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	if (inMessage.find("KILL") == 0){
		userNum=userNum-1;
		cout << "Current Users: " << userNum << endl;
		if (userNum == 0){
		chatLog.clear();
		}
	}
	
	if (inMessage.find("GET") == 0){
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
	if (inMessage.find("**KILL**") == 0){
		chatLog.clear();
	}
	
	if (inMessage.find("**GET**") == 0){
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
		for (unsigned int i = 0; i < chatLog.size(); i++){
			string outMessage = chatLog[i];
			cout << outMessage << endl;
			sendfifo.openwrite();
			sendfifo.send(outMessage);
			sendfifo.fifoclose();
		}
	//After all the messages have been sent, send out the $END signal
		string outMessage = "$END";
		cout << outMessage << endl;
		sendfifo.openwrite();
		sendfifo.send(outMessage);
		sendfifo.fifoclose();
	}
  }
  return 0;
}