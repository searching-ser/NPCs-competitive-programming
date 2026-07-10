# AGENTS.md

## Project overview

This repository builds the NPCs competitive-programming codebook: a compact A4
reference notebook intended for printing and use during contests. It combines
algorithm notes, formulas, terminology, and tested GNU C++17 snippets.

LaTeX is the typesetting/PDF backend. `minted` 3 delegates syntax tokenization to
Pygments, while `\inputminted` ensures the code printed in the book is the same code
compiled by the test suite. The supported build produces selectable landscape/two-column
or portrait/single-column PDFs in both color and monochrome under `build/`; generated
PDFs are CI artifacts and are not source-controlled.

## Repository structure

```text
.
├── main.tex                         # Shared content and portrait/color entry point
├── monochrome.tex                   # Portrait/monochrome wrapper
├── landscape.tex                    # Landscape/two-column color wrapper
├── landscape-monochrome.tex         # Landscape/two-column monochrome wrapper
├── style/
│   └── codebook.sty                 # Geometry, typography, headings, TOC, minted defaults
├── sections/
│   ├── main_template.tex            # General template, fast I/O, binary search
│   ├── math.tex                     # Formulas and GCD/LCM
│   ├── nomenclature.tex             # Mathematical notation table
│   ├── graph_algorithm.tex          # BFS
│   └── misc.tex                     # Small reusable idioms
├── snippets/cpp/
│   ├── template.cpp                 # General GNU C++17 contest template
│   ├── debugging.h                  # DEBUG-only stream helpers
│   └── *.cpp                        # Canonical printable snippets
├── tests/
│   ├── snippets_test.cpp            # Functional checks for composable snippets
│   └── debugging_test.cpp           # Standalone debug-header check
├── scripts/
│   ├── check_snippets.sh            # Strict GNU C++17 compilation/test runner
│   └── check_pdf.sh                 # PDF metadata, A4, and embedded-font checks
├── Makefile                         # Supported build/test interface
├── .github/workflows/codebook.yml  # GNU C++ checks and pinned TeX Live CI build
└── README.md                        # User-facing setup and common commands
```

Untracked `.docx` and `.pdf` files may exist in a working copy as reference/export
material. They are not build inputs. Treat them as user-owned: do not delete, modify,
or import them unless explicitly requested.

## Build process

Run all commands from the repository root.

```sh
make check        # Strict compile, functional tests, template release/debug checks
make pdf          # Default landscape layout, both print profiles and PDF checks
make landscape    # Landscape/two-column color and monochrome PDFs
make portrait     # Portrait/single-column color and monochrome PDFs
make pdf-all      # All four layout/profile combinations
make color        # Color profile for LAYOUT (default: landscape)
make monochrome   # Monochrome profile for LAYOUT
make all          # C++ checks, then default landscape PDF build
make clean        # Remove generated output
```

Set `LAYOUT=landscape` or `LAYOUT=portrait` when building an individual profile.
Output names include the selected layout and profile. CI builds all four combinations.

`make check` uses `CXX` (default `g++`) with GNU C++17, optimization, warnings, and
`-Werror`. Set `CXX=g++-15` or another GNU compiler when the platform's `g++` alias is
not GCC.

The PDF build requires `latexmk`, a current LaTeX distribution, `minted` 3, and
Python 3.8+. TeX Live 2024+ trusts `latexminted` through restricted shell escape;
older TeX Live and MiKTeX may need explicit permission. Do not add unrestricted
`-shell-escape` to the default build. CI uses the date-pinned
`danteev/texlive:2026-07-01` image and uploads all four PDFs as workflow artifacts.

`scripts/check_pdf.sh` uses `pdfinfo` and `pdffonts` when available. It checks nonempty
A4 PDFs, title metadata, and font embedding. Visual inspection is still required.

## Important files and ownership

- `main.tex` owns title/author metadata, document section order, and the conditional
  two-column body. It should remain a small orchestration file.
- `style/codebook.sty` owns all global page, heading, TOC, hyperlink, and code-listing
  presentation. Do not put competing global style rules in topic files.
- The profile/layout `.tex` entry points are thin wrappers. Every combination must
  contain identical topic content.
- `sections/*.tex` owns prose, formulas, headings, and references to canonical snippets.
- `snippets/cpp/*` is the single source of truth for printable code. Do not duplicate
  these implementations inside LaTeX.
- `tests/*` validates snippet behavior and composition. A snippet is not ready for the
  book merely because Pygments can render it.
- `Makefile` is the public build interface. CI and documentation should call its targets
  rather than inventing separate build commands.
- `build/` is disposable generated output. Never edit or commit its contents.

## Design philosophy

- Optimize for actual paper: fast scanning, crisp text, useful density, stable page
  breaks, and legibility under grayscale printing or photocopying.
- Correctness outranks breadth. Every reusable implementation should state or make
  clear its complexity, indexing, invariants, constraints, and sentinel behavior.
- Code color is secondary information. The monochrome profile must remain fully usable.
- Preserve code fidelity. Do not introduce typographic substitutions or visual wrapping
  that obscures token boundaries.
- Keep one canonical code copy and consume it from both LaTeX and tests.
- Prefer deterministic, documented builds over editor-specific setup.
- Landscape/two-column is the default layout; portrait/single-column remains supported.
  Keep representative snippets safe in both. Reduce whitespace before shrinking code
  to an unreadable size, and never rely on arbitrary token splitting.

