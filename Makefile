CC = g++
CFLAGS = -c -Wall

all:
	@echo "Use 'make build' to compile the project"
	@echo "Use 'make run' to run the project"
	@echo "Use 'make clean' to clean the project"

build: src/main.cpp src/image.cpp
	mkdir -p build
	$(CC) $(CFLAGS) src/main.cpp -o build/main.o
	$(CC) $(CFLAGS) src/image.cpp -o build/image.o
	$(CC) build/main.o build/image.o -o build/main

run: build
	./build/main $(ARGS)

clean:
	rm -rf build/*.o build/main