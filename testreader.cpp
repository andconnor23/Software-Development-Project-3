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

int main (int argc, char **argv){

   // Create Bible object to process the raw text file
   Bible webBible("/home/class/csc3004/Bibles/web-complete");

   int bookNum, chapterNum, verseNum, numberOfVerses;
   LookupResult result;

   cout << "Using Bible from: ";
   webBible.display();

   if (argc != 5){
      cerr << "Usage: " << argv[0] << " Enter a Bible book number, chapter, starting verse, and number of verses." << endl;
      exit(2);
   }

   bookNum = atoi(argv[1]);
   chapterNum = atoi(argv[2]);
   verseNum = atoi(argv[3]);
   numberOfVerses = atoi(argv[4]);

   if (bookNum < 1 || bookNum > 66) {
      result = NO_BOOK;
      cerr << webBible.error(result) << endl;
      exit(2);
   }
   // Create a reference from the numbers
   Ref ref(bookNum, chapterNum, verseNum);

   cout << webBible.getOffset(ref) << endl;

   Ref test1(1, 1, 1);
   Ref test2(1, 1, 2);
   Ref test3(1, 1, 3);
   Ref test4(66, 22, 21);

   cout << webBible.getOffset(test1) << endl;
   cout << webBible.getOffset(test2) << endl;
   cout << webBible.getOffset(test3) << endl;
   cout << webBible.getOffset(test4) << endl;

   // Use the Bible object to retrieve the verse by reference
//   cout << "Looking up reference: ";
//   ref.display();
//   cout << endl;

//   vector<Verse> verse = webBible.lookup(ref, result, numberOfVerses);
//   cout << "Result status: " << result << endl;
//   if (result == SUCCESS){
//     for (int i = 0; i < numberOfVerses; i++){
//	      if (!(verse[i].getVerse() == "Uninitialized Verse!")){
//   		   verse[i].display();
//	         cout << endl;
//      }
//	      else{
//		      cout << "Cannot display full number of verses due to reaching the end of the Bible." << endl;
//		      break;
//   	   }
//      }
//   }

}
