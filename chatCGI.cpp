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
  string results = "hi";
  
  // Create AJAX objects to recieve information from web page.
  form_iterator uname = cgi.getElement("uname");
  form_iterator message = cgi.getElement("message");

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);s
  
  // Call server to get results
  string stMessage = **message;
  string stUsername = **uname;
  
  cout << "Content-Type: text/plain\n\n";
  /* Get a message from a server and then cout it*/
  /* Repeat until the $END signal is received */
  do{
  recfifo.openread();
  results = recfifo.recv();
  recfifo.fifoclose();
  if (results.find("$END") == string::npos)
  {
  results = results + "<p>";
  cout << results << endl;
  }
  } while (results.find("$END") == string::npos);
  
  
  return 0;
  }
