int lambda_no_capture(int a, int b) {
  auto add = [](int lhs, int rhs) -> int { return lhs + rhs; };
  return add(a, b);
}

int lambda_default_value_capture(int x, int y) {
  auto sum = [=] { return x + y; };
  return sum();
}

void lambda_default_reference_capture(int& x, int& y) {
  auto increment_both = [&] { ++x; ++y; };
  increment_both();
}

int lambda_explicit_value_capture(int x) {
  auto twice = [x] { return 2 * x; };
  ++x;  // The lambda still holds the original copy.
  return twice();
}

void lambda_explicit_reference_capture(int& x) {
  auto increment = [&x] { ++x; };
  increment();
}
