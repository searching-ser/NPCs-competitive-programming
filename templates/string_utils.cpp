#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------
//  1. String Manipulation & Parsing Helpers
// ---------------------------------------------

// Split string by whitespace
vector<string> split_ws(const string &s) {
  stringstream ss(s);
  string token;
  vector<string> res;
  while (ss >> token) res.push_back(token);
  return res;
}

// Split string by single character delimiter (e.g., ',' or ':')
vector<string> split(const string &s, char delim) {
  vector<string> res;
  string cur;
  for (char c : s) {
    if (c == delim) {
      res.push_back(cur);
      cur.clear();
    } else {
      cur += c;
    }
  }
  res.push_back(cur);
  return res;
}

// Split string by a multi-character delimiter
vector<string> split(const string &s, const string &delim) {
  vector<string> res;
  size_t start = 0, end = 0;
  while ((end = s.find(delim, start)) != string::npos) {
    res.push_back(s.substr(start, end - start));
    start = end + delim.length();
  }
  res.push_back(s.substr(start));
  return res;
}

// Join container elements into a string with a delimiter
template <class T>
string join(const vector<T> &v, const string &delim = " ") {
  ostringstream oss;
  for (size_t i = 0; i < v.size(); ++i) {
    if (i > 0) oss << delim;
    oss << v[i];
  }
  return oss.str();
}

// Trimming whitespace
string ltrim(string s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); }));
  return s;
}
string rtrim(string s) {
  s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
  return s;
}
string trim(string s) { return ltrim(rtrim(move(s))); }

// Case conversions
string to_lower(string s) {
  for (char &c : s) c = (char)tolower((unsigned char)c);
  return s;
}
string to_upper(string s) {
  for (char &c : s) c = (char)toupper((unsigned char)c);
  return s;
}

// Replace all occurrences of 'from' with 'to'
string replace_all(string s, const string &from, const string &to) {
  if (from.empty()) return s;
  size_t pos = 0;
  while ((pos = s.find(from, pos)) != string::npos) {
    s.replace(pos, from.length(), to);
    pos += to.length();
  }
  return s;
}

// ---------------------------------------------
//  2. Linear Pattern Matching: KMP & Z-Algo
// ---------------------------------------------

// KMP: Compute Prefix Function (pi[i] = length of longest proper prefix of s[0..i] that is also suffix)
vector<int> prefix_function(const string &s) {
  int n = (int)s.size();
  vector<int> pi(n, 0);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

// KMP: Find all starting indices of 'pat' in 'text' in O(|text| + |pat|)
vector<int> kmp_search(const string &text, const string &pat) {
  if (pat.empty()) return {};
  string s = pat + '#' + text;
  vector<int> pi = prefix_function(s);
  vector<int> matches;
  int m = (int)pat.size();
  for (int i = m + 1; i < (int)s.size(); ++i) {
    if (pi[i] == m) {
      matches.push_back(i - 2 * m); // 0-based start index in text
    }
  }
  return matches;
}

// Z-Algorithm: z[i] = longest common prefix between s and s[i..n-1] in O(N)
vector<int> z_function(const string &s) {
  int n = (int)s.size();
  vector<int> z(n, 0);
  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

// Z-Search: Find all starting indices of 'pat' in 'text' in O(|text| + |pat|)
vector<int> z_search(const string &text, const string &pat) {
  if (pat.empty()) return {};
  string s = pat + '#' + text;
  vector<int> z = z_function(s);
  vector<int> matches;
  int m = (int)pat.size();
  for (int i = m + 1; i < (int)s.size(); ++i) {
    if (z[i] >= m) {
      matches.push_back(i - (m + 1));
    }
  }
  return matches;
}

// ---------------------------------------------
//  3. std::regex Recipes for CP
// ---------------------------------------------

// Check if entire string matches pattern
bool regex_full_match(const string &s, const string &pat) {
  regex re(pat);
  return regex_match(s, re);
}

// Extract all numbers (including negative integers) from text
vector<long long> extract_all_ints(const string &s) {
  regex re(R"(-?\d+)");
  sregex_iterator next(s.begin(), s.end(), re);
  sregex_iterator end;
  vector<long long> res;
  while (next != end) {
    res.push_back(stoll(next->str()));
    ++next;
  }
  return res;
}

// Extract all words/tokens matching regex
vector<string> extract_all_tokens(const string &s, const string &pat = R"(\w+)") {
  regex re(pat);
  sregex_iterator next(s.begin(), s.end(), re);
  sregex_iterator end;
  vector<string> res;
  while (next != end) {
    res.push_back(next->str());
    ++next;
  }
  return res;
}

// Extract capture groups: e.g. "x=12, y=34" with "x=(\d+),\s*y=(\d+)"
pair<string, string> extract_pair(const string &s, const string &pat) {
  regex re(pat);
  smatch match;
  if (regex_search(s, match, re) && match.size() >= 3) {
    return {match[1].str(), match[2].str()};
  }
  return {"", ""};
}

// Replace regex matches: e.g. replace consecutive spaces with a single space
string regex_sanitize(const string &s, const string &pat = R"(\s+)", const string &fmt = " ") {
  regex re(pat);
  return regex_replace(s, re, fmt);
}

// ---------------------------------------------
//  Demonstration & Tests in main()
// ---------------------------------------------
int main() {
  // 1. Text Parsing
  string raw = "  apple, banana , cherry,date  ";
  cout << "Original: [" << raw << "]\n";
  cout << "Trimmed:  [" << trim(raw) << "]\n";
  
  auto parts = split(trim(raw), ',');
  cout << "Split by comma:\n";
  for (auto &p : parts) cout << "  [" << trim(p) << "]\n";
  
  vector<int> nums = {10, 20, 30, 40};
  cout << "Joined vector: " << join(nums, " -> ") << "\n";

  // 2. Pattern Matching (KMP & Z-algorithm)
  string text = "ababcabcabababd";
  string pat = "ababd";
  auto kmp_res = kmp_search(text, pat);
  auto z_res = z_search(text, pat);
  cout << "\nKMP match index of '" << pat << "' in '" << text << "': " << join(kmp_res, ", ") << "\n";
  cout << "Z-algo match index: " << join(z_res, ", ") << "\n";

  // 3. Regex Extractions
  string log_entry = "Player 42 scored -15 points at 2026-08-28. Extra data: [x=100, y=250]";
  cout << "\nLog text: " << log_entry << "\n";
  
  auto ints = extract_all_ints(log_entry);
  cout << "Extracted integers: " << join(ints, ", ") << "\n";

  auto coords = extract_pair(log_entry, R"(x=(\d+),\s*y=(\d+))");
  cout << "Captured coords: x=" << coords.first << ", y=" << coords.second << "\n";

  string messy = "This   has    way     too   many   spaces.";
  cout << "Sanitized string: " << regex_sanitize(messy) << "\n";

  return 0;
}
