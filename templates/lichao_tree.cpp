#include <bits/stdc++.h>
using namespace std;

// =========================================
//  Li Chao Segment Tree / Convex Hull Trick
//
//  WHAT IT IS USED FOR:
//  -----------------------------------------
//  Maintains a dynamic envelope of linear
//  functions (lines y = m * x + c) and supports:
//    1. Inserting lines in ANY order
//       (no monotonic slope requirement!)
//    2. Querying min (or max) at any x
//       in O(log(MAX_X - MIN_X)) time.
//
//  DP OPTIMIZATION PATTERN:
//  -----------------------------------------
//  Solves transitions of the form:
//    dp[i] = min_{j < i} (m_j * x_i + c_j) + extra(i)
//  Reduces O(N^2) brute force to O(N log(range)).
//
//  EXAMPLE (Squared Distance / Frog 3):
//    dp[i] = min_{j < i} [ dp[j] + (h[i] - h[j])^2 + C ]
//    dp[i] = (h[i]^2 + C) + min_{j < i} [ (-2*h[j])*h[i] + (dp[j] + h[j]^2) ]
//    -> Slope:     m = -2 * h[j]
//    -> Intercept: c = dp[j] + h[j]^2
//    -> Query:     x = h[i]
//    -> Extra:     extra = h[i]^2 + C
// =========================================

using ll = long long;
constexpr ll LINF = 4e18; // Use -LINF for max queries

struct Line {
  ll m, c;
  ll eval(ll x) const { return m * x + c; }
};

// Li Chao Tree for MINIMUM queries
// (Flip '<' to '>' and min() to max() for MAXIMUM queries)
class LiChaoTree {
private:
  struct Node {
    Line line;
    int left = -1, right = -1;
    Node(Line l) : line(l) {}
  };

  ll min_x, max_x;
  vector<Node> tree;

  static constexpr Line DEFAULT_LINE = {0, LINF};

  int get_left(int u) {
    if (tree[u].left == -1) {
      tree[u].left = (int)tree.size();
      tree.emplace_back(DEFAULT_LINE);
    }
    return tree[u].left;
  }

  int get_right(int u) {
    if (tree[u].right == -1) {
      tree[u].right = (int)tree.size();
      tree.emplace_back(DEFAULT_LINE);
    }
    return tree[u].right;
  }

  void add_line(int u, ll l, ll r, Line new_line) {
    ll mid = l + (r - l) / 2;
    bool mid_better = new_line.eval(mid) < tree[u].line.eval(mid); // '<' for min, '>' for max

    if (mid_better) {
      swap(tree[u].line, new_line);
    }

    if (l == r) return;

    bool left_better = new_line.eval(l) < tree[u].line.eval(l); // '<' for min, '>' for max
    if (left_better) {
      int lc = get_left(u);
      add_line(lc, l, mid, new_line);
    } else {
      int rc = get_right(u);
      add_line(rc, mid + 1, r, new_line);
    }
  }

  ll query(int u, ll l, ll r, ll x) {
    if (u == -1) return LINF; // LINF for min, -LINF for max
    ll res = tree[u].line.eval(x);
    if (l == r) return res;

    ll mid = l + (r - l) / 2;
    if (x <= mid && tree[u].left != -1) {
      res = min(res, query(tree[u].left, l, mid, x)); // min() for min, max() for max
    } else if (x > mid && tree[u].right != -1) {
      res = min(res, query(tree[u].right, mid + 1, r, x));
    }
    return res;
  }

public:
  LiChaoTree(ll min_x = 0, ll max_x = 1'000'000'000)
      : min_x(min_x), max_x(max_x) {
    tree.emplace_back(DEFAULT_LINE);
  }

  // Insert a new line: y = m * x + c
  void add_line(ll m, ll c) {
    add_line(0, min_x, max_x, {m, c});
  }

  // Query the minimum y value among all lines at x
  ll query(ll x) {
    return query(0, min_x, max_x, x);
  }
};

int main() {
  // --- Example 1: Basic Line Envelope ---
  // Lines: L1: y=2x+10, L2: y=-x+25, L3: y=18
  LiChaoTree lct(0, 100);
  lct.add_line(2, 10);
  lct.add_line(-1, 25);
  lct.add_line(0, 18);

  printf("=== Example 1: Direct Envelope Queries ===\n");
  for (ll x : {0, 5, 8, 10, 15}) {
    printf("x = %2lld -> min y = %2lld\n", x, lct.query(x));
  }

  // --- Example 2: DP Optimization (Frog 3) ---
  // dp[i] = min_{j<i} (dp[j] + (h[i]-h[j])^2 + C)
  printf("\n=== Example 2: DP Optimization (Frog 3) ===\n");
  int n = 5;
  ll C = 6;
  vector<ll> h = {1, 2, 4, 7, 9};
  vector<ll> dp(n, 0);

  // x-coordinate domain is [0, max(h)]
  LiChaoTree dp_tree(0, 100);

  // Insert base case: j = 0
  // Line: m = -2*h[0], c = dp[0] + h[0]^2
  dp_tree.add_line(-2 * h[0], dp[0] + h[0] * h[0]);

  for (int i = 1; i < n; ++i) {
    // Query best line at x = h[i]
    ll best = dp_tree.query(h[i]);
    dp[i] = best + h[i] * h[i] + C;

    // Insert new line for future transitions from i
    dp_tree.add_line(-2 * h[i], dp[i] + h[i] * h[i]);
  }

  for (int i = 0; i < n; ++i) {
    printf("Stone %d (h=%2lld): dp = %lld\n", i, h[i], dp[i]);
  }

  return 0;
}
