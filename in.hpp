#ifndef IN_HPP
#define IN_HPP

#include <fstream>
#include <vector>

class Reader {
public:
  Reader (char const *filename) : _file(filename) { }
  /// should be the same as Grid::number for this project
  typedef int number;
  /// reads the Input file. Returns Hanan Grid if literal is false and the given Grid if literal is true
  void read( std::vector<number> x[3], std::vector<unsigned> &T, bool literally = false);
private:
  std::ifstream _file;
  std::vector<number> read_line();
};

#endif