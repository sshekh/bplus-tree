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
  fout.open("res.out", ios::out);
  double key, range; 
  string data;
  clock_t start, end;
  while(cin >> type) {
    switch(type) {
      case 0 :
        cin >> key >> data;
        start = clock();
        tree.insert(key, data);
        end = clock();
        fout << type << " " << (end - start) << "\n";
        //fout << key << " " << data << "\n";
        break;
      case 1 :
        cin >> key;
        //cout << "searching " << key << "\n";
        start = clock();
        tree.query(key, key);
        end = clock();
        fout << type << " " << (end - start) << "\n";
        break;
      case 2:
        cin >> key >> range;
        //cout << "ranging " << key - range << " " << key + range << "\n";
        start = clock(); 
        tree.query(key - range, key + range);
        end = clock();
        fout << type << " " << (end - start) << "\n";
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

