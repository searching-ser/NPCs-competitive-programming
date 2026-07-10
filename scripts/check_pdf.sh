#!/bin/sh
set -eu

if ! command -v pdfinfo >/dev/null 2>&1; then
  echo "pdfinfo is unavailable; skipping PDF metadata checks."
  exit 0
fi

for pdf in "$@"; do
  test -s "$pdf"
  pdfinfo "$pdf" | grep -q '^Pages:[[:space:]]*[1-9]'
  pdfinfo "$pdf" | grep -q '^Page size:[[:space:]]*595.*841.*A4'
  pdfinfo "$pdf" | grep -q '^Title:[[:space:]]*NPCs Competitive Programming Codebook'

  if command -v pdffonts >/dev/null 2>&1; then
    if pdffonts "$pdf" | tail -n +3 | awk '$4 != "yes" { exit 1 }'; then
      :
    else
      echo "PDF contains a font that is not embedded: $pdf" >&2
      exit 1
    fi
  fi
done

echo "PDF metadata, A4 page size, and font embedding checks passed."
