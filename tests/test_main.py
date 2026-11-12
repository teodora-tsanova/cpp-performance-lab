import subprocess
import unittest
from pathlib import Path
import random

PROJECT_DIR = Path(__file__).parent.parent
DATA_DIR = PROJECT_DIR / "data"




class TestMain(unittest.TestCase):
    def test_randomized_comparison(self):
        rng = random.Random(42)
        q = 10_000

        queries = []

        for _ in range(q):
            operation = rng.randint(1, 3)

            if operation == 3:
                value = rng.randint(1, 10)
            else:
                value = rng.randint(1, 100)

            queries.append((operation, value))

        input_data = str(q) + "\n"
        input_data += "\n".join(
            f"{operation} {value}"
            for operation, value in queries
        )
        result = subprocess.run(
        ["./build/app"],
        input=input_data + "\n",
        capture_output=True,
        text=True,
        check=True
    )

    def run_test_case(self, name):
        input_data = (DATA_DIR / f"{name}.in").read_text()
        expected = (DATA_DIR / f"{name}.out").read_text()
        result = subprocess.run(
            ["./build/app"],
            input=input_data,
            capture_output=True,
            text=True,
            check=True
        )

        self.assertEqual(result.stdout.strip(), expected.strip())

    def test_basic(self):
        self.run_test_case("basic")

    def test_delete_missing(self):
        self.run_test_case("delete_missing")

    def test_frequency_queries(self):
        input_data = """8
    1 5
    1 6
    3 2
    1 10
    1 10
    1 6
    2 5
    3 2
    """

        result = subprocess.run(
            ["./build/app"],
            input=input_data,
            capture_output=True,
            text=True,
            check=True
        )

        self.assertEqual(result.stdout.strip(), "0\n1")

if __name__ == "__main__":
    unittest.main()