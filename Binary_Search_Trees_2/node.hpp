#pragma once
#include <string>

class node : public std::string {
  public:
    node();
    node(std::string s); // pass in the string of characters to set the node to
    int count; // number of times the word represented by this node occurs
    node* before; // tree of nodes of all words that come "before" this one.
    node* after; // tree of nodes of all words that come "after" this one.
};
