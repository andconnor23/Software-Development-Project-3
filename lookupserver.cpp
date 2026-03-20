/***************************************************************************
 * sslookupserver.cpp  -  Program to serve Shakespeare search results
 *
 * copyright : (C) 2009 by Jim Skon
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "fifo.h"
#include "Bible.h"
#include "Ref.h"
#include "Verse.h"

using namespace std;

string receive_pipe = "request";
string send_pipe = "reply";

/* Server main line,create name MAP, wait for and serve requests */
int main()
{

   /* Create the communication fifos */
   Fifo recfifo(receive_pipe);
   Fifo sendfifo(send_pipe);

   Bible bible("/home/class/csc3004/Bibles/web-complete");
   LookupResult result;
   recfifo.openread(); // only open once

   // "infinite loop" for server: repeat each time a request is received
   while (true)
   {
      string request = recfifo.recv();
      cout << "Requested verses: " << request << endl;
      int book, chapter, verse, numberOfVerses;
      sscanf(request.c_str(), "%d:%d:%d", &book, &chapter, &verse);
      Ref ref(book, chapter, verse);
      Verse v = bible.lookup(ref, result);

      sendfifo.openwrite();

      if (result == SUCCESS) {
         sendfifo.send(v.getVerse());
      }
      else {
         sendfifo.send("Error: Verse not found");
      }

      sendfifo.send("$end");
      sendfifo.fifoclose();
   }
}
