/* sslookupclient.cpp
 * Shakespeare full-text search client:
 * receives an Ajax request from web client
 * extracts search string, and sends request to sslookupserver
 */
#include <iostream>
#include <fstream>
#include <string>

// Stuff for Ajax
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

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
#include <list>
#include "fifo.h"
using namespace std;


#define LOG_FILENAME "/home/class/csc3004/tmp/andconnor-lookupclient.log"
#define logging // enable log file
#include "logfile.h"

// Pipes for communication
string receive_pipe = "reply";
string send_pipe = "request";

int main()
{
   // prepare the response output,
   // send required header before any other output

   cout << "Content-Type: text/html\r\n\r\n";
   Cgicc cgi;

   form_iterator book = cgi.getElement("book");
   form_iterator chapter = cgi.getElement("chapter");
   form_iterator verse = cgi.getElement("verse");
   form_iterator num = cgi.getElement("num_verse");

   string b = (book != cgi.getElements().end()) ? **book : "1";
   string c = (chapter != cgi.getElements().end() && **chapter != "") ? **chapter : "1";
   string v = (verse != cgi.getElements().end() && **verse != "") ? **verse : "1";
   string n = (num != cgi.getElements().end() && **num != "") ? **num : "1";

   string searchString = b + ":" + c + ":" + v + ":" + n;

   int length = searchString.length();

   Fifo recfifo(receive_pipe);
   Fifo sendfifo(send_pipe);

#ifdef logging
   logFile.open(logFilename.c_str(),ios::out);
#endif

   sendfifo.openwrite();
   log("Open request pipe");

   // Call server to get results
   sendfifo.send(searchString);
   log("Request: "+searchString);

   recfifo.openread();
   log("Open reply fifo");

   // output the response to the web page
   string results = "";
   int times = 0; // Counter for header lines
   while (true)
   {
      results = recfifo.recv();

      if (results == "") continue;

      if (results == "$end")
         break;

      log("Reply: "+results);
      if (results != "$end")
      {
         int pos = results.find("|");
         string text = results;

         if (pos != string::npos) {
            text = results.substr(pos + 1);
         }

         cout << text << "<br>";
      }
   }
   cout << endl; // flush output when done

   recfifo.fifoclose();
   log("close reply fifo");

   sendfifo.fifoclose();
   log("close request fifo");

   return 0;
}
