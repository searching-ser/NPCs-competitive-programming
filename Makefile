SHELL := /bin/sh

CXX ?= g++
LATEXMK ?= latexmk
BUILD_DIR ?= build
LATEX_FLAGS := -pdf -interaction=nonstopmode -halt-on-error -file-line-error -outdir=$(BUILD_DIR)

.PHONY: all pdf color monochrome check verify-pdf clean

all: check pdf

pdf: verify-pdf

color:
	@mkdir -p $(BUILD_DIR)
	$(LATEXMK) $(LATEX_FLAGS) -jobname=codebook-color main.tex

monochrome:
	@mkdir -p $(BUILD_DIR)
	$(LATEXMK) $(LATEX_FLAGS) -jobname=codebook-monochrome monochrome.tex

check:
	CXX="$(CXX)" sh scripts/check_snippets.sh

verify-pdf: color monochrome
	sh scripts/check_pdf.sh $(BUILD_DIR)/codebook-color.pdf $(BUILD_DIR)/codebook-monochrome.pdf

clean:
	$(LATEXMK) -C -outdir=$(BUILD_DIR) main.tex monochrome.tex
	$(RM) -r $(BUILD_DIR)
