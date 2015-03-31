#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdio>
#include <algorithm>
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
  void dump() {
    ofstream fout(This.fname);
    fout << k << " " << isLeaf << "\n";
    for(int i = 0; i < k; ++i) fout << keys[i] << " "; fout << "\n";
    for(int i = 0; i < k + 1; ++i) fout << children[i].fname << " "; fout << "\n";
  }
  // Returns the key and pointer of the new child created of nd
  pair<double, nptr> insert(double key, nptr file);
};

pair<double, nptr> node::insert(double key, nptr keyf) {
  if(isLeaf) {
    int idx = lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    keys.insert(idx, key);
    children.insert(idx, keyf);
    ++k;
    double newk = -1;
    nptr newsib;
    if(k > MAXK) {
      idx = (MAXK  + 1) / 2;
      news.open();
      node new_sib(newsib);
      new_sib.isLeaf = true;
      new_sib.keys.assign(keys.begin() + idx, keys.end());      
      newk = new_sib.keys[0];
      new_sib.children.assign(children.begin() + idx, children.end());
      keys.resize(idx);
      children.resize(idx);
      children.push_back(newsib);
      new_sib.dump();
    }
    dump(); 
    return make_pair(newk, newsib);
  } else {
    int idx = lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    auto newc = (*children[idx]).insert(key, keyf);   // newc.first is the starting key, newc.second is the file
    if(newc.key == -1) return newc;   // no new child created
    idx = lower_bound(keys.begin(), keys.end(), newc.first) - keys.begin();
    keys.insert(idx, newc.first);
    children.insert(idx, newc.second);
    ++k;    
    double newk = -1;
    nptr newsib;
    if(k > MAXK) {
      idx = (MAXK + 1) / 2; // idx is middle element
      newr.open();     
      node new_sib(newsib);
      new_sib.keys.assign()
    }
  }
}

node operator*(const nptr s) {
  shared_ptr<node> np(new node(s));
  np->load();
  return *np;
}

nptr operator&(const node nd) {
  return nd.This;
}

#endif
