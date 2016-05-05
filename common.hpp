#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <stdexcept>

#define CHECK(IS_TRUE) \
  if (not (IS_TRUE)) { \
    std::cout << "Error thrown in file " << __FILE__ << " line " << __LINE__ << std::endl; \
    throw std::runtime_error(""); \
  }

#define INPUTCHECK(IS_TRUE) \
  if (not (IS_TRUE)) { \
    std::cout << "Input invalid." << std::endl; \
    std::cout << "See file " << __FILE__ << " line " << __LINE__ << std::endl; \
    throw std::runtime_error(""); \
  }

#endif