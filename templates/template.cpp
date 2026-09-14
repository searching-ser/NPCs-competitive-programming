#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#  define de(...)
std::println(std::cout,
             "[{} = ({})]",
#  __VA_ARGS__,
             std::make_tuple(__VA_ARGS__))

#  define deb(x) cout << #x << '=' << x << '\n';
#else
#  define de(...) ((void)0)
#endif

  // --- Type Aliases ---
  using ll = long long;
using ull  = unsigned long long;
using ld   = long double;
using pii  = pair<int, int>;
using pll  = pair<ll, ll>;
using vi   = vector<int>;
using vl   = vector<ll>;
using vpi  = vector<pii>;
using vpl  = vector<pll>;
using vvi  = vector<vi>;
using vvl  = vector<vl>;

template <class T>
using vec = vector<T>;

template <class T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

// --- Constants ---
constexpr int INF  = 1e9 + 7;
constexpr ll  LINF = 4e18;
constexpr int MOD  = 1e9 + 7;
constexpr int MOD9 = 998244353;

vvi d4 = {{-1, 0},   // U
          {0, 1},    // R
          {1, 0},    // D
          {0, -1}};  // L
vvi d8 = {{-1, 0},   // U
          {-1, 1},   // UR
          {0, 1},    // R
          {1, 1},    // DR
          {1, 0},    // D
          {1, -1},   // DL
          {0, -1},   // L
          {-1, -1}}; // UL


// --- Macros & Shortcuts ---
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fo(i, n) for (int i = 0; i < (int)(n); ++i)
#define foi(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define fod(i, a, b) for (int i = (int)(a); i > (int)(b); --i)

// --- Utility Functions ---
template <class T, class U>
inline bool chmin(T &a, const U &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T, class U>
inline bool chmax(T &a, const U &b) {
  return a < b ? a = b, 1 : 0;
}

template <class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (auto &x : v)
    is >> x;
  return is;
}
void solve() {
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
