#include "node.hpp"
#include "bptree.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int main() {
  Bptree tree;
  int type;
  ofstream fout;
  fout.open("time.out", ios::out);
  double key, range; 
  string data;
  chrono::time_point<Clock> start, end;
  chrono::duration<double> diff;
  unsigned fstart, fend;
  while(cin >> type) {
    switch(type) {
      case 0 :
        cin >> key >> data;
        fstart = tree.now();
        start = Clock::now();

        tree.insert(key, data);
        
        end = Clock::now();
        fend = tree.now();
        diff = end - start;
        fout << type << " " << diff.count() << " " << fend - fstart << "\n";
        //fout << key << " " << data << "\n";
        break;
      case 1 :
        cin >> key;
        //cout << "searching " << key << "\n";
        fstart = tree.now();
        start = Clock::now();

        tree.query(key, key);
        
        end = Clock::now();
        fend = tree.now();
        diff = end - start;
        fout << type << " " << diff.count() << " " << fend - fstart << "\n";
        break;
      case 2:
        cin >> key >> range;
        //cout << "ranging " << key - range << " " << key + range << "\n";
        fstart = tree.now();
        start = Clock::now();

        tree.query(key - range, key + range);
        
        end = Clock::now();
        fend = tree.now();
        diff = end - start;
        fout << type << " " << diff.count() << " " << fend - fstart << "\n";
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

