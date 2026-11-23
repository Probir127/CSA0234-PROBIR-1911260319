"""Run the real lab executables with examples, boundaries and invalid inputs."""
from pathlib import Path
import ctypes
import json
import math
import os
import random
import re
import struct
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
CATALOG = json.loads((ROOT / 'experiments.json').read_text())
BY_NUMBER = {item['number']: item for item in CATALOG}
RUN_COUNT = 0


def invoke(number, data, directory):
    global RUN_COUNT
    RUN_COUNT += 1
    executable = ROOT / os.environ.get('LAB_BUILD_DIR', 'build') / Path(BY_NUMBER[number]['executable']).name
    result = subprocess.run([str(executable)],
                            input=data, text=True, capture_output=True,
                            cwd=directory, timeout=10, check=False)
    if any(marker in result.stderr for marker in ('runtime error:', 'ERROR: AddressSanitizer', 'ERROR: LeakSanitizer')):
        raise AssertionError(result.stderr)
    return result


class LabExperiments(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='c-lab-tests-')
        self.directory = Path(self.temporary.name)
        (self.directory / 'input.txt').write_text('Hello world\nSecond line\n')

    def tearDown(self):
        self.temporary.cleanup()

    def expect(self, number, data, output):
        result = invoke(number, data, self.directory)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stderr, '')
        self.assertEqual(result.stdout, output)
        return result

    def reject(self, number, data):
        result = invoke(number, data, self.directory)
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertIn('Error:', result.stderr)

    def seed_binary(self):
        self.expect(119, BY_NUMBER[119]['sample_input'], BY_NUMBER[119]['expected_output'])

    def test_numeric_boundaries(self):
        cases = [
            (3, '-1000000 1000000', 'Sum: 0\n'),
            (4, '-4 -4', '-4 -4\n'), (5, '0 0', '0 0\n'),
            (6, '0', 'Area: 0.00\nCircumference: 0.00\n'),
            (8, '1000 5 0', 'Interest: 0.00\nAmount: 1000.00\n'),
            (9, 'F 32', 'Celsius: 0.00\n'), (9, 'C -40', 'Fahrenheit: -40.00\n'),
            (10, '0', 'Years: 0\nWeeks: 0\nDays: 0\n'),
            (18, '86400', '24:00:00\n'), (19, '999', 'Hundreds: 9\nTens: 9\nUnits: 9\n'),
            (28, '-4', 'Modulus: Even\nBitwise: Even\n'),
            (29, '5 5 5', 'Largest: 5\n'), (30, '1900', 'Not a leap year\n'),
            (30, '2024', 'Leap year\n'), (32, '90', 'Grade: A\n'), (32, '59.99', 'Grade: F\n'),
            (33, '1 2 1', 'Roots: -1.00 -1.00\n'),
            (33, '1 0 1', 'Roots: -0.00 + 1.00i, -0.00 - 1.00i\n'),
            (36, '0', 'Sum: 0\n'), (37, '0', 'Factorial: 1\n'),
            (37, '20', f'Factorial: {math.factorial(20)}\n'),
            (38, '0', '\n'), (39, '1', 'Not prime\n'), (39, '2', 'Prime\n'),
            (40, '0 1', '\n'), (41, '0', 'Armstrong\n'), (41, '10', 'Not Armstrong\n'),
            (42, '0', 'Palindrome\n'), (43, '1000', 'Reversed: 1\n'),
            (44, '0 0', 'GCD: 0\nLCM: 0\n'), (44, '0 7', 'GCD: 7\nLCM: 0\n'),
            (45, '1', 'Not perfect\n'), (45, '6', 'Perfect\n'),
            (102, '0', 'Factorial: 1\n'), (104, '0 0', 'GCD: 0\n'),
            (105, '1', 'A -> C\n'), (106, '0 0', 'Power: 1.000000\n'),
        ]
        for number, data, output in cases:
            with self.subTest(number=number, data=data): self.expect(number, data, output)

    def test_rejections(self):
        cases = [(3, '3x 4'), (3, '9'*300), (6, '-1'), (8, '1000 NaN 2'),
                 (9, 'X 2'), (11, 'AB'), (16, '1 2 3'), (17, '101 1 2 3 4'),
                 (19, '99'), (23, '8'), (25, '1 0'), (27, '1 1 32'),
                 (31, '1 / 0'), (31, '1 % 2'), (32, '-1'), (33, '0 2 3'),
                 (34, '9'), (37, '21'), (38, '94'), (40, '10 2'),
                 (49, '101'), (50, '0'), (53, '3 1 3 2 2'),
                 (57, '2 2 1 0'), (59, '0 2'), (60, '11 1 1'),
                 (64, 'x'*256+'\n'), (69, 'hello!\nhello\n'),
                 (73, '1\n\n90\n'), (78, '29 2 1900 1 3 1900'),
                 (79, '2\n1\nA\n50\n1\nB\n60\n'),
                 (85, '1\n1\nA\n10 0 0 20'), (93, '1 4 2'),
                 (95, '2 1 3\nA\n0'), (102, '21'), (106, '0 -1'),
                 (107, '3 2 1 3 2'), (111, '0'), (112, '0 1'),
                 (114, '4 1 0 0'), (116, ''),
                 (117, 'missing.txt\ncopy.txt\n'), (118, 'missing.txt\n'),
                 (120, '1 90')]
        for number, data in cases:
            with self.subTest(number=number, data=data): self.reject(number, data)

    def test_sorting_and_array_properties(self):
        rng = random.Random(1911260319)
        for count in (0, 1, 2, 25, 100):
            values = [rng.randint(-100, 100) for _ in range(count)]
            data = str(count)+' '+' '.join(map(str, values))
            ordered = ' '.join(map(str, sorted(values)))+'\n'
            for number in (54, 55, 56):
                with self.subTest(number=number, count=count): self.expect(number, data, ordered)
            self.expect(51, data, ' '.join(map(str, reversed(values)))+'\n')
            self.expect(58, data, ' '.join(map(str, dict.fromkeys(values)))+'\n')
        self.expect(57, '0 0', '\n')
        self.expect(50, '3 -9 -2 -5', 'Largest: -2\nSmallest: -9\n')

    def test_search_boundaries(self):
        for number in (52, 53, 107):
            for data, index in [('0 7', -1), ('1 4 4', 0), ('1 4 3', -1),
                                ('5 1 3 5 7 9 1', 0), ('5 1 3 5 7 9 9', 4),
                                ('5 1 3 5 7 9 8', -1)]:
                with self.subTest(number=number, data=data): self.expect(number, data, f'Index: {index}\n')
        for number in (53, 107):
            result = invoke(number, '5 1 2 2 2 3 2', self.directory)
            self.assertEqual(result.returncode, 0)
            self.assertIn(result.stdout, ['Index: 1\n', 'Index: 2\n', 'Index: 3\n'])

    def test_matrix_properties(self):
        self.expect(60, '2 2 2 1 -2 3 4 1 0 0 1', '1 -2\n3 4\n')
        self.expect(61, '1 3 7 8 9', '7\n8\n9\n')
        self.expect(63, '1 7', 'Main diagonal: 7\nSecondary diagonal: 7\nSymmetric\n')
        self.expect(63, '2 1 2 3 4', 'Main diagonal: 5\nSecondary diagonal: 5\nNot symmetric\n')
        self.expect(59, '1 1 10000 -10000', 'Addition:\n0\nSubtraction:\n20000\n')

    def test_strings(self):
        for text in ('', 'a', 'A man a plan', 'x'*255):
            self.expect(64, text+'\n', f'Length: {len(text)}\n')
            self.expect(65, text+'\n', text[::-1]+'\n')
        self.expect(66, '\n', 'Palindrome\n')
        self.expect(66, 'Level\n', 'Not palindrome\n')
        self.expect(68, '\nabc\n', 'Concatenated: abc\nComparison: -1\n')
        self.expect(68, 'same\nsame\n', 'Concatenated: samesame\nComparison: 0\n')
        self.expect(69, 'Dormitory\nDirty room\n', 'Anagrams\n')
        self.expect(69, 'ab\naa\n', 'Not anagrams\n')
        self.expect(71, 'a a\n', '32:1\n97:2\n')
        self.expect(72, 'abc\n\n', 'Index: 0\n')
        self.expect(72, 'abc\nabcdef\n', 'Index: -1\n')
        self.expect(72, 'abc\nz\n', 'Index: -1\n')

    def test_structures_and_menus(self):
        self.expect(77, '23 59 59 0 0 0', '23:59:59\n')
        self.expect(78, '1 1 2000 1 1 2000', 'Dates are equal\n')
        self.expect(80, '1\n1\nMira\n80\n2', 'Not found\n')
        self.expect(83, '1 1\nC\nAuthor\n2 1 2 1 3 1 3 1 2 9 0',
                    'Added\nBorrowed\nUnavailable\nReturned\nAlready available\nNot found\n')
        self.expect(84, '1\nAlex\n100\n2 200 3 0', 'Insufficient funds\n1 | Alex | 100 cents\n')
        self.expect(86, '1 1\nPen\n2 10\n3 1 3 4 0',
                    'Added\nInsufficient stock\n1 | Pen | 2 | 10 cents\nStock value cents: 20\n')
        self.expect(87, '1\nMira\n99', 'Inside copy: 100.00\nCaller: 99.00\n')
        self.expect(88, '1\nMira\n99', 'Caller: 100.00\n')
        self.expect(92, '1 -7', 'Integer: -7\n')
        self.expect(92, '3\nhello\n', 'Text: hello\n')
        self.expect(95, '1 1 1\nAlex\n1 1\nSam\n3 0',
                    'Booked: 1\nSeat already reserved\n1 | Alex\n')
        self.expect(96, '1 2 3 1 -2 3', '0 0\n')

    def test_recursion_and_memory(self):
        values = [0, 1]
        for _ in range(91): values.append(values[-1]+values[-2])
        expected = ' '.join(map(str, values))+'\n'
        for number in (38, 103): self.expect(number, '93', expected)
        self.expect(103, '0', '\n')
        self.expect(108, '0\n\n', 'Digit sum: 0\nReversed: \n')
        self.expect(111, '1 -7 0', 'malloc: -7\ncalloc first: 0\nrealloc: -7\n')
        self.expect(115, '3 2 7 1 7 2 7 3 0', '\nNot found\nInserted\nDeleted\n\n')
        self.expect(115, '1 1 1 2 1 3 2 3 2 1 3 0',
                    'Inserted\nInserted\nInserted\nDeleted\nDeleted\n2\n')

    def test_file_contents(self):
        self.expect(116, 'hello\n', 'Read: hello\n')
        self.assertEqual((self.directory/'notes.txt').read_bytes(), b'hello\n')
        self.expect(117, 'input.txt\ncopy.txt\n', 'Copied\n')
        self.assertEqual((self.directory/'copy.txt').read_bytes(), (self.directory/'input.txt').read_bytes())
        self.reject(117, 'input.txt\ninput.txt\n')
        (self.directory/'alias.txt').symlink_to(self.directory/'input.txt')
        before = (self.directory/'input.txt').read_bytes()
        self.reject(117, 'input.txt\nalias.txt\n')
        self.assertEqual((self.directory/'input.txt').read_bytes(), before)
        for data, output in [('', 'Characters: 0\nWords: 0\nLines: 0\n'),
                             ('one two', 'Characters: 7\nWords: 2\nLines: 1\n'),
                             ('\n\n', 'Characters: 2\nWords: 0\nLines: 2\n')]:
            (self.directory/'input.txt').write_text(data)
            self.expect(118, 'input.txt\n', output)

    def test_binary_random_access(self):
        class Student(ctypes.Structure):
            _fields_ = [('roll', ctypes.c_int), ('name', ctypes.c_char*256), ('mark', ctypes.c_double)]
        self.seed_binary()
        path = self.directory/'students.dat'
        original = path.read_bytes()
        result = invoke(120, '2 95', self.directory)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('2 | Arun | 95.00\n', result.stdout)
        changed = path.read_bytes()
        self.assertEqual(len(original), len(changed))
        self.assertEqual(struct.unpack('@I', changed[:4])[0], 2)
        first = Student.from_buffer_copy(changed[4:4+ctypes.sizeof(Student)])
        second = Student.from_buffer_copy(changed[4+ctypes.sizeof(Student):])
        self.assertEqual((first.roll, first.mark), (1, 80))
        self.assertEqual((second.roll, second.mark), (2, 95))
        self.reject(120, '999 80')
        self.assertEqual(path.read_bytes(), changed)
        path.write_bytes(changed[:-1])
        self.reject(120, '2 80')


def sample_test(item):
    def test(self):
        if item['number'] == 120: self.seed_binary()
        result = invoke(item['number'], item['sample_input'], self.directory)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stderr, '')
        if item['expected_output'] is not None:
            self.assertEqual(result.stdout, item['expected_output'])
        else:
            for phrase in item['contains']: self.assertIn(phrase, result.stdout)
        # The public input format accepts exactly the fields documented for it.
        self.reject(item['number'], item['sample_input']+'\nUNEXPECTED\n')
    return test


for entry in CATALOG:
    setattr(LabExperiments, f'test_sample_{entry["number"]:03d}', sample_test(entry))


if __name__ == '__main__':
    outcome = unittest.main(verbosity=1, exit=False)
    print(f'Executed {RUN_COUNT} program invocations across {len(CATALOG)} experiments.', flush=True)
    raise SystemExit(0 if outcome.result.wasSuccessful() else 1)
