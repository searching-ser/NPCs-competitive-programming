#!/bin/sh
set -eu

if ! command -v pdfinfo >/dev/null 2>&1; then
  echo "pdfinfo is unavailable; skipping PDF metadata checks."
  exit 0
fi

for pdf in "$@"; do
  test -s "$pdf"
  pdfinfo "$pdf" | grep -q '^Pages:[[:space:]]*[1-9]'
  case "$pdf" in
    *landscape*)
      pdfinfo "$pdf" | grep -q '^Page size:[[:space:]]*841.*595.*A4'
      ;;
    *portrait*)
      pdfinfo "$pdf" | grep -q '^Page size:[[:space:]]*595.*841.*A4'
      ;;
    *)
      echo "PDF filename does not identify its layout: $pdf" >&2
      exit 1
      ;;
  esac
  pdfinfo "$pdf" | grep -q '^Title:[[:space:]]*NPCs Competitive Programming Codebook'

  if command -v pdffonts >/dev/null 2>&1; then
    # Font types such as "Type 1" contain spaces, so the `emb` column does not
    # have a fixed field number. Read it relative to the five stable trailing
    # columns: emb, sub, uni, object ID, and generation ID.
    if pdffonts "$pdf" | tail -n +3 | awk '
      NF >= 5 && $(NF - 4) != "yes" {
        print "Non-embedded font row: " $0 > "/dev/stderr"
        failed = 1
      }
      END { exit failed }
    '; then
      :
    else
      echo "PDF contains a font that is not embedded: $pdf" >&2
      exit 1
    fi
  fi
done

echo "PDF metadata, A4 page size, and font embedding checks passed."
