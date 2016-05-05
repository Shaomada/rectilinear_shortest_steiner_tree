
#include "common.hpp"
#include "grid.hpp"
#include "in.hpp"

#include <vector>

/*
#include <algorithm>
#include <queue>
*/

int main (int argc, char **argv) {
  try {
    CHECK(argc>=2)
    std::vector<Reader::number> x[3];
    std::vector<unsigned> T;
    Reader r(argv[1]);
    r.read(x, T);
    Grid G(x, T);
    Grid::number smt = G.run_dijkstra_steiner();
    std::cout << "file:\t" << argv[1] << "\tsmt:\t" << smt << std::endl;
  }
  catch (std::runtime_error e) {
    return 1;
  }
  return 0; 
}