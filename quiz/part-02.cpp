#include <iostream>

struct X {
  X() { std::cout << 1; }
  ~X() { std::cout << 2; }
};

int main()
{
  X a();
  X b{};
}
