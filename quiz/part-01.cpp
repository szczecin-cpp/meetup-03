#include <iostream>
#include <limits>

int main() {
  unsigned int a = std::numeric_limits<unsigned int>::min();
  unsigned int b = std::numeric_limits<unsigned int>::max();
  std::cout << a++ << " " << ++b;
}
