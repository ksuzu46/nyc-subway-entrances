# Makefile
gcc_options = -std=c++17 -Wall --pedantic-error
target = bin/exe
sources = $(shell find . -type f -path '*src*/*' -name '*.cpp')
objects = $(patsubst %.cpp, %.o, $(sources))

$(target): $(objects)
	g++ $(gcc_options) -o $@ $^
	@echo "Built successfull."
	@echo "Try 'make run' to run the program"

$(objects): %.o : %.cpp
	g++ $(gcc_options) -c $< -o $@

run: ./bin/exe
	./bin/makeRunAll

clean:
	@rm -rf $(objects) $(target)

.PHONY: clean
