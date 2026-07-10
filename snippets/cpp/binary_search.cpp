// Returns an index containing x, or -1 when x is absent.
int binary_search_index(const vector<int>& values, int x) {
  int lo = 0, hi = (int)values.size() - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (values[mid] == x) return mid;
    if (values[mid] < x) lo = mid + 1;
    else hi = mid - 1;
  }
  return -1;
}
