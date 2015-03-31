#include "node.hpp"
#include "bptree.hpp"
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  nptr file;
  file.open();
  node nd = *file;  // same as nd(file) 
  for(int i = 0; i < nd.k; ++i) {
    nd.keys[i] += 1;
  }
  nd.dump();
  file = &nd;
  nd = *file;
  nd.load();
  for(int i = 0; i < nd.k; ++i) cout << nd.keys[i] << " "; cout << "\n";

  return 0;
}

