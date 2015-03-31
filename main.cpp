#include "node.hpp"
#include "bptree.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main() {
  Bptree tree;
  //tree.insert(0.56, "hello");
  //tree.insert(0.99, "world");
  int q, type;
  cin >> q;
  ofstream fout;
  fout.open("inserted", ios::out | ios::app);
  double key, range; 
  string data;
  while(q--) {
    cin >> type;
    if(type == 0) {
      cin >> key >> data;
      tree.insert(key, data);
      fout << key << " " << data << "\n";
    } else {
      cin >> key >> range;
      tree.query(key - range, key + range);
    }
  }
  fout.close();
  //tree.print();

  return 0;
}

