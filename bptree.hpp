#include "node.hpp"
#include <utility>

struct Bptree {
  Bptree() {
    ifstream fin("bplustree.config");
    fin >> MAXK >> nptr::cnt;
    if(nptr::cnt != 0) fin >> root.fname;
  }
  ~Bptree() {
    ofstream fout("bplustree.config");
    fout << MAXK << " " << nptr::cnt << " " << root.fname << "\n";
  }
  nptr root;
  void insert(double key, string data) {
    nptr dataf; dataf.open();
    ofstream fout(dataf.fname);
    fout << data;
    fout.close();
    if(nptr::cnt == 1) {  // tree not created yet, (one node created for data)
      root.open();
      node root_node(root);
      root_node.isLeaf = true;
      root_node.insert(key, dataf);
    } else {
      node root_node(root);
      auto kn = root_node.insert(key, dataf);
      if(kn.first == -1) return;
      nptr newr; newr.open();
      cerr << "new root = (" << kn.first << "," << newr.fname << "->" << root.fname << "," << kn.second.fname << ")\n";
      node new_rnode(newr);
      new_rnode.clear();    // it will try to load data from newr, which may push junk in it
      new_rnode.keys.push_back(kn.first); ++new_rnode.k;
      new_rnode.children.push_back(root);
      new_rnode.children.push_back(kn.second);
      root = &new_rnode;
      for(nptr d : new_rnode.children) cerr << d.fname << " ";
      new_rnode.dump();
    }
  }
  void print() {
    cerr << "starting with root:\n";
    rprint((*root));
  }
};