## Coding conventions

### GNU C++17

- Target `-std=gnu++17`; `<bits/stdc++.h>` is allowed in the general contest template.
- Use `DEBUG=1` to enable `debugging.h`. Release and debug template configurations must
  both compile.
- Prefer compact contest-ready interfaces, but do not sacrifice defined behavior or
  hide important preconditions.
- State complexity in nearby LaTeX prose or a concise source comment.
- Divide before multiplying where it reduces overflow risk, and document when numeric
  bounds are still the caller's responsibility.
- Reusable fragments may assume the general template's aliases/imports when that saves
  printed space. Their tests must supply the same context explicitly.
- Give new globally visible functions specific names to reduce collisions when snippets
  are combined.

### LaTeX

- Use one `\section` per major topic and `\subsection` per algorithm or concept.
- Include C++ with `\cppsnippet[options]{snippets/cpp/file.cpp}`.
- Use explicit `.tex` extensions in `\input` commands.
- Escape LaTeX-special characters in prose; never escape source inside external files.
- Keep global formatting in `style/codebook.sty`.
- Heading hooks reserve page space, but agents must still inspect rendered transitions.
- Do not enable `breakanywhere`; arbitrary token splitting harms contest readability.
- Per-listing font overrides should be exceptional. `\tiny` is currently reserved for
  the long general template.

## Adding or modifying content

1. Check `git status`; preserve unrelated and untracked user files.
2. Read the target section, source snippet, and existing tests.
3. Add or modify the canonical file under `snippets/cpp/`.
4. Add functional or compile coverage under `tests/`.
5. Reference the canonical path from the section with `\cppsnippet`.
6. Run `make check` with GCC, including release/debug checks when relevant.
7. Run `make pdf-all` with the supported TeX toolchain.
8. Inspect all four PDFs at 100%/actual size: title and TOC, longest lines, formulas,
   column flow, heading/listing transitions, page bottoms, final page, and grayscale
   contrast.
9. Inspect the LaTeX log for errors, missing glyphs/references, and overfull boxes.
10. Update README/AGENTS when the public build contract or structure changes.

If a required tool is unavailable, complete every remaining check and report precisely
what was not verified.

## Current limitations and technical debt

- The content set remains small and covers only a few introductory snippets.
- There is no automated visual regression comparison; PDF checks are structural only.
- The checked PDF is untagged unless the selected LaTeX engine/package versions add
  tagging; PDF/UA and archival conformance are not configured.
- Pygments' built-in `friendly` theme is used for both profiles; the monochrome build
  converts it through xcolor's `gray` model. A project-owned token theme may eventually
  provide tighter control over print contrast.
- The general template is rendered at `\tiny` to control page count; actual-size print
  review must confirm it remains legible in both supported layouts.
- The test suite combines compatible fragments into one translation unit but does not
  yet test every edge constraint or overflow boundary.
- CI pins a dated TeX Live image tag, not an immutable image digest or action commit SHA.
- Naming retains historical files such as `graph_algorithm.tex`; renaming them is low
  priority unless a broader taxonomy is introduced.
- No event-specific limits for pages, paper size, binding, color, or generated material
  are encoded. Confirm contest rules before final printing.

## Future improvement ideas

- Add more algorithms with explicit metadata for complexity, dependencies, indexing,
  and numeric limits.
- Add golden/reference tests for advanced data structures and randomized differential
  tests where appropriate.
- Add rendered-page image comparison with a small, deliberately reviewed tolerance.
- Pin CI images and third-party actions by immutable digest/SHA.
- Create a project-owned Pygments theme for color and grayscale contrast targets.
- Add an index and a one-page quick-reference sheet as the content grows.
- Evaluate tagged PDF/PDF-UA support and validate with veraPDF.
- Add configurable Letter output only if an actual contest requires it.
- Add source/license attribution conventions before importing third-party snippets.

## Common pitfalls

- Do not edit generated PDFs or treat reference Word/PDF exports as source.
- Do not duplicate printed code inside `.tex`; use `\inputminted` via `\cppsnippet`.
- Do not validate GNU contest code solely with Apple Clang; `<bits/stdc++.h>` requires a
  GCC/libstdc++ environment.
- Do not define `DEBUG=0` with old `#ifdef DEBUG` semantics. The template deliberately
  checks both definition and value.
- Do not enable unrestricted shell escape by default. Configure `latexminted` as the
  permitted executable on older toolchains.
- Do not change column width or enable arbitrary line breaking without inspecting real
  long code in both layouts.
- Do not judge colors only on a backlit screen; inspect the monochrome PDF and paper.
- Do not commit `build/`, `_minted-*`, LaTeX auxiliaries, or locally generated PDFs.
- Do not assume `make pdf` ran successfully merely because C++ tests passed; the
  toolchains are independent.

## Assumptions for AI agents

- The primary artifact is a contest-usable printed PDF, not a web-first book.
- LaTeX plus `minted` is the approved implementation until maintainers request another
  migration.
- GNU C++17 is the intended contest environment.
- `snippets/cpp/` is canonical; sections are presentation and explanation only.
- All layout and color profiles must remain content-identical.
- Generated PDFs are CI/local artifacts and should not be committed.
- Untracked reference documents are user-owned and outside normal task scope.
