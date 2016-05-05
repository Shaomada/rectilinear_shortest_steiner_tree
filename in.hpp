#ifndef IN_HPP
#define IN_HPP

#include "common.hpp"
#include <fstream>
#include <vector>

class Reader {
public:
  typedef int number;
  Reader (char const *filename) : _file(filename) { }
  void read( std::vector<number> x[3], std::vector<unsigned> &T);
private:
  std::ifstream _file;
  std::vector<number> read_line();
};

#endif