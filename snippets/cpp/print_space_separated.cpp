template <class T>
void print_space_separated(const vector<T>& values) {
  for (int i = 0; i < (int)values.size(); ++i)
    cout << values[i] << " \n"[i + 1 == (int)values.size()];
}
