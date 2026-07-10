bool descending_compare(int lhs, int rhs) {
  return lhs > rhs;
}

void sort_descending_with_lambda(vector<int>& values) {
  sort(values.begin(), values.end(), [](int lhs, int rhs) {
    return lhs > rhs;
  });
}

void sort_descending_with_function(vector<int>& values) {
  sort(values.begin(), values.end(), descending_compare);
}
