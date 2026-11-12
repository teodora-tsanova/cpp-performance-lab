CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET = build/app
SOURCE = src/main.cpp src/frequency_queries.cpp

UNIT_TEST_TARGET = build/unit_tests
UNIT_TEST_SOURCE = tests/test_frequency_queries.cpp src/frequency_queries.cpp

.PHONY: all cl test unit_test

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

$(UNIT_TEST_TARGET): $(UNIT_TEST_SOURCE) src/frequency_queries.h
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc $(UNIT_TEST_SOURCE) -o $(UNIT_TEST_TARGET) -lgtest -lgtest_main -pthread

unit-test: $(UNIT_TEST_TARGET)
	./$(UNIT_TEST_TARGET)

cl:
	rm -rf build

test: all
	python3 -m unittest discover -s tests -v