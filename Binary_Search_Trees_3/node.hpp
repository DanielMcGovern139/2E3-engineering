#pragma once
#include <string>

class node : public std::string {
  public:
  node();
  node(std::string chars, int number);
  // "before" points to the subtree of words that come
  // before this word in alphabetical order
  node *before;
  // "after" points to the subtree of words that come
  // after this word in alphabetical order, duh.
  node *after;
  node *next; // the next word in the list of words comprising the book
  node *list_of_later_occurrences; // pointer to the next occurrence of the same word
  node *end_of_list_of_later_occurrences;
  int word_number;
  int count; // number of times it is added to the tree
};
