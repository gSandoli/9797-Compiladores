# Makefile
.PHONY: all build test container cp

all: build test

install:
	@sudo apt-get update && sudo apt-get install -y build-essential flex bison make cmake libllvm-13-ocaml-dev libllvm13 llvm-13 llvm-13-dev llvm-13-doc llvm-13-examples llvm-13-runtime clang-13 clang-tools-13 clang-13-doc libclang-common-13-dev libclang-13-dev libclang1-13 clang-format-13 python3-clang-13 clangd-13 clang-tidy-13 libfuzzer-13-dev lldb-13 lld-13 libc++-13-dev libc++abi-13-dev libomp-13-dev libclc-13-dev libunwind-13-dev libmlir-13-dev mlir-13-tools ; \
 
build:
	@rm -rf sc build/ ; \
	mkdir build ; \
	cd build ; \
	cmake .. ; \
	make ; \

test:
	@./sc tests/test.s ; \

container: 
	@docker build -t environment-compiler-9797 . ; \
	docker run --name diogo -it -d environment-compiler-9797 ; \

container-run:
	@docker run --name diogo -it -d environment-compiler-9797 ; \

cp: 
	@docker cp .  diogo:code/ ; \
	docker exec -it diogo /bin/bash ; \
