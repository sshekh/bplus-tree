#include "node.hpp"
#include <utility>

struct Bptree {
  Bptree() {
    ifstream fin("bplustree.config");
    fin >> MAXK;
  }
  nptr root;
  void insert(double key, string data) {
    auto kn = root->insert(key);
  }
};
