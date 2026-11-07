CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET = build/app
SOURCE = src/main.cpp

.PHONY: all cl test

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

cl:
	rm -rf build

test: all
	python3 -m unittest discover -s tests -v