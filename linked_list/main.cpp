//Write a program, using linked lists, to read the contents of a book, such as might be found at the Gutenberg Project, and print out a list of the words and the number of times they occur, in order of their first occurrence.



#include <iostream>
#include <string>
#include "word.hpp"

using namespace std;

int main() {

word* book_head = nullptr; //definition of linked list.. initially no words in this book
string temp_word;
cin >> temp_word;
book_head = new word(); // create new linked list object to store book_head
book_head -> assign(temp_word); //assigning book_head the value it just read in (temp)..link
  
while (cin.eof() == false) {
  cin >> temp_word;	
  bool found = false; 
  word* w = book_head; //w is a pointer too a linked list object which points to book_head
    
  while (w != nullptr){	
    if (*w == temp_word){ //if incoming word is equal to the current word w the add it to total..remember w iterate through the list and so we can compare the words 
      w-> count++; 
      found = true;
        }

    else if (w->next != nullptr){
        //we move to the next word in the list
        //we are trying to see if the word is already in the the linked list  
      w = w->next;	// go to w's next value 
        }
        
    else { //else the word has not been found in the list so
    //we need to add the newword to the linked list
      word* next_word = new word(); //next_word is a pointer_
       //new link_list object to store next word
      next_word -> assign(temp_word); // assigning next word the value of the word
      w->next = next_word;  //the next word in the list which  w points to will be assigned next_word
      found = true; //the new word now exists in the list
        }	

      if (found)
          break;	//break the inner while loop when we have new word	
      } 
    } 

  word* w = book_head; //print the list starting from the head 
  while (w != nullptr) {
  	cout << "\"" << *w  << "\" " << w->count << endl; // dereferencing w
    w = w->next;
  }

  // Delete objects in list
  w = book_head;
  while (w != nullptr) {
    word* t = w->next;
    delete w;
    w = t;
  }
} 
//E.G
// head
// w
// WE - FEEL - THAT - THE 

//so everytime a new word is added down the bottom of the list,  w always restarts on the head node  and goes thru the list comparing each value in the list with the incoming word
//if the word isnt in the list we add it to the end of list 
