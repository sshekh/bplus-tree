#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;

int MAXK;

/* Node for the B+ tree
 * Nptr is pointer to node
 */
struct nptr {
  char fname[15];
  static int cnt;
  nptr() {}
  void open() {
    ++cnt;
    sprintf(fname, "nodes/%.4d", cnt);
  }
};

int nptr::cnt = 0;

struct node {
  vector<double> keys;
  vector<nptr> children;
  int k;
  bool isLeaf;
  nptr This;    // file for itself
  node(const nptr s) : isLeaf(false), k(0), This(s) {}
  node() : isLeaf(false), k(0) {}
  void load() {
    ifstream fin(This.fname);
    fin >> k >> isLeaf;
    keys.resize(k); children.resize(k);
    for(int i = 0; i < k; ++i) fin >> keys[i]; 
    for(int i = 0; i < k + 1; ++i) fin >> children[i].fname;
  }
  void unload() {
    ofstream fout(This.fname);
    fout << k << " " << isLeaf << "\n";
    for(int i = 0; i < k; ++i) fout << keys[i] << " "; fout << "\n";
    for(int i = 0; i < k + 1; ++i) fout << children[i].fname << " "; fout << "\n";
  }
  // Returns the key and pointer of the new child created of nd
  pair<double, nptr> insert(double key);
};

node operator*(const nptr s) {
  shared_ptr<node> np(new node(s));
  np->load();
  return *np;
}

nptr operator&(const node nd) {
  return nd.This;
}

pair<double, nptr> node::insert(double key) {  
  
}
#endif
