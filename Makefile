# Makefile
.PHONY: all build test container cp

all: build test
 
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
