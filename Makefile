# HPDL-Planner -- atajos de compilacion/ejecucion
BUILD_DIR ?= build
JOBS      ?= $(shell nproc 2>/dev/null || echo 4)
ARGS      ?= -d examples/blocks.hpdl -p examples/blocks-problem.hpdl

.PHONY: all build run example clean distclean

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR) -j$(JOBS)

run: build
	$(BUILD_DIR)/planner $(ARGS)

example: build
	$(BUILD_DIR)/planner -d examples/blocks.hpdl -p examples/blocks-problem.hpdl

clean:
	@cmake --build $(BUILD_DIR) --target clean 2>/dev/null || true

distclean:
	rm -rf $(BUILD_DIR)
