#include "node.hpp"
#include "bptree.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main() {
  Bptree tree;
  int type;
  ofstream fout;
  fout.open("inserted", ios::out | ios::app);
  double key, range; 
  string data;
  while(cin >> type) {
    switch(type) {
      case 0 :
        cin >> key >> data;
        tree.insert(key, data);
        fout << key << " " << data << "\n";
        break;
      case 1 :
        cin >> key;
        cout << "searching " << key << "\n";
        tree.query(key, key);
        break;
      case 2:
        cin >> key >> range;
        cout << "ranging " << key - range << " " << key + range << "\n";
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

