#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int MAXK;

/* Node for the B+ tree
 * Nptr is pointer to node
 */
struct nptr {
  char fname[15];
  static int cnt;
  nptr() { strcpy(fname, "Null"); }
  void open() {
    sprintf(fname, "nodes/%.4d", cnt);
    ++cnt;
  }
};

int nptr::cnt = 0;

struct node {
  vector<double> keys;
  vector<nptr> children;
  bool isLeaf;
  int k;
  nptr This;    // file for itself
  node(const nptr s) : isLeaf(false), This(s), k(0) { }
  node() : isLeaf(false), k(0) {}
  void load() {
    ifstream fin(This.fname);
    fin >> k >> isLeaf;
    keys.resize(k); children.resize(k + 1);
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
  void print() {
    cerr << "size of node = " << k << " ";
    fprintf(stderr, "name = %s\n", This.fname + 6);
    for(int i = 0; i < children.size(); ++i) {
      fprintf(stderr, "%s", children[i].fname + 6);
      if(i < keys.size()) fprintf(stderr, ",%.2lf,", keys[i]);
    }
    cerr << endl;
  }
};

node operator*(const nptr& s) {
  shared_ptr<node> np(new node(s));
  np->load();
  return *np;
}

nptr operator&(const node& nd) {
  return nd.This;
}

pair<double, nptr> node::insert(double key, nptr keyf) {
  if(isLeaf) {
    int idx = lower_bound(keys.begin(), keys.end(), key) - keys.begin();
    keys.insert(idx + keys.begin(), key); ++k;
    children.insert(idx + children.begin(), keyf);
    double newk = -1;
    nptr newsib;
    if(k > MAXK) {
      idx = (MAXK  + 1) / 2;
      newsib.open();
      node new_sib(newsib);
      new_sib.isLeaf = true;
      new_sib.keys.assign(keys.begin() + idx, keys.end()); new_sib.k = new_sib.keys.size();
      newk = new_sib.keys[0];
      new_sib.children.assign(children.begin() + idx, children.end());
      keys.resize(idx); k = idx;
      children.resize(idx);
      children.push_back(newsib);
      new_sib.dump();
    }
    dump();
    return make_pair(newk, newsib);
  } else {
    int idx = upper_bound(keys.begin(), keys.end(), key) - keys.begin();
    auto newc = (*children[idx]).insert(key, keyf);   // newc.first is the starting key, newc.second is the node with >= newc.first
    if(newc.first == -1) return newc;   // no new child created
    idx = upper_bound(keys.begin(), keys.end(), newc.first) - keys.begin();
    keys.insert(idx + keys.begin(), newc.first); ++k;
    children.insert(idx + 1 + children.begin(), newc.second);
    double newk = -1;
    nptr newsib;
    if(k > MAXK) {
      idx = (MAXK + 1) / 2; // idx is middle element
      newsib.open();
      node new_sib(newsib);
      new_sib.keys.assign(keys.begin() + idx + 1, keys.end()); new_sib.k = new_sib.keys.size();
      new_sib.children.assign(children.begin() + idx + 1, children.end());
      newk = keys[idx];
      keys.resize(idx); k = idx;
      children.resize(idx + 1);
      new_sib.dump();
    }
    dump();
    return make_pair(newk, newsib);
  }
}

void rprint(node nd) {
    if(nd.isLeaf) {
      cerr << "leaf " << nd.This.fname << "\n";
      for(int i = 0; i < nd.keys.size(); ++i) {
        ifstream fin(nd.children[i].fname);
        string data; fin >> data;
        cerr << nd.children[i].fname << " (" << nd.keys[i] << "," << data << ")" << " ";
        fin.close();
      }
      cerr << " -> " << nd.children[nd.keys.size()].fname <<"\n";
    } else {
      nd.print();
      for(nptr childp : nd.children) rprint(*childp);
    } 
}

#endif
