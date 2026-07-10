#include <bits/stdc++.h>

// Compile with -DDEBUG=1 to enable debug output.
#if defined(DEBUG) && DEBUG
#  include "debugging.h"
#else
#  define de(...)
#endif

using namespace std;

using ll  = long long;
using ld  = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T>
using vec  = vector<T>;
using vi   = vector<int>;
using vl   = vector<ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using vvi  = vector<vi>;
using vvl  = vector<vl>;

#define all(x) begin(x), end(x)
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define rall(x) rbegin(x), rend(x)
#define len(x) ll((x).size())
#define pb push_back
#define eb emplace_back
#define F first
#define S second

#define fo(i, n) for (int i = 0, _n = (int)(n); i < _n; ++i)
#define foi(i, a, b) for (int i = (int)(a), _b = (int)(b); i < _b; ++i)
#define fod(i, a, b) for (int i = (int)(a); i > (int)(b); --i) // (a, b]
#define foa(x, c) for (auto &x : (c))
#define prn(x) cout << x << '\n'
#define pr(x) cout << x << ' '

constexpr int INF  = 1e9;
constexpr ll  LINF = 4'000'000'000'000'000'000LL;
constexpr int MOD  = 1'000'000'007;
// constexpr int MOD = 998244353;

inline ll mod(ll x, ll m = MOD) {
  x %= m;
  if (x < 0)
    x += m;
  return x;
}

template <class T>
bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
istream &operator>>(istream &is, vec<T> &a) {
  for (auto &x : a)
    is >> x;
  return is;
}

template <class A, class B>
istream &operator>>(istream &is, pair<A, B> &p) {
  return is >> p.first >> p.second;
}

#if !defined(DEBUG) || !DEBUG
template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << p.first << ' ' << p.second;
}

template <class T>
ostream &operator<<(ostream &os, const vec<T> &a) {
  for (int i = 0; i < len(a); i++) {
    if (i)
      os << ' ';
    os << a[i];
  }
  return os;
}
#endif

int  n, m, u, v;
vi   elements;
void solve() {
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
