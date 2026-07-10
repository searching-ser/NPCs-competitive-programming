# NPCs Competitive Programming Codebook

A print-first competitive-programming reference notebook built with LaTeX,
`minted`, and Pygments. The build produces color and monochrome A4 PDFs from the
same tested GNU C++17 snippet sources.

## Requirements

- GNU Make
- GNU C++ with C++17 support
- `latexmk` and a current LaTeX distribution
- `minted` 3 and Python 3.8+
- Optional PDF checks: Poppler (`pdfinfo` and `pdffonts`)

TeX Live 2024 and newer can run `latexminted` through restricted shell escape;
unrestricted `-shell-escape` is normally unnecessary. Older TeX Live releases and
MiKTeX may require explicitly allowing `latexminted`. Only enable unrestricted shell
escape for trusted documents when no narrower configuration is available.

## Build and test

Run commands from the repository root:

```sh
make check        # Compile and run all GNU C++17 snippet checks
make color        # build/codebook-color.pdf
make monochrome   # build/codebook-monochrome.pdf
make pdf          # Both profiles plus PDF metadata/font checks
make all          # Snippet checks followed by both PDFs
make clean
```

Override detected tools when needed:

```sh
make check CXX=g++-15
make pdf LATEXMK=/path/to/latexmk
```

Generated PDFs and LaTeX auxiliaries live in `build/` and are not committed. CI
builds both profiles and publishes them as the `npc-codebook-pdfs` workflow artifact.

## Repository structure

```text
main.tex                    Color-profile document entry point
monochrome.tex              Monochrome-profile wrapper
style/codebook.sty          Layout, typography, minted, and print profiles
sections/*.tex              Topic prose and snippet inclusion order
snippets/cpp/               Canonical printable GNU C++17 sources
tests/                      Focused snippet/debug-helper tests
scripts/check_snippets.sh   Compiler/test orchestration
scripts/check_pdf.sh        A4, metadata, and font-embedding checks
Makefile                    Supported local build interface
.github/workflows/          Reproducible CI build and artifacts
AGENTS.md                   Detailed contributor and AI-agent onboarding
```

## Adding a snippet

1. Add the canonical source under `snippets/cpp/`.
2. Include that file from the appropriate topic using `\cppsnippet{...}`.
3. Add focused coverage to `tests/snippets_test.cpp`, or a dedicated test when
   combining snippets in one translation unit is inappropriate.
4. Run `make check` and `make pdf`.
5. Inspect both PDFs at actual print size, especially long lines and page breaks.

Substantial code must not be duplicated inside `.tex` files. Printed listings and
compiler tests should consume the same source file.
