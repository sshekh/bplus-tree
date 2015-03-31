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
    } else if(type == 2) {
      cin >> key >> range;
      tree.query(key - range, key + range);
    } else if(type == 4) {
       cin >> key >> key; 
    } else if(type == 5) {
        tree.print();
    }
  }
  fout.close();

  return 0;
}

