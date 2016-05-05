#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>

template <typename T, typename Compare>
class Heap {
public:
  class Node {
  public:
    Node (T content, size_t pos)
      : content(content), pos(pos) {}
    T content;
    size_t pos;
  };
  Heap (Compare c) : _heap(), _c(c) {};
  ~Heap () { for (Node *n : _heap) delete n; }
  Node *add (T content);
  void decrease (Node *n);
  T extract_min();

  std::vector<Node *> get_heap () {
    return _heap;
  }
private:
  std::vector<Node *> _heap;
  Compare _c;
  
  bool cmp (const Node *n, const Node *m) const {
    return _c(n->content, m->content);
  }
};

template <typename T, typename Compare>
typename Heap<T,Compare>::Node *Heap<T,Compare>::add (T content) {
  size_t i, j = _heap.size();
  Node *n = new Node(content, j);
  _heap.push_back(n);
  while (i=j,j=(i-1)/2,i>0&&cmp(_heap.at(i),_heap.at(j))) {
    std::swap(_heap.at(i), _heap.at(j));
    std::swap(_heap.at(i)->pos, _heap.at(j)->pos);
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