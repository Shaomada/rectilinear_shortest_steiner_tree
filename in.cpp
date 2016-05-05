#include "in.hpp"
#include <sstream>
#include <stdexcept>
#include <algorithm>

void Reader::read( std::vector<number> x[3], std::vector<unsigned> &T)
{
  std::vector<number> input[4];
  for (unsigned i = 0; i < 4; i++) {
    input[i] = read_line();
  }
  if (input[3].size() % 3 != 0) {
    throw std::runtime_error("total number of terminal coordinates not devisble by 3.");
  }
  
  // x[i%3]: All existing terminal coordinates in dim i%3
  for (unsigned i = 0; i < input[3].size(); i++) {
    x[i%3].push_back(input[3].at(i));
  }
  for (unsigned i = 0; i < 3; i++) {
    std::sort(x[i].begin(), x[i].end());
    x[i].erase(std::unique(x[i].begin(), x[i].end()), x[i].end());
  }
  unsigned i, j, s = 0;;
  for (i = 0; i < input[3].size(); i++) {
    for (j = 0; j < x[i%3].size(); j++) {
      if (x[i%3].at(j) == input[3].at(i)) {
	if (i%3 == 0) {
	  s = j;
	} else if (i%3 == 1) {
	  s += x[0].size()*j;
	} else {
	  s+= x[0].size()*x[1].size()*j;
	  T.push_back(s);
	}
	break;
      }
    }
    // make sure the value is also in input[i%3]
    for (j = 0; j < input[i%3].size(); j++) {
      if (input[i%3].at(j) == input[3].at(i)) {
	break;
      }
    }
    if (j==input[i%3].size()) {
      throw std::runtime_error("terminal coordinates not found in given grid");
    }
  }
}

std::vector<Reader::number> Reader::read_line() {
  std::vector<number> v;
  std::string line;
  if (not std::getline(_file, line) ) {
    throw std::runtime_error("too few lines");
  }
  std::stringstream ss(line);
  number tmp;
  while (ss >> tmp, ss) {
    v.push_back(tmp);
  }
  return v;
}