#include "node.hpp"
#include <utility>

struct Bptree {
  Bptree() {
    ifstream fin("bplustree.config");
    fin >> MAXK;
  }
  nptr root;
  void insert(double key, string data) {
    nptr dataf; 
    dataf.open();
    ofstream fout(dataf.fname);
    fout << data;
    fout.close();
    //TODO check the case when root is Null
    node root_node(root);
    auto kn = root_node.insert(key, dataf);
  }
};
