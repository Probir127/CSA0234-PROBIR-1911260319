"""Exercise the compiled programs through their documented stdin/stdout interfaces."""
from pathlib import Path
import subprocess
import unittest

BUILD = Path(__file__).resolve().parents[1] / "build"


class Examples(unittest.TestCase):
    def run_program(self, name, data):
        return subprocess.run(
            [str(BUILD / name)], input=data, text=True, capture_output=True,
            timeout=5, check=False,
        )

    def expect(self, name, data, output):
        result = self.run_program(name, data)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stderr, "")
        self.assertEqual(result.stdout, output)

    def reject(self, name, data):
        result = self.run_program(name, data)
        self.assertEqual(result.returncode, 1)
        self.assertEqual(result.stderr, "Invalid input\n")
        self.assertEqual(result.stdout, "")

    def test_pogil(self):
        self.expect("01_pogil_arrays", "5 1 2 3 4 5", "Sum: 15\nMean: 3.00\n")
        self.expect("01_pogil_arrays", "3 -5 0 2", "Sum: -3\nMean: -1.00\n")
        self.expect("01_pogil_arrays", "1 7", "Sum: 7\nMean: 7.00\n")
        self.expect("01_pogil_arrays", "100 " + "2147483647 " * 100,
                    "Sum: 214748364700\nMean: 2147483647.00\n")

    def test_jigsaw(self):
        self.expect("02_jigsaw_statistics", "5 12 7 19 7 5",
                    "Min: 5\nMax: 19\nSum: 50\nMean: 10.00\n")
        self.expect("02_jigsaw_statistics", "3 -9 -2 -7",
                    "Min: -9\nMax: -2\nSum: -18\nMean: -6.00\n")
        self.expect("02_jigsaw_statistics", "1 0",
                    "Min: 0\nMax: 0\nSum: 0\nMean: 0.00\n")
        self.expect("02_jigsaw_statistics", "2 -2147483648 2147483647",
                    "Min: -2147483648\nMax: 2147483647\nSum: -1\nMean: -0.50\n")

    def test_inventory(self):
        self.expect("03_scale_up_inventory", "3 2 1250 3 499 0 999",
                    "Total cents: 3997\nTotal value: 39.97\n")
        self.expect("03_scale_up_inventory", "2 0 1250 10 0",
                    "Total cents: 0\nTotal value: 0.00\n")
        self.expect("03_scale_up_inventory", "100 " + "10000 1000000 " * 100,
                    "Total cents: 1000000000000\nTotal value: 10000000000.00\n")
        for data in ("0", "101", "1 -1 10", "1 10001 10", "1 1 -1",
                     "1 1 1000001", "1 2", "1 2 1.5"):
            with self.subTest(data=data):
                self.reject("03_scale_up_inventory", data)

    def test_primes(self):
        for value in (2, 3, 97, 2147483647):
            with self.subTest(value=value):
                self.expect("04_pltbl_prime", str(value), f"{value} is prime\n")
        for value in (-2147483648, -3, 0, 1, 4, 49, 2147483646):
            with self.subTest(value=value):
                self.expect("04_pltbl_prime", str(value), f"{value} is not prime\n")

    def test_bounds(self):
        self.expect("05_critical_bounds", "0", "Count: 0\nSum: 0\n")
        self.expect("05_critical_bounds", "1 -12", "Count: 1\nSum: -12\n")
        self.expect("05_critical_bounds", "100 " + "-2147483648 " * 100,
                    "Count: 100\nSum: -214748364800\n")
        for data in ("-1", "101", "2 1", "1 cat", "1 2147483648"):
            with self.subTest(data=data):
                self.reject("05_critical_bounds", data)

    def test_quiz(self):
        for answers, score, correct_count in (
            ("1 2 3 1 2", 5, 5), ("2 1 1 2 1", 0, 0),
            ("1 1 3 2 2", 3, 3),
        ):
            with self.subTest(answers=answers):
                result = self.run_program("06_quiz", answers)
                self.assertEqual(result.returncode, 0, result.stderr)
                self.assertEqual(result.stderr, "")
                self.assertTrue(result.stdout.endswith(f"Score: {score}/5\n"))
                self.assertEqual(result.stdout.count("\nCorrect;"), correct_count)
                self.assertEqual(result.stdout.count("\nIncorrect;"), 5 - correct_count)
        for data in ("0 2 3 1 2", "1 2 4 1 2", "1 2 3 1"):
            with self.subTest(data=data):
                self.reject("06_quiz", data)

    def test_swap(self):
        for a, b in ((10, 20), (-5, 0), (7, 7), (-2147483648, 2147483647)):
            with self.subTest(a=a, b=b):
                self.expect("07_role_play_swap", f"{a} {b}",
                            f"Before: {a} {b}\nInside value function: {b} {a}\n"
                            f"After value call: {a} {b}\nAfter pointer call: {b} {a}\n")

    def test_search(self):
        for data, index in (
            ("5 2 4 6 8 10 8", 3), ("5 2 4 6 8 10 2", 0),
            ("5 2 4 6 8 10 10", 4), ("5 2 4 6 8 10 7", -1),
            ("3 2 4 6 0", -1), ("3 2 4 6 9", -1),
            ("0 7", -1), ("1 4 4", 0), ("1 4 3", -1),
            ("4 -9 -3 0 5 -3", 1), ("5 1 2 2 2 3 2", 2),
            ("2 -2147483648 2147483647 2147483647", 1),
            ("100 " + " ".join(map(str, range(100))) + " 99", 99),
        ):
            with self.subTest(data=data):
                self.expect("08_flipped_search", data, f"Index: {index}\n")
        for data in ("-1 2", "101", "3 1 3 2 3", "2 1 2", "0 cat"):
            with self.subTest(data=data):
                self.reject("08_flipped_search", data)

    def test_input_contracts(self):
        valid = {
            "01_pogil_arrays": "1 0", "02_jigsaw_statistics": "1 0",
            "03_scale_up_inventory": "1 1 0", "04_pltbl_prime": "2",
            "05_critical_bounds": "0", "06_quiz": "1 2 3 1 2",
            "07_role_play_swap": "1 2", "08_flipped_search": "0 1",
        }
        for name, data in valid.items():
            for bad in ("", "abc", "9" * 100, data + " extra", data + " 9"):
                with self.subTest(program=name, data=bad):
                    self.reject(name, bad)
        for name in ("01_pogil_arrays", "02_jigsaw_statistics"):
            for bad in ("0", "101", "-1", "2 7", "1 1.2", "1 2147483648"):
                with self.subTest(program=name, data=bad):
                    self.reject(name, bad)


if __name__ == "__main__":
    unittest.main(verbosity=2)
