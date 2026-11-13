# C++ Performance Lab

A C++20 project for exploring software development, automated testing, algorithm optimization, and performance benchmarking.

The project implements the **Frequency Queries** problem using two different algorithms and compares their performance under different compiler optimization levels.

## Technologies

- C++20
- Python 3 (unittest)
- GoogleTest
- GNU Make
- Docker
- Git and GitHub
- GitHub Actions

## Project Structure

```text
cpp-performance-lab/
├── .github/
│   └── workflows/
│       └── ci.yml
├── benchmarks/
│   ├── benchmark.cpp
│   └── run_benchmarks.py
├── data/
│   └── benchmark_1m.in
├── src/
│   ├── main.cpp
│   ├── frequency_queries.cpp
│   └── frequency_queries.h
├── tests/
│   ├── test_main.py
│   └── test_frequency_queries.cpp
├── Dockerfile
├── Makefile
└── README.md
```

## Development Environment

The project uses Docker to provide a reproducible Linux development environment.

The Docker image is based on Ubuntu 24.04 and installs:

- GCC and build tools
- Python 3
- Git
- GoogleTest

### Build the Docker image

```bash
docker build -t cpp-performance-lab:1.0 .
```

### Create and start a container

```bash
docker run -it --name cpp-lab \
    -v "$PWD":/workspace \
    cpp-performance-lab:1.0
```

The project directory is mounted into `/workspace` inside the container. This means files are shared between the host and the container.

To restart an existing container:

```bash
docker start -ai cpp-lab
```

## Build

Build the main application:

```bash
make
```

Run the application:

```bash
./build/app
```

## Testing

The project contains two types of automated tests.

### C++ unit tests

GoogleTest is used to test the frequency query implementations directly.

```bash
make unit-test
```

### Python integration tests

Python unittest is used to test the application using input and expected-output files, including randomized comparisons.

```bash
make test
```

## Performance Benchmarking

Two implementations of the Frequency Queries algorithm are benchmarked:

- **Original:** uses a map scan to find whether a number with a given frequency exists.
- **Optimized:** maintains both number-to-frequency and frequency-to-count mappings, allowing average O(1) frequency lookups.

The benchmark executables are compiled with two optimization levels:

- `-O0`: compiler optimizations disabled
- `-O2`: compiler optimizations enabled

### Build benchmark executables

```bash
make benchmark-build
```

### Run benchmarks

```bash
python3 benchmarks/run_benchmarks.py
```

By default, each configuration is executed five times and the median execution time is reported.

The number of repetitions can be changed:

```bash
python3 benchmarks/run_benchmarks.py --repetitions 10
```

The script also checks that all configurations produce the same checksum.

## Continuous Integration

GitHub Actions automatically builds and tests the project on:

- Pushes to `main`
- Pull requests targeting `main`

The CI workflow includes two jobs:

1. **Build and test:** builds the application and runs C++ unit tests and Python integration tests.
2. **Benchmark:** builds the benchmark executables and runs the performance benchmarks.

### Manual benchmark execution

The workflow can also be triggered manually from the GitHub Actions tab.

When starting a manual run, the number of benchmark repetitions can be configured through the `repetitions` input. The default is 5.

## Goals

- Explore modern C++ development.
- Improve algorithm efficiency and understand time complexity.
- Practice automated testing and test coverage.
- Understand compiler optimization and performance measurement.
- Build reproducible development environments with Docker.
- Develop and maintain a CI pipeline using GitHub Actions.