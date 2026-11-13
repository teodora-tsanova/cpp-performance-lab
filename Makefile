CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET = build/app
SOURCE = src/main.cpp src/frequency_queries.cpp

UNIT_TEST_TARGET = build/unit_tests
UNIT_TEST_SOURCE = tests/test_frequency_queries.cpp src/frequency_queries.cpp

BENCHMARK_SOURCE = benchmarks/benchmark.cpp src/frequency_queries.cpp

BENCHMARK_O0 = build/benchmark-O0
BENCHMARK_O2 = build/benchmark-O2

.PHONY: all cl test unit-test benchmark-build

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

$(UNIT_TEST_TARGET): $(UNIT_TEST_SOURCE) src/frequency_queries.h
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc $(UNIT_TEST_SOURCE) -o $(UNIT_TEST_TARGET) -lgtest -lgtest_main -pthread

$(BENCHMARK_O0): $(BENCHMARK_SOURCE) src/frequency_queries.h
	mkdir -p build
	$(CXX) -std=c++20 -Wall -Wextra -Wpedantic -O0 -Isrc $(BENCHMARK_SOURCE) -o $(BENCHMARK_O0)

$(BENCHMARK_O2): $(BENCHMARK_SOURCE) src/frequency_queries.h
	mkdir -p build
	$(CXX) -std=c++20 -Wall -Wextra -Wpedantic -O2 -Isrc $(BENCHMARK_SOURCE) -o $(BENCHMARK_O2)



unit-test: $(UNIT_TEST_TARGET)
	./$(UNIT_TEST_TARGET)

cl:
	rm -rf build

test: all
	python3 -m unittest discover -s tests -v

benchmark-build: $(BENCHMARK_O0) $(BENCHMARK_O2)