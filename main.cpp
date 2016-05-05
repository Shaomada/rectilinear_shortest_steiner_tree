#include "grid.hpp"
#include "in.hpp"
#include <vector>
#include <iostream>

int main (int argc, char **argv) {
  try {
    if (argc < 2) {
      std::cout << "Please gie input file name as argument" << std::endl;
    }
    std::vector<Reader::number> x[3];
    std::vector<unsigned> T;
    Reader r(argv[1]);
    r.read(x, T);
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