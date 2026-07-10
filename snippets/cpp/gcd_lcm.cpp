// Inputs are non-negative. O(log(min(a, b))).
ll gcd_ll(ll a, ll b) {
  while (b != 0) {
    a %= b;
    swap(a, b);
  }
  return a;
}

// Divide before multiplying to reduce overflow risk.
ll lcm_ll(ll a, ll b) {
  return a == 0 || b == 0 ? 0 : a / gcd_ll(a, b) * b;
}
