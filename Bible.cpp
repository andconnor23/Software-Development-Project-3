 /* Bible class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: 
 */

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// Default constructor
Bible::Bible()
{ 
   infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; isOpen = false; }

// REQUIRED: lookup finds a given verse in this Bible
vector<Verse> Bible::lookup(Ref ref, LookupResult& status, int numberOfVerses)
{ 
   // TODO: scan the file to retrieve the line that holds ref ...
   instream.open(infile.c_str(), ios::in);
   instream.unsetf(ios::skipws);
   string str;
   status = OTHER; // placeholder until retreival is attempted
   isOpen = true;
   vector<Verse> verse(numberOfVerses);
   while (getline(instream, str)){
      Ref newRef = Ref(str);
      if (newRef.getBook() == ref.getBook()){
         // update the status variable
         if (newRef.getChapter() == ref.getChapter()){
            if (newRef.getVerse() == ref.getVerse()){
               status = SUCCESS;
               verse[0] = Verse(str);
	       break;
	    }
         }
	 if (newRef.getChapter() > ref.getChapter()){
	    status = NO_VERSE;
	    break;
	 }
      }
      if (newRef.getBook() > ref.getBook()){
	 status = NO_CHAPTER;
	 break;
      }
   }
   if (status == SUCCESS){
      for (int i = 1; i < numberOfVerses; i++){
         if (getline(instream, str)){
   	    Ref newRef = Ref(str);
	    if (newRef.getBook() > 66 && newRef.getChapter() > 22 && newRef.getVerse() > 21){
	       break;
            }
   	    verse[i] = Verse(str); 
         }
      }
   }
   if (status != SUCCESS){
      cerr << error(status) << endl;
   }
   // default verse, to be replaced by a verse object
   return verse;

}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status)
{
    if (!isOpen) {
        instream.open(infile.c_str(), ios::in);
        instream.unsetf(ios::skipws);
        isOpen = true;
    }

    string str;
    if (getline(instream, str)) {
        status = SUCCESS;
        return Verse(str);
    }

    status = NO_VERSE;
    return Verse();
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status)
{
   if (status == NO_BOOK){
      return "Book not recognized";
   }
   else if (status == NO_CHAPTER){
      return "Chapter not found";
   }
   else{
      return "Verse not found";
   }

}

void Bible::display()
{
   cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status)
{
   return ref;
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status)
{
   return ref;
}
