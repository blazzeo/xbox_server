server: build
	@./exec/server

client: build
	@./exec/client

build:
	@cmake --build build

.PHONY: build run
