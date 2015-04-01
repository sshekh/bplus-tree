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
    switch(type) {
      case 0 :
        cin >> key >> data;
        tree.insert(key, data);
        fout << key << " " << data << "\n";
        break;
      case 1 :
        cin >> key;
        tree.query(key, key);
        break;
      case 2:
        cin >> key >> range;
        tree.query(key - range, key + range);
        break;
      case 4 :
        cin >> key >> key;    // do nothing
        break;
      case 5:
        tree.print();
        break;
      default:
        cerr << "Wrong type!!!!!\n";
    }
  }
  fout.close();

  return 0;
}

