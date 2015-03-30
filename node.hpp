#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdio>
using namespace std;
/* Node for the B+ tree
 * Nptr is pointer to node
 */


#ifndef NODE_H
#define NODE_H
int MAXK;

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
  int nk;
  bool isLeaf;
  nptr This;    // file for itself
  node(const nptr s) : isLeaf(false), nk(0), This(s) {}
  node() : isLeaf(false), nk(0) {}
  void load() {
    ifstream fin(This.fname);
    fin >> nk >> isLeaf;
    keys.resize(nk); children.resize(nk);
    for(int i = 0; i < nk; ++i) fin >> keys[i]; 
    for(int i = 0; i < nk + 1; ++i) fin >> children[i].fname;
  }
  void unload() {
    ofstream fout(This.fname);
    fout << nk << " " << isLeaf << "\n";
    for(int i = 0; i < nk; ++i) fout << keys[i] << " "; fout << "\n";
    for(int i = 0; i < nk + 1; ++i) fout << children[i].fname << " "; fout << "\n";
  }
};

node operator*(const nptr s) {
  shared_ptr<node> np(new node(s));
  np->load();
  return *np;
}

nptr operator&(const node nd) {
  return nd.This;
}
#endif
