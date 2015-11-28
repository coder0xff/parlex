#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>

#define DEBUG(x) { std::cout << __FILE__ << "(" << __LINE__ << ") DEBUG: " << x << std::endl; }

#endif