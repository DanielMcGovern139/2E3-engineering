// use a binary tree to store the words in the sample text and output them in order of their occurance, 'the' would be printed out first because it appears most often in the text'... called a frquency tree 

#include <iostream>
#include <string>
#include <fstream>
#include "node.hpp"

using namespace std;

// forward declarations
bool add_node_to_tree_alphabetically(string st, node*& tree);
// note: alphabetically above means keyed by alphabetical order of words
void add_node_to_tree_numerically(string st, int frequency, node*& tree);
// note: numerically above means keyed by frequency
void alphabetic_tree_to_frequency_tree(node* alphabetic_tree, node*& frequency_tree);

void print_tree(node* tree);
void print_tree_backward(node* tree);
void delete_tree(node* tree);

int main() {
  int unique_word_count = 0;
  node* alphabetic_tree = nullptr;
  string ifilename;
  ifstream ifile;
  // bool file_opened;
  do {
    cout << "Enter book's filename:" << endl;
    cin >> ifilename;
    ifile.open(ifilename);
    if (ifile.is_open() == false) {
      cout << "Can't open file \"" << ifilename << "\"." << endl;
    }
  } while (!ifile.is_open());

  while (!ifile.eof()) {
    string temp;
    ifile >> temp;
    if (!ifile.fail()){
      if (add_node_to_tree_alphabetically(temp,alphabetic_tree) == true) { // it's a whole new word
        unique_word_count++;
      } 
      // process the incoming word
    }
  }
  ifile.close();

  //cout << "Alphabetic Tree:" << endl;
  //print_tree(alphabetic_tree);
  
  // now, create a new tree with the nodes odered by their frequencies.

  node* frequency_tree = nullptr;
  alphabetic_tree_to_frequency_tree(alphabetic_tree,frequency_tree);

  cout << endl << "Frequency Tree:" << endl;
  print_tree_backward(frequency_tree); //we need to print the tree from right to left so starting with 
                                       //largest count 

  // clean up
  delete_tree(alphabetic_tree); 
  delete_tree(frequency_tree);

}

bool add_node_to_tree_alphabetically(string st, node*& tree) {
  bool resp;
  if (tree == nullptr) {
    tree = new node(st); // the new tree consists of just this node
    resp = true;
 }
  else if (st == *tree) { // if the strings have the same sequence of characters
      tree->count++;
      resp = false;
    } 
  else {
    if (st < *tree) {
        resp = add_node_to_tree_alphabetically(st,tree->before);
  } else {
        resp = add_node_to_tree_alphabetically(st,tree->after);
      }
    }
  return resp;
}

//making a count tree
void add_node_to_tree_numerically(string st, int frequency, node*& tree) {
  if (tree == nullptr) {
    tree = new node(st); // the new tree consists of just this node
    tree->count = frequency;
  } else {
    if (frequency < tree->count) {
      add_node_to_tree_numerically(st, frequency, tree->before); 
    } else {
      add_node_to_tree_numerically(st, frequency, tree->after);
    }
  }
}

//deletes tree
void delete_tree(node* tree) {
  if (tree != nullptr) {
    delete_tree(tree->before);
    delete_tree(tree->after);
    delete tree;
  }
}

// this traverses the tree "forwards" -- first to last
void print_tree(node* tree) {
  if (tree != nullptr) {
    print_tree(tree->before); 
    cout << *tree << " " << tree->count << endl;
    print_tree(tree->after);
  }
}

// this traverses the tree "backwards" -- last to first
void print_tree_backward(node* tree) {
  if (tree != nullptr) {
    print_tree_backward(tree->after); //keep going to the furtherst point to the right 
    cout << *tree << " " << tree->count << endl; //print its value
    print_tree_backward(tree->before); // go to the node just before that one and loop back and print it

    //when you loop around for the second time you will try and go further right, you will be as far right as poossible and then just print it 
  } 
}

//here we just take one word at a time from the alphabetic tree and put it in the frequency tree
void alphabetic_tree_to_frequency_tree(node* alphabetic_tree, node*& frequency_tree){
  if (alphabetic_tree != nullptr) {
    alphabetic_tree_to_frequency_tree(alphabetic_tree->before, frequency_tree);
    add_node_to_tree_numerically(*alphabetic_tree, alphabetic_tree->count, frequency_tree);
    alphabetic_tree_to_frequency_tree(alphabetic_tree->after, frequency_tree);
  }
}
