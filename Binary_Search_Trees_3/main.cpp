/*
Write a program to read the contents of a book, such as might be found at the Gutenberg Project, and store the words and the number of times they occur in a Binary Tree
The book must be read from a file, and not from the standard input cin. Once the book is read in, the program must print out the total number of words in the book and the 
total number of distinct words. Then the user should be asked to enter a word and the program should print out all word pairs that start with that inputted word. So if the
user enters the word "the", the program should print the total number of pairs and list them with the number of occurrences of the word pair, as exemplified below.

e.g Word pairs starting with "the" were found 29 times.
"the Monophysite" was found once.
"the barbarians," was found once.
"the boundless" was found once. 

The user should be able to repeatedly enter and search for words until the they terminate the program. 

*/

#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"

using namespace std;


void delete_tree(node* tree);
void print_word_pairs_tree(string first_word, node* second_words_tree);
bool add_word_to_tree(node*& word, node*& tree);
node* find_word_node(string word_to_check, node* tree);

int main() {
  bool file_opened = false;
	string filename;
	ifstream ifile;

	while (file_opened == false) {
		cout << "Please enter the name of the book file:" << endl;
		cin >> filename;
		ifile.open(filename);
		if (ifile.is_open()) { // is_open() is a method which will return true if the open() succeeded
			file_opened = true;
		} else {
			cout << "An error occurred attempting to open the file \"" << filename << "\"." << endl;
		}
	}

	node* tree = nullptr; // start with an empty tree
	node* book = nullptr; // and an empty book
	node* end_of_book = nullptr;
  int wordcount = 0; // optional
  int individual_word_count = 0; // optional

  while (ifile.eof() == false) {
    string t_word;
    ifile >> t_word;
    if (ifile.fail() == false) {
			wordcount++;
			// here, wordcount is effectively the word number in the book
			// useful for debugging.
			node* new_node = new node(t_word, wordcount);
			// the new word is added to the tree and also
			// added to the list of words comprising the book
			// here, add to the tree
      if (add_word_to_tree(new_node, tree)) {
      	individual_word_count++;
      }
      // here, add to the sequence of words comprising the book
      if (book == nullptr) {
      	book = new_node;
      	end_of_book = new_node;
      } else {
      	end_of_book->next = new_node;
      	end_of_book = new_node;
      }
    }
  }
  ifile.close();
  cout << "The file \"" << filename << "\" contains " << wordcount << " words of which " << individual_word_count << " are distinct." << endl;
  
  while(cin.eof() == false){
    cout << "please enter a word you wish to check" << endl;
    string word_to_check;
    cin >> word_to_check;
    if(cin.fail() == false){
      //locate the node for this word_to_check in the tree 
      node* word_node = find_word_node(word_to_check, tree);
      if(word_node == nullptr){
        cout << "the word " << word_to_check << "was not found" << endl;
      }
       else { //create a new tree to hold all the subsequent words
         node* second_words_tree = nullptr;
         int second_word_count = 0;
         node* tlist = word_node;
         do { //attempt to access each subsequent word 
           
             node* tnext = tlist->next;
             if(tnext != nullptr){
               //add the new second word to the search
               node* second_word = new node(*tnext, tnext->word_number);
               add_word_to_tree(second_word, second_words_tree);
               second_word_count++;
             }
             tlist = tlist->list_of_later_occurrences;
         } while(tlist != nullptr);
         
          switch(second_word_count){
            case 0:
						cout << "Word pairs starting with \"" << word_to_check << "\" were not found." << endl;
						break;
					case 1:
						cout << "Word pairs starting with \"" << word_to_check << "\" were found once." << endl;
						break;
					case 2:
						cout << "Word pairs starting with \"" << word_to_check << "\" were found twice." << endl;
						break;
					default:
						cout << "Word pairs starting with \"" << word_to_check << "\" were found " << second_word_count << " times." << endl;
						break;
          }

          // now, print out the second word tree
				print_word_pairs_tree(word_to_check, second_words_tree);
				// now delete the second_word_tree
				delete_tree(second_words_tree);
       }
    }
  }


  
  return 0;
}

// returns true if the word is new, false otherwise
bool add_word_to_tree(node*& word, node*& tree) {
	bool response;
	
  if (tree == nullptr) {
		tree = word;
		response = true; // it is a new word
	} 
  else if (*word == *tree) {
			tree->count++;
			response = false; // it is not a new word
			if (tree->list_of_later_occurrences == nullptr) { // if it's the second occurrence
				tree->list_of_later_occurrences = word;//list_of_later_occurrences points to the word..like the next pointer 
				tree->end_of_list_of_later_occurrences = word;
			} else { // it's a subsequent occurrence
       //the end_of_list_of_later_occurrences pointer points to the word 
				tree->end_of_list_of_later_occurrences->list_of_later_occurrences = word;
				tree->end_of_list_of_later_occurrences = word;
			}
		} 
   else {
			  if(*word < *tree) {
				response = add_word_to_tree(word, tree->before);
			} else {
				response = add_word_to_tree(word, tree->after);
			}
		}
	
	return response;
}

//returns the node for the particular word, so if the function returns the response as the nullptr then the word was not found 
node* find_word_node(string word_to_check, node* tree) {
	node* response;
	if (tree == nullptr) {
		response = nullptr;
	} else {
		if (word_to_check == *tree) {
			response = tree;
		} else {
			if (word_to_check < *tree) {
				response = find_word_node(word_to_check, tree->before);
			} else {
				response = find_word_node(word_to_check, tree->after);
			}
		}
	}
	return response;
}

void delete_tree(node *tree) {
	if (tree != nullptr) {
		delete_tree(tree->before);
		delete_tree(tree->after);
		delete tree;
	}
}

void print_word_pairs_tree(string first_word, node* second_words_tree) {
  if (second_words_tree != nullptr) {
    print_word_pairs_tree(first_word, second_words_tree->before);
    switch (second_words_tree->count) {
    	case 1:
    		cout << "\"" << first_word << " " << *second_words_tree << "\" was found once." << endl;
    		break;
    	case 2:
    		cout << "\"" << first_word << " " << *second_words_tree << "\" was found twice." << endl;
    		break;
    	default:
    		cout << "\"" << first_word << " " << *second_words_tree << "\" was found " << second_words_tree->count << " times." << endl;
    		break;
    }
    print_word_pairs_tree(first_word, second_words_tree->after);
  }
}
