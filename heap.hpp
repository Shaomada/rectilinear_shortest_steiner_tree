#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T, typename Compare>
class Heap {
public:
  bool test_heap ();
  class Node {
  public:
    Node (T content, size_t pos)
      : content(content), pos(pos) {}
    T content;
    size_t pos;
  };
  Heap (Compare c) : _heap(), _cmp(c) {};
  Node *add (T content);
  void decrease (Node *n);
  T extract_min();

  std::vector<Node *> get_heap () {
    return _heap;
  }
private:
  std::vector<Node *> _heap;
  Compare _cmp;
  
  bool cmp (const Node *n, const Node *m) const {
    return _cmp(n->content, m->content);
  }
};

template <typename T, typename Compare>
bool Heap<T,Compare>::test_heap () {
  for (unsigned i = 1; i < _heap.size(); i++) {
    if (cmp(_heap.at(i), _heap.at((i-1)/2))) {
      std::cout << "heap_test failed for pair " << i << " " << (i-1)/2 << std::endl;
      return false;
    }
  }
  for (unsigned i = 0; i < _heap.size(); i++) {
    if (i != _heap.at(i)->pos) {
      std::cout << "heap_test failed for pos of " << i << std::endl;
      return false;
    }
  }
  return true;
}

template <typename T, typename Compare>
typename Heap<T,Compare>::Node *Heap<T,Compare>::add (T content) {
  size_t i, j = _heap.size();
  Node *n = new Node(content, j);
  _heap.push_back(n);
  while (i=j,j=(i-1)/2,i>0&&cmp(_heap.at(i),_heap.at(j))) {
    std::swap(_heap.at(i), _heap.at(j));
    std::swap(_heap.at(i)->pos, _heap.at(j)->pos);
  }
  if (not test_heap()) {
    std::cout << "adding caused heap to fail" << std::endl;
  }
  return n;
}

template <typename T, typename Compare>
void Heap<T, Compare>::decrease (Node *n) {
  size_t i, j = n->pos;
  while ((i = j) && cmp(_heap.at(i), _heap.at((j = (i-1)/2)))) {
    std::swap(_heap.at(i), _heap.at(j));
    std::swap(_heap.at(i)->pos, _heap.at(j)->pos);
  }
  if (not test_heap()) {
    std::cout << "decreasing caused heap to fail" << std::endl;
  }
}

template <typename T, typename Compare>
T Heap<T, Compare>::extract_min () {
  if (_heap.size() == 0) {
    return T();
  }
  T l = _heap.front()->content;
  delete _heap.front();
  _heap.front() = _heap.back();
  _heap.pop_back();
  _heap.front()->pos = 0;
  size_t i = 0;
  while(true) {
    size_t min_index = i;
    if (2*i+1 < _heap.size() && cmp(_heap.at(2*i+1), _heap.at(min_index))) {
      min_index = 2*i+1;
    }
    if (2*i+2 < _heap.size() && cmp(_heap.at(2*i+2), _heap.at(min_index))) {
      min_index = 2*i+2;
    }
    if (i == min_index) {
      if (not test_heap()) {
	std::cout << "extracting caused heap to fail" << std::endl;
      }
      return l;
    }
    else {
      std::swap (_heap.at(i), _heap.at(min_index));
      std::swap (_heap.at(i)->pos, _heap.at(min_index)->pos);
      i = min_index;
    }
  }
}

#endif