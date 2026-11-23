"""Integration checks for the local runner, using real C executables."""
import importlib.util
import json
from pathlib import Path
import threading
import unittest
from urllib.error import HTTPError
from urllib.request import Request, urlopen

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('mila_runner', ROOT / 'demo/run_project.py')
RUNNER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(RUNNER)


class LocalRunner(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.server = RUNNER.ThreadingHTTPServer(('127.0.0.1', 0), RUNNER.Handler)
        cls.thread = threading.Thread(target=cls.server.serve_forever, daemon=True)
        cls.thread.start()
        cls.base = f'http://127.0.0.1:{cls.server.server_port}'

    @classmethod
    def tearDownClass(cls):
        cls.server.shutdown()
        cls.server.server_close()
        cls.thread.join(timeout=3)

    def post(self, payload, origin=None, path='/run'):
        headers = {'Content-Type': 'application/json'}
        if origin:
            headers['Origin'] = origin
        request = Request(self.base + path, data=json.dumps(payload).encode(), headers=headers)
        try:
            response = urlopen(request, timeout=5)
        except HTTPError as error:
            response = error
        with response:
            return response.code, json.load(response)

    def test_page(self):
        with urlopen(self.base, timeout=5) as response:
            page = response.read().decode()
        self.assertIn('MILA activity runner', page)
        self.assertIn('Run C program', page)
        self.assertNotIn('__ACTIVITIES__', page)

    def test_actual_outputs(self):
        status, data = self.post({'program': '01_pogil_arrays', 'input': '3 1 2 3'}, self.base)
        self.assertEqual(status, 200)
        self.assertEqual(data, {'stdout': 'Sum: 6\nMean: 2.00\n', 'stderr': '', 'exit_status': 0})
        status, data = self.post({'program': '05_critical_bounds', 'input': '101'})
        self.assertEqual(status, 200)
        self.assertEqual(data, {'stdout': '', 'stderr': 'Invalid input\n', 'exit_status': 1})

    def test_allowlist(self):
        for program in ('../../bin/sh', 'unknown', ['04_pltbl_prime']):
            with self.subTest(program=program):
                self.assertEqual(self.post({'program': program, 'input': '97'})[0], 400)

    def test_bad_requests(self):
        for payload in ([], {}, {'program': '04_pltbl_prime', 'input': 97},
                        {'program': '04_pltbl_prime', 'input': '1' * 9000}):
            with self.subTest(payload_type=type(payload).__name__):
                self.assertEqual(self.post(payload)[0], 400)
        self.assertEqual(self.post({'program': '04_pltbl_prime', 'input': '97'},
                                   'https://example.com')[0], 403)
        self.assertEqual(self.post({}, path='/missing')[0], 404)


if __name__ == '__main__':
    unittest.main(verbosity=2)
