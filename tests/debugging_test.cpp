#include "../snippets/cpp/debugging.h"

int main() {
  std::vector<int> values = {1, 2, 3};
  std::tuple<int, int> edge = {4, 5};
  std::tuple<> empty;
  de(values, edge, empty);
}
