/* Ref class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: Andrew Connor
 */

#include "Ref.h"
#include <iostream>
#include <string>

using namespace std;

/* GetNextToken - general routine for getting next token from a string
 * Parameters
 *    str - string to search. search is destructive, i.e., token is removed.
 *    delimiters - string, a list of characters to use a delimiters between tokens
 * Returns: string token (removed from str)
 */
string GetNextToken(string& str, const string& delimiters = " ")
{
    // Find first non-delimiter
   size_t startPos = str.find_first_not_of(delimiters);

   // If no token found ? return empty safely
   if (startPos == string::npos) {
      str = "";
      return "";
   }

   // Find end of token
   size_t endPos = str.find_first_of(delimiters, startPos);

   // Extract token
   string next;
   if (endPos == string::npos) {
      next = str.substr(startPos);
      str = "";
   } else {
      next = str.substr(startPos, endPos - startPos);
      str = str.substr(endPos + 1);
   }

   return next;
}

// Ref member functions

// Default constructor
Ref::Ref() {book = 0; chapter = 0; verse = 0;}  	

// Parse constructor - receives a line "34:5:7 text"
Ref::Ref(const string s)
{ 
   string rtext = s; // make local copy of string to avoid modifying parameter
   // parse the reference - notice, currently there is no error checking!
    
   // Get book number
   string strbook = GetNextToken(rtext,":");
   book = atoi(strbook.c_str());
    
   // Get the chapter number
   string strchap = GetNextToken(rtext,":");
   chapter = atoi(strchap.c_str());
    
   // Get the verse number
   string strverse = GetNextToken(rtext," ");
   verse = atoi(strverse.c_str());
}

// Construct Ref from three integers
Ref::Ref(const int b, const int c, const int v) 
{ 	
   book = b;
   chapter = c;
   verse = v;
}

// Accessors
int Ref::getBook() const {return book;}	     // Access book number
int Ref::getChapter() const {return chapter;}	 // Access chapter number
int Ref::getVerse() const {return verse;}     // Access verse number


// REQUIRED: == comparison
bool Ref::operator==(Ref & ref)
{
   // TODO: implement comparison functions
   return (ref.getBook() == book && ref.getChapter() == chapter && ref.getVerse() == verse);
}

// OPTIONAL: define < and > comparisons

bool Ref::operator<(const Ref& ref) const{
   if (book != ref.getBook()){
      return book < ref.getBook();
   }
   else if (chapter != ref.getChapter()){
      return chapter < ref.getChapter();
   }
   else {
      return verse < ref.getVerse();
   }
}

// Display Reference
void Ref::display()
{
   std::string bookNames[66] = {"Genesis", "Exodus", "Leviticus", "Numbers", "Deuternonomy", "Joshua", "Judges", "Ruth", "1 Samuel", "2 Samuel",
      "1 Kings", "2 Kings", "1 Chronicles", "2 Chronicles", "Ezra", "Nehemiah", "Esther", "Job", "Psalms", "Proverbs", "Ecclesiastes", "Song of Solomon",
      "Isaiah", "Jeremiah", "Lamentations", "Ezekiel", "Daniel", "Hosea", "Joel", "Amos", "Obadiah", "Johah", "Micah", "Nahum", "Habakkuk", "Zepheniah",
      "Haggai", "Zechariah", "Malachi", "Matthew", "Mark", "Luke", "John", "Acts", "Romans", "1 Corinthians", "2 Corinthians", "Galatians", "Ephesians",
      "Philippians", "Colossians", "1 Thessalonians", "2 Thessalonians", "1 Timothy", "2 Timothy", "Titus", "Philemon", "Hebrews", "James", "1 Peter",
      "2 Peter", "1 John", "2 John", "3 John", "Jude", "Revelation"};
   string bookName = bookNames[book - 1];
   // TODO: modify display function to show book name instead of book number
   cout << bookName << " " << chapter << ":" << verse;
}
