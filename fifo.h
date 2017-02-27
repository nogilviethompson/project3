/***************************************************************************
* fifo.cpp  -  code to allow interprocess communication via a fifo, or "names pipe"
 *
* copyright : (C) 2009 by Jim Skon
*
* This code permits the creation and use of FIFOs for communication
* between processes.  
* 
* the named piped is created and used in /tmp
* 
***************************************************************************/
#ifndef FIFO_H
#define FIFO_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#define MaxMess 200
#define MODE 0777
#define MESSTERM '\n'
#define PATH "/tmp/"
  // SIGniture assures the pipe is unique amoung users
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#define SIG "ogilviethompsonh_"
=======
#define SIG "grigullb_"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
#define SIG "grigullb_"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
#define SIG "grigullb_"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba

using namespace std;

class Fifo {

 private: 

  int fd;   // File descriptor for pipes
  string pipename;
  
 public:
  // create a named pipe (FIFO)
  Fifo();
  Fifo(string);

  void openread();    // Start a new read transaction
  void openwrite();   // Start a new write transaction
  void fifoclose();       // Finish a transaction

string recv();    // Get the next record
  void send(string);    // Send a record
};
#endif
