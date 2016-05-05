#include "grid.hpp"

Grid::number Grid::run_dijkstra_steiner()
{
  unsigned t = _T.size()-1;
  size_t other_terminals = (1<<t)-1;
  for (unsigned s = 0; s < t; s++) {
    decrease (_T.at(s), 1<<s, 0);
  }
  while (true) {
    Label label = _h.extract_min();
    _l.at(label.v).erase(label.I);
    _P.at(label.v).emplace(label.I, label);
    if (label.v == _T[t] && label.I == other_terminals) {
      return label.l;
    }
    for (unsigned w : neighbours(label.v)) {
      decrease(w, label.I, label.l+l1(label.v, w));
    }
    for (const std::pair<size_t,Label> &p : _P.at(label.v)) {
      if ((label.I & p.first) == 0) {
	decrease (label.v, label.I+p.first, label.l + p.second.l);
      }
    }
  }
}

Grid::number Grid::l1 (unsigned v, unsigned w) const {
  number ret_val = 0;
  for (unsigned short dim = 0; dim < 3; dim++) {
    ret_val += abs(_x[dim].at(decode(dim,v)) - _x[dim].at(decode(dim,w)));
  }
  return ret_val;
}

std::vector<unsigned> Grid::neighbours(unsigned v) const {
  std::vector<unsigned> ret_val;  
  unsigned coords[3];
  for (unsigned short dim = 0; dim < 3; dim++) {
    coords[dim] = decode(dim, v);
  }
  for (unsigned short dim = 0; dim < 3; dim++) {
    if (coords[dim] > 0) {
      coords[dim]--;
      ret_val.push_back(encode(coords));
      coords[dim]++;
    }
    if (coords[dim] != _x[dim].size()-1) {
      coords[dim]++;
      ret_val.push_back(encode(coords));
      coords[dim]--;
    }
  }
  return ret_val;
}

void Grid::decrease (unsigned v, size_t I, number l)
{
  if (_P.at(v).count(I) == 0) {
    auto p = _l.at(v).find(I);
    if (p == _l.at(v).end()) {
      _l.at(v).emplace(I, _h.add(Label(v, I, l)));
    } else if (p->second->content.l > l) {
      p->second->content.l = l;
      _h.decrease(p->second);
    }
  }
}

Grid::Grid(std::vector<number> x[3], std::vector<unsigned> T)
  : _x{x[0],x[1],x[2]}
  , _T(T)
  , _n(_x[0].size()*_x[1].size()*_x[2].size())
  , _P(_n, std::map<size_t,Label>())
  , _l(_n, std::map<size_t,typename Heap<Label,C>::Node*>())
  , _c(this)
  , _h(_c)
{
}

Grid::number Grid::lb (unsigned v, size_t I) const {
  number x_min[3], x_max[3];
  unsigned short dim;
  for (dim = 0; dim < 3; dim++) {
    x_min[dim] = x_max[dim] = _x[dim].at(decode(dim, v));
  }
  for (unsigned j = 0; j < _T.size(); j++) {
    if ((I>>j)%2 != 0) {
      for (dim = 0; dim < 3; dim++) {
	number x = _x[dim].at(decode(dim, _T.at(j)));
	if (x > x_max[dim]) {
	  x_max[dim] = x;
	} else if (x < x_min[dim]) {
	  x_min[dim] = x;
	}
      }
    }
  }
  return x_max[0]-x_min[0]+x_max[1]-x_min[1]+x_max[2]-x_min[2];
}

unsigned Grid::decode (unsigned short dim, unsigned v) const {
  if (v >= _n || dim > 2) {
    return (unsigned) std::numeric_limits<unsigned>::max();
  }
  else if (dim == 0){
    return v % _x[0].size();
  }
  else {
    v /= _x[0].size();
    if (dim == 1) {
      return v % _x[1].size();
    }
    else {
      return v / _x[1].size();
    }
  }
}