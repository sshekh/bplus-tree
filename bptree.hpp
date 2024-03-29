#include "node.hpp"
#include <utility>
#include <cstring>

const double EPS = 1e-10;

struct Bptree {
  Bptree() {
    ifstream fin("bplustree.config");
    fin >> MAXK; fin.close();
    fin.open("tree.config", ios::in);
    fin >> nptr::cnt;
    if(nptr::cnt != 0) fin >> root.fname >> fcnt;
    ++fcnt;
    fin.close();
  }
  ~Bptree() {
    ofstream fout("tree.config"); ++fcnt;
    fout << nptr::cnt << " " << root.fname << " " << fcnt << "\n";
    fout.close();
  }
  nptr root;
  vector< pair<double, string> > result;
  unsigned now() {    // get the total number of file accesses till now
    return fcnt;
  }
  void insert(double key, string data) {
    nptr dataf; dataf.open();
    ofstream fout(dataf.fname); ++fcnt;
    fout << data;
    fout.close();
    if(nptr::cnt == 1) {  // tree not created yet, (one node created for data)
      root.open();
      node root_node(root);
      root_node.isLeaf = true;
      root_node.insert(key, dataf);
    } else {
      node root_node = *root;
      auto kn = root_node.insert(key, dataf);
      if(kn.first == -1) return;
      nptr newr; newr.open();
      node new_rnode(newr);
      new_rnode.keys.push_back(kn.first); ++new_rnode.k;
      new_rnode.children.push_back(root);
      new_rnode.children.push_back(kn.second);
      root = &new_rnode;
      new_rnode.dump();
    }
  }
  void query(double low, double high) {   // print all values x low <= x <= high
    if(nptr::cnt == 0) return;
    result.clear();
    node nd = *root;
    int idx, idxe;
    while(!nd.isLeaf) {
      idx = lower_bound(nd.keys.begin(), nd.keys.end(), low - EPS) - nd.keys.begin();
      nd = *nd.children[idx];
    }
    idx = 0;                                // skipping the part < low
    while(idx < nd.k && nd.keys[idx] < low - EPS) {
      ++idx;
      if(idx == nd.k) {
        if(!strcmp(nd.children[idx].fname, "Null")) {
          idx = 9999;
          break;
        }
        nd = (*nd.children[idx]);
        idx = 0;
      }
    }
    string data;
    while(idx < nd.k && nd.keys[idx] <= high + EPS) {
      ifstream fin(nd.children[idx].fname); ++fcnt;
      fin >> data; fin.close();
      //cout << nd.keys[idx] << ":" << data << " ";
      result.push_back(make_pair(nd.keys[idx], data));
      ++idx;
      if(idx == nd.k) {
        if(!strcmp(nd.children[idx].fname, "Null")) break;
        nd = *(nd.children[idx]);
        idx = 0;
      }
    }
    //cout << "\n";
  }
  void print() {
    cerr << "starting with root:\n";
    rprint((*root));
  }
};
