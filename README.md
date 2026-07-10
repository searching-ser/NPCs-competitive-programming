# NPCs Competitive Programming Codebook

A print-first competitive-programming reference notebook built with LaTeX,
`minted`, and Pygments. The build produces selectable landscape/two-column or
portrait/single-column A4 PDFs, each in color and monochrome, from the same tested
GNU C++17 snippet sources.

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
make pdf          # Default landscape layout, both print profiles
make landscape    # Landscape/two-column color and monochrome PDFs
make portrait     # Portrait/single-column color and monochrome PDFs
make pdf-all      # All four layout/profile combinations
make color        # Color PDF for LAYOUT (default: landscape)
make monochrome   # Monochrome PDF for LAYOUT
make all          # Snippet checks, then the default landscape PDFs
make clean
```

Select the layout for an individual profile with the `LAYOUT` variable:

```sh
make LAYOUT=portrait color
make LAYOUT=landscape monochrome
```

Outputs include both choices in their names, for example
`build/codebook-landscape-color.pdf` and
`build/codebook-portrait-monochrome.pdf`.

Override detected tools when needed:

```sh
make check CXX=g++-15
make pdf LATEXMK=/path/to/latexmk
```

Generated PDFs and LaTeX auxiliaries live in `build/` and are not committed. CI
builds all four layout/profile combinations and publishes them as the
`npc-codebook-pdfs` workflow artifact.

## Repository structure

```text
main.tex                    Shared content and portrait/color entry point
monochrome.tex              Portrait/monochrome wrapper
landscape.tex               Landscape/two-column color wrapper
landscape-monochrome.tex    Landscape/two-column monochrome wrapper
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
4. Run `make check` and `make pdf-all`.
5. Inspect all four PDFs at actual print size, especially long lines, column flow,
   and page breaks.

Substantial code must not be duplicated inside `.tex` files. Printed listings and
compiler tests should consume the same source file.
