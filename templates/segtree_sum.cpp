#include <bits/stdc++.h>
using namespace std;

// =========================================
//  Generic Lazy Segment Tree (0-indexed)
//
//  HOW TO CUSTOMIZE FOR DIFFERENT QUERIES:
//  -----------------------------------------
//  1. Range Sum (RSQ):
//       IDENTITY = 0;
//       combine(a, b) = a + b;
//       apply(p, L, R, val):
//         st[p] = val * (R - L + 1);  (set)
//         st[p] += val * (R - L + 1); (add)
//
//  2. Range Min (RMQ):
//       IDENTITY = INF;  (2e9 or 4e18)
//       combine(a, b) = min(a, b);
//       apply(p, L, R, val):
//         st[p] = val;  (set)
//         st[p] += val; (add)
//
//  3. Range Max (RMaxQ):
//       IDENTITY = -INF; (-2e9 or -4e18)
//       combine(a, b) = max(a, b);
//       apply(p, L, R, val):
//         st[p] = val;  (set)
//         st[p] += val; (add)
//
//  4. Special Query (e.g. {min, count}):
//       Use a struct with custom combine.
// =========================================

template <class T = long long>
class SegmentTree {
private:
  int n;
  vector<T> A, st, lazy;
  vector<bool> has_lazy;

  // ============ CUSTOMIZE HERE ============
  static constexpr T IDENTITY = 0; // RSQ: 0 | RMQ: 2e9 | RMaxQ: -2e9

  T combine(T a, T b) const {
    // RSQ: a + b | RMQ: min | RMaxQ: max
    return a + b;
  }

  void apply_lazy(int p, int L, int R, T val) {
    // Range Assignment:
    st[p] = val * (R - L + 1);
    lazy[p] = val;
    has_lazy[p] = true;

    // (Alternative: Range Addition):
    // st[p] += val * (R - L + 1);
    // lazy[p] += val;
    // has_lazy[p] = true;
  }
  // ========================================

  int l(int p) { return p << 1; }
  int r(int p) { return (p << 1) + 1; }

  void push(int p, int L, int R) {
    if (!has_lazy[p] || L == R) return;
    int m = (L + R) / 2;
    apply_lazy(l(p), L, m, lazy[p]);
    apply_lazy(r(p), m + 1, R, lazy[p]);
    has_lazy[p] = false;
    lazy[p] = 0;
  }

  void build(int p, int L, int R) {
    if (L == R) {
      st[p] = A[L];
      return;
    }
    int m = (L + R) / 2;
    build(l(p), L, m);
    build(r(p), m + 1, R);
    st[p] = combine(st[l(p)], st[r(p)]);
  }

  void update(int p, int L, int R, int i, int j, T val) {
    if (i > j || L > j || R < i) return;
    if (L >= i && R <= j) {
      apply_lazy(p, L, R, val);
      return;
    }
    push(p, L, R);
    int m = (L + R) / 2;
    update(l(p), L, m, i, j, val);
    update(r(p), m + 1, R, i, j, val);
    st[p] = combine(st[l(p)], st[r(p)]);
  }

  T query(int p, int L, int R, int i, int j) {
    if (i > j || L > j || R < i) return IDENTITY;
    if (L >= i && R <= j) return st[p];
    push(p, L, R);
    int m = (L + R) / 2;
    return combine(query(l(p), L, m, i, j),
                   query(r(p), m + 1, R, i, j));
  }

public:
  SegmentTree(int sz)
      : n(sz), A(n, 0), st(4 * n, IDENTITY),
        lazy(4 * n, 0), has_lazy(4 * n, false) {}

  SegmentTree(const vector<T> &initialA)
      : n((int)initialA.size()), A(initialA),
        st(4 * n, IDENTITY), lazy(4 * n, 0),
        has_lazy(4 * n, false) {
    build(1, 0, n - 1);
  }

  void update(int i, int j, T val) { update(1, 0, n - 1, i, j, val); }
  void update(int idx, T val)      { update(1, 0, n - 1, idx, idx, val); }

  T query(int i, int j) { return query(1, 0, n - 1, i, j); }
  T RSQ(int i, int j)   { return query(i, j); }
  T RMQ(int i, int j)   { return query(i, j); }
};

int main() {
  vector<long long> A = {18, 17, 13, 19, 15, 11, 20, 99}; // n = 8
  SegmentTree<long long> st(A);

  printf("              idx    0,  1,  2,  3,  4,  5,  6,  7\n");
  printf("              A is {18, 17, 13, 19, 15, 11, 20, 99}\n");
  printf("RSQ(1, 3) = %lld\n", st.query(1, 3)); // 17+13+19 = 49
  printf("RSQ(4, 7) = %lld\n", st.query(4, 7)); // 15+11+20+99 = 145
  printf("RSQ(3, 4) = %lld\n", st.query(3, 4)); // 19+15 = 34

  st.update(5, 5, 77); // update A[5] to 77
  printf("\nNow, modify A into {18, 17, 13, 19, 15, 77, 20, 99}\n");
  printf("RSQ(1, 3) = %lld\n", st.query(1, 3)); // 49 (unchanged)
  printf("RSQ(4, 7) = %lld\n", st.query(4, 7)); // 15+77+20+99 = 211
  printf("RSQ(3, 4) = %lld\n", st.query(3, 4)); // 34 (unchanged)

  st.update(0, 3, 30); // update A[0..3] to 30
  printf("\nNow, modify A into {30, 30, 30, 30, 15, 77, 20, 99}\n");
  printf("RSQ(1, 3) = %lld\n", st.query(1, 3)); // 30+30+30 = 90
  printf("RSQ(4, 7) = %lld\n", st.query(4, 7)); // 211 (unchanged)
  printf("RSQ(3, 4) = %lld\n", st.query(3, 4)); // 30+15 = 45

  st.update(3, 3, 7); // update A[3] to 7
  printf("\nNow, modify A into {30, 30, 30,  7, 15, 77, 20, 99}\n");
  printf("RSQ(1, 3) = %lld\n", st.query(1, 3)); // 30+30+7 = 67
  printf("RSQ(4, 7) = %lld\n", st.query(4, 7)); // 211 (unchanged)
  printf("RSQ(3, 4) = %lld\n", st.query(3, 4)); // 7+15 = 22

  return 0;
}
