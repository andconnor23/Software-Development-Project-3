/* Verse class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: 
 */

#include "Verse.h"
#include <iostream>

using namespace std;

// Default constructor
Verse::Verse()
{  	
   verseText = "Uninitialized Verse!";
   verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s)
{
   // TODO: use Ref constructor to create verseRef
   verseRef = Ref(s);


   // store the remainder of the string in verseText

   
  string::size_type startPos = s.find_first_not_of(" ", 0);

  string::size_type endPos = s.find_first_of(" ", startPos);

  string cut = s.substr(endPos - startPos + 1, string::npos);
  verseText = cut;
 

}  	

// REQUIRED: Accessors
string Verse::getVerse()
{
   return verseText; 
}

Ref Verse::getRef()
{
   return verseRef;
}

// display reference and verse
void Verse::display()
{
   verseRef.display();
   cout << " " << verseText;
}
