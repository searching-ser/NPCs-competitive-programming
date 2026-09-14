#include <bits/stdc++.h>
using namespace std;

// =========================================
//  Grid & Matrix Transformation Cheat Sheet
//
//  COORDINATE MAPPING SUMMARY (R x C):
//  -----------------------------------------
//  Original:    (r, c)
//  Transpose:   (c, r)               [C x R]
//  Rotate 90 CW: (c, R - 1 - r)      [C x R]
//  Rotate 90 CCW:(C - 1 - c, r)      [C x R]
//  Rotate 180:  (R - 1 - r, C - 1 - c) [R x C]
//  Flip Horiz:  (r, C - 1 - c)       [R x C]
//  Flip Vert:   (R - 1 - r, c)       [R x C]
//
//  DIAGONALS:
//  -----------------------------------------
//  Anti-diagonal (top-right to bot-left): r + c = const
//  Main diagonal (top-left to bot-right):  r - c = const
// =========================================

// --- 1. Transpose (R x C -> C x R) ---
template <class T>
vector<vector<T>> transpose(const vector<vector<T>> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<vector<T>> res(C, vector<T>(R));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[c][r] = g[r][c];
  return res;
}

vector<string> transpose(const vector<string> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<string> res(C, string(R, ' '));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[c][r] = g[r][c];
  return res;
}

// --- 2. Rotate 90 Degrees Clockwise ---
template <class T>
vector<vector<T>> rotate90_cw(const vector<vector<T>> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<vector<T>> res(C, vector<T>(R));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[c][R - 1 - r] = g[r][c];
  return res;
}

vector<string> rotate90_cw(const vector<string> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<string> res(C, string(R, ' '));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[c][R - 1 - r] = g[r][c];
  return res;
}

// --- 3. Rotate 90 Degrees Counter-Clockwise ---
template <class T>
vector<vector<T>> rotate90_ccw(const vector<vector<T>> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<vector<T>> res(C, vector<T>(R));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[C - 1 - c][r] = g[r][c];
  return res;
}

// --- 4. Rotate 180 Degrees ---
template <class T>
vector<vector<T>> rotate180(const vector<vector<T>> &g) {
  if (g.empty()) return {};
  int R = g.size(), C = g[0].size();
  vector<vector<T>> res(R, vector<T>(C));
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      res[R - 1 - r][C - 1 - c] = g[r][c];
  return res;
}

// --- 5. In-place Square Matrix Rotate 90 CW (O(1) extra space) ---
template <class T>
void rotate_square_inplace(vector<vector<T>> &mat) {
  int N = mat.size();
  for (int i = 0; i < N; ++i)
    for (int j = i + 1; j < N; ++j)
      swap(mat[i][j], mat[j][i]); // Transpose
  for (int i = 0; i < N; ++i)
    reverse(mat[i].begin(), mat[i].end()); // Reverse each row
}

// --- 6. Flips / Reflections ---
template <class T>
vector<vector<T>> flip_h(vector<vector<T>> g) { // Horizontal flip (left <-> right)
  for (auto &row : g) reverse(row.begin(), row.end());
  return g;
}

template <class T>
vector<vector<T>> flip_v(vector<vector<T>> g) { // Vertical flip (top <-> bottom)
  reverse(g.begin(), g.end());
  return g;
}

// --- 7. Clockwise Spiral Traversal ---
template <class T>
vector<T> spiral_order(const vector<vector<T>> &g) {
  if (g.empty()) return {};
  vector<T> order;
  int top = 0, bot = (int)g.size() - 1;
  int left = 0, right = (int)g[0].size() - 1;

  while (top <= bot && left <= right) {
    for (int c = left; c <= right; ++c) order.push_back(g[top][c]);
    ++top;
    for (int r = top; r <= bot; ++r) order.push_back(g[r][right]);
    --right;
    if (top <= bot) {
      for (int c = right; c >= left; --c) order.push_back(g[bot][c]);
      --bot;
    }
    if (left <= right) {
      for (int r = bot; r >= top; --r) order.push_back(g[r][left]);
      ++left;
    }
  }
  return order;
}

// --- 8. Generate R x C Spiral Matrix (1 .. R*C) ---
vector<vector<int>> generate_spiral(int R, int C) {
  vector<vector<int>> g(R, vector<int>(C, 0));
  int val = 1, top = 0, bot = R - 1, left = 0, right = C - 1;
  while (top <= bot && left <= right) {
    for (int c = left; c <= right; ++c) g[top][c] = val++;
    ++top;
    for (int r = top; r <= bot; ++r) g[r][right] = val++;
    --right;
    if (top <= bot) {
      for (int c = right; c >= left; --c) g[bot][c] = val++;
      --bot;
    }
    if (left <= right) {
      for (int r = bot; r >= top; --r) g[r][left] = val++;
      ++left;
    }
  }
  return g;
}

// --- 9. Neighbor Directions (dr, dc) & Bounds Check ---
constexpr pair<int, int> d4[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // U, R, D, L
constexpr pair<int, int> d8[8] = {
  {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
  {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

inline bool in_bounds(int r, int c, int R, int C) {
  return r >= 0 && r < R && c >= 0 && c < C;
}

// =========================================
//  Demonstration in main()
// =========================================
int main() {
  vector<vector<int>> mat = {
    {1, 2, 3},
    {4, 5, 6}
  };

  auto print_grid = [](const string &title, const auto &g) {
    cout << "--- " << title << " ---\n";
    for (const auto &row : g) {
      for (const auto &val : row) cout << setw(3) << val;
      cout << '\n';
    }
  };

  print_grid("Original (2x3)", mat);
  print_grid("Transpose (3x2)", transpose(mat));
  print_grid("Rotate 90 CW (3x2)", rotate90_cw(mat));
  print_grid("Rotate 90 CCW (3x2)", rotate90_ccw(mat));
  print_grid("Rotate 180 (2x3)", rotate180(mat));
  print_grid("Flip Horizontal", flip_h(mat));
  print_grid("Flip Vertical", flip_v(mat));

  auto spiral_mat = generate_spiral(3, 4);
  print_grid("Generated 3x4 Spiral", spiral_mat);

  auto spiral_vals = spiral_order(spiral_mat);
  cout << "--- Spiral Traversal Order ---\n";
  for (int x : spiral_vals) cout << x << ' ';
  cout << "\n";

  return 0;
}
