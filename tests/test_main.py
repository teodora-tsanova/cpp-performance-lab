import subprocess
import unittest


class TestMain(unittest.TestCase):
    #class TestMain():

    def test_hello_message(self):
        result = subprocess.run(
            ["./build/app"],
            capture_output=True,
            text=True,
            check=True
        )

        self.assertEqual(result.stdout.strip(), "Hello!!")


if __name__ == "__main__":
    unittest.main()