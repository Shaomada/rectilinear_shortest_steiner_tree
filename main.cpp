#include "grid.hpp"
#include "in.hpp"
#include <vector>
#include <iostream>
#include <cstring>

int main (int argc, char **argv) {
  try {
    if (argc < 2) {
      std::cout << "Usage: Input [--literally]" << std::endl;
      std::cout << std::endl << "use --literally if you do NOT wish to use the Hanan grid" << std::endl;
    }
    bool literally = false;
    if (argc >= 3 &&  strcmp(argv[2], "--literally") == 0) {
      literally = true;
    }
    std::vector<Reader::number> x[3];
    std::vector<unsigned> T;
    Reader r(argv[1]);
    r.read(x, T, literally);
    Grid G(x, T);
    Grid::number smt = G.run_dijkstra_steiner();
    std::cout << "file:\t" << argv[1] << "\tsmt:\t" << smt << std::endl;
    return 0;
  }
  catch (std::runtime_error e) {
    std::cout << "Exception thrown. Please check if the input file has valid format." << std::endl;
    return 1;
  }
}