/*****************************************************************************/
/*                                                                           */
/*  Filename:     indexclienttest.cpp                                        */
/*  Author(s):    Jim Skon                                                   */
/*  Last Update:  2/10/2013                                                  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

//Stuff for pipes                                                               
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fifo.h"
   
using namespace std;

// Pipes for communication 
string receive_pipe = "reply";
string send_pipe = "request";

int main () {

  // Word is the word we are looking for
  string word;  
  Fifo recfifo(receive_pipe);
  Fifo sendfifo(send_pipe);


  while (1){
    cout << "Enter verse: (book:chapter:verse) " << endl;
    cin >> word;

    sendfifo.openwrite();
    sendfifo.send(word);

    // prepare the output              
    cout << "Content-Type: text/plain\n\n"
	 << "Search string: " << word << endl;

    // output the response to the web page
    recfifo.openread();
    string results = "";
    while (results != "$end") {
      results = recfifo.recv();
      if (results != "$end") {
	cout << results << endl;
      }
    }
  recfifo.fifoclose();
  sendfifo.fifoclose();
  }
 
  return 0;
}
  
