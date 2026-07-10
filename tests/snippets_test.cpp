#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#include "../snippets/cpp/fast_io.cpp"
#include "../snippets/cpp/binary_search.cpp"
#include "../snippets/cpp/gcd_lcm.cpp"
#include "../snippets/cpp/bfs.cpp"
#include "../snippets/cpp/print_space_separated.cpp"
#include "../snippets/cpp/lambda_captures.cpp"
#include "../snippets/cpp/lambda_sort.cpp"

int main() {
  configure_fast_io();

  const vector<int> sorted = {1, 3, 3, 7, 11};
  int found = binary_search_index(sorted, 7);
  assert(found >= 0 && sorted[found] == 7);
  assert(binary_search_index(sorted, 2) == -1);
  assert(binary_search_index({}, 2) == -1);

  assert(gcd_ll(48, 18) == 6);
  assert(gcd_ll(0, 0) == 0);
  assert(lcm_ll(12, 18) == 36);
  assert(lcm_ll(0, 18) == 0);

  const vector<vector<int>> graph = {
      {1, 2}, {0, 3}, {0}, {1}, {}};
  assert((bfs_distances(graph, 0) == vector<int>{0, 1, 1, 2, -1}));

  assert(lambda_no_capture(2, 3) == 5);
  assert(lambda_default_value_capture(4, 7) == 11);

  int x = 4;
  int y = 9;
  lambda_default_reference_capture(x, y);
  assert(x == 5 && y == 10);
  assert(lambda_explicit_value_capture(6) == 12);
  lambda_explicit_reference_capture(x);
  assert(x == 6);

  vector<int> lambda_sorted = {4, 1, 7, 4};
  sort_descending_with_lambda(lambda_sorted);
  assert((lambda_sorted == vector<int>{7, 4, 4, 1}));

  vector<int> function_sorted = {4, 1, 7, 4};
  sort_descending_with_function(function_sorted);
  assert(function_sorted == lambda_sorted);

  ostringstream captured;
  streambuf* previous = cout.rdbuf(captured.rdbuf());
  print_space_separated(vector<int>{4, 8, 15});
  print_space_separated(vector<int>{});
  cout.rdbuf(previous);
  assert(captured.str() == "4 8 15\n");
}
