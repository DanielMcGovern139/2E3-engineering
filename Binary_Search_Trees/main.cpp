/*
A program to read the contents of a book, such as might be found at the Gutenberg Project, and store the words and the number of times they occur in a binary tree. 
The book is read from a file and not from a standard input cin. The program must print out the total number of words in the book and the total number of distinct words.
Then the user can be asked to enter a word, if the entered word is in the book, the program must print the number of times that word occurs in the book.  If the word does not
occur a suitable message should be printed.  The user should be allowed to repeatedly search for words until they want to termiante the program.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"

using namespace std;

// forward declarations
void print_tree(node *tree);
bool process_word(string new_word, node*& tree);
int get_word_count(string word_to_check, node* tree);

int main() {
	bool file_opened = false;
	string filename;
	ifstream ifile;

	while (file_opened == false) { //this while loop only deals with whether the file can be opened
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
  int wordcount = 0; // optional
  int individual_word_count = 0; // optional

  while (ifile.eof() == false) {
    string t_word;
    ifile >> t_word;
    if (ifile.fail() == false) {
			wordcount++;
      if (process_word(t_word, tree)) {
      	individual_word_count++;
      }
    }
  }
  ifile.close();
  cout << "The file \"" << filename << "\" contains " << wordcount << " words of which " << individual_word_count << " are distinct." << endl;

  // print_tree(tree);

  while (cin.eof() == false) {
  	cout << "Please enter the word you wish to check:" << endl;
  	string word_to_check;
  	cin >> word_to_check;
  	if (cin.fail() == false) {
			int occurrence_count = get_word_count(word_to_check, tree);
			switch (occurrence_count) {
				case 0:
					cout << "The word \"" << word_to_check << "\" was not found." << endl;
					break;
				case 1:
					cout << "The word \"" << word_to_check << "\" was found once." << endl;
					break;
				case 2:
					cout << "The word \"" << word_to_check << "\" was found twice." << endl;
					break;
				default:
					cout << "The word \"" << word_to_check << "\" was found " << occurrence_count << " times." << endl;
					break;
			}
  	}
  }
  cout << "Goodbye" << endl;
  return 0; // tell the OS everything is peachy
}

// returns the number of times a word is found or zero if not found
int get_word_count(string word_to_check, node* tree) {
	int response;
	if (tree == nullptr) {
		response = 0; // word definitely not found
	} 
  else if (word_to_check == *tree) {
			response = tree->count; // found it
		} 
    
  else {
			if (word_to_check < *tree) {
				response = get_word_count(word_to_check, tree->before);
			} 
      else {
				response = get_word_count(word_to_check, tree->after);
			}
		}
	
	return response;
}

// returns true if the word is new, false otherwise
bool process_word(string new_word, node*& tree) {
	bool response;
	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_word);
		response = true; // it is a new word
	}
  else if (new_word == *tree) {
			tree->count++;
			response = false; // it is not a new word
		} 
  else {
			if (new_word < *tree) {
				response = process_word(new_word, tree->before);
		  }
      else {
				response = process_word(new_word, tree->after);
			}
		}
	
	return response;
}

void print_tree(node *tree) {
  if (tree != nullptr) {
    print_tree(tree->before);
    cout << "\"" << *tree <<"\" " << tree->count << endl;
    print_tree(tree->after);
  }
}
