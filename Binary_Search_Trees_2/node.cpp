#include "node.hpp"
#include <string>

node::node() {
  count = 1;
  before = nullptr;
  after = nullptr;
}

node::node(std::string s) : node() {
  assign(s);
}
