#ifndef GRID_HPP
#define GRID_HPP

#include "common.hpp"
#include <limits>
#include <vector>
#include <map>
#include "heap.hpp"

class Grid {
public:
  typedef int number;
  class Label {
  public:
    inline Label () {}
    inline Label (unsigned v, size_t I, number l) : v(v), I(I), l(l) {}
    // inline Label (const Label &o) : Label(o.v, o.I, o.l);
    unsigned v;
    size_t I;
    number l;
    number lb (const Grid *g) const;
  };

  struct C {
    C (Grid *g) : g(g) {}
    inline bool operator()(const Label lhs, const Label rhs) const {
      return lhs.l - rhs.lb(g) < rhs.l - lhs.lb(g);
    }
    const Grid *g;
  };

  Grid () : _c(this), _h(_c) {}
  Grid (const Grid &g) : Grid () {}
  Grid (std::vector<number> x[3], std::vector<unsigned> T);
  /// call on a Grid immeadiatly after constructing it to run the same-name algorithm
  number run_dijkstra_steiner ();
  /// size of _T
  inline size_t nr_terminals () const;
  /// a feasible lower bound for run_dijkstra_steiner, implemented bounding_box (v+(_T-I))
  number lb (unsigned v, size_t I) const;
private:
  // all cordinates which appear for grid vertices grouped by dimension
  const std::vector<number> _x[3];
  // set of terminal vertices for the instance of minimal steiner tree
  const std::vector<unsigned> _T;
  // number of vertices
  unsigned _n;
  // saves all permanent labels
  std::vector<std::map<size_t, Label> > _P;
  /// saves all labels currently in the heap
  std::vector<std::map<size_t, typename Heap<Label,C>::Node*> > _l;
  /// provides a sorting function for the heap
  C _c;
  /// a heap to save all non-infinite non-premanent labels
  Heap<Label,C> _h;

  /// if the label for v, I is non-permanent, decreases l to the given number if neccessary
  void decrease (unsigned v, size_t I, number l);
  /// an injection of the valid grid indices to 0, ..., nr-vertices, max for invalid input
  inline unsigned encode (unsigned v[3]) const;
  /// the inverse to \e encode projected into the dim-th dimension, max for invalid input
  inline unsigned decode (unsigned short dim, unsigned v) const;
  /// the distance of 2 encoded vertices in l1 norm
  number l1 (unsigned v, unsigned w) const;
  /// all encoded neighbours of an encoded vertex
  std::vector<unsigned> neighbours(unsigned v) const;
};

/// TEMPLATE AND INLINE SECTION

inline Grid::number Grid::Label::lb (const Grid *g) const
{
  return g->lb(v, (1 << g->nr_terminals())- 1 - I);
}

inline size_t Grid::nr_terminals () const 
{ 
  return _T.size();
}

inline unsigned Grid::encode (unsigned v[3]) const {
  return v[0]+_x[0].size()*(v[1]+_x[1].size()*v[2]);
}

#endif