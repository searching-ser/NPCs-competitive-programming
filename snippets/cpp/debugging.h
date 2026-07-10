#pragma once

#include <cstddef>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec) {
  if (vec.empty()) {
    out << "[]";
    return out;
  }
  out << '[';
  for (std::size_t i = 0; i + 1 < vec.size(); ++i) {
    out << vec[i] << ", ";
  }
  return out << vec.back() << ']';
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &pair) {
  return out << '(' << pair.first << ", " << pair.second << ')';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::deque<T> &deq) {
  if (deq.empty()) {
    out << "[]";
    return out;
  }
  out << '[';
  for (std::size_t i = 0; i + 1 < deq.size(); ++i) {
    out << deq[i] << ", ";
  }
  return out << deq.back() << ']';
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream                     &out,
                         const std::unordered_map<T1, T2> &map) {
  out << '{';
  for (auto it = map.begin(); it != map.end(); it++) {
    std::pair<T1, T2> element = *it;
    out << element.first << ": " << element.second;
    if (std::next(it) != map.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, const std::map<T1, T2> &map) {
  out << '{';
  for (auto it = map.begin(); it != map.end(); it++) {
    std::pair<T1, T2> element = *it;
    out << element.first << ": " << element.second;
    if (std::next(it) != map.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::unordered_set<T> &set) {
  out << '{';
  for (auto it = set.begin(); it != set.end(); it++) {
    T element = *it;
    out << element;
    if (std::next(it) != set.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::multiset<T> &set) {
  out << '{';
  for (auto it = set.begin(); it != set.end(); it++) {
    T element = *it;
    out << element;
    if (std::next(it) != set.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename T>
std::ostream &operator<<(std::ostream                     &out,
                         const std::unordered_multiset<T> &set) {
  out << '{';
  for (auto it = set.begin(); it != set.end(); it++) {
    T element = *it;
    out << element;
    if (std::next(it) != set.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::set<T> &set) {
  out << '{';
  for (auto it = set.begin(); it != set.end(); it++) {
    T element = *it;
    out << element;
    if (std::next(it) != set.end()) {
      out << ", ";
    }
  }
  return out << '}';
}

template <typename... Types>
std::ostream &operator<<(std::ostream &out, const std::tuple<Types...> &value) {
  out << '(';
  std::size_t index = 0;
  std::apply(
      [&](const auto &...elements) {
        ((out << (index++ == 0 ? "" : ", ") << elements), ...);
      },
      value);
  return out << ')';
}

inline void debug_out() {
  std::cerr << '\n';
}

template <typename Head, typename... Tail>
inline void debug_out(const Head &head, const Tail &...tail) {
  std::cerr << head;
  if constexpr (sizeof...(tail) > 0) {
    std::cerr << ", ";
  }
  debug_out(tail...);
}

#define de(...)                                                                \
  do {                                                                         \
    std::cerr << "[" << #__VA_ARGS__ << "] = ";                                \
    debug_out(__VA_ARGS__);                                                    \
  } while (0)
