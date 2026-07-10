SHELL := /bin/sh

CXX ?= g++
LATEXMK ?= latexmk
BUILD_DIR ?= build
LAYOUT ?= landscape
LATEX_FLAGS := -pdf -interaction=nonstopmode -halt-on-error -file-line-error -outdir=$(BUILD_DIR)

VALID_LAYOUTS := landscape portrait

ifeq ($(filter $(LAYOUT),$(VALID_LAYOUTS)),)
$(error LAYOUT must be one of: $(VALID_LAYOUTS))
endif

ifeq ($(LAYOUT),landscape)
COLOR_SOURCE := landscape.tex
MONOCHROME_SOURCE := landscape-monochrome.tex
else
COLOR_SOURCE := main.tex
MONOCHROME_SOURCE := monochrome.tex
endif

COLOR_PDF := $(BUILD_DIR)/codebook-$(LAYOUT)-color.pdf
MONOCHROME_PDF := $(BUILD_DIR)/codebook-$(LAYOUT)-monochrome.pdf

.PHONY: all pdf pdf-all landscape portrait color monochrome check verify-pdf clean

all: check pdf

pdf: verify-pdf

pdf-all:
	$(MAKE) LAYOUT=landscape pdf
	$(MAKE) LAYOUT=portrait pdf

landscape:
	$(MAKE) LAYOUT=landscape pdf

portrait:
	$(MAKE) LAYOUT=portrait pdf

color:
	@mkdir -p $(BUILD_DIR)
	$(LATEXMK) $(LATEX_FLAGS) -jobname=codebook-$(LAYOUT)-color $(COLOR_SOURCE)

monochrome:
	@mkdir -p $(BUILD_DIR)
	$(LATEXMK) $(LATEX_FLAGS) -jobname=codebook-$(LAYOUT)-monochrome $(MONOCHROME_SOURCE)

check:
	CXX="$(CXX)" sh scripts/check_snippets.sh

verify-pdf: color monochrome
	sh scripts/check_pdf.sh $(COLOR_PDF) $(MONOCHROME_PDF)

clean:
	$(RM) -r $(BUILD_DIR)
