#include "node.hpp"
#include <utility>

struct Bptree {
  Bptree() {
    ifstream fin("bplustree.config");
    fin >> MAXK;
  }
  nptr root;

};
