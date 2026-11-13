import subprocess
import time
import statistics
import argparse

INPUT_FILE = "data/benchmark_1m.in"

parser = argparse.ArgumentParser()
parser.add_argument(
    "--repetitions",
    type=int,
    default=5,
    help="Number of benchmark executions per configuration"
)

args = parser.parse_args()
REPETITIONS = args.repetitions

if REPETITIONS < 1:
    parser.error("--repetitions must be at least 1")

configurations = [
    ("Original", "-O0", "./build/benchmark-O0", "original"),
    ("Optimized", "-O0", "./build/benchmark-O0", "optimized"),
    ("Original", "-O2", "./build/benchmark-O2", "original"),
    ("Optimized", "-O2", "./build/benchmark-O2", "optimized"),
]

results = {}

expected_checksum = None

for algorithm, optimization, executable, argument in configurations:
    times = []
    checksums = []

    for repetition in range(REPETITIONS):
        with open(INPUT_FILE, "rb") as input_file:
            start = time.perf_counter()

            process = subprocess.run(
                [executable, argument],
                stdin=input_file,
                capture_output=True,
                text=True,
                check=True
            )

            elapsed = time.perf_counter() - start

        times.append(elapsed)

        checksum = process.stdout.strip().split()[-1]
        checksums.append(checksum)

    if len(set(checksums)) != 1:
        raise RuntimeError("Inconsistent checksums!")

    current_checksum = checksums[0]

    if expected_checksum is None:
        expected_checksum = current_checksum
    elif current_checksum != expected_checksum:
        raise RuntimeError(
            f"Checksum mismatch: expected {expected_checksum}, "
            f"got {current_checksum} for {algorithm} {optimization}"
    )

    key = (algorithm, optimization)
    results[key] = statistics.median(times)

    print(
        f"{algorithm:10} {optimization}: "
        f"median = {results[key]:.3f}s"
        )

print("\nSpeedup comparison:")

for optimization in ["-O0", "-O2"]:
    original = results[("Original", optimization)]
    optimized = results[("Optimized", optimization)]

    print(
        f"{optimization}: "
        f"{original / optimized:.2f}x faster"
    )














