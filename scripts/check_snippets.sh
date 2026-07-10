#!/bin/sh
set -eu

CXX=${CXX:-g++}
CXXFLAGS=${CXXFLAGS:--std=gnu++17 -O2 -Wall -Wextra -Wpedantic -Werror}
TMP_DIR=$(mktemp -d "${TMPDIR:-/tmp}/npcs-codebook.XXXXXX")
trap 'rm -rf "$TMP_DIR"' EXIT HUP INT TERM

echo "Checking snippets with $CXX"

$CXX $CXXFLAGS tests/snippets_test.cpp -o "$TMP_DIR/snippets_test"
"$TMP_DIR/snippets_test"

$CXX $CXXFLAGS tests/debugging_test.cpp -o "$TMP_DIR/debugging_test"
"$TMP_DIR/debugging_test" >/dev/null 2>&1

$CXX $CXXFLAGS -I snippets/cpp -fsyntax-only snippets/cpp/template.cpp
$CXX $CXXFLAGS -DDEBUG=0 -I snippets/cpp -fsyntax-only snippets/cpp/template.cpp
$CXX $CXXFLAGS -DDEBUG=1 -I snippets/cpp -fsyntax-only snippets/cpp/template.cpp

echo "All GNU C++17 snippet checks passed."
