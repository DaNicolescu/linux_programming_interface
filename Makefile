# Top-level aggregator Makefile
# Finds sub-Makefiles under `src/` and provides convenient targets

SHELL := /bin/bash

# use find to get directories that contain a Makefile
SUBDIRS := $(shell find src -name Makefile -printf '%h\n' | sort -u)

.PHONY: all build clean list help $(SUBDIRS)

all: build


build:
	@echo "Running 'make' in subdirectories (build default target)..."; \
	for d in $(SUBDIRS); do \
		if [ -f $$d/Makefile ]; then \
			echo "==> $$d"; \
			$(MAKE) -C $$d || exit 1; \
		else \
			echo "(skipping $$d: no Makefile)"; \
		fi; \
	done


clean:
	@echo "Running 'make clean' in subdirectories..."; \
	for d in $(SUBDIRS); do \
		if [ -f $$d/Makefile ]; then \
			echo "==> $$d"; \
			$(MAKE) -C $$d clean || true; \
		fi; \
	done


list:
	@echo "Discovered sub-Makefiles in:"; \
	for d in $(SUBDIRS); do echo " - $$d"; done


help:
	@printf "Usage:\n"; \
	printf "  make            -> runs 'make build' in all subdirs\n"; \
	printf "  make build      -> same as above\n"; \
	printf "  make clean      -> runs 'make clean' in all subdirs\n"; \
	printf "  make list       -> prints subdirs with Makefiles\n"; \
	printf "  make -C <dir> <target> -> run any target in a specific subdir\n"

# convenience: allow calling a specific subdir target like `make chapter_4/4.1 build`
%:
	@d=$$@; \
	if [ -f $$d/Makefile ]; then \
		$(MAKE) -C $$d $(MAKECMDGOALS); \
	else \
		echo "No Makefile in '$$d'"; exit 1; \
	fi
