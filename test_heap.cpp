#include "heap.hpp"
#include <iostream>

struct Compare {
  bool operator()(const int *lhs, const int *rhs) const {
    return *lhs > *rhs;
  }
};

void huch() {}

int main () {
  Compare c;
  Heap<int,Compare> h(c);
  int numbers[1000] = {1, 2, 3, 7, 4, 8, 6 ,254 ,245 , 134, 5 ,25 ,52 ,525 ,526 ,621 ,26};
  typedef Heap<int,Compare>::Node Node;
  Node *nodes[1000];
  unsigned pos;
  for (pos = 0; pos < 7; pos++) {
    nodes[pos] = h.add(numbers+pos);
  }
  numbers[1] = 0;
  h.decrease(nodes[1]);
  for (auto &n : h.get_heap()) {
    std::cout << " " << *n->content;
  }
  std::cout << std::endl;
  int *i;
  huch();
  while ((i = h.extract_min())) {
    std::cout << *i << std::endl;
  }
  return 0;
}