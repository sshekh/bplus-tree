#include "node.hpp"
#include "bptree.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  Bptree tree;
  //tree.insert(0.56, "hello");
  //tree.insert(0.99, "world");
  int q;
  cin >> q;
  while(q--) {
    double key; string data;
    cin >> key >> data;
    tree.insert(key, data);
  }
  tree.print();

  return 0;
}

