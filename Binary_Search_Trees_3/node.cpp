#include "node.hpp"

node::node() {
	count = 1;
	next = nullptr;
  before = nullptr;
  after = nullptr;
  list_of_later_occurrences = nullptr;
  end_of_list_of_later_occurrences = nullptr;
}

node::node(std::string chars, int number) : node() {
	word_number = number;
	this->assign(chars);
}
